#include "TH1D.h"
#include "TH2D.h"
#include "TCut.h"
#include "TChain.h"
#include "TLegend.h"
#include "TFile.h"
//----------------
// To aggregate the output root files in analyze_out from here:
// modify hadd_bash_script to have the correct number of files
//  bash
//  source hadd_bash_script
//  exit
//----------------

//#include "sPhenixStyle.C"
#include "/phenix/u/yuhw/RootMacros/sPHENIXStyle/sPhenixStyle.C"

void analyze_evaluator_tracks_condor(int proc = 0, int n_list = 5){

  // For Hijing events with embedded particles

  // for tracking efficiency
  // for Pythia events, we need to exclude anything not detectable! Choose charged pions and protons
  TCut good_gtrack_cut = Form("gtrackID>=0 && gprimary == 1 && abs(gvz) < 10 && abs(geta) < 1 &&  (abs(gflavor) == 211 || abs(gflavor) == 2212)");
  TCut good_track_cut = Form("gtrackID>=0 && gprimary == 1 && abs(gvz) < 10 && abs(geta) < 1  && (abs(gflavor) == 211 || abs(gflavor) == 2212)  && ntpc > 20 && quality < 10");   
  // alternative track cuts for MM's purity
  //TCut good_gtrack_cut = Form("gtrackID>=0 && gembed == 1 && gprimary == 1 && ntpc > 20 && quality < 10 && abs(gvz) < 10 && nmms > 1");
  //TCut good_track_cut = Form("gtrackID>=0 && gembed == 1 && gprimary == 1 && ntpc > 20 && quality < 10 && abs(gvz) < 10 && ntrumms > 1");

    TCut pt_cut = Form("abs(pt/gpt-1) < 0.2");  // 20% cut
    //TCut pt_cut = Form("");  // no cut
    TCut test_cut = "gnmaps > 2 && gntpc > 20 && gvt > -10 && gvt < 7000";
    //TCut test_cut = "";
    TCut vertex_ntracks_cut = "ntracks > 0";

    char fname[500];
    sprintf(fname,"analyze_out/ntp_track_out_%i.root",proc);
    TFile *fout = new TFile(fname,"recreate");

  TChain* ntp_track = new TChain("ntp_track","reco tracks");
  TChain* ntp_gtrack = new TChain("ntp_gtrack","g4 tracks");
  TChain* ntp_vertex = new TChain("ntp_vertex","track vertex");

  int nstart = proc * n_list;
  int ifile = 0; 
  
  TH1D *hnvtx = new TH1D("hnvtx","number of vertices",100,0,100);
  for(int i=nstart;i<n_list+nstart;i++)
    {
      char name[500];
      ifile = i;

      // pad number to 4 characters
      char input_str[500];
      sprintf(input_str,"%04d", ifile);

      // Running directories

      //sprintf(name,"/sphenix/user/frawley/new_macros_april27/macros/detectors/sPHENIX/eval_output/g4svtx_eval_%i.root",i);
      sprintf(name,"/sphenix/user/frawley/new_macros_april27/macros/detectors/sPHENIX/eval_output/eval_out_%i.root",i);
  
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

  cout << " ntp_gtrack chain entries = " << ntp_gtrack->GetEntries() << endl;
  cout << " ntp_track chain entries = " << ntp_track->GetEntries() << endl;
  cout << " ntp_vertex chain entries = " << ntp_vertex->GetEntries() << endl;

 
  TH2D *hcrossing_vs_gvt = new TH2D("hcrossing_vs_gvt","crossing vs gvt", 2600, -13000, 13000, 200, -20, 100);
  ntp_track->Draw("crossing:gvt>>hcrossing_vs_gvt", good_track_cut,"goff");
  hcrossing_vs_gvt->Write();
  TH2D *hcrossing_vs_eta = new TH2D("hcrossing_vs_eta","crossing vs eta", 200, -1.5, 1.5, 200, -20, 100);
  ntp_track->Draw("crossing:eta>>hcrossing_vs_eta", good_track_cut, "goff");
  hcrossing_vs_eta->Write();
  TH1D *hcrossing = new TH1D("hcrossing","hcrossing",200,-20,100.0);
  ntp_track->Draw("crossing>>hcrossing", good_track_cut, "goff");  
  hcrossing->Write();

  TH1D *hntrutpc3 = new TH1D("hntrutpc3","hntrutpc3",200,-2,50.0);
  ntp_gtrack->Draw("ntrutpc3>>hntrutpc3",good_track_cut && test_cut, "goff");
  double max = hntrutpc3->GetMaximum();
  hntrutpc3->SetMaximum(max*1.4);
  hntrutpc3->Write();
  
  TH1D *hntrutpc1 = new TH1D("hntrutpc1","hntrutpc1",200,-2,50.0);
  ntp_gtrack->Draw("ntrutpc1>>hntrutpc1",good_track_cut && test_cut, "goff");
  hntrutpc1->SetMaximum(max*1.4);
  hntrutpc1->Write();


  TH1D *hntrutpc2 = new TH1D("hntrutpc2","hntrutpc2",200,-2,50.0);
  ntp_gtrack->Draw("ntrutpc2>>hntrutpc2", good_track_cut && test_cut, "goff");
  hntrutpc2->SetMaximum(max*1.4);
  hntrutpc2->Write();

  TH1D *hdphi = new TH1D("hdphi","hdphi",200,-0.1,0.1);
  ntp_gtrack->Draw("phi-gphi>>hdphi",good_track_cut && test_cut, "goff");
  hdphi->Write();


  TH1D *htrz = new TH1D("htrz","htrz",200,-50.0,50.0);
  ntp_gtrack->Draw("pcaz>>htrz",good_track_cut && test_cut, "goff");
  htrz->Write();


  TH1D *hdeta = new TH1D("hdeta","hdeta",500,-0.3,0.3);
  ntp_gtrack->Draw("eta-geta>>hdeta",good_track_cut && test_cut,"goff");
  hdeta->Write();

  TH2D *hnmaps_vs_gvz = new TH2D("hnmaps_vs_gvz","nmaps vs gvz",200,-20,20,100,-1,4);
  ntp_gtrack->Draw("nmaps:gvz>>hnmaps_vs_gvz",good_gtrack_cut && good_track_cut && test_cut, "goff");
  hnmaps_vs_gvz->Write();

  TH2D *hnmaps_vs_geta = new TH2D("hnmaps_vs_geta","nmaps vs geta",200,-1.1,1.1,100,-1,4);
  ntp_gtrack->Draw("nmaps:geta>>hnmaps_vs_geta", good_gtrack_cut && good_track_cut && test_cut, "goff");
  hnmaps_vs_geta->Write();

  TH1D *hzvt = new TH1D("hzvt","hzvt",500,-12.0,12.0);
  ntp_vertex->Draw("vz>>hzvt", vertex_ntracks_cut,"goff");
  hzvt->Write();
  TH1D *hxvt = new TH1D("hxvt","hxvt",500,-0.5,0.5);
  ntp_vertex->Draw("vx>>hxvt", vertex_ntracks_cut,"goff");
  hxvt->Write();
  TH1D *hyvt = new TH1D("hyvt","hyvt",500,-0.5,0.5);
  ntp_vertex->Draw("vy>>hyvt", vertex_ntracks_cut,"goff");
  hyvt->Write();

  TH1D *hntpc = new TH1D("hntpc","hntpc",200,0.0,50.0);
  ntp_gtrack->Draw("ntpc>>hntpc", good_track_cut && test_cut,"goff");
  hntpc->Write();

  TH1D *hnvtxtracks = new TH1D("hnvtxtracks","hnvtxtracks",100,0.0,100.0);
  ntp_vertex->Draw("ntracks>>hnvtxtracks","ntracks > 0 && gembed > 0","goff");
  hnvtxtracks->Write();

  TH1D *hnvtxtracks_pu = new TH1D("hnvtxtracks_pu","hnvtxtracks_pu",100,0.0,100.0);
  ntp_vertex->Draw("ntracks>>hnvtxtracks_pu","ntracks > 0 && gembed <= 0","goff");
  hnvtxtracks_pu->Write();

  TH1D *hgvt = new TH1D("hgvt","gvt signal vertices",5000,-2500.0,2500.0);
  ntp_vertex->Draw("gvt>>hgvt","ntracks > 0 && gembed > 0","goff");
  hgvt->Write();

  TH1D *hgvt_pu = new TH1D("hgvt_pu","gvt pileup vertices",17000,-5000.0,12000.0);
  ntp_vertex->Draw("gvt>>hgvt_pu","ntracks > 0 && gembed <= 0","goff");
  hgvt_pu->Write();

   double vterr_limit = 0.1;
  TH1D *hzvterr = new TH1D("hzvterr","hzvterr",200,-vterr_limit,vterr_limit);
  hzvterr->GetXaxis()->SetNdivisions(504); 
  hzvterr->GetXaxis()->SetTitle("vz - gvz (cm)"); 
  ntp_vertex->Draw("(vz-gvz)>>hzvterr", vertex_ntracks_cut,"goff");
  hzvterr->Write();
  TH2D *hzvterr_2d = new TH2D("hzvterr_2d","zvterr vs ntracks",200, 0, 40, 200,-vterr_limit,vterr_limit);
  ntp_vertex->Draw("(vz-gvz):ntracks>>hzvterr_2d", vertex_ntracks_cut,"goff");
  hzvterr_2d->Write();

  TH1D *hxvterr = new TH1D("hxvterr","hxvterr",200,-vterr_limit,vterr_limit);
  hxvterr->GetXaxis()->SetNdivisions(504); 
  hxvterr->GetXaxis()->SetTitle("vx - gvx (cm)"); 
  ntp_vertex->Draw("(vx-gvx)>>hxvterr", vertex_ntracks_cut,"goff");
  hxvterr->Write();
  TH2D *hxvterr_2d = new TH2D("hxvterr_2d","xvterr vs ntracks",200, 0, 40, 200,-vterr_limit,vterr_limit);
  ntp_vertex->Draw("(vx-gvx):ntracks>>hxvterr_2d", vertex_ntracks_cut,"goff");
  hxvterr_2d->Write();

  TH1D *hyvterr = new TH1D("hyvterr","hyvterr",200,-vterr_limit,vterr_limit);
  hyvterr->GetXaxis()->SetNdivisions(504); 
  hyvterr->GetXaxis()->SetTitle("vy - gvy (cm)"); 
  ntp_vertex->Draw("(vy-gvy)>>hyvterr", vertex_ntracks_cut,"goff");
  hyvterr->Write();
  TH2D *hyvterr_2d = new TH2D("hyvterr_2d","yvterr vs ntracks",200, 0, 40, 200,-vterr_limit,vterr_limit);
  ntp_vertex->Draw("(vy-gvy):ntracks>>hyvterr_2d", vertex_ntracks_cut,"goff");
  hyvterr_2d->Write();

  TH1D *hnmvtx = new TH1D("hnmvtx","hnmvtx", 100, -1, 4);
  ntp_gtrack->Draw("nmaps>>hnmvtx", good_track_cut && pt_cut && test_cut,"goff");
  hnmvtx->Write();

  TH1D *hqual = new TH1D("hqual","hqual", 100, 0, 20);
  ntp_gtrack->Draw("quality>>hqual", "ntpc > 20 && nmaps > 1" && good_gtrack_cut && pt_cut && test_cut,"goff");
  hqual->Write();

  int nbinptres = 60;  // number of bins in pT
  int nbinpteff = 120;  // number of bins in pT
  //int nbinpteff = 60;  // number of bins in pT
  int nbinptdca = 60;  // number of bins in pT
  //int nbin = 400;  // number of bins in Y slice
  int nbin = 400;  // number of bins in Y slice
  double range = 0.4;
  double ptmax = 20.0;

  TH2D *h1 = new TH2D("h1","h1",nbinptres, 0.0 ,ptmax,nbin,-range,range);
  ntp_gtrack->Draw("(pt-gpt)/gpt:gpt>>h1",good_track_cut && pt_cut && test_cut,"goff");
  h1->FitSlicesY();
  TH1D*h1_1 = (TH1D*)gDirectory->Get("h1_1");
  TH1D*h1_2 = (TH1D*)gDirectory->Get("h1_2");

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

  TH1D* h3_den = new TH1D("h3_den","; p_{T}; Efficiency",nbinpteff, 0, ptmax);
  TH1D* h3_num = (TH1D*)h3_den->Clone("h3_num");;
  TH1D* h3_eff = (TH1D*)h3_den->Clone("h3_eff");;

  cout<<__LINE__<<": Good track cut " << good_track_cut << " pT cut " << pt_cut << endl;
  ntp_gtrack->Draw("gpt>>h3_den",good_gtrack_cut && test_cut,"goff");
  ntp_gtrack->Draw("gpt>>h3_num",good_track_cut && pt_cut && test_cut,"goff");

  for(int i=1;i<=h3_den->GetNbinsX();++i){
    double pass = h3_num->GetBinContent(i);
    double all = h3_den->GetBinContent(i);
    double eff = 0;
    if(all > pass)
      eff = pass/all;
    else if(all > 0)
      eff = 1.;

    h3_eff->SetBinContent(i, eff);
  }

  h3_eff->SetStats(0);
  h3_eff->SetTitle("; p_{T} [GeV/c]; eff.");
  h3_eff->SetMarkerStyle(20);
  h3_eff->SetMarkerColor(kBlack);
  h3_eff->SetLineColor(kBlack);
  h3_eff->GetYaxis()->SetRangeUser(0.0, 1.1);

  h3_den->Write();
  h3_num->Write();
  h3_eff->Write();

  TH2D *h2 = new TH2D("h2","h2",nbinptdca, 0,ptmax,nbin,-0.03,0.03);
  ntp_gtrack->Draw("(dca3dxy):gpt>>h2",good_track_cut && pt_cut && test_cut,"goff");

  h2->FitSlicesY();
  TH1D*h2_1 = (TH1D*)gDirectory->Get("h2_1");
  TH1D*h2_2 = (TH1D*)gDirectory->Get("h2_2");

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

  TH2D *h3 = new TH2D("h3","h3",nbinptdca, 0, ptmax, nbin, -0.05, 0.05);
  ntp_gtrack->Draw("(dca3dz):gpt>>h3",good_track_cut && pt_cut && test_cut,"goff");
  // if tracking is not run, dca3dz is not filled 
 //ntp_gtrack->Draw("(pcaz-gvz):gpt>>h3",good_track_cut && pt_cut && test_cut);
  h3->FitSlicesY();
  TH1D*h3_1 = (TH1D*)gDirectory->Get("h3_1");
  TH1D*h3_2 = (TH1D*)gDirectory->Get("h3_2");

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

  TH2D *h6 = new TH2D("h6","h6",nbinpteff, 0, ptmax, nbin, -1.0, 6.0);
  ntp_gtrack->Draw("ntrumaps:gpt>>h6",good_track_cut && pt_cut && test_cut,"goff");
 
  TH1D *h6_1 = new TH1D("h6_1","h6_1",nbin, 0.0, 1.2);
  int binlo = h6->GetYaxis()->FindBin(2.5);
  int binhi = h6->GetYaxis()->FindBin(5.5);
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

  h6->Write();
  h6_1->Write();
  h6_2->Write();

  hnvtx->Write();

  cout << " Average vertices per file = " << hnvtx->GetMean()  << endl;

  cout << " ntp_gtrack chain entries = " << ntp_gtrack->GetEntries() << endl;
  cout << " ntp_track chain entries = " << ntp_track->GetEntries() << endl;
  cout << " ntp_vertex chain entries = " << ntp_vertex->GetEntries() << endl;

  std::cout << "All done" << std::endl;
}
