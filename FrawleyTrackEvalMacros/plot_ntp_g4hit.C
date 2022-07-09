#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCut.h"
#include "TChain.h"
#include "TLegend.h"
#include "TFile.h"

//#include "sPhenixStyle.C"
#include "/phenix/u/yuhw/RootMacros/sPHENIXStyle/sPhenixStyle.C"

void plot_ntp_g4hit(
		    //const char* input = "g4svtx_eval.root",
		    const char* input = "/sphenix/user/frawley/pileup/macros/macros/g4simulations/eval_output/g4svtx_eval_1.root_g4svtx_eval.root",
		    const int min_nfromtruth = 30
		){

  //SetsPhenixStyle();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetOptTitle(1);

  // For Hijing events with embedded particles

  // default nomaps cuts:
  //TCut good_gtrack_cut = Form("gtrackID>=0 && gembed > 0 && gntpc > 30 && gprimary == 1");
  //TCut good_track_cut = Form("gtrackID>=0 && gembed > 0 && gntpc > 30 && gprimary == 1 && ntpc > 20 && quality < 10");

  // for tracking efficiency
    TCut good_gtrack_cut = Form("gtrackID>=0 && gembed == 1 && gprimary == 1 && abs(gvz) < 10");
    TCut good_track_cut = Form("gtrackID>=0 && gembed == 1 && gprimary == 1 && ntpc > 20 && quality < 10 && abs(gvz) < 10");
    //TCut good_track_cut = Form("gtrackID>=0 && gembed == 1 && gprimary == 1 && ntpc > 20 && abs(gvz) < 10");
  // for MM's eff
  //TCut good_gtrack_cut = Form("gtrackID>=0 && gembed == 1 && gprimary == 1 && ntpc > 20 && quality < 10 && abs(gvz) < 10 && nmms > 1");
  //TCut good_track_cut = Form("gtrackID>=0 && gembed == 1 && gprimary == 1 && ntpc > 20 && quality < 10 && abs(gvz) < 10 && ntrumms > 1");

  //TCut pt_cut = Form("abs(pt/gpt-1) < 0.25");  // 25% cut
  TCut pt_cut = Form("");  // no cut
  
  TCut good_tpc_cut = Form("ntrutpc1 > -1 && ntrutpc 2 > -1 && ntrutpc3 > -1");
  TCut good_phi_cut = Form("abs(phi-gphi) <0.1");
  TCut good_eta_cut = Form("abs(eta-geta) <0.1");

  /*
  TCut good_tpc_cut = Form("ntrutpc1 > 0 && ntrutpc 2 > 0 && ntrutpc3 > 0");
  TCut good_phi_cut = Form("abs(phi-gphi) <0.03");
  TCut good_eta_cut = Form("abs(eta-geta) <0.008");
  */

  //TCut test_cut = good_tpc_cut+ good_eta_cut + good_phi_cut;
  TCut test_cut = "ntrumaps == 3";


  TFile *fout = new TFile("root_files/ntp_track_out.root","recreate");

  TChain* ntp_track = new TChain("ntp_track","reco tracks");
  TChain* ntp_gtrack = new TChain("ntp_gtrack","g4 tracks");
  TChain* ntp_vertex = new TChain("ntp_vertex","track vertex");

  bool use_list = false;
  int n_list = 1000;
  int ifile = 0; 
  
  TH1D *hnvtx = new TH1D("hnvtx","number of vertices",100,0,10);
  for(int i=0;i<n_list;i++)
    {
      char name[500];
      ifile = i;

      // pad number to 4 characters
      char input_str[500];
      sprintf(input_str,"%04d", ifile);

      // Running directories

      sprintf(name,"/sphenix/user/frawley/new_macros_april27/macros/detectors/sPHENIX/eval_output/eval_out-0%s.root",input_str);

      //sprintf(name,"/sphenix/user/frawley/new_macros_april27/macros/detectors/sPHENIX/eval_output/eval_out_%i.root",ifile);
  

      // S&C review
      //==========
      // MB tpctracker with xyrej 800
      //sprintf(name,"/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/pions_0_20_0_20_phtpctracker_vtxassoc_xyrej_800_norefit_default_wins_eval_output/EmbedOut_0_20fm_50kHz_bkg_0_20fm-0000000001-0%s_g4svtx_eval.root",embed_input_str); 
      // central tpctracker with xyrej 800
      //sprintf(name,"/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/pions_0_488_0_20_phtpctracker_vtxassoc_xyrej_800_norefit_default_wins_eval_output/EmbedOut_0_488fm_50kHz_bkg_0_20fm-0000000001-0%s_g4svtx_eval.root",embed_input_str); 

      // get the number of vertices
      TChain ntp_vertex_temp;
      ntp_vertex_temp->Add(name);
      int nvtx = ntp_vertex_temp->GetEntries();
      hnvtx->Fill(nvtx);
      delete ntp_vertex_temp;

      cout << "Adding file number " << i << " with name " << name << endl;
	    
      ntp_gtrack->Add(name);
      ntp_track->Add(name);
      ntp_vertex->Add(name);
    }

  cout << " ntp_gtrack chain entries = " << ntp_gtrack->GetEntries() << endl;
  cout << " ntp_track chain entries = " << ntp_track->GetEntries() << endl;
  cout << " ntp_vertex chain entries = " << ntp_vertex->GetEntries() << endl;

  TCanvas *cntrutpc = new TCanvas("cntrutpc","cntrutpc",5,5,1600,800);
  cntrutpc->Divide(3,1);

  cntrutpc->cd(3);
  TH1D *hntrutpc3 = new TH1D("hntrutpc3","hntrutpc3",200,-2,50.0);
  ntp_gtrack->Draw("ntrutpc3>>hntrutpc3",good_track_cut && test_cut);
  double max = hntrutpc3->GetMaximum();
  hntrutpc3->SetMaximum(max*1.4);
  hntrutpc3->Draw();
  hntrutpc3->Write();

  cntrutpc->cd(1);
  TH1D *hntrutpc1 = new TH1D("hntrutpc1","hntrutpc1",200,-2,50.0);
  ntp_gtrack->Draw("ntrutpc1>>hntrutpc1",good_track_cut && test_cut);
  hntrutpc1->SetMaximum(max*1.4);
  hntrutpc1->Draw();
  hntrutpc1->Write();

  cntrutpc->cd(2);
  TH1D *hntrutpc2 = new TH1D("hntrutpc2","hntrutpc2",200,-2,50.0);
  ntp_gtrack->Draw("ntrutpc2>>hntrutpc2", good_track_cut && test_cut);
  hntrutpc2->SetMaximum(max*1.4);
  hntrutpc2->Draw();
  hntrutpc2->Write();

  TCanvas *cdphi = new TCanvas("cdphi","cdphi");
  TH1D *hdphi = new TH1D("hdphi","hdphi",200,-0.1,0.1);
  ntp_gtrack->Draw("phi-gphi>>hdphi",good_track_cut && test_cut);
  hdphi->Draw();
  hdphi->Write();


  TCanvas *ctrz = new TCanvas("ctrz","ctrz");
  TH1D *htrz = new TH1D("htrz","htrz",200,-50.0,50.0);
  ntp_gtrack->Draw("pcaz>>htrz",good_track_cut && test_cut);
  htrz->Draw();
  htrz->Write();


  TCanvas *cdeta = new TCanvas("cdeta","cdeta");
  TH1D *hdeta = new TH1D("hdeta","hdeta",500,-0.3,0.3);
  ntp_gtrack->Draw("eta-geta>>hdeta",good_track_cut && test_cut);
  hdeta->Draw();
  hdeta->Write();

  TCanvas *cmaps2d = new TCanvas("cmaps2d","cmaps2d", 5,5,1600,800);
  cmaps2d->Divide(2,1);

  cmaps2d->cd(1);
  TH2D *hnmaps_vs_gvz = new TH2D("hnmaps_vs_gvz","nmaps vs gvz",200,-20,20,100,-1,4);
  ntp_gtrack->Draw("nmaps:gvz>>hnmaps_vs_gvz",good_gtrack_cut && test_cut);
  hnmaps_vs_gvz->Draw();
  hnmaps_vs_gvz->Write();

  cmaps2d->cd(2);
  TH2D *hnmaps_vs_geta = new TH2D("hnmaps_vs_geta","nmaps vs geta",200,-1.1,1.1,100,-1,4);
  ntp_gtrack->Draw("nmaps:geta>>hnmaps_vs_geta", good_gtrack_cut && test_cut);
  hnmaps_vs_geta->Draw();
  hnmaps_vs_geta->Write();

  TCanvas *cvtx = new TCanvas("cvtx","cvtx");
  TH1D *hzvt = new TH1D("hzvt","hzvt",500,-15.0,15.0);
  ntp_vertex->Draw("vz>>hzvt");
  hzvt->Draw();
  hzvt->Write();

  TCanvas *cntpc = new TCanvas("cntpc","cntpc");
  TH1D *hntpc = new TH1D("hntpc","hntpc",200,0.0,50.0);
  ntp_gtrack->Draw("ntpc>>hntpc", good_track_cut && test_cut);
  hntpc->Draw();
  hntpc->Write();

  TCanvas *cvtxerr = new TCanvas("cvtxerr","cvtxerr");
  cvtxerr->Divide(2,1);
  cvtxerr->cd(0);
  TH1D *hzvterr = new TH1D("hzvterr","hzvterr",1000,-0.1,0.1);
  ntp_vertex->Draw("(vz-gvz)>>hzvterr");
  hzvterr->Draw();
  hzvterr->Write();
  cvtxerr->cd(1);
  TH1D *hxvterr = new TH1D("hxvterr","hxvterr",1000,-0.1,0.1);
  ntp_vertex->Draw("(vx-gvx)>>hxvterr");
  hxvterr->Draw();
  hxvterr->Write();

  TCanvas *cmvtx = new TCanvas("cmvtx","cmvtx");
  TH1D *hnmvtx = new TH1D("hnmvtx","hnmvtx", 100, -1, 4);
  ntp_gtrack->Draw("nmaps>>hnmvtx", good_track_cut && pt_cut && test_cut);
  hnmvtx->Draw();
  hnmvtx->Write();

  TCanvas *cqual = new TCanvas("cqual","cqual");
  TH1D *hqual = new TH1D("hqual","hqual", 100, 0, 20);
  ntp_gtrack->Draw("quality>>hqual", "gtrackID>=0 && gembed >= 1 && ntpc > 20 && nmaps > 1" && pt_cut);
  hqual->Draw();
  hqual->Write();

  int nbinptres = 60;  // number of bins in pT
  // int nbinpteff = 120;  // number of bins in pT
  int nbinpteff = 60;  // number of bins in pT
  int nbinptdca = 60;  // number of bins in pT
  //int nbin = 400;  // number of bins in Y slice
  int nbin = 400;  // number of bins in Y slice
  double range = 0.4;
  double ptmax = 20.0;

  TCanvas *cpt = new TCanvas("cpt","cpt");
  TH2D *h1 = new TH2D("h1","h1",nbinptres, 0.0 ,ptmax,nbin,-range,range);
  ntp_gtrack->Draw("(pt-gpt)/gpt:gpt>>h1",good_track_cut && pt_cut && test_cut);
  h1->FitSlicesY();
  TH1D*h1_1 = (TH1D*)gDirectory->Get("h1_1");
  TH1D*h1_2 = (TH1D*)gDirectory->Get("h1_2");
  h1_2->Draw("e");

  h1_1->SetMarkerStyle(4);
  h1_1->SetMarkerColor(kBlack);
  h1_1->SetLineColor(kBlack);

  h1_2->SetMarkerStyle(20);
  h1_2->SetMarkerColor(kBlack);
  h1_2->SetLineColor(kBlack);
  h1_2->GetYaxis()->SetRangeUser(0, 0.05);
  h1_2->GetYaxis()->SetTitleOffset(1.5);
  h1_2->SetStats(0);
  h1_2->SetTitle(";p_{T} [GeV/c];#frac{#Delta p_{T}}{p_{T}}");

  h1->Write();
  h1_2->Write();

  TCanvas * c3 = new TCanvas("c3","c3");
  TH1D* h3_den = new TH1D("h3_den","; p_{T}; Efficiency",nbinpteff, 0, ptmax);
  TH1D* h3_num = (TH1D*)h3_den->Clone("h3_num");;
  TH1D* h3_eff = (TH1D*)h3_den->Clone("h3_eff");;

  cout<<__LINE__<<": Good track cut " << good_track_cut << " pT cut " << pt_cut << endl;
  ntp_gtrack->Draw("gpt>>h3_den",good_gtrack_cut);
  ntp_gtrack->Draw("gpt>>h3_num",good_track_cut && pt_cut && test_cut);

  for(int i=1;i<=h3_den->GetNbinsX();++i){
    double pass = h3_num->GetBinContent(i);
    double all = h3_den->GetBinContent(i);
    double eff = 0;
    if(all > pass)
      eff = pass/all;
    else if(all > 0)
      eff = 1.;

    //double err = BinomialError(pass, all); 
    h3_eff->SetBinContent(i, eff);
    //h3_eff->SetBinError(i, err);
  }

  h3_eff->Draw("p");
  h3_eff->SetStats(0);
  h3_eff->SetTitle("; p_{T} [GeV/c]; eff.");
  h3_eff->SetMarkerStyle(20);
  h3_eff->SetMarkerColor(kBlack);
  h3_eff->SetLineColor(kBlack);
  h3_eff->GetYaxis()->SetRangeUser(0.0, 1.1);

  h3_den->Write();
  h3_num->Write();
  h3_eff->Write();

  TCanvas *c4 = new TCanvas("c4","c4",5,5,800,800);


  TH2D *h2 = new TH2D("h2","h2",nbinptdca, 0,ptmax,nbin,-0.03,0.03);
  ntp_gtrack->Draw("(dca3dxy):gpt>>h2",good_track_cut && pt_cut && test_cut);
  // if tracking is not run, dca3dxy is not filled
  //ntp_gtrack->Draw("( (0.0-pcax)*(0.0-gvy) - (pcax-gvx)*(pcay-0.0) ) / sqrt(pcax*pcax+pcay*pcay):gpt>>h2",good_track_cut && pt_cut && test_cut);

  h2->FitSlicesY();
  TH1D*h2_1 = (TH1D*)gDirectory->Get("h2_1");
  TH1D*h2_2 = (TH1D*)gDirectory->Get("h2_2");
  h2_2->Draw("e");

  h2_1->SetMarkerStyle(4);
  h2_1->SetMarkerColor(kBlack);
  h2_1->SetLineColor(kBlack);

  h2_2->SetMarkerStyle(20);
  h2_2->SetMarkerColor(kBlack);
  h2_2->SetLineColor(kBlack);
  h2_2->GetYaxis()->SetRangeUser(0.,0.01);
  h2_2->GetYaxis()->SetTitleOffset(1.5);
  h2_2->SetStats(0);
  h2_2->SetTitle(";p_{T} [GeV/c];dca2d (cm)}");

  h2->Write();
  h2_2->Write();


  TCanvas *c5 = new TCanvas("c5","c5",5,5,800,800);

  TH2D *h3 = new TH2D("h3","h3",nbinptdca, 0, ptmax, nbin, -0.05, 0.05);
  ntp_gtrack->Draw("(dca3dz):gpt>>h3",good_track_cut && pt_cut && test_cut);
  // if tracking is not run, dca3dz is not filled
  //ntp_gtrack->Draw("(pcaz-gvz):gpt>>h3",good_track_cut && pt_cut && test_cut);
  h3->FitSlicesY();
  TH1D*h3_1 = (TH1D*)gDirectory->Get("h3_1");
  TH1D*h3_2 = (TH1D*)gDirectory->Get("h3_2");
  h3_2->Draw("e");

  h3_1->SetMarkerStyle(4);
  h3_1->SetMarkerColor(kBlack);
  h3_1->SetLineColor(kBlack);

  h3_2->SetMarkerStyle(20);
  h3_2->SetMarkerColor(kBlack);
  h3_2->SetLineColor(kBlack);
  h3_2->GetYaxis()->SetRangeUser(0.,0.01);
  h3_2->GetYaxis()->SetTitleOffset(1.5);
  h3_2->SetStats(0);
  h3_2->SetTitle(";p_{T} [GeV/c];dca2d (cm)}");

  h3->Write();
  h3_2->Write();

  TCanvas *c6 = new TCanvas("c6","c6", 5,5,1200, 800);

  TH2D *h6 = new TH2D("h6","h6",nbinptdca, 0, ptmax, nbin, -1.0, 4.0);
  ntp_gtrack->Draw("ntrumaps:gpt>>h6",good_track_cut && pt_cut && test_cut);
  h6->Draw();
 
  TH1D *h6_1 = new TH1D("h6_1","h6_1",nbin, 0.0, 1.2);
  int binlo = h6->GetYaxis()->FindBin(2.5);
  int binhi = h6->GetYaxis()->FindBin(3.5);
  h6->ProjectionX("h6_1",binlo,binhi);
  h6_1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  h6_1->SetLineWidth(2.0);
  h6_1->SetLineColor(kBlue);


  TH1D *h6_2 = new TH1D("h6_2","h6_2",nbin, 0.0, 1.2);
  binlo = h6->GetYaxis()->FindBin(-0.5);
  binhi = h6->GetYaxis()->FindBin(0.5);
  h6->ProjectionX("h6_2",binlo,binhi);
  h6_2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  h6_2->SetLineColor(kRed);
  h6_2->SetLineWidth(2.0);


  h6_1->Draw();
  h6_2->Draw("same");

  TLegend *l = new TLegend(0.15,0.75,0.45,0.85,"","NDC");
  l->SetBorderSize(1);
  l->AddEntry(h6_2,"ntrumaps = 0","l");
  l->AddEntry(h6_1,"ntrumaps = 3","l");
  l->Draw();

  h6->Write();
  h6_1->Write();
  h6_2->Write();

  TCanvas *cnvtx = new TCanvas("cnvtx","cnvtx",5, 5, 800,800);
  hnvtx->Draw();
  hnvtx->Write();

  cout << " Average vertices per collision = " << hnvtx->GetMean()  << endl;

  cout << " ntp_gtrack chain entries = " << ntp_gtrack->GetEntries() << endl;
  cout << " ntp_track chain entries = " << ntp_track->GetEntries() << endl;
  cout << " ntp_vertex chain entries = " << ntp_vertex->GetEntries() << endl;

  /*
  TCanvas *c7 = new TCanvas("c7","c7", 5,5,1200, 800);

  TH2D *h7 = new TH2D("h7","h7",nbin, 0, 1.1, nbin, -1.0, 50.0);
  ntp_track->Draw("ntrutpc:gpt>>h7","ntrumaps == 0");
  h7->Draw();
  */
  /* 
  TH1D *h7_1 = new TH1D("h7_1","h7_1",100, 0.0, 1.2);
  h7->ProjectionX("h7_1");
  h7_1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  h7_1->SetLineWidth(2.0);
  h7_1->SetLineColor(kBlue);
  h7_1->Draw();
  */
  /*
  TH2D *h8 = new TH2D("h8","h8",100, 0, 1.1, 100, -1.0, 50.0);
  ntp_track->Draw("ntrutpc:gpt>>h7","ntrumaps == 3");
  h8->Draw();

  TH1D *h8_1 = new TH1D("h8_1","h8_1",100, 0.0, 1.2);
  h8->ProjectionX("h8_1");
  h8_1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  h8_1->SetLineColor(kRed);
  h8_1->SetLineWidth(2.0);
  h8_1->Draw("same");

  TLegend *l = new TLegend(0.15,0.75,0.45,0.85,"","NDC");
  l->SetBorderSize(1);
  l->AddEntry(h7_1,"ntrumaps = 0","l");
  l->AddEntry(h8_1,"ntrumaps = 3","l");
  l->Draw();
  */
}
