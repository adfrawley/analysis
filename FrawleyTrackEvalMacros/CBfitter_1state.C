#include <TF1.h>
#include <TMath.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLatex.h>


//____________________________________________
Double_t CrystallBall2( Double_t x, Double_t mean, Double_t sigma, Double_t alpha1, Double_t n1, Double_t alpha2, Double_t n2 )
{

  Double_t t = (x-mean)/sigma;
  if( t < -alpha1 )
  {
    Double_t a = TMath::Power( n1/alpha1, n1 )*TMath::Exp( -TMath::Power( alpha1, 2 )/2 );
    Double_t b = n1/alpha1 - alpha1;
    return a/TMath::Power( b - t, n1 );

  } else if( t > alpha2 ) {

    Double_t a = TMath::Power( n2/alpha2, n2 )*TMath::Exp( -TMath::Power( alpha2,2 )/2 );
    Double_t b = n2/alpha2 - alpha2;
    return a/TMath::Power( b + t, n2 );

  } else return TMath::Exp( -TMath::Power( t, 2 )/2 );

}

//____________________________________________
Double_t CrystallBall2Integral( Double_t sigma, Double_t alpha1, Double_t n1, Double_t alpha2, Double_t n2 )
{
  // get corresponding integral
  alpha1 = fabs( alpha1 );
  alpha2 = fabs( alpha2 );
  return sigma*(
		n1/(alpha1*(n1-1))*TMath::Exp( -pow( alpha1, 2 )/2 ) +
		n2/(alpha2*(n2-1))*TMath::Exp( -pow( alpha2,2 )/2 ) +
    TMath::Sqrt( TMath::Pi()/2)*TMath::Erfc( -alpha1/TMath::Sqrt(2) ) -
    TMath::Sqrt( TMath::Pi()/2)*TMath::Erfc( alpha2/TMath::Sqrt(2) ) );

}

//____________________________________________
Double_t CrystallBall2( Double_t *x, Double_t *par )
{

  // get normalized Crystal ball
  Double_t result = CrystallBall2( x[0], par[1], par[2], par[3], par[4], par[5], par[6] );

  // get integral
  Double_t integral = CrystallBall2Integral( par[2], par[3], par[4], par[5], par[6] );

  // return scaled Crystalball so that par[0] corresponds to integral
  return par[0] * result/integral;

}


Double_t CBcalc(Double_t *xx, Double_t *par)
{
  double f;
  double x = xx[0];

  // The four parameters (alpha, n, x_mean, sigma) plus normalization (N) are:
  double alpha = par[0];
  double n = par[1];
  double x_mean = par[2];
  double sigma = par[3];
  double N = par[4];

  // we need:
  double A = pow( (n/TMath::Abs(alpha)),n) * exp(-pow(alpha,2)/2.0);
  double B = n/TMath::Abs(alpha) - TMath::Abs(alpha);

  // The Crystal Ball function is:
  if( (x-x_mean)/sigma > -alpha)
    {
      f = N * exp( -pow(x-x_mean,2) / (2.0*pow(sigma,2)));
    }
  else
    {
      f = N * A * pow(B - (x-x_mean)/sigma, -n);
    }

  double Nexp = par[5];
  double slope = par[6];
  
  TF1 *fexp = new TF1("fexp","[0]*exp([1]*x)",7,11);
  fexp->SetParameter(0,Nexp);
  fexp->SetParameter(1,slope);

  f = f + fexp->Eval(x);
  return f;
}

Double_t Upscalc(Double_t *xx, Double_t *par)
{
  double x = xx[0];
  
  // The input parameters are:
  double alpha1s = par[0];
  double n1s = par[1];
  double sigma1s = par[2];
  double m1s = par[3];
  double m2s = par[4];
  double m3s = par[5];
  double N1s = par[6];
  double N2s = par[7];
  double N3s = par[8];
  double Nexp = par[9];
  double slope = par[10];

  // Construct the Y(1S) CB shape

  TF1 *f1 = new TF1("f1",CBcalc,7,11,5);
  f1->SetParameter(0,alpha1s);
  f1->SetParameter(1,n1s);
  f1->SetParameter(2,m1s);
  f1->SetParameter(3,sigma1s);
  f1->SetParameter(4,N1s);
  
  TF1 *f2 = new TF1("f2",CBcalc,7,11,5);
  f2->SetParameter(0,alpha1s);
  f2->SetParameter(1,n1s);
  f2->SetParameter(2,m2s);
  f2->SetParameter(3,sigma1s);
  f2->SetParameter(4,N2s);

  TF1 *f3 = new TF1("f3",CBcalc,7,11,5);
  f3->SetParameter(0,alpha1s);
  f3->SetParameter(1,n1s);
  f3->SetParameter(2,m3s);
  f3->SetParameter(3,sigma1s);
  f3->SetParameter(4,N3s);

  TF1 *fexp = new TF1("fexp","[0]*exp([1]*x)",7,11);
  fexp->SetParameter(0,Nexp);
  fexp->SetParameter(1,slope);
  
  

  double mass = f1->Eval(x) + f2->Eval(x) + f3->Eval(x) + fexp->Eval(x);

  return mass;
}


