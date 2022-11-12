#include <fstream>
#include <iostream>

#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TStyle.h>
# include <TGraph.h>
#include <TF1.h>


void test_search_wins()
{
  gStyle->SetOptStat(1);

  TH2D *hdphipt = new TH2D("hdphipt","dphi vs pT",1000, 0, 20,1000, -0.7, 0.7);
  hdphipt->GetXaxis()->SetTitle("TPC p_{T}");
  hdphipt->GetXaxis()->SetTitleOffset(1.3);
  hdphipt->GetYaxis()->SetTitle("#Delta#phi");

  TH2D *hdphi_phi = new TH2D("hdphi_phi","dphi vs phi",1000, -3.2, 3.2,1000, -3.2, 3.2);
  hdphi_phi->GetXaxis()->SetTitle("TPC #phi");
  hdphi_phi->GetXaxis()->SetTitleOffset(1.3);
  hdphi_phi->GetYaxis()->SetTitle("Si #phi");

  TH2D *hdetapt = new TH2D("hdetapt","deta vs pT",1000,0, 20, 1000, -0.1,0.1);
  hdetapt->GetXaxis()->SetTitle("TPC p_{T}");
  hdetapt->GetXaxis()->SetTitleOffset(1.3);
  hdetapt->GetYaxis()->SetTitle("#Delta#eta");

  TH2D *hdxpt = new TH2D("hdxpt","dx vs pT",1000,0, 20, 1000, -0.4, 0.4);
  hdxpt->GetXaxis()->SetTitle("TPC p_{T}");
  hdxpt->GetXaxis()->SetTitleOffset(1.3);
  hdxpt->GetYaxis()->SetTitle("#Delta x");

  TH2D *hdypt = new TH2D("hdypt","dy vs pT",1000,0, 20, 1000, -0.4, 0.4);
  hdypt->GetXaxis()->SetTitle("TPC p_{T}");
  hdypt->GetXaxis()->SetTitleOffset(1.3);
  hdypt->GetYaxis()->SetTitle("#Delta y");

  TH2D *hdzpt = new TH2D("hdzpt","dz vs pT",1000,0, 20, 1000, -0.8, 0.8);
  hdzpt->GetXaxis()->SetTitle("TPC p_{T}");
  hdzpt->GetXaxis()->SetTitleOffset(1.3);
  hdzpt->GetYaxis()->SetTitle("#Delta z");

  TH1D *hdx = new TH1D("hdx","hdx", 1000,-0.5, 0.5);
  hdx->GetXaxis()->SetTitle("TPC x - Si x (cm)");
  TH1D *hdy = new TH1D("hdy","hdy", 1000,-0.5, 0.5);
  hdy->GetXaxis()->SetTitle("TPC y - Si y (cm)");
  TH1D *hdz = new TH1D("hdz","hdz", 1000,-0.5, 0.5);
  hdz->GetXaxis()->SetTitle("TPC z - Si z (cm)");

  TH1D *hdphi = new TH1D("hdphi","hdphi", 1000,-0.1, 0.1);
  hdphi->GetXaxis()->SetTitle("TPC phi - Si phi (rad)");

  TH1D *hdeta = new TH1D("hdeta","hdeta", 1000,-0.01, 0.01);
  hdeta->GetXaxis()->SetTitle("TPC eta - Si eta");

  double eta_tpc, eta_si, phi_tpc, phi_si, pt;
  double x_tpc, x_si, y_tpc, y_si, z_tpc, z_si;
  double dphi,  deta, dx, dy, dz;
  char dummy[500];

  double ptmin = 6.0;

  ifstream fin;
  fin.open("/sphenix/user/frawley/new_macros_april27/macros/detectors/sPHENIX/search_wins_data1.txt",ios::in);
  if(!fin)
    {
      cout << "Failed to open input file" << endl;
      return; 
    }
  int cnt=0;
  while(cnt < 9045) 
    {
      fin >> dummy >> dummy >> pt >> dummy >> phi_tpc >> dummy >> phi_si >> dummy >> dphi >> dummy 
	  >> eta_tpc >> dummy >> eta_si >> dummy >> deta >> dummy >> x_tpc >> dummy  
	  >> y_tpc >>  dummy >> z_tpc >> dummy >> dx >> dummy >> dy >> dummy >> dz;

      /*
	Try_silicon:  pt 5.06346 tpc_phi -3.11061 si_phi -3.10711 dphi -0.00350118 tpc_eta -0.704315 si_eta -0.701091 deta -0.0032239 tpc_x -0.000896004 tpc_y 0.0289067 tpc_z -4.88719 dx -0.000515362 dy 0.0178735 dz 0.0972977
      */

      if(cnt < 100)
	std::cout << "line " << cnt << " pt " << pt << " phi_tpc " << phi_tpc << " phi_si " << phi_si << " dphi " << dphi << " eta_tpc " << eta_tpc << " eta_si " << eta_si << " deta " << deta << " dx " << dx << " dy " << dy << " dz " << dz << std::endl;

      //hdphi->Fill(pt, phi_tpc-phi_si);
      hdphipt->Fill(pt, dphi);
      hdphi_phi->Fill(phi_tpc, phi_si);
      //hdeta->Fill(pt, eta_tpc-eta_si);
      hdetapt->Fill(pt, deta);

      hdxpt->Fill(pt, dx);
      hdypt->Fill(pt, dy);
      hdzpt->Fill(pt, dz);

      if(pt > ptmin)
	{
	  hdx->Fill(dx);
	  hdy->Fill(dy);
	  hdz->Fill(dz);

	  hdphi->Fill(dphi);
	  hdeta->Fill(deta);
	}

      cnt++;
    }

  TCanvas *c1 = new TCanvas("c1","c1",5,5,1200,800);
  c1->Divide(2);

  c1->cd(1);
  gPad->SetLeftMargin(0.15);
  gPad->SetLogx(1);
  hdphipt->Draw();

  c1->cd(2);
  gPad->SetLeftMargin(0.15);
  gPad->SetLogx(1);
  hdetapt->Draw();

  // Extract the pT dependence of the dphi centroid
  // Read points off these plots and make a TGraph!

  double pT[9] = {0.2, 0.4, 0.6, 1.0, 2.0, 4.0, 10.0, 20.0, 40.0};
  //double dPhi[9] = {0.65, 0.33, 0.22, 0.13, 0.07, 0.034, 0.013, 0.006, 0.003};
  double dPhi[9] = {-0.65, -0.33, -0.22, -0.13, -0.07, -0.034, -0.013, -0.006, -0.003};

  TGraph *gr = new TGraph(9, pT, dPhi);
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(1.5);
  gr->SetMarkerColor(kRed);
  c1->cd(1);
  //   gr->Draw("p same");

  // now fit the TGraph

  TF1 *f1 = new TF1("f1", "[0] + [1]/x^[2]");
  //  gr->Fit(f1);

  TCanvas *c2 = new TCanvas("c2","c2",50,50,800,800);
  hdphi_phi->Draw();

  TCanvas *cpos = new TCanvas("cpos","cpos", 50,50,1600,800);
  cpos->Divide(3,1);
  cpos->cd(1);
  gPad->SetLogy(1);
  hdx->Draw();
  cpos->cd(2);
  gPad->SetLogy(1);
  hdy->Draw();
  cpos->cd(3);
  gPad->SetLogy(1);
  hdz->Draw();

  TCanvas *cpospt = new TCanvas("cpospt","cpospt",50,50,1600,800);
  cpospt->Divide(3,1);
  cpospt->cd(1);
  hdxpt->Draw();
  cpospt->cd(2);
  hdypt->Draw();
  cpospt->cd(3);
  hdzpt->Draw();

  TCanvas *cdphieta = new TCanvas("cdphieta","cdphieta",50,50,1600,800);
  cdphieta->Divide(2,1);
  cdphieta->cd(1);
  gPad->SetLogy(1);
  hdphi->Draw();
  cdphieta->cd(2);
  gPad->SetLogy(1);
  hdeta->Draw();

}
