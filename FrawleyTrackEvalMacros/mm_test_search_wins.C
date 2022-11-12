#include <fstream>
#include <iostream>

#include <TH1D.h>
#include <TCanvas.h>
#include <TStyle.h>


void mm_test_search_wins()
{
  gStyle->SetOptStat(1);

  TH1D *hdrphi_1 = new TH1D("hdrphi_1","drphi 1",200, -0.5, 0.5);
  hdrphi_1->GetXaxis()->SetTitle("drphi");
  TH1D *hdrphi_2 = new TH1D("hdrphi_2","drphi 2",200, -15, 15.0);
  hdrphi_2->GetXaxis()->SetTitle("drphi");

  TH1D *hdz_1 = new TH1D("hdz_1","dz 1",200, -15, 15);
  hdz_1->GetXaxis()->SetTitle("dz");
  TH1D *hdz_2 = new TH1D("hdz_2","dz 2",200, -0.5, 0.5);
  hdz_2->GetXaxis()->SetTitle("dz");

  TH1D *hrphi_1 = new TH1D("hrphi_1","rphi 1",500, -300, 300);
  hrphi_1->GetXaxis()->SetTitle("rphi");

  TH1D *hz_2 = new TH1D("hz_2","z 2",500, -30, 30);
  hz_2->GetXaxis()->SetTitle("z");

  TH1D *hmatch = new TH1D("hmatch","Match", 100, 0, 5 );
  hmatch->GetXaxis()->SetTitle("match number");

  double drphi, dz, clus_rphi, clus_z;
  int layer, match;
  char dummy[500];

  ifstream fin;
  //fin.open("circle_fit_rphi_z.txt",ios::in);
  fin.open("circle_fit_rphi_z_occ_4k.txt",ios::in);
  
  int cnt=0;
  while(cnt < 430) 
    {
      fin >> dummy >> layer >> dummy >> drphi >> dummy >> dz >> dummy >> clus_rphi >> dummy >> clus_z >> dummy >> match;

      if(drphi > 100) continue;

      std::cout << " cnt " << cnt << " layer " << layer << " drphi " << drphi << " dz " << dz << " clus_rphi " << clus_rphi << " clus_z " << clus_z << " match " << match << std::endl;

      hmatch->Fill(match);

      if(layer == 55)
	{
	  hdrphi_1->Fill(drphi);
	  hdz_1->Fill(dz);	  
	  hrphi_1->Fill(clus_rphi);
	}
      else
	{
	  hdrphi_2->Fill(drphi);
	  hdz_2->Fill(dz);	  
	  hz_2->Fill(clus_z);
	}

      cnt++;
    }

  TCanvas *c1 = new TCanvas("c1","c1",5,5,1200,800);
  c1->Divide(2,2);

  c1->cd(1);
  gPad->SetLeftMargin(0.15);
  hdrphi_1->Draw();

  c1->cd(2);
  gPad->SetLeftMargin(0.15);
  hdrphi_2->Draw();

  c1->cd(3);
  gPad->SetLeftMargin(0.15);
  hdz_1->Draw();

  c1->cd(4);
  gPad->SetLeftMargin(0.15);
  hdz_2->Draw();

  TCanvas *c2 = new TCanvas("c2","c2",5,5,1200,800);
  c2->Divide(2,1);

  c2->cd(1);
  hrphi_1->Draw();

  c2->cd(2);
  hz_2->Draw();

  TCanvas *c3 = new TCanvas("c3","c3",5,5,1200,800);
  hmatch->Draw();
}
