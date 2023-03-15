#include "TH2D.h"
#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TLine.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TColor.h"
#include "TF1.h"

#include <iostream>

#include "sPhenixStyle.C"

void plot_ntp_track_out()
{

  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  bool pp_mode = false;

 double ptmax = 10.0;
double slice_low = 5.0;
double slice_high = 6.0;
 if(pp_mode)
   {
     ptmax = 10.0;
     slice_low = 1.0;
     slice_high = 2.0;
   }

  std::vector<std::string> finvec;
  std::vector<std::string> legvec;
  std::vector<int> col;

  //============


  // tuning tests
  //========== 

  /*
  finvec.push_back("reorg_truth_all_100pions_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "reorg truth all 100 pions");
  col.push_back(kBlue); 


  finvec.push_back("reorg_check_tpc_truth_100pions_analyze_out/ntp_track_out.root");
  legvec.push_back( "recheck truth tpc 100 pions");
  col.push_back(kBlack); 
  */

  /*
  finvec.push_back("reorg_pythiaMB_pu_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "reorg PYTHIA MB + 3 MHz");
  col.push_back(kGreen); 
  */
  /*
  finvec.push_back("reorg_truth_match_100pions_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "reorg truth match 100 pions");
  col.push_back(kBlue); 
  */


  finvec.push_back("root_files/perturb4_150files_ntp_track_out.root");
  legvec.push_back( "100 pions MVTX/INTT 40 15 TPC/TPOT 150");
  col.push_back(kRed); 


  finvec.push_back("reorg_final_100pions_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "reorg 100 pions");
  col.push_back(kViolet); 



  /*
 finvec.push_back("newbins_newcuts_truth_all_nodist_100pions_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "truth all 100 pions");
  col.push_back(kBlack); 
  */

  /*
  finvec.push_back("newbins_newcuts_truth_matching_nodist_100pions_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "truth matching 100 pions");
  col.push_back(kBlack); 
  */
  /*
  finvec.push_back("newbins_newcuts_repo_nodist_100pions_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "newcuts repo normal tracking 100 pions");
  col.push_back(kViolet); 
  */  
  /*
  finvec.push_back("newcuts_nodist_100pions_analyze_out/ntp_track_out.root  ");
  //legvec.push_back( "newcuts no dist/corr, 100 pions");
  legvec.push_back( "100 pions");
  col.push_back(kRed); 
  */

  
  /*
finvec.push_back("newbins_newcuts_nodist_100pions_analyze_out/ntp_track_out.root  ");
  //legvec.push_back( "newcuts no dist/corr, 100 pions");
  legvec.push_back( "new normal tracking 100 pions");
  col.push_back(kBlue); 
  */
  
  /*
  finvec.push_back("newcuts_truth_tpc_and_match_nodist_100pions_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "newcuts truth tpc and match no dist/corr, 100 pions");
  col.push_back(kMagenta); 
  */
  /*
  finvec.push_back("new_truth_tpc_and_match_nodist_100pions_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "truth tpc and match no dist/corr, 100 pions");
  col.push_back(kBlack); 
  */
  /*
  finvec.push_back("truth_tpc_nodist_100pions_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "truth tpc no dist/corr, 100 pions");
  col.push_back(kRed); 
  */
  /*
  finvec.push_back("nodist_100pions_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "repo normal tracking 100 pions");
  col.push_back(kViolet); 
  */

  

  /*
  finvec.push_back("static_dist_100pions_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "static dist/corr, 100 pions");
  col.push_back(kViolet); 
  */

  /*
  finvec.push_back("nopp_100pions_analyze_out/ntp_track_out.root  ");
  legvec.push_back( "nopp, 100 pions");
  col.push_back(kRed); 
  */

  /*  
  finvec.push_back("analyze_out_ppintt_latest/ntp_track_out.root  ");
  legvec.push_back( "latest pp mode, INTT time, ERO, 0-7 #mus cut");
  col.push_back(kRed); 
  */

  /*
  finvec.push_back("analyze_out_pp_intt/ntp_track_out.root  ");
  legvec.push_back( "pp mode, INTT time, ERO, 0-7 #mus cut");
  col.push_back(kBlack); 
  */

  /*
  finvec.push_back("analyze_out_pp_nointt_noround/ntp_track_out.root");
  legvec.push_back( "pp, no INTT time, ERO, 0-7 #mus cut");
  col.push_back(kRed); 
  */

  /*
  finvec.push_back("root_files/nointt_pp_truth_seeds_0_660evts_ntp_track_out.root");
  legvec.push_back( "pp mode, extended RO, 0-7 #mus cut");
  col.push_back(kRed); 
  */


  /*
  finvec.push_back("root_files/new_testz35mm_ppmode_gnmaps3_charm_3MHz_ntp_track_out.root");
  legvec.push_back( "new ppmode testz35mm charm 3 MHz gembed 1 gnmaps 3");
  col.push_back(kBlue); 
  */
  /*
  finvec.push_back("root_files/new_nonpp_gnmaps3_charm_3MHz_ntp_track_out.root");
  legvec.push_back( "new nonpp charm 3 MHz gembed 1 gnmaps 3");
  col.push_back(kGreen); 
  */
  /*
  finvec.push_back("root_files/repo_charm_3MHz_ntp_track_out.root");
  legvec.push_back( "new nonpp charm 3 MHz");
  col.push_back(kBlue); 
  */

  /*
  finvec.push_back("root_files/new_ppmode_gnmaps3_charm_3MHz_ntp_track_out.root");
  legvec.push_back( "new ppmode charm 3 MHz gembed 1 gnmaps 3");
  col.push_back(kRed); 
  */
  /*
  finvec.push_back("root_files/new_ppmode_charm_3MHz_ntp_track_out.root");
  legvec.push_back( "new ppmode charm 3 MHz gembed 1");
  col.push_back(kViolet); 
  */  
  /*
  finvec.push_back("root_files/new_nonpp_charm_3MHz_ntp_track_out.root");
  legvec.push_back( "repo charm 3MHz");
  col.push_back(kBlack); 

  finvec.push_back("root_files/new_nonpp_gnmaps3_charm_3MHz_ntp_track_out.root");
  legvec.push_back( "repo charm 3MHz gembed 1 gnmaps3");
  col.push_back(kBlack); 
  */
  /*
  finvec.push_back("root_files/new_nonpp_gnmaps_100pions_ntp_track_out.root");
  legvec.push_back( "100 pions non pp gnmaps 3");
  col.push_back(kBlack); 

  finvec.push_back("root_files/new_ppmode_gnmaps3_100pions_ntp_track_out.root");
  legvec.push_back( "100 pions ppmode gnmaps 3");
  col.push_back(kViolet); 
  */
  /*
  finvec.push_back("root_files/new_nonpp_static_distortions_100pions_ntp_track_out.root");
  legvec.push_back( "100 pions non pp static dist.");
  col.push_back(kViolet); 
  
  finvec.push_back("root_files/new_ppmode_static_distortions_100pions_ntp_track_out.root");
  legvec.push_back( "100 pions non pp static dist.");
  col.push_back(kMagenta); 
  
  finvec.push_back("root_files/repo_static_distortions_100pions_ntp_track_out.root");
  legvec.push_back( "100 pions non pp static dist.");
  col.push_back(kGreen); 
  

  finvec.push_back("root_files/repo_100pions_ntp_track_out.root");
  legvec.push_back( "100 pions repo code");
  col.push_back(kBlack); 
  */
  /*
  finvec.push_back("root_files/new_nonpp_100pions_ntp_track_out.root");
  legvec.push_back( "100 pions non pp mode");
  col.push_back(kBlue); 

  finvec.push_back("root_files/new_ppmode_100pions_ntp_track_out.root");
  legvec.push_back( "100 pions pp mode");
  col.push_back(kRed); 
  */

  /*
  finvec.push_back("analyze_out_pythia_charm_ppmode_gembed0/ntp_track_out.root");
  legvec.push_back( "charm pp mode  gembed < 1");
  col.push_back(kGreen); 
  */

  /*
  finvec.push_back("analyze_out_pythia_charm_ppmode_gembed1/ntp_track_out.root");
  legvec.push_back( "charm pp mode  gembed 1");
  col.push_back(kRed); 


  finvec.push_back("analyze_out_pythia_charm_nonppmode_gembed1/ntp_track_out.root");
  legvec.push_back( "charm auau mode  gembed 1");
  col.push_back(kBlue); 
  */

  /* 
  // This is a good repo  baseline
  finvec.push_back("analyze_out_repo_gembed1/ntp_track_out.root");
  legvec.push_back( "Repo D0 pileup gembed 1");
  col.push_back(kBlack); 

  // After successfully making triggered mode functionally identical to repo code
  finvec.push_back("fixed_D0_nonpp_mode_analyze_out/ntp_track_out.root");
  legvec.push_back( "new auau mode D0 pileup gembed 1");
  col.push_back(kBlue); 

  finvec.push_back("analyze_out_gembed0/ntp_track_out.root");
  legvec.push_back( "pp mode D0 pileup +/-2.5 microsec gembed < 1");
  col.push_back(kRed); 
  */

  /*
  finvec.push_back("root_files/pythia_jet_tmatch_test_ntp_track_out.root");
  legvec.push_back( "Pythia jet tbin matching");
  col.push_back(kViolet); 
  */

  /*
  finvec.push_back("root_files/current_performance_Oct24_2021_MB_Hijing_100pions_ntp_track_out.root");
  legvec.push_back( "Hijing + 50 KHz pileup + 100pions");
  col.push_back(kBlack); 
  */

  /*
  finvec.push_back("root_files/pythia_D0_pu_scanembed_ntp_track_out.root");
  legvec.push_back( "Pythia D0 PU scan embed");
  col.push_back(kGreen); 
  */

  /*
  finvec.push_back("root_files/PRcheck_pythia_single_dca80_qual5_nmaps3_equal_wt_pair_outlier_rejection_100_ntp_track_out.root");
  legvec.push_back( "Pythia jet vertexing PRcheck");
  col.push_back(kBlue); 
  */

  /*  
  // Best Rave reference
  finvec.push_back("root_files/pythia_single_Rave_nmaps3_ntp_track_out.root");
  legvec.push_back( "Pythia jet Rave nmaps3");
  col.push_back(kBlack); 
  */

  /*
  // qual 4, no change from qual 5
  finvec.push_back("root_files/pythia_single_dca80_qual4_nmaps3_equal_wt_pair_outlier_rejection_100_ntp_track_out.root");
  legvec.push_back( "Pythia jet pair outlier rej 100 qual 4");
  col.push_back(kBlue); 
  */

  /*
  finvec.push_back("root_files/pythia_single_Rave_nomaps_ntp_track_out.root");
  legvec.push_back( "Pythia jet Rave nomaps");
  col.push_back(kBlack); 
  */


  // S&C review plots
  bool sandc = false;
  if(sandc)
    {

      // MB tpctracker with vtxassoc and xy outlier rejection
      //finvec.push_back("root_files/vtxassoc_xyrej_800_norefit_ntpc15_tpctracker_0_20_0_20_default_wins_ntp_track_out.root");
      finvec.push_back("root_files/pions_0_20_0_20_xyrej800_25percent_ntp_track_out.root");
      legvec.push_back( "MB PHTpcTracker VtxAssoc xy outliers 800 #mum");
      col.push_back(kBlue);

      /*      
      // Central tpctracker with vtxassoc and xy outlier rejection
      //finvec.push_back("root_files/vtxassoc_xyrej_800_norefit_ntpc15_tpctracker_0_488_0_20_default_wins_ntp_track_out.root");
      finvec.push_back("root_files/pions_0_488_0_20_xyrej800_25percent_ntp_track_out.root");
      legvec.push_back( "Central PHTpcTracker VtxAssoc Reject XY outliers 800 #mum");
      col.push_back(kRed);      
      */
      /*
      // original CA seeder no rej
      finvec.push_back("root_files/nomapscut_0_20_0_20_wins_03_005_mag4_3gev_mag2_6gev_ntp_track_out.root");
      legvec.push_back( "MB CA wins 03 005 mag 2 6GeV mag4 3gev_nomapscut");
      col.push_back(kBlack);
      */
    }

  //==========


  unsigned int nfiles = finvec.size();

  TCanvas *cxvtres = new TCanvas("cxvtres","cxvtres", 5, 5, 1600,800);
  cxvtres->Divide(2,1);
  cxvtres->cd(1);
  gPad->SetLeftMargin(0.18);
  cxvtres->cd(2);
  gPad->SetLeftMargin(0.18);
  TCanvas *cntpc = new TCanvas("cntpc","number of TPC clusters",5,5,1600,800);
  cntpc->Divide(nfiles,1);
  TCanvas *cnvtx = new TCanvas("cnvtx","number of collision vertices",5,5,1600,800);
  cnvtx->Divide(nfiles,1);
 TCanvas *cgvt = new TCanvas("cgvt","signal vertex time",5,5,1600,800);
 cgvt->Divide(nfiles,1);
 TCanvas *cgvt_pu = new TCanvas("cgvt_pu","pileup vertex time",5,5,1600,800);
 cgvt_pu->Divide(nfiles,1);
 TCanvas *cnvtxtracks = new TCanvas("cnvtxtracks","number of tracks per signal vertex",5,5,1600,800);
 cnvtxtracks->Divide(nfiles,1);
 TCanvas *cnvtxtracks_pu = new TCanvas("cnvtxtracks_pu","number of tracks per pileup vertex",5,5,1600,800);
  cnvtxtracks_pu->Divide(nfiles,1);
  TCanvas *cmaps_geta = new TCanvas("cmaps_geta","maps association vs geta",5,5,1600,800);
  cmaps_geta->Divide(nfiles,1);
  TCanvas *cmaps_gvz = new TCanvas("cmaps_gvz","maps association vs gz",5,5,1600,800);
  cmaps_gvz->Divide(nfiles,1);
  TCanvas *cxvtx = new TCanvas("cxvtx","cxvtx",5,5,1600,800);
  cxvtx->Divide(nfiles,1);
  TCanvas *cyvtx = new TCanvas("cyvtx","cyvtx",5,5,1600,800);
  cyvtx->Divide(nfiles,1);
  TCanvas *czvtx = new TCanvas("czvtx","czvtx",5,5,1600,800);
  czvtx->Divide(nfiles,1);
  TCanvas *cvtxerr_x = new TCanvas("cvtxerr_x","cvtxerr X",5,5,1600,1200);
  TCanvas *cvtxerr_y = new TCanvas("cvtxerr_y","cvtxerr Y",5,5,1600,1200);
  TCanvas *cvtxerr_z = new TCanvas("cvtxerr_z","cvtxerr Z",5,5,1600,1200); 
  TCanvas *ctemp0 = new TCanvas("ctemp0","ctemp0",5,5,1600,800);
  ctemp0->Divide(nfiles,1);
  TCanvas *cslice = new TCanvas("cslice","cslice",5,5,1600,800);
  cslice->Divide(nfiles,1);
  TCanvas *cpt = new TCanvas("cpt","cpt",5,5,1600,1200); 
  //cpt->Divide(2,1);
  cpt->cd(); gPad->SetLeftMargin(0.2);
  //cpt->cd(2); gPad->SetLeftMargin(0.2);
  TCanvas *ceff = new TCanvas("ceff","ceff",5,5,1200,800);
  ceff->SetLeftMargin(0.18);
  TCanvas *ctemp1 = new TCanvas("ctemp1","ctemp1",5,5,1200,800);
  ctemp1->Divide(nfiles,1);
  TCanvas *cslicexy = new TCanvas("cslicexy","cslicexy",5,5,1600,800);
  cslicexy->Divide(nfiles,1);
  TCanvas *cdcaxy = new TCanvas("cdcaxy","cdcaxy",5,5,1200,800); 
  cdcaxy->SetLeftMargin(0.2);
  gPad->SetGrid();
  TCanvas *ctemp2 = new TCanvas("ctemp2","ctemp2",5,5,1200,800);
  ctemp2->Divide(nfiles,1);
  TCanvas *csliceZ = new TCanvas("csliceZ","csliceZ",5,5,1600,800);
  csliceZ->Divide(nfiles,1);
  TCanvas *cdcaZ = new TCanvas("cdcaZ","cdcaZ",5,5,1200,800); 
  cdcaZ->SetLeftMargin(0.2);
  gPad->SetGrid();
  TCanvas *cmvtx= new TCanvas("cmvtx","cmvtx",5,5,1200,800);
  cmvtx->SetLeftMargin(0.2);
  TCanvas *ccomb= new TCanvas("ccomb","ccomb",5,5,1200,800);
  ccomb->SetLeftMargin(0.2);
  TCanvas *cqual = new TCanvas("cqual","cqual");
  cqual->Divide(nfiles,1);
TCanvas *ccrossing = new TCanvas("ccrossing","ccrossing",5,5,800,800);
ccrossing->Divide(nfiles,2);
TCanvas *ctrgvt = new TCanvas("ctrgvt","ctrgvt",5,5,1200,800);
  ctrgvt->Divide(nfiles,1);

  TLegend *lpd = new TLegend(0.3, 0.4, 0.85, 0.5, "", "NDC");
  lpd->SetBorderSize(1);
  lpd->SetFillColor(kWhite);
  lpd->SetFillStyle(1001);


  TLegend *lvtxerr_x = new TLegend(0.1, 0.88, 0.9, 0.96, "", "NDC");
  lvtxerr_x->SetBorderSize(1);
  lvtxerr_x->SetFillColor(kWhite);
  lvtxerr_x->SetFillStyle(1001);
  TLegend *lvtxerr_y = new TLegend(0.1, 0.88, 0.9, 0.96, "", "NDC");
  lvtxerr_y->SetBorderSize(1);
  lvtxerr_y->SetFillColor(kWhite);
  lvtxerr_y->SetFillStyle(1001);
  TLegend *lvtxerr_z = new TLegend(0.1, 0.88, 0.9, 0.96, "", "NDC");
  lvtxerr_z->SetBorderSize(1);
  lvtxerr_z->SetFillColor(kWhite);
  lvtxerr_z->SetFillStyle(1001);

  TF1 *fz = new TF1("fz","gaus");
  fz->SetRange(-0.02, 0.02);

  for(unsigned int i=0; i<finvec.size();++i)
    {
      TLatex *lat = new TLatex(0.2,0.6,legvec[i].c_str());
      lat->SetNDC();

      TFile *fin = new TFile(finvec[i].c_str());

      TH1D *hnvtx;
      fin->GetObject("hnvtx",hnvtx);
      if(hnvtx)
	{
	  cnvtx->cd(i+1);
	  hnvtx->Draw();
	}

      TH1D *hnvtxtracks;
      fin->GetObject("hnvtxtracks",hnvtxtracks);
      if(hnvtxtracks)
	{
	  cnvtxtracks->cd(i+1);
	  hnvtxtracks->GetXaxis()->SetRangeUser(0, 100);
	  hnvtxtracks->GetXaxis()->SetTitle("Tracks per vertex");
	  hnvtxtracks->DrawCopy();
	  //lat->Draw();
	}

      TH1D *hnvtxtracks_pu;
      fin->GetObject("hnvtxtracks_pu",hnvtxtracks_pu);
      if(hnvtxtracks_pu)
	{
	  cnvtxtracks_pu->cd(i+1);
	  hnvtxtracks_pu->GetXaxis()->SetRangeUser(0, 30);
	  hnvtxtracks->GetXaxis()->SetTitle("Tracks per vertex");
	  hnvtxtracks_pu->Draw();
	}

      TH1D *hgvt;
      fin->GetObject("hgvt",hgvt);
      if(hgvt)
	{
	  std::cout << " Found hgvt " << std::endl;
	  cgvt->cd(i+1);
	  hgvt->GetXaxis()->SetNdivisions(504); 
	  hgvt->GetXaxis()->SetTitle("time (ns)");
	  hgvt->DrawCopy();
	}

      TH1D *hgvt_pu;
      fin->GetObject("hgvt_pu",hgvt_pu);
      if(hgvt_pu)
	{
	  cgvt_pu->cd(i+1);
	  hgvt_pu->GetXaxis()->SetNdivisions(504); 
	  hgvt_pu->GetXaxis()->SetTitle("time (ns)");
	  hgvt_pu->GetXaxis()->SetRangeUser(-10, 12000.0);
	  hgvt_pu->DrawCopy();
	}

      TH2D *hcrossing_vs_gvt;
      fin->GetObject("hcrossing_vs_gvt",hcrossing_vs_gvt);
      if(hcrossing_vs_gvt)
	{
	  std::cout << "Found hcrossing_vs_gvt " << std::endl;
	  ccrossing->cd(2*i+1);
	  hcrossing_vs_gvt->GetXaxis()->SetTitle("eta");
	  hcrossing_vs_gvt->GetYaxis()->SetTitle("gvt");
	  hcrossing_vs_gvt->DrawCopy();
	}

      TH2D *hcrossing_vs_eta;
      fin->GetObject("hcrossing_vs_eta",hcrossing_vs_eta);
      if(hcrossing_vs_eta)
	{
	  std::cout << "Found hcrossing_vs_eta " << std::endl;
	  ccrossing->cd(2*i+2);
	  hcrossing_vs_eta->GetXaxis()->SetTitle("eta");
	  hcrossing_vs_eta->GetYaxis()->SetTitle("crossing");
	  hcrossing_vs_eta->DrawCopy();
	}

      TH1D *htrgvt;
      fin->GetObject("htrgvt",htrgvt);
      if(htrgvt)
	{
	  std::cout << "Found htrgvt " << std::endl;
	  ctrgvt->cd(i+1);
	  htrgvt->DrawCopy();
	}

      TH1D *hntpc;
      fin->GetObject("hntpc",hntpc);
      if(hntpc)
	{
	  cntpc->cd(i+1);
	  gPad->SetLeftMargin(0.15);
	  hntpc->GetXaxis()->SetTitle("layer");
	  //hntp->GetYaxis()->SetTitle("layer");
	  hntpc->Draw();
	  lat->Draw();
	}

      TH1D *hqual;
      fin->GetObject("hqual",hqual);
      if(hqual)
	{
	  cqual->cd(i+1);
	  hqual->GetXaxis()->SetTitle("quality");
	  hqual->Draw();
	}


      TH1D *hzvt;
      fin->GetObject("hzvt",hzvt); 
      if(hzvt)
	{
	  czvtx->cd(i+1);
	  hzvt->Draw();\
	}

      TH1D *hxvt;
      fin->GetObject("hxvt",hxvt); 
      if(hxvt)
	{
	  cxvtx->cd(i+1);
	  hxvt->Draw();
	  std::cout << " hxvt mean " << hxvt->GetMean() << " RMS " << hxvt->GetRMS() << std::endl;
	}

      TH1D *hyvt;
      fin->GetObject("hyvt",hyvt); 
      if(hyvt)
	{
	  cyvtx->cd(i+1);
	  hyvt->Draw();
	  std::cout << " hyvt mean " << hyvt->GetMean() << " RMS " << hyvt->GetRMS() << std::endl;
	}


      cvtxerr_x->cd(); gPad->SetLogy(1);
      cvtxerr_y->cd(); gPad->SetLogy(1);
      cvtxerr_z->cd(); gPad->SetLogy(1);

      double scale_factor = 0.9;   // 0.9 best
      double vtxerr_range = 0.02;

      char tmp[500];
      TH1D *hxvterr;
      fin->GetObject("hxvterr",hxvterr); 
      if(hxvterr)
	{
	  if(i==1) hxvterr->Scale(scale_factor);
	  hxvterr->GetXaxis()->SetRangeUser(-vtxerr_range, vtxerr_range);
	  cvtxerr_x->cd( );
	  hxvterr->SetLineWidth(2);
	  hxvterr->SetMarkerStyle(20);
	  hxvterr->SetMarkerSize(1);
	  hxvterr->SetLineColor(col[i]);
	  std::cout << " plotting hxvterr for file " << i << " on pad " << i+1 << std::endl; 
	  if(i==0)
	    hxvterr->Draw();
	  else
	    hxvterr->Draw("same");
	  
	  //  int nv = hxvterr->GetEntries();
	  //sprintf(tmp," nv: %i RMS: %.4f",nv, sigma);
	  double sigma = hxvterr->GetRMS();
	  sprintf(tmp," RMS: %.5f",sigma);
	  std::string all = legvec[i] + tmp;
	  lvtxerr_x->AddEntry(hxvterr, all.c_str(),"l");

	}
      TH1D *hyvterr;
      fin->GetObject("hyvterr",hyvterr); 
      if(hyvterr)
	{
	  if(i==1) hyvterr->Scale(scale_factor);
	  hyvterr->GetXaxis()->SetRangeUser(-vtxerr_range, vtxerr_range);

	  cvtxerr_y->cd();
	  hyvterr->SetLineWidth(2);
	  hyvterr->SetMarkerStyle(20);
	  hyvterr->SetMarkerSize(1);
	  hyvterr->SetLineColor(col[i]);
	  std::cout << " plotting hyvterr for file " << i << " on pad " << i+2 << std::endl; 
	  if(i==0)
	    hyvterr->Draw();
	  else
	    hyvterr->Draw("same");

	  double sigma = hyvterr->GetRMS();
	  sprintf(tmp," RMS: %.5f",sigma);
	  std::string all = legvec[i] + tmp;
	  lvtxerr_y->AddEntry(hxvterr, all.c_str(),"l");
	}


      TH1D *hzvterr;
      fin->GetObject("hzvterr",hzvterr); 
      if(hzvterr)
	{
	  if(i==1) hzvterr->Scale(scale_factor);
	  hzvterr->GetXaxis()->SetRangeUser(-vtxerr_range, vtxerr_range);
	  cvtxerr_z->cd();
	  hzvterr->SetLineWidth(2);
	  hzvterr->SetMarkerStyle(20);
	  hzvterr->SetMarkerSize(1);
	  hzvterr->SetLineColor(col[i]);
	  std::cout << " plotting hzvterr for file " << i << " on pad " << 3 << std::endl; 
	  if(i==0)
	    hzvterr->Draw();
	  else
	    hzvterr->Draw("same");

	  double sigma = hzvterr->GetRMS();
	  sprintf(tmp," RMS: %.5f",sigma);
	  std::string all = legvec[i] + tmp;
	  lvtxerr_z->AddEntry(hxvterr, all.c_str(),"l");
	}


      cvtxerr_x->cd(); lvtxerr_x->Draw();
      cvtxerr_y->cd(); lvtxerr_y->Draw();
      cvtxerr_z->cd(); lvtxerr_z->Draw();


      // mvtx association
      cmaps_geta->cd(i+1);
      TH2D *hnmeta2d;
      fin->GetObject("hnmaps_vs_geta",hnmeta2d);
      if(hnmeta2d)
	{

	  int nlow = hnmeta2d->GetYaxis()->FindBin(2.5);
	  int nhigh = hnmeta2d->GetYaxis()->FindBin(3.5);
	  /*
	  int nlow = hnmeta2d->GetYaxis()->FindBin(-0.5);
	  int nhigh = hnmeta2d->GetYaxis()->FindBin(0.5);
	  */
	  cout << "nlow " << nlow << " nhigh " << nhigh << endl;
	  char hname[500];
	  sprintf(hname,"hnmeta%i",i);
	  TH1D *hnmeta = hnmeta2d->ProjectionX(hname,nlow,nhigh); 
	  hnmeta->DrawCopy();
	}
      else
	{
	  cout << "Failed to find histogram hnmaps_vs_geta" << endl;
	}

      cmaps_gvz->cd(i+1);
      TH2D *hnmgvz2d;
      fin->GetObject("hnmaps_vs_gvz",hnmgvz2d);
      if(hnmgvz2d)
	{
	  /*
	  int nlow = hnmgvz2d->GetYaxis()->FindBin(2.5);
	  int nhigh = hnmgvz2d->GetYaxis()->FindBin(3.5);
	  */
	  int nlow = hnmgvz2d->GetYaxis()->FindBin(-0.5);
	  int nhigh = hnmgvz2d->GetYaxis()->FindBin(0.5);

	  cout << "nlow " << nlow << " nhigh " << nhigh << endl;
	  char hname[500];
	  sprintf(hname,"hnmgvz%i",i);
	  TH1D *hnmgvz = hnmgvz2d->ProjectionX(hname,nlow,nhigh); 
	  hnmgvz->DrawCopy();
	}
      else
	{
	  cout << "Failed to find histogram hnmaps_vs_gvz" << endl;
	}

      // pT resolution

      TH2D *hpt2d;
      fin->GetObject("h1",hpt2d); 
      std::cout << hpt2d->GetEntries() << std::endl;
      hpt2d->FitSlicesY();
      TH1D *hptres =  (TH1D*)gDirectory->Get("h1_2");
      TH1D *hptcent = (TH1D*)gDirectory->Get("h1_1");
      ctemp0->cd(i+1);
      hpt2d->Draw("colz");

      int binlow = hpt2d->GetXaxis()->FindBin(slice_low);
      int binhigh = hpt2d->GetXaxis()->FindBin(slice_high);
      char hname[500];
      sprintf(hname,"hptslice%i",i);
      TH1D *hptslice = hpt2d->ProjectionY(hname,binlow, binhigh);
      cslice->cd(i+1);
      hptslice->DrawCopy();
      hptslice->Fit("gaus");

      cpt->cd();
      hptres->GetYaxis()->SetTitleOffset(2.1);
      hptres->GetXaxis()->SetTitleOffset(1.2);
      hptres->SetMarkerStyle(20);
      hptres->SetMarkerSize(1.2);
      hptres->SetMarkerColor(col[i]);
      hptres->GetXaxis()->SetRangeUser(0, ptmax);
      hptres->GetYaxis()->SetRangeUser(0.0, 0.04);
      hptres->SetTitle(";p_{T} [GeV/c];#frac{#Delta p_{T}}{p_{T}} (resolution)");
      if(i == 0)
	hptres->DrawCopy("p");
      else
	hptres->DrawCopy("p same");

      lpd->AddEntry(hptres, legvec[i].c_str(), "p");
      /*
      cpt->cd(2);
      hptcent->GetYaxis()->SetTitleOffset(2.1);
      hptcent->GetXaxis()->SetTitleOffset(1.2);
      hptcent->SetMarkerStyle(20);
      hptcent->SetMarkerSize(1.2);
      hptcent->SetMarkerColor(col[i]);
      hptcent->GetXaxis()->SetRangeUser(0, ptmax);
      hptcent->GetYaxis()->SetRangeUser(-0.1, 0.1);
      hptcent->SetTitle(";p_{T} [GeV/c];#frac{#Delta p_{T}}{p_{T}} (offset)");
      if(i==0)
	hptcent->DrawCopy("p");
      else
	hptcent->DrawCopy("p same");
      */

      // vertex resolutions vs ntracks
      TH2D *hxvterr_2d;
      fin->GetObject("hxvterr_2d",hxvterr_2d); 
      if(hxvterr_2d)
	{
	  cxvtres->cd(1);
	  hxvterr_2d->FitSlicesY();
	  TH1D *hxvtres =  (TH1D*)gDirectory->Get("hxvterr_2d_2");
	  TH1D *hxvtcent = (TH1D*)gDirectory->Get("hxvterr_2d_1");
	  hxvtres->GetYaxis()->SetTitleOffset(2.0);
	  hxvtres->GetXaxis()->SetTitleOffset(1.2);
	  hxvtres->SetMarkerStyle(20);
	  hxvtres->SetMarkerSize(1.2);
	  hxvtres->SetMarkerColor(col[i]);
	  hxvtres->GetYaxis()->SetRangeUser(0.0, 0.006);
	  hxvtres->GetYaxis()->SetTitle("Vertex #Deltax");
	  hxvtres->GetXaxis()->SetTitle("ntracks");
	  if(i==0)
	    hxvtres->DrawCopy();
	  else
	    hxvtres->Draw("same");
	}

      // vertex resolutions vs ntracks
      TH2D *hzvterr_2d;
      fin->GetObject("hzvterr_2d",hzvterr_2d); 
      if(hzvterr_2d)
	{
	  cxvtres->cd(2);
	  hzvterr_2d->FitSlicesY();
	  TH1D *hzvtres =  (TH1D*)gDirectory->Get("hzvterr_2d_2");
	  TH1D *hzvtcent = (TH1D*)gDirectory->Get("hzvterr_2d_1");
	  hzvtres->GetYaxis()->SetTitleOffset(2.0);
	  hzvtres->GetXaxis()->SetTitleOffset(1.2);
	  hzvtres->SetMarkerStyle(20);
	  hzvtres->SetMarkerSize(1.2);
	  hzvtres->SetMarkerColor(col[i]);
	  hzvtres->GetYaxis()->SetRangeUser(0.0, 0.006);
	  hzvtres->GetYaxis()->SetTitle("Vertex #Deltaz");
	  hzvtres->GetXaxis()->SetTitle("ntracks");
	  if(i==0)
	    hzvtres->DrawCopy();
	  else
	    hzvtres->Draw("same");
	}

      // Efficiency
      ceff->cd();
      TH1D *hnum = 0;
      TH1D *hden = 0;
      fin->GetObject("h3_num",hnum);
      fin->GetObject("h3_den",hden);

      TH1D* heff = (TH1D*)hden->Clone("heff");;

      for(int ib=1;ib<=hden->GetNbinsX();++ib)
	{
	  double pass = hnum->GetBinContent(ib);
	  double all = hden->GetBinContent(ib);
	  double eff = 0;
	  if(all > pass)
	    eff = pass/all;
	  else if(all > 0)
	    eff = 1.;
	  heff->SetBinContent(ib, eff);
	}  

      heff->SetTitle("MB Hijing + 50 KHz pileup + 100 pions");
      heff->GetYaxis()->SetTitle("Efficiency");
      heff->GetYaxis()->SetTitleOffset(1.5);
      heff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
      heff->GetXaxis()->SetTitleOffset(1.2);
      heff->SetMarkerStyle(20);
      heff->SetMarkerSize(1.5);
      heff->SetMarkerColor(col[i]);
      heff->GetXaxis()->SetRangeUser(0.0, ptmax);
      heff->GetYaxis()->SetRangeUser(0.0, 1.0);
      if(i==0)
	heff->DrawCopy("p");
      else
	heff->DrawCopy("p same");

      TLine *unit = new TLine(0,1.0,ptmax,1.0);
      //unit->Draw();

      // dca xy resolution
      cdcaxy->cd();
      TH2D *hdca2d;
      fin->GetObject("h2",hdca2d);
      ctemp1->cd(i+1);
      hdca2d->Draw("colz");

      binlow = hdca2d->GetXaxis()->FindBin(slice_low);
      binhigh = hdca2d->GetXaxis()->FindBin(slice_high);
      TH1D* hdcaxyslice = hdca2d->ProjectionY("hdcaxyslice",binlow, binhigh);
      hdcaxyslice->SetLineColor(col[i]);      
      cslicexy->cd(i+1);
      hdcaxyslice->Draw();
      hdcaxyslice->Fit("gaus");

      cdcaxy->cd();  
      TF1 *f1 = new TF1("f1","gaus");
      f1->SetRange(-0.01, 0.01);
       hdca2d->FitSlicesY(f1);
       TH1D*hdcares = (TH1D*)gDirectory->Get("h2_2");
      hdcares->GetYaxis()->SetTitleOffset(2.1);
      hdcares->GetYaxis()->SetTitle("DCA(r#phi) (cm)");
      hdcares->GetXaxis()->SetTitleOffset(1.2);
      hdcares->GetXaxis()->SetTitle("p_{T} (GeV/c)");
      hdcares->SetMarkerStyle(20);
      hdcares->SetMarkerSize(1.2);
      hdcares->SetMarkerColor(col[i]);
      hdcares->GetYaxis()->SetRangeUser(0, 0.008);
      hdcares->GetXaxis()->SetRangeUser(0, ptmax);
      if(i==0) 
	hdcares->DrawCopy("p");
      else
	hdcares->DrawCopy("p same");

      // dca z resolution
      TH2D *hdcaZ2d;
      fin->GetObject("h3",hdcaZ2d);
      ctemp2->cd(i+1);
      hdcaZ2d->Draw("colz");

      binlow = hdcaZ2d->GetXaxis()->FindBin(slice_low);
      binhigh = hdcaZ2d->GetXaxis()->FindBin(slice_high);
      TH1D* hdcazslice = hdcaZ2d->ProjectionY("hdcazslice",binlow, binhigh);
      hdcazslice->SetLineColor(col[i]);      
      csliceZ->cd(i+1);
      hdcazslice->Draw();
      hdcazslice->Fit("gaus");

      cdcaZ->cd();
      hdcaZ2d->FitSlicesY(fz);
      TH1D* hdcaZres = (TH1D*)gDirectory->Get("h3_2");

      hdcaZres->GetYaxis()->SetTitleOffset(2.1);
      hdcaZres->GetYaxis()->SetTitle("DCA(Z) (cm)");
      hdcaZres->GetXaxis()->SetTitleOffset(1.2);
      hdcaZres->GetXaxis()->SetTitle("p_{T} (GeV/c");
      hdcaZres->SetMarkerStyle(20);
      hdcaZres->SetMarkerSize(1.2);
      hdcaZres->SetMarkerColor(col[i]);
      hdcaZres->GetYaxis()->SetRangeUser(0, 0.008);
      hdcaZres->GetXaxis()->SetRangeUser(0, ptmax);
      if(i==0)      
	hdcaZres->DrawCopy("p");
      else
	hdcaZres->DrawCopy("p same");

      // Plot the fraction of tracks matched to the MVTX
      cmvtx->cd();
      TH2D *hnmvtx = 0;
      fin->GetObject("h6",hnmvtx);
      if(!hnmvtx) cout << " Did not get hnmvtx" << endl;

      //hnmvtx->DrawCopy("p");

      binlow = hnmvtx->GetYaxis()->FindBin(2.5);
      binhigh = hnmvtx->GetYaxis()->FindBin(5.5);
      cout << "binlow " << binlow << " binhigh " << binhigh << endl;
      TH1D *hnmaps_hit = hnmvtx->ProjectionX("hnmaps_hit",binlow, binhigh);;

      binlow = hnmvtx->GetYaxis()->FindBin(-0.5);
      binhigh = hnmvtx->GetYaxis()->FindBin(5.5);
      cout << "binlow " << binlow << " binhigh " << binhigh << endl;
      TH1D *hnmaps_all = hnmvtx->ProjectionX("hnmaps_all",binlow, binhigh);;

      TH1D *hnmaps = (TH1D*) hnmaps_all->Clone();
      for(int ib=1;ib<=hnmaps_hit->GetNbinsX();++ib)
	{
	  double hit = hnmaps_hit->GetBinContent(ib);
	  double all = hnmaps_all->GetBinContent(ib);
	  double eff = 0;
	  if(all > hit)
	    eff = hit/all;
	  else if(all > 0)
	    eff = 1.;
	  hnmaps->SetBinContent(ib, eff);
	}  

      hnmaps->GetXaxis()->SetTitle("p_{T} (GeV/c)");
      hnmaps->GetYaxis()->SetTitle("MVTX association efficiency");
      hnmaps->GetYaxis()->SetTitleOffset(1.5);
      hnmaps->GetXaxis()->SetTitleOffset(1.2);
      hnmaps->GetXaxis()->SetRangeUser(0.0, ptmax);
      hnmaps->SetMinimum(0);
      hnmaps->SetMaximum(1.0);
      hnmaps->SetMarkerStyle(20);
      hnmaps->SetMarkerSize(1.5);
      hnmaps->SetMarkerColor(col[i]);

      if(i==0)
	{
	  hnmaps->DrawCopy("p");
	  unit->Draw();
	}
      else
      hnmaps->DrawCopy("p same");

      // Combine track efficiency and MVTX association efficiency

      ccomb->cd();

      cout << " hnmaps bins " << hnmaps->GetNbinsX() << " heff bins " << heff->GetNbinsX() << endl;
      heff->Rebin(1);
      cout << heff->GetNbinsX() << endl;

      TH1D *hcomb = (TH1D*) hnmaps->Clone();
      for(int icomb=1; icomb<= hnmaps->GetNbinsX(); ++icomb)
	{
	  double vmaps = hnmaps->GetBinContent(icomb);
	  double vtrack = heff->GetBinContent(icomb);
	  double eff = 0;
	  eff = vmaps * vtrack;
	  //cout << " icomb " << icomb << " vmaps " << vmaps << " vtrack " << vtrack << " comb " << eff << endl;
	  hcomb->SetBinContent(icomb, eff);
	}  

      hcomb->GetXaxis()->SetRangeUser(0,ptmax);	  
      hcomb->GetYaxis()->SetTitle("Efficiency for MVTX associated tracks");

      TLine *unit2 = new TLine(0,1.0,ptmax,1.0);

      if(i==0)
	{
	  hcomb->DrawCopy("p");
	  unit2->Draw();
	}
      else
      hcomb->DrawCopy("p same");

    }
  
  cpt->cd();  lpd->Draw();

  cxvtres->cd(1);  lpd->Draw();
  cxvtres->cd(2);  lpd->Draw();
  
  cdcaxy->cd();  lpd->Draw();
  
  cdcaZ->cd();  lpd->Draw();
  
  ceff->cd();  lpd->Draw();
  
  cmvtx->cd();  lpd->Draw();
  
  ccomb->cd();  lpd->Draw();
  
  
  
}

