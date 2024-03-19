#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TFile.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TChain.h>
#include <TCut.h>
#include <TNtuple.h>
#include <TLorentzVector.h>
#include <TCanvas.h>
#include <Eigen/Dense>

void SecVertPlotter_Kshort()
{
  gStyle->SetOptTitle(1);

  //TFile *fin = new TFile("/sphenix/tg/tg01/hf/frawley/kshort_baseline/combined_Kshort.root");
  //TFile *fin = new TFile("/sphenix/tg/tg01/hf/frawley/kshort_inflation1/combined_Kshort.root");
  //TFile *fin = new TFile("/sphenix/tg/tg01/hf/frawley/kshort_inflation2/combined_Kshort.root");
  //TFile *fin = new TFile("/sphenix/tg/tg01/hf/frawley/kshort_inflation4/combined_Kshort.root");
  //TFile *fin = new TFile("/sphenix/tg/tg01/hf/frawley/kshort_inflation8/combined_Kshort.root");
  TFile *fin = new TFile("/sphenix/tg/tg01/hf/frawley/kshort_baseline_3/combined_secvert.root");

  TNtuple *ntp;
  fin->GetObject("ntp", ntp);


  Float_t decaymass = 0.13957;

  Float_t x1, y1,z1,x2,y2,z2;
  Float_t px1, py1, pz1, px2, py2, pz2;
  Float_t dca3dxy1, dca3dxy2, dca3dz1, dca3dz2;
  Float_t vposx1, vposy1, vposz1, vposx2, vposy2, vposz2;
  Float_t vmomx1, vmomy1, vmomz1, vmomx2, vmomy2, vmomz2;
  Float_t pca_relx_1, pca_rely_1, pca_relz_1, pca_relx_2, pca_rely_2, pca_relz_2;
  Float_t charge1, charge2, tpcClusters_1, tpcClusters_2, quality1, quality2, eta1, eta2;
  Float_t vertex_x, vertex_y, vertex_z;
  Float_t has_silicon1, has_silicon2;
  Float_t pair_dca;

  ntp->SetBranchAddress("x1",&x1);
  ntp->SetBranchAddress("y1",&y1);
  ntp->SetBranchAddress("z1",&z1);
  ntp->SetBranchAddress("x2",&x2);
  ntp->SetBranchAddress("y2",&y2);
  ntp->SetBranchAddress("z2",&z2);

  ntp->SetBranchAddress("px1",&px1);
  ntp->SetBranchAddress("py1",&py1);
  ntp->SetBranchAddress("pz1",&pz1);
  ntp->SetBranchAddress("px2",&px2);
  ntp->SetBranchAddress("py2",&py2);
  ntp->SetBranchAddress("pz2",&pz2);

  ntp->SetBranchAddress("dca3dxy1",&dca3dxy1);
  ntp->SetBranchAddress("dca3dz1",&dca3dz1);
  ntp->SetBranchAddress("dca3dxy2",&dca3dxy2);
  ntp->SetBranchAddress("dca3dz2",&dca3dz2);

  ntp->SetBranchAddress("vposx1",&vposx1);
  ntp->SetBranchAddress("vposy1",&vposy1);
  ntp->SetBranchAddress("vposz1",&vposz1);
  ntp->SetBranchAddress("vposx2",&vposx2);
  ntp->SetBranchAddress("vposy2",&vposy2);
  ntp->SetBranchAddress("vposz2",&vposz2);
  ntp->SetBranchAddress("vmomx1",&vmomx1);
  ntp->SetBranchAddress("vmomy1",&vmomy1);
  ntp->SetBranchAddress("vmomz1",&vmomz1);
  ntp->SetBranchAddress("vmomx2",&vmomx2);
  ntp->SetBranchAddress("vmomy2",&vmomy2);
  ntp->SetBranchAddress("vmomz2",&vmomz2);

  ntp->SetBranchAddress("pca_relx_1",&pca_relx_1);
  ntp->SetBranchAddress("pca_rely_1",&pca_rely_1);
  ntp->SetBranchAddress("pca_relz_1",&pca_relz_1);
  ntp->SetBranchAddress("pca_relx_2",&pca_relx_2);
  ntp->SetBranchAddress("pca_rely_2",&pca_rely_2);
  ntp->SetBranchAddress("pca_relz_2",&pca_relz_2);

  ntp->SetBranchAddress("charge1",&charge1);
  ntp->SetBranchAddress("charge2",&charge2);
  ntp->SetBranchAddress("eta1",&eta1);
  ntp->SetBranchAddress("eta2",&eta2);
  ntp->SetBranchAddress("tpcClusters_1",&tpcClusters_1);
  ntp->SetBranchAddress("tpcClusters_2",&tpcClusters_2);

  ntp->SetBranchAddress("quality1",&quality1);
  ntp->SetBranchAddress("quality2",&quality2);

  ntp->SetBranchAddress("has_silicon1",&has_silicon1);
  ntp->SetBranchAddress("has_silicon2",&has_silicon2);

  ntp->SetBranchAddress("vertex_x",&vertex_x);
  ntp->SetBranchAddress("vertex_y",&vertex_y);
  ntp->SetBranchAddress("vertex_z",&vertex_z);

  ntp->SetBranchAddress("pair_dca",&pair_dca);

  double min_mass = 0.35;
  double max_mass = 0.65;
  int nmassbins = 1000;
  double sig_lo = 0.47;
  double sig_hi = 0.53;

  double qual_cut = 5.0;   // 5
  double min_tpc_clusters = 40; // 40
  double pair_dca_cut = 0.2;  // 0.2
  double min_dca_cut_silicon = 0.02; //0.02
  double pair_dca_cut_silicon = 0.05; // 0.05
 
  TH1D *hmass_si = new TH1D("hmass_si","",nmassbins,min_mass,max_mass);
  hmass_si->GetXaxis()->SetTitle("Invariant mass (GeV/c^2)");
  TH1D *hmass_nosi = new TH1D("hmass_nosi","",nmassbins,min_mass,max_mass);
  hmass_nosi->GetXaxis()->SetTitle("Invariant mass (GeV/c^2)");
  TH2D *hptmass = new TH2D("hptmass","mass vs pT", 200, 0, 10.0, 200, 0, 1.0);
  TH1D *hpt = new TH1D("hpt","pair pT",200,0,10);
  TH1D *hinv_eta = new TH1D("hinv_eta","pair eta",200,-1.5,1.5);
  hinv_eta->GetXaxis()->SetTitle("pair eta");
  TH2D *hpteta = new TH2D("hpteta","eta vs pT", 200, -1.5, 1.5, 200, 0.0, 10);
  hpteta->GetXaxis()->SetTitle("pair eta");
  hpteta->GetYaxis()->SetTitle("pair pT");
  TH1D *hpath_si = new TH1D("hpath_si","Decay radius Si match",200,0,40);
  hpath_si->GetXaxis()->SetTitle("cm");
  TH1D *hpath_nosi = new TH1D("hpath_nosi","Decay radius no silicon match",200,0,40);
  hpath_nosi->GetXaxis()->SetTitle("cm");
 TH2D *hdecay = new TH2D("hdecay","Decay radius vs decay z",200,-30,30,200,0,40);
  hdecay->GetXaxis()->SetTitle("decay z (cm)");
  hdecay->GetYaxis()->SetTitle("decay radius (cm)");
  TH2D *hdecaypos = new TH2D("hdecaypos","decay position XY",200, -40, 40, 200,-40,40);
  hdecaypos->GetXaxis()->SetTitle("decay X (cm)");
  hdecaypos->GetYaxis()->SetTitle("decay Y (cm)");

  int entries = ntp->GetEntries();
  for(int i=0;i<entries;++i)
    {
      ntp->GetEntry(i);

      // common single track cuts
      if(quality1 > qual_cut || quality2 > qual_cut) continue;
      if(tpcClusters_1 < min_tpc_clusters || tpcClusters_2 < min_tpc_clusters) continue;
      // track pair cut
      if(fabs(pair_dca) > pair_dca_cut) continue;

      TLorentzVector t1;
      Float_t E1 = sqrt(pow(vmomx1,2) + pow(vmomy1,2) + pow(vmomz1,2) + pow(decaymass,2));
      t1.SetPxPyPzE(vmomx1,vmomy1,vmomz1,E1);

      TLorentzVector t2;
      Float_t E2 = sqrt(pow(vmomx2,2) + pow(vmomy2,2) + pow(vmomz2,2) + pow(decaymass,2));
      t2.SetPxPyPzE(vmomx2,vmomy2,vmomz2,E2);

      TLorentzVector tsum;
      tsum = t1+t2;

      double invariant_mass = tsum.M();
      double invariant_eta = tsum.Eta();
      double invariant_phi = tsum.Phi();
      double invariant_pt = tsum.Pt();

      // difference from the event vertex
      Eigen::Vector3d VTX(vertex_x, vertex_y, vertex_z);  // asssociated event vertex
      Eigen::Vector3d PCA( (vposx1+vposx2)/2.0, (vposy1+vposy2)/2.0, (vposz1+vposz2)/2.0);
      Eigen::Vector3d path = PCA - VTX;

      double decay_radius = sqrt( pow(PCA(0),2) + pow(PCA(1),2) );
 
      // no silicon match case
      if( (fabs(dca3dxy1) > 0.14 && fabs(dca3dxy2) > 0.14)
	  && (fabs(dca3dz1) > 0.12 && fabs(dca3dz2) > 0.12) )
	{
	  hptmass->Fill(invariant_pt,invariant_mass);
	  if(invariant_mass > sig_lo && invariant_mass < sig_hi)
	    hpt->Fill(invariant_pt);
	  
	  if ( invariant_pt > 0.4) 
	    {	  
	      if( (has_silicon1 + has_silicon2) == 0)
		{
		  hmass_nosi->Fill(invariant_mass);	  
		  if(invariant_mass > sig_lo && invariant_mass < sig_hi)
		    {
		      hpath_nosi->Fill(decay_radius);
		      hdecay->Fill(PCA(2), decay_radius);
		      hdecaypos->Fill(PCA(0),PCA(1));
		      hinv_eta->Fill(invariant_eta);
		      hpteta->Fill(invariant_eta, invariant_pt);
		    }
		}
	    }
	}
      
      // has silicon match case
      if( (fabs(dca3dxy1) > min_dca_cut_silicon && fabs(dca3dxy2) > min_dca_cut_silicon)
	  && (fabs(dca3dz1) > min_dca_cut_silicon && fabs(dca3dz2) > min_dca_cut_silicon) 
	  && (pair_dca < pair_dca_cut_silicon) )
	{
	  if ( invariant_pt > 0.4) 
	    {
	      if( (has_silicon1 + has_silicon2) == 2)
		{
		  hmass_si->Fill(invariant_mass);
		  if(invariant_mass > sig_lo && invariant_mass < sig_hi)
		    {
		      hpath_si->Fill(decay_radius);
		      hinv_eta->Fill(invariant_eta);
		      hpteta->Fill(invariant_eta, invariant_pt);
		    }
		}
	    }
	}
    }

  TCanvas *cmass = new TCanvas("cmass","cmass",5,5,1200,600);
  cmass->Divide(2,1);
  cmass->cd(1);
  hmass_nosi->Draw();
  cmass->cd(2);
  hmass_si->Draw();


  bool fit = true;
  if(fit)
    {
      // fit the mass peak for unmatched tracks
      cmass->cd(1);
      TF1 *f1 = new TF1("f1", "gaus(0) + [3] + [4]*x",0.32,0.67);

      f1->SetParameter(0, 400.0);
      f1->SetParameter(1, 0.5);
      f1->SetParameter(2, 0.01);
      f1->SetParameter(3,20);
      f1->SetParameter(4,0);
      hmass_nosi->Fit("f1","R");

      std:: cout << "hmass_nosi: Area of f1 is " << f1->Integral(sig_lo,sig_hi) << endl;
      TF1 *fbg1 = new TF1("fbg1","[0] + [1]*x", 0.32,0.67);
      fbg1->SetParameters(f1->GetParameter(3), f1->GetParameter(4));
      std:: cout << "Area of fbg1 is " << fbg1->Integral(sig_lo, sig_hi) << endl;
      std::cout << "    difference is signal: " <<   f1->Integral(sig_lo,sig_hi) - fbg1->Integral(sig_lo, sig_hi) << endl;
      std::cout << "    ratio S/B " <<  (f1->Integral(sig_lo,sig_hi) - fbg1->Integral(sig_lo,sig_hi)) /  fbg1->Integral(sig_lo,sig_hi) << std::endl;
      
      TF1 *fg1 = new TF1("fg1","gaus(0)", sig_lo,sig_hi);
      fg1->SetParameters(f1->GetParameter(0), f1->GetParameter(1), f1->GetParameter(2));
      std:: cout << std::endl << "Check: Area of fg1 is " << fg1->Integral(sig_lo,sig_hi) << endl;

      // fit the mass peak for silicon matched tracks
      cmass->cd(2);
      TF1 *f2 = new TF1("f2", "gaus(0) + [3] + [4]*x",0.32,0.67);
      sig_lo = 0.483;
      sig_hi = 0.510;
      f2->SetParameter(0, 20.0);
      f2->SetParameter(1, 0.498);
      f2->SetParameter(2, 0.004);
      f2->SetParameter(3,0);
      f2->SetParameter(4,0);
      hmass_si->Fit("f2","R L");

      std:: cout << "hmass_si: Area of f2 is " << f2->Integral(sig_lo,sig_hi) << endl;
      TF1 *fbg2 = new TF1("fbg2","[0] + [1]*x", 0.32,0.67);
      fbg2->SetParameters(f2->GetParameter(3), f2->GetParameter(4));
      std:: cout << "Area of fbg2 is " << fbg2->Integral(sig_lo, sig_hi) << endl;
      std::cout << "    difference is signal: " <<   f2->Integral(sig_lo,sig_hi) - fbg2->Integral(sig_lo, sig_hi) << endl;
      std::cout << "    ratio S/B " <<  (f2->Integral(sig_lo,sig_hi) - fbg2->Integral(sig_lo,sig_hi)) /  fbg2->Integral(sig_lo,sig_hi) << std::endl;
      
      TF1 *fg2 = new TF1("fg2","gaus(0)", sig_lo,sig_hi);
      fg2->SetParameters(f1->GetParameter(0), f2->GetParameter(1), f2->GetParameter(2));
      std:: cout << std::endl << "Check: Area of fg2 is " << fg2->Integral(sig_lo,sig_hi) << endl;

      int binlo = hmass_si->FindBin(0.48);
      int binhi = hmass_si->FindBin(0.52);
      std::cout << " area of signal in hmass_si = " << hmass_si->Integral(binlo, binhi) << std::endl;

    }

  TCanvas *cpath = new TCanvas("cpath", "path", 100,100,1200,600);
  cpath->Divide(2,1);

  cpath->cd(1);
  hpath_si->DrawCopy();

  cpath->cd(2);
  hpath_nosi->DrawCopy();


  TCanvas *cdecay = new TCanvas("cdecay", "", 150,150, 1200, 600);
  cdecay->Divide(2,1);
  cdecay->cd(1);
  hdecay->DrawCopy();
  cdecay->cd(2);

  hdecaypos->Draw();

  TCanvas *cpt = new TCanvas("cpt","", 100,100, 1200, 600);
  cpt->Divide(2,1);

  cpt->cd(1);
  hptmass->Draw();

  cpt->cd(2);
  hpt->Draw();

  TCanvas *ceta = new TCanvas("ceta","", 100,100, 1200, 600);
  ceta->Divide(2,1);
  ceta->cd(1);
  hinv_eta->Draw();
  ceta->cd(2);
  hpteta->Draw();

}
