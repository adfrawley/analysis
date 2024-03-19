#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCut.h"
#include "TChain.h"
#include "TLegend.h"
#include "TFile.h"

//#include "sPhenixStyle.C"
#include "/phenix/u/yuhw/RootMacros/sPHENIXStyle/sPhenixStyle.C"

void analyze_evaluator_tracks(){

  //SetsPhenixStyle();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptTitle(1);

  // For Hijing events with embedded particles

  // for tracking efficiency
  // for Pythia events, we need to exclude anything not detectable! Choose charged pions and protons
  TCut good_gtrack_cut = Form("gtrackID>=0 && gprimary == 1 && abs(gvz) < 10 && abs(geta) < 1 &&  (abs(gflavor) == 211 || abs(gflavor) == 2212) && gnmaps >2");
  TCut good_track_cut = Form("gtrackID>=0 && gprimary == 1 && abs(gvz) < 10 && abs(geta) < 1  && (abs(gflavor) == 211 || abs(gflavor) == 2212)  && gnmaps > 2 && quality < 30");   
  //TCut good_gtrack_cut = Form("gtrackID>=0 && gprimary == 1 && abs(gvz) < 10 && abs(geta) < 1 &&  (abs(gflavor) == 211 || abs(gflavor) == 2212) ");
  // TCut good_track_cut = Form("gtrackID>=0 && gprimary == 1 && abs(gvz) < 10 && abs(geta) < 1  && (abs(gflavor) == 211 || abs(gflavor) == 2212)  && quality < 30");   
  // alternative track cuts for MM's purity
  //TCut good_gtrack_cut = Form("gtrackID>=0 && gembed == 1 && gprimary == 1 && ntpc > 20 && quality < 10 && abs(gvz) < 10 && nmms > 1");
  //TCut good_track_cut = Form("gtrackID>=0 && gembed == 1 && gprimary == 1 && ntpc > 20 && quality < 10 && abs(gvz) < 10 && ntrumms > 1");

    //TCut pt_cut = Form("abs(pt/gpt-1) < 0.2");  // 20% cut
    TCut pt_cut = Form("");  // no cut
    
    //TCut test_cut = "gnmaps == 3 && gvt > -10 && gvt < 7000";
    TCut test_cut = "";
    //TCut vertex_ntracks_cut = "ntracks > 100";
    TCut vertex_ntracks_cut = "ntracks > 0";

    //TFile *fout = new TFile("root_files/ntp_track_out.root","recreate");
    TFile *fout = new TFile("root_files/ntp_track_out.root","recreate");

  TChain* ntp_track = new TChain("ntp_track","reco tracks");
  TChain* ntp_gtrack = new TChain("ntp_gtrack","g4 tracks");
  TChain* ntp_vertex = new TChain("ntp_vertex","track vertex");

  TH1D *hnvtx = new TH1D("hnvtx","number of vertices",100,0,100);

  bool use_new = false;
  if(use_new)
    {
      ntp_track->Add("/sphenix/user/frawley/macros_working/macros/detectors/sPHENIX/10evts_G4sPHENIX_g4svtx_eval.root");
      ntp_track->Add("/sphenix/user/frawley/macros_working/macros/detectors/sPHENIX/60evts_G4sPHENIX_g4svtx_eval.root");
      ntp_gtrack->Add("/sphenix/user/frawley/macros_working/macros/detectors/sPHENIX/10evts_G4sPHENIX_g4svtx_eval.root");
      ntp_gtrack->Add("/sphenix/user/frawley/macros_working/macros/detectors/sPHENIX/60evts_G4sPHENIX_g4svtx_eval.root");
      ntp_vertex->Add("/sphenix/user/frawley/macros_working/macros/detectors/sPHENIX/60evts_G4sPHENIX_g4svtx_eval.root");
      ntp_vertex->Add("/sphenix/user/frawley/macros_working/macros/detectors/sPHENIX/10evts_G4sPHENIX_g4svtx_eval.root");

      ntp_track->Add("/sphenix/user/frawley/macros_working/macros/detectors/sPHENIX/ppmode_70_1_G4sPHENIX_g4svtx_eval.root");
      ntp_gtrack->Add("/sphenix/user/frawley/macros_working/macros/detectors/sPHENIX/ppmode_70_1_G4sPHENIX_g4svtx_eval.root");
      ntp_vertex->Add("/sphenix/user/frawley/macros_working/macros/detectors/sPHENIX/ppmode_70_1_G4sPHENIX_g4svtx_eval.root");      
      ntp_track->Add("/sphenix/user/frawley/macros_working/macros/detectors/sPHENIX/ppmode_70_2_G4sPHENIX_g4svtx_eval.root");
      ntp_gtrack->Add("/sphenix/user/frawley/macros_working/macros/detectors/sPHENIX/ppmode_70_2_G4sPHENIX_g4svtx_eval.root");
      ntp_vertex->Add("/sphenix/user/frawley/macros_working/macros/detectors/sPHENIX/ppmode_70_2_G4sPHENIX_g4svtx_eval.root");      

    }
  else
    {
      int n_list = 20;
      int nstart = 0;
      int ifile = 0; 
      

      for(int i=nstart;i<n_list+nstart;i++)
	{
	  char name[500];
	  ifile = i;
	  
	  //if(i==150) continue;
	  
	  // pad number to 4 characters
	  //      char input_str[500];
	  //sprintf(input_str,"%04d", ifile);
	  
	  // Running directories
	  
	  //sprintf(name,"/sphenix/user/frawley/jan20_2023/macros/detectors/sPHENIX/eval_out/proc_%i_g4svtx_eval.root",i);
	  //sprintf(name,"/sphenix/tg/tg01/hf/frawley/D0_piK_jets_5GeV/eval_proc_%i_g4svtx_eval.root",i);
	  //sprintf(name,"/sphenix/tg/tg01/hf/frawley/Pythia_jet_10GeV/eval_proc_%i_g4svtx_eval.root",i);

	  //
	  sprintf(name,"/sphenix/tg/tg01/hf/frawley/streaming_sim_pythia8_pileup_files/readout_20ms/evaluator_files/eval_out_dist/pythia_pp_%i_g4svtx_eval.root",i);
	  //sprintf(name,"/sphenix/tg/tg01/hf/frawley/streaming_sim_pythia8_pileup_files/readout_20ms/evaluator_files/eval_out_nodist/pythia_pp_%i_g4svtx_eval.root",i);
	  

	  // S&C review
	  //==========
	  // MB tpctracker with xyrej 800
	  //sprintf(name,"/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/pions_0_20_0_20_phtpctracker_vtxassoc_xyrej_800_norefit_default_wins_eval_output/EmbedOut_0_20fm_50kHz_bkg_0_20fm-0000000001-0%s_g4svtx_eval.root",embed_input_str); 
	  // central tpctracker with xyrej 800
	  //sprintf(name,"/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/pions_0_488_0_20_phtpctracker_vtxassoc_xyrej_800_norefit_default_wins_eval_output/EmbedOut_0_488fm_50kHz_bkg_0_20fm-0000000001-0%s_g4svtx_eval.root",embed_input_str); 
	  
	  cout << "Adding file number " << i << " with name " << name << endl;
	  
	  // get the number of vertices
	  TChain *ntp_vertex_temp  = new TChain("ntp_vertex","temp vertices");
	  ntp_vertex_temp->Add(name);
	  if(ntp_vertex_temp)
	    {
	      int nvtx = ntp_vertex_temp->GetEntries();
	      hnvtx->Fill(nvtx);	 delete ntp_vertex_temp;
	    }
	  
	  ntp_gtrack->Add(name);
	  ntp_track->Add(name);
	  ntp_vertex->Add(name);
	}
    }

  cout << " ntp_gtrack chain entries = " << ntp_gtrack->GetEntries() << endl;
  cout << " ntp_track chain entries = " << ntp_track->GetEntries() << endl;
  cout << " ntp_vertex chain entries = " << ntp_vertex->GetEntries() << endl;

  double maxcrossing = 250;
  double maxgvt = 25000;

  TCanvas *ccrossing = new TCanvas("ccrossing","ccrossing",5,5,800,800);
  ccrossing->Divide(2,2);
  TH2D *hcrossing_vs_gvt = new TH2D("hcrossing_vs_gvt","crossing vs gvt", 2600, -13000, maxgvt, 500, -20, maxcrossing);
  ccrossing->cd(1);
  ntp_track->Draw("crossing:gvt>>hcrossing_vs_gvt", good_track_cut);
  hcrossing_vs_gvt->Draw();
  hcrossing_vs_gvt->Write();
  TH2D *hcrossing_vs_eta = new TH2D("hcrossing_vs_eta","crossing vs eta", 200, -1.5, 1.5, 500, -20, maxcrossing);
  ccrossing->cd(2);
  ntp_track->Draw("crossing:eta>>hcrossing_vs_eta");
  hcrossing_vs_eta->Draw();
  hcrossing_vs_eta->Write();
  TH1D *hcrossing = new TH1D("hcrossing","hcrossing",500,-20,maxcrossing);
  ccrossing->cd(3);
  ntp_track->Draw("crossing>>hcrossing");  
  hcrossing->Draw();
  hcrossing->Write();

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
  cvtx->Divide(3,1);
  cvtx->cd(1);
  TH1D *hzvt = new TH1D("hzvt","hzvt",500,-12.0,12.0);
  ntp_vertex->Draw("vz>>hzvt", vertex_ntracks_cut);
  hzvt->Draw();
  hzvt->Write();
  cvtx->cd(2);
  TH1D *hxvt = new TH1D("hxvt","hxvt",500,-0.5,0.5);
  ntp_vertex->Draw("vx>>hxvt", vertex_ntracks_cut);
  hxvt->Draw();
  hxvt->Write();
  cvtx->cd(3);
  TH1D *hyvt = new TH1D("hyvt","hyvt",500,-0.5,0.5);
  ntp_vertex->Draw("vy>>hyvt", vertex_ntracks_cut);
  hyvt->Draw();
  hyvt->Write();

  TCanvas *cntpc = new TCanvas("cntpc","cntpc");
  TH1D *hntpc = new TH1D("hntpc","hntpc",200,0.0,50.0);
  ntp_gtrack->Draw("ntpc>>hntpc", good_track_cut && test_cut);
  hntpc->Draw();
  hntpc->Write();

  TCanvas *cnvtxtracks = new TCanvas("cnvtxtracks","cnvtxtracks signal");
  TH1D *hnvtxtracks = new TH1D("hnvtxtracks","hnvtxtracks",120,0.0,120.0);
  ntp_vertex->Draw("ntracks>>hnvtxtracks","ntracks > 0 && gembed > 0 && gvt < 7000");
  hnvtxtracks->Draw();
  hnvtxtracks->Write();

  TCanvas *cnvtxtracks_pu = new TCanvas("cnvtxtracks_pu","cnvtxtracks pileup");
  TH1D *hnvtxtracks_pu = new TH1D("hnvtxtracks_pu","hnvtxtracks_pu",120,0.0,120.0);
  ntp_vertex->Draw("ntracks>>hnvtxtracks_pu","ntracks > 0 && gembed <= 0 && gvt < 7000");
  hnvtxtracks_pu->Draw();
  hnvtxtracks_pu->Write();

  TCanvas *ctrgvt = new TCanvas("ctrgvt","truth track gvt signal");
  TH1D *htrgvt = new TH1D("htrgvt","track gvt signal",44000,-5000.0, 24000.0);
  ntp_gtrack->Draw("gvt>>htrgvt","gnmaps > 2");
  htrgvt->Draw();
  htrgvt->Write();

  TCanvas *cgvt = new TCanvas("cgvt","gvt signal");
  TH1D *hgvt = new TH1D("hgvt","gvt for signal vertices",5000,-2500.0,2500.0);
  ntp_vertex->Draw("gvt>>hgvt","ntracks > 0 && gembed > 0");
  hgvt->Draw();
  hgvt->Write();

  TCanvas *cgvt_pu = new TCanvas("cgvt_pu","gvt pileup");
  TH1D *hgvt_pu = new TH1D("hgvt_pu","gvt for pileup vertices",44000,-20000.0,24000.0);
  ntp_vertex->Draw("gvt>>hgvt_pu","ntracks > 0 && gembed <= 0");
  hgvt_pu->Draw();
  hgvt_pu->Write();

   double vterr_limit = 0.1;
   //double vterr_limit = 0.001;
  TCanvas *cvtxerr = new TCanvas("cvtxerr","cvtxerr", 5,5,1600,800);
  cvtxerr->Divide(3,1);
  cvtxerr->cd(1);
  TH1D *hzvterr = new TH1D("hzvterr","hzvterr",200,-vterr_limit,vterr_limit);
  hzvterr->GetXaxis()->SetNdivisions(504); 
  hzvterr->GetXaxis()->SetTitle("vz - gvz (cm)"); 
  ntp_vertex->Draw("(vz-gvz)>>hzvterr", vertex_ntracks_cut);
  hzvterr->Draw();
  hzvterr->Write();
  TH2D *hzvterr_2d = new TH2D("hzvterr_2d","zvterr vs ntracks",200, 0, 40, 200,-vterr_limit,vterr_limit);
  ntp_vertex->Draw("(vz-gvz):ntracks>>hzvterr_2d", vertex_ntracks_cut);
  hzvterr_2d->Write();
  hzvterr_2d->Draw();

  cvtxerr->cd(2);
  TH1D *hxvterr = new TH1D("hxvterr","hxvterr",200,-vterr_limit,vterr_limit);
  hxvterr->GetXaxis()->SetNdivisions(504); 
  hxvterr->GetXaxis()->SetTitle("vx - gvx (cm)"); 
  ntp_vertex->Draw("(vx-gvx)>>hxvterr", vertex_ntracks_cut);
  hxvterr->Draw();
  hxvterr->Write();
  TH2D *hxvterr_2d = new TH2D("hxvterr_2d","xvterr vs ntracks",200, 0, 40, 200,-vterr_limit,vterr_limit);
  ntp_vertex->Draw("(vx-gvx):ntracks>>hxvterr_2d", vertex_ntracks_cut);
  hxvterr_2d->Write();
  hxvterr_2d->Draw();

  cvtxerr->cd(3);
  TH1D *hyvterr = new TH1D("hyvterr","hyvterr",200,-vterr_limit,vterr_limit);
  hyvterr->GetXaxis()->SetNdivisions(504); 
  hyvterr->GetXaxis()->SetTitle("vy - gvy (cm)"); 
  ntp_vertex->Draw("(vy-gvy)>>hyvterr", vertex_ntracks_cut);
  hyvterr->Draw();
  hyvterr->Write();
  TH2D *hyvterr_2d = new TH2D("hyvterr_2d","yvterr vs ntracks",200, 0, 40, 200,-vterr_limit,vterr_limit);
  ntp_vertex->Draw("(vy-gvy):ntracks>>hyvterr_2d", vertex_ntracks_cut);
  hyvterr_2d->Write();
  hyvterr_2d->Draw();

  TCanvas *cmvtx = new TCanvas("cmvtx","cmvtx");
  TH1D *hnmvtx = new TH1D("hnmvtx","hnmvtx", 100, -1, 4);
  ntp_gtrack->Draw("nmaps>>hnmvtx", good_track_cut && pt_cut && test_cut);
  hnmvtx->Draw();
  hnmvtx->Write();

  TCanvas *cqual = new TCanvas("cqual","cqual");
  TH1D *hqual = new TH1D("hqual","hqual", 100, 0, 30);
  ntp_gtrack->Draw("quality>>hqual", "gtrackID>=0 && ntpc > 20 && nmaps > 1" && pt_cut && test_cut);
  hqual->Draw();
  hqual->Write();

  int nbinptres = 60;  // number of bins in pT
  // int nbinpteff = 120;  // number of bins in pT
  //int nbinpteff = 60;  // number of bins in pT
  int nbinpteff = 40;  // number of bins in pT
  int nbinptdca = 60;  // number of bins in pT
  //int nbin = 400;  // number of bins in Y slice
  int nbin = 400;  // number of bins in Y slice
  double range = 0.4;
  //double ptmax = 20.0;
  double ptmax = 8.0;

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
  h1_2->GetYaxis()->SetRangeUser(0, 0.15);
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
  ntp_gtrack->Draw("gpt>>h3_den",good_gtrack_cut && test_cut);
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

  // efficiency vs gvt
  double gvtmax = 22000;
  int nbingvteff = 100;
  TCanvas * cteff = new TCanvas("cteff","cteff");
  cteff->Divide(3,1);
  TH1D* hteff_den = new TH1D("hteff_den","; gvt; Efficiency",nbingvteff, 0, gvtmax);
  TH1D* hteff_num = (TH1D*)hteff_den->Clone("hteff_num");;
  TH1D* hteff_eff = (TH1D*)hteff_den->Clone("hteff_eff");;
  ntp_gtrack->Draw("gvt>>hteff_den",good_gtrack_cut && test_cut && "gpt > 0.7");
  ntp_gtrack->Draw("gvt>>hteff_num",good_track_cut && pt_cut && test_cut && "gpt > 0.7");

  for(int i=1;i<=hteff_den->GetNbinsX();++i){
    double pass = hteff_num->GetBinContent(i);
    double all = hteff_den->GetBinContent(i);
    double eff = 0;
    if(all > pass)
      eff = pass/all;
    else if(all > 0)
      eff = 1.;

    //double err = BinomialError(pass, all); 
    hteff_eff->SetBinContent(i, eff);
    //hteff_eff->SetBinError(i, err);
  }

  cteff->cd(1);
  hteff_num->Draw();
  hteff_num->Write();

  cteff->cd(2);
  hteff_den->Draw();
  hteff_den->Write();
 
  cteff->cd(3);
  hteff_eff->Draw("p");
  hteff_eff->SetStats(0);
  hteff_eff->SetTitle("; gvt ns; eff. (pT > 0.7)");
  hteff_eff->SetMarkerStyle(20);
  hteff_eff->SetMarkerColor(kBlack);
  hteff_eff->SetLineColor(kBlack);
  hteff_eff->GetYaxis()->SetRangeUser(0.0, 1.1);
  hteff_eff->Write();

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

  TH2D *h6 = new TH2D("h6","h6",nbinpteff, 0, ptmax, nbin, -1.0, 4.0);
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

  cout << " Average vertices per file = " << hnvtx->GetMean()  << endl;

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