void CBfitter_1state()
{
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetOptTitle(0);

  TFile *file1S, *file2S, *file3S;
  TH1 *recomass1S, *recomass2S, *recomass3S;

  bool draw_gauss = true;

  // if all are false, do AuAu 0-10%
  bool pp = false;
  bool pAu = false;
  bool AuAu_20pc = false;
  bool AuAu_10pc = true;

  //bool do_subtracted = true;
 
  //file1S = new TFile("analyze_quarkonia_out/ups_embed_out.root");
  file1S = new TFile("root_files/ups_embed_out.root");

  if(!file1S)
    {
      cout << "Failed to open file  " << endl;
      exit(1); 
    }

  recomass1S = (TH1 *)file1S->Get("recomass");

  TH1 *recomass = (TH1*)recomass1S->Clone("recomass1");
  if(!recomass)
    {
      cout << "Failed to get recomass histogram  " << endl;
      exit(1); 
    }

  recomass->GetXaxis()->SetTitle("invariant mass (GeV/c^{2})");
  recomass->SetTitle("Y(1S,2S,3S) #rightarrow e^{+}e^{-}");
  recomass->SetMarkerStyle(20);
  recomass->SetMarkerSize(1);
  recomass->SetLineStyle(kSolid);
  recomass->SetLineWidth(2);
  recomass->Sumw2();  

  int nrebin = 1;  // set to 2 to match background histo binning, but this worsens resolution slightly. Use 1 for signal fit
  //int nrebin = 2;  // set to 2 to match background histo binning, but this worsens resolution slightly. Use 1 for signal fit
  recomass->Rebin(nrebin);

  //bool cb2 = true;
  bool cb2 = false;
  if(!cb2)
    {
      TCanvas *cups = new TCanvas("cups","cups",5,5,800,800);
      recomass->DrawCopy("p");
      
      TF1 *f1S = new TF1("f1S",CBcalc,7,11,7);
      f1S->SetParameter(0, 0.5);     // alpha
      f1S->SetParameter(1, 5.0);      // n
      f1S->SetParameter(2, 9.46);      // xmean
      f1S->SetParameter(3, 0.1);     // sigma
      f1S->SetParameter(4, 1000.0);    // N
      f1S->SetParameter(5, 150.0);
      f1S->SetParameter(6,-1.0); 

      f1S->SetParNames("alpha1S","n1S","m1S","sigma1S","N1S");
      f1S->SetLineColor(kBlue);
      f1S->SetLineWidth(3);
      f1S->SetLineStyle(kDashed);
      
      recomass->Fit(f1S);
      f1S->Draw("same");
      cout << "f1S pars " <<  f1S->GetParameter(3) << "   " << f1S->GetParError(3) << endl;


      TF1 *fexp = new TF1("fexp","[0]*exp([1]*x)",7,11);
      fexp->SetParameter(0,f1S->GetParameter(5));
      fexp->SetParameter(1,f1S->GetParameter(6));
      fexp->SetLineColor(kRed);
      fexp->SetLineStyle(kDashed);
      fexp->Draw("same");
      
      char resstr[500];
      sprintf(resstr,"#sigma_{1S} = %.1f #pm %.1f MeV", f1S->GetParameter(3)*1000, f1S->GetParError(3)*1000);
      TLatex *res = new TLatex(0.13,0.55,resstr);
      res->SetNDC();
      res->SetTextSize(0.05);
      res->Draw();
      
      
      double binw = recomass->GetBinWidth(1);
      double renorm = 1.0/binw;   // (1 / (bin_width of data in GeV) )
      cout << "renorm = " << renorm << endl;
      
      cout << "Area of f1S is " << renorm * f1S->Integral(7,11) << endl;
     cout << "Area of fexp is " << renorm * fexp->Integral(7,11) << endl;
     cout << "Area of CB fit is " <<  renorm * f1S->Integral(7,11) - renorm * fexp->Integral(7,11) << endl;
      
      // Extract ratio of yield in central gaussian to total
      
      TF1 *fgauss = new TF1("fgauss","gaus(0)",7,11);
      fgauss->SetParameter(0, f1S->GetParameter(4));
      fgauss->SetParameter(1, f1S->GetParameter(2));
      fgauss->SetParameter(2, f1S->GetParameter(3));
      fgauss->SetLineColor(kRed);
      if(draw_gauss) 
	fgauss->Draw("same");
      
      // calculate fraction of yield in gaussian
      double area_fgauss =  renorm * fgauss->Integral(7,11);
      double area_f1S = renorm * f1S->Integral(7,11);
      double fraction = area_fgauss / area_f1S;
      
      
      cout << "Parameters of fgauss = " << fgauss->GetParameter(0) << "  " << fgauss->GetParameter(1) << "  " << fgauss->GetParameter(2) << " Area of fgauss is " << renorm * fgauss->Integral(7,11) << " fraction in fgauss " << fraction << endl;
      
      char labfrac[500];
      sprintf(labfrac, "Gauss fraction %.2f", fraction);
      TLatex *lab = new TLatex(0.13,0.75,labfrac);
      lab->SetNDC();
      lab->SetTextSize(0.05);
      if(draw_gauss)  lab->Draw();
    }
  else
    {
      // CB2
      
      TCanvas *CB2 = new TCanvas("CB2","CB2",400,5,800,800);
      recomass->DrawCopy("p");
            
      TF1 *f2 = new TF1("f2",CrystallBall2,7,11,7);
      
      f2->SetParameter(0, 1000 ); 
      f2->SetParameter(1, 9.46 ); 
      f2->SetParameter(2, 0.1 );
      f2->SetParameter(3, 1); 
      f2->SetParameter(4, 3); 
      f2->SetParameter(5, 1 ); 
      f2->SetParameter(6, 5 ); 
      f2->SetParNames("normalization", "mean", "sigma","alpha1","n1","alpha2","n2");

      f2->SetParLimits(1, 9.30, 9.60);
      f2->SetParLimits(2, 0.06, 0.20);
      f2->SetParLimits(3, 0.120, 10);
      f2->SetParLimits(4, 1.01, 10); 
      f2->SetParLimits(5, 0.1, 10); 
      f2->SetParLimits(6, 1.01, 10);       

      recomass->Fit(f2);
      f2->Draw("same");
      cout << "f2 pars " <<  f2->GetParameter(2) << "   " << f2->GetParError(2) << endl;

      char resstr[500];
      sprintf(resstr,"#sigma_{1S} = %.1f #pm %.1f MeV", f2->GetParameter(2)*1000, f2->GetParError(2)*1000);
      TLatex *res = new TLatex(0.13,0.55,resstr);
      res->SetNDC();
      res->SetTextSize(0.05);
      res->Draw();

      double binw = recomass->GetBinWidth(1);
      double renorm = 1.0/binw;   // (1 / (bin_width of data in GeV) )
      cout << "renorm = " << renorm << endl;
      
      cout << "Area of f2 is " << renorm * f2->Integral(7,11) << endl;

      // get the core gaussian part of the yield
      TF1 *fgauss = new TF1("fgauss","gaus(0)",7,11);
      fgauss->SetParameter(0, f2->GetParameter(0));  // norm
      fgauss->SetParameter(1, f2->GetParameter(1));  // mean
      fgauss->SetParameter(2, f2->GetParameter(2));  // sigma
      fgauss->SetLineColor(kRed);
      if(draw_gauss) 
	fgauss->Draw("same");
      
      // calculate fraction of yield in gaussian
      double area_fgauss =  fgauss->Integral(7,11) * renorm;
      double area_f2 = f2->Integral(7,11) * renorm;
      double fraction = area_fgauss / area_f2;
      
      
      cout << "Parameters of fgauss = " << fgauss->GetParameter(0) << "  " << fgauss->GetParameter(1) << "  " << fgauss->GetParameter(2) << " Area of fgauss is " << renorm * fgauss->Integral(7,11) << " fraction in fgauss " << fraction << endl;
      
      char labfrac[500];
      sprintf(labfrac, "Gauss fraction %.2f", fraction);
      TLatex *lab = new TLatex(0.13,0.75,labfrac);
      lab->SetNDC();
      lab->SetTextSize(0.05);
      if(draw_gauss)  lab->Draw();
      
    }

}
