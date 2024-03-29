#include <TChain.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLegend.h>
#include <TLine.h>
#include <TLatex.h>
#include <TRandom1.h>
#include <TPolyLine.h>
#include <iostream>
#include <fstream>
#include <TMath.h>
//#include <iomanip.h>
#include <TLorentzVector.h>

//#define TEST

void quarkonia_reconstruction_embedded_pp()
{
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1);
  gStyle->SetOptTitle(1);

  int verbose = 0;
  int embed_flag = 1;  // embedding flag used during Upsilon generation

  // track cuts  
  //double quality_cut = 3.0;
  double quality_cut = 10.0;
  //double quality_cut = 7.0;
  double dca3dxy_cut = 0.1;
  double dca3dz_cut = 0.1;
  double nmaps_cut = 3;
  double ptcut = 1.0;
  double etacut = 1.2;
  double ntpc_cut = 30;
 
  char lepton[100];
  sprintf(lepton,"electron");
  
  double decaymass=0.000511;
  cout << "Assuming decay particle mass is " << decaymass << endl;

  // Define some histograms
  
  int nbpt = 20;
  double ptmax = 10.0;

  TH1F* hrquality = new TH1F("hrquality", "Reconstructed track Quality", 1000, 0, 10);
  TH1F* hrdca3dxy = new TH1F("hrdca3dxy", "Reconstructed track dca3dxy", 1000, 0, 0.05);
  TH1F* hrdca3dz = new TH1F("hrdca3dz", "Reconstructed track dca3dz", 1000, 0, 0.05);
  TH1F* hrpt = new TH1F("hrpt"," pT", nbpt, 0.0, ptmax);
  TH1F* hgpt = new TH1F("hgpt","g4 pT", nbpt, 0.0, ptmax);

  TH1D *g4mass = new TH1D("g4mass","G4 input invariant mass",200,7.0,11.0);
  g4mass->GetXaxis()->SetTitle("invariant mass (GeV/c^{2})");
  TH1D *g4mass_primary = new TH1D("g4mass_primary","G4 input invariant mass",200,7.0,11.0);
  g4mass_primary->GetXaxis()->SetTitle("invariant mass (GeV/c^{2})");

  TH1D *recomass = new TH1D("recomass","Reconstructed invariant mass",200,7.0,11.0);
  recomass->GetXaxis()->SetTitle("invariant mass (GeV/c^{2})");
  TH1D *recomass_primary = new TH1D("recomass_primary","Reconstructed invariant mass",200,7.0,11.0);
  recomass_primary->GetXaxis()->SetTitle("invariant mass (GeV/c^{2})");

  int ups_state = 1;   // used in naming of output files
  //int ups_state = 2;   // used in naming of output files
  //int ups_state = 3;   // used in naming of output files

  // Number of upsilons to process - quit after this number is reached
  int nups_requested = 0;
  double pair_acc = 0.60 * 0.9 * 0.98;  // fraction into 1 unit of rapidity * pair eID fraction * trigger fraction 
  // These values are for 1 year of pp running
  if(ups_state == 1)  nups_requested = pair_acc * (8769 * 1.126) / (0.38 * 0.9 * 0.98);  // pair_acc * yield for 197 /pb (= 15590)
  if(ups_state == 2)  nups_requested = pair_acc * (2205 * 1.126) / (0.38 * 0.9 * 0.98); //  pair_acc * yield for 197 /pb (= 3920)
  if(ups_state == 3)  nups_requested = pair_acc * (1156 * 1.126) / (0.38 * 0.9 * 0.98); //  pair_acc * yield for 197 /pb (=2055) 

  nups_requested = 100000;  // take them all
 
  cout << "ups_state = " << ups_state << " Upsilons requested = " << nups_requested << endl;

  int nrecog4mass = 0;
  int nrecormass = 0;
  int nevents = 0;
  
  // Open the g4 evaluator output file
  cout << "Reading electron ntuples " << endl; 

  // The condor job output files -  we open them one at a time and process them
  for(int ifile=0;ifile<2000;ifile++)
    {
      if(nrecormass > nups_requested)
	{
	  cout << "Reached requested number of reco Upsilons, quit out of file loop" << endl;
	  break;
	}
      
      char name[500];

      //sprintf(name,"/sphenix/user/frawley/new_macros_april27/macros/detectors/sPHENIX/eval_output/g4svtx_eval_%i.root",ifile);
      sprintf(name,"/sphenix/user/frawley/new_macros_april27/macros/detectors/sPHENIX/eval_output/eval_out_%i.root",ifile);

      cout << "Adding file " << name << endl;

      TChain* ntp_track = new TChain("ntp_track","reco tracks");
      TChain* ntp_gtrack = new TChain("ntp_gtrack","g4 tracks");
      TChain* ntp_vertex = new TChain("ntp_vertex","events");
      TChain *ntp_cluster = new TChain("ntp_cluster","clusters");
      TChain *ntp_g4hit = new TChain("ntp_g4hit","G4 hits");
      
      ntp_vertex->Add(name);
      ntp_track->Add(name);
      ntp_gtrack->Add(name);


      cout << "ntp_track contains " << ntp_track->GetEntries() << " entries " 
	   << " ntp_gtrack contains " << ntp_gtrack->GetEntries() << " entries " << endl;


      // Ntuple access variables
      // This include file contains the definitions of the ntuple variables                                                                        
#include "ntuple_variables.C"
    
      //=======================
      // Loop over events
      //=======================

      ntracks = ntp_track->GetEntries();
      ngtracks = ntp_gtrack->GetEntries();

      int nr = 0;
      int ng = 0;

      //============================
      // process G4 tracks
      // for this event
      //============================

      int iev = 0;

      int ng4trevt_elec = 0;
      int ng4trevt_pos = 0;
      int g4trnum_elec[1000] = {0};
      int g4trnum_pos[1000] = {0};

      for(int ig=0;ig<ngtracks;ig++)
	{
	  int recoget1 = ntp_gtrack->GetEntry(ig);
	  if(!recoget1)
	    {
	      //if(verbose > 0) 
	      cout << "Did not get entry for ig = " << ig << endl;
	      break;
	    }

	  if(tpt < 1.0)
	    continue;

	  //std::cout << " found ig = " << ig << " tevent " << tevent << " ng " << ng << " ngtracks " << ngtracks << std::endl;

	  // This bookkeeping is needed because the evaluator records for each event the total track count in ntp_vertex, even 
	  // when it writes out only embedded tracks
	  if(tevent != iev || ig == ngtracks-1)
	    {
	      if(verbose > 0) 
		cout << " reached new event for ig = " << ig << " tevent = " << tevent << endl; 
	    
	      if(verbose)
	      cout << "For file " << ifile << " event " << iev << " found " << ng4trevt_elec << " g4 electrons and " << ng4trevt_pos << " g4 positrons"  << endl;
	      iev++;
  
	      // make all pairs of g4 (truth) electrons and positrons
	      for(int ielec=0;ielec<ng4trevt_elec;ielec++)
		{
		  int recoelec = ntp_gtrack->GetEntry(g4trnum_elec[ielec]);
		  
		  double elec_pT = sqrt(tpx*tpx+tpy*tpy);
		  double elec_eta = asinh(tpz/sqrt(tpx*tpx+tpy*tpy));
		  
		  int gtrid1 = tgtrackid;
		  
		  TLorentzVector t1;
		  double E1 = sqrt( pow(tpx,2) + pow(tpy,2) + pow(tpz,2) + pow(decaymass,2));	  
		  t1.SetPxPyPzE(tpx,tpy,tpz,E1);	  
		  
		  // print out track details
		  if(verbose > 1)
		    cout << "  Pair electron:  iev " << iev << " ielec " << ielec
			 << " g4trnum_elec " << g4trnum_elec[ielec]
			 << " tgtrackid " << tgtrackid
			 << " tflavor " << tflavor
			 << " tpx " << tpx
			 << " tpy " << tpy
			 << " tpz " << tpz
			 << " elec_eta " << elec_eta
			 << " elec_gpT " << elec_pT
			 << endl;
		  
		  for(int ipos =0;ipos<ng4trevt_pos;ipos++)
		    {
		      int recopos = ntp_gtrack->GetEntry(g4trnum_pos[ipos]);
		      
		      int gtrid2 = tgtrackid;
		      
		      double pos_pT = sqrt(tpx*tpx+tpy*tpy);
		      double pos_eta = asinh(tpz/sqrt(tpx*tpx+tpy*tpy));
		      
		      // print out track details
		      if(verbose > 1)
			cout << "  Pair positron: iev " << iev << " ipos " << ipos
			     << " g4trnum_pos " << g4trnum_pos[ipos]
			     << " tgtrackid " << tgtrackid
			     << " tflavor " << tflavor
			     << " tpx " << tpx
			     << " tpy " << tpy
			     << " tpz " << tpz
			     << " pos_eta " << pos_eta
			     << " pos_gpT " << pos_pT
			     << endl;
	      	      
		      // Make G4 invariant mass 
		      
		      TLorentzVector t2;
		      double E2 = sqrt( pow(tpx,2) + pow(tpy,2) + pow(tpz,2) + pow(decaymass,2));
		      t2.SetPxPyPzE(tpx,tpy,tpz,E2);	  
		      
		      TLorentzVector t = t1+t2;
		      
		      if(verbose)
			cout << "                       reco'd g4 mass = " << t.M() << endl << endl;	    
		      
		      if(t.M() > 7.0 && t.M() < 11.0)
			{
			  nrecog4mass++;
			  g4mass->Fill(t.M());	
			  hgpt->Fill(t.Pt());
			  
			  // Capture the mass spectrum where both tracks are the primary Upsilon decay electrons
			  g4mass_primary->Fill(t.M());	  
			  
			}
		    }  // end of ipos loop
		} // end of ielec loop

	      ng4trevt_elec = 0;
	      ng4trevt_pos = 0;
      	    }

	  if(tembed != embed_flag)
	    continue;

	  if(tflavor == 11)
	    {
	      // electron
	      ng4trevt_elec++;
	      if(ng4trevt_elec > 999)
		continue;
	      
	      if(verbose)
		cout << " Found electron:" << endl
		     << "  ig " << ig
		     << " ng4trevt_elec " << ng4trevt_elec
		     << " gtrackID " << tgtrackid
		     << " gflavor " << tflavor
		     << " tpx " << tpx
		     << " tpy " << tpy
		     << " tpz " << tpz
		     << endl;
	      
	      g4trnum_elec[ng4trevt_elec-1] = ig;
	    }

	  if(tflavor == -11)
	    {
	      // positron
	      ng4trevt_pos++;
	      if(ng4trevt_pos > 999)
		continue;
	      
	      if(verbose)
		cout << " Found positron:" << endl
		     << "  ig " << ig
		     << " ng4trevt_pos " << ng4trevt_pos
		     << " gtrackID " << tgtrackid
		     << " gflavor " << tflavor
		     << " tpx " << tpx
		     << " tpy " << tpy
		     << " tpz " << tpz
		     << endl;
	      
	      g4trnum_pos[ng4trevt_pos-1] = ig;
	    }
	}  // end of ig loop	  
      
      
      if(verbose)
	{
	  cout << " # of g4 electron tracks = " << ng4trevt_elec 
	       << " # of g4 positron tracks = " << ng4trevt_pos << endl;
	}
	  
	  
      //=============================
      // process reconstructed tracks
      // for this event
      //=============================

      iev = 0;
      
      int nrtrevt = 0;
      int nr_elec = 0;
      int nr_pos = 0;
      int rectrnum_elec[1000];
      int rectrnum_pos[1000];

      //cout << "Number of ntp_track entries = " << recoget << endl;

      for(int ir=0;ir<ntracks;ir++)
	{
	  int recoget = ntp_track->GetEntry(ir);
	  if(!recoget)
	    {
	      cout << "Did not get entry for ir = " << ir << endl;
	      break;
	    }

	  if( rpt < 1.0)
	    continue;

	  if(revent != iev || ir == ntracks-1)
	    {
	      if(verbose > 1) 
		cout << " reached new event for ir = " << ir << " revent = " << revent << endl; 

	      if(verbose)
		cout << "For file " << ifile << " event " << iev << " found " << nr_elec << " reco electrons and " << nr_pos << " reco positrons"  << endl;

	      nevents++;
	      iev++;

	      for(int ielec = 0;ielec<nr_elec;ielec++)
		{
		  
		  TLorentzVector t1;
		  
		  int recoget1 = ntp_track->GetEntry(rectrnum_elec[ielec]);
		  
		  int trid1 = rgtrackid;	  
		  
		  double E1 = sqrt( pow(rpx,2) + pow(rpy,2) + pow(rpz,2) + pow(decaymass,2));
		  t1.SetPxPyPzE(rpx,rpy,rpz,E1);	  
		  
		  for(int ipos = 0;ipos<nr_pos;ipos++)
		    {
		      int recoget2 = ntp_track->GetEntry(rectrnum_pos[ipos]);
		      
		      int trid2 = rgtrackid;	  
		      
		      TLorentzVector t2;
		      double E2 = sqrt( pow(rpx,2) + pow(rpy,2) + pow(rpz,2) + pow(decaymass,2));
		      
		      t2.SetPxPyPzE(rpx,rpy,rpz,E2);	  
		      
		      TLorentzVector t = t1+t2;
		      
		      if(verbose)
			cout << " reco'd track mass = " << t.M() << endl;	    
		      
		      if(t.M() > 7.0 && t.M() < 11.0)
			{
			  nrecormass++;
			  recomass->Fill(t.M());	  
			  hrpt->Fill(t.Pt());
			  
			  // Capture the mass spectrum where both tracks are the primary Upsilon decay electrons
			  if( (trid1 == 1 || trid1 == 2) && (trid2 == 1 || trid2 == 2) ) 
			    recomass_primary->Fill(t.M());	  
			}
		    }
		}
	      nr_elec = 0;
	      nr_pos = 0;
	    }

	  if(rgembed != embed_flag)
	   continue;

	  //if(rcrossing != 0)
	  //continue;
	  
	  hrquality->Fill(rquality);
	  hrdca3dxy->Fill(rdca3dxy);
	  hrdca3dz->Fill(rdca3dz);

	  // track quality cuts	
	  if(rquality > quality_cut)  continue;
	  if(fabs(rdca3dxy) > dca3dxy_cut) continue;
	  if(fabs(rdca3dz) > dca3dz_cut) continue;
	  if(rnmaps < nmaps_cut) continue;
	  if(rpt < ptcut) continue;
	  if(reta > etacut) continue;
	  if(rntpc < ntpc_cut) continue;

	  // make a list of electrons and positrons
	  if(rcharge == -1)
	    {
	      nr_elec++;
	      rectrnum_elec[nr_elec-1] = ir;	      
	    }

	  if(rcharge == 1)
	    {
	      nr_pos++;
	      rectrnum_pos[nr_pos-1] = ir;	      
	    }

	  double rpT = sqrt(rpx*rpx+rpy*rpy);
	  double reta = asinh(rpz/sqrt(rpx*rpx+rpy*rpy));
	  
	  // print out track details
	  if(verbose)
	    cout << "     revent " << revent << " ir " << ir
		 << " rgtrackid " << rgtrackid
		 << " rgflavor " << rgflavor
		 << " rvz " << rvz
		 << " reta " << reta
		 << " rpT " << rpT
		 << endl;
	} // end of ir loop

      delete ntp_gtrack;
      delete ntp_track;
      delete ntp_cluster;
      delete ntp_vertex;
    }

  cout << "nevents = " << nevents << endl;

  cout << "nrecog4mass = " << nrecog4mass << endl;

  cout << "nrecormass = " << nrecormass << endl;

  //======================================================
  // End of loop over events and generation of mass histos
  //=====================================================

  TCanvas *cq = new TCanvas("cq","cq",5,5,600,600 );
  cq->Divide(2,2);
  cq->cd(1);
  hrquality->Draw();
  cq->cd(2);
  gPad->SetLogy(1);
  hrdca3dxy->Draw();
  cq->cd(3);
  gPad->SetLogy(1);
  hrdca3dz->Draw();

  // Mass histos
  
  TCanvas *cmass = new TCanvas("cmass","cmass",10,10,800,600);

  recomass_primary->SetLineColor(kRed);
  recomass->SetLineColor(kBlack);
  recomass->DrawCopy();  
  recomass_primary->DrawCopy("same");  

  TCanvas *cm_comp = new TCanvas("cm_comp","cm_comp",10,10,800,800);
  cm_comp->Divide(2,1);
  cm_comp->cd(1);
  recomass->Draw();
  recomass_primary->Draw("same");

  // we want from 7 to 11 GeV/c^2 - the whole range
  double yreco = recomass->Integral();
  double yreco_primary = recomass_primary->Integral();
  cout << "Reconstructed mass spectrum has " << yreco_primary << " entries from primary tracks and " << yreco << " entries total " << endl;

  cm_comp->cd(2);
  
  g4mass_primary->SetLineColor(kRed);
  g4mass->Draw();
  g4mass_primary->Draw("same");

  double yg4_primary = g4mass_primary->Integral();
  double yg4 = g4mass->Integral();
  cout << "G4 mass spectrum has " << yg4_primary << " entries from primary tracks and  " << yg4 << " entries total" << endl;

  cout << "Reconstruction efficiency is " << yreco_primary/yg4_primary << endl;

  // Output histos for reconstructed Upsilons

  char fname[500];

  sprintf(fname,"root_files/ups_embed_out.root");

  cout << "Create output file " << fname << endl;

  TFile *fout1 = new TFile(fname,"recreate");
  recomass->Write();
  recomass_primary->Write();
  g4mass->Write();
  g4mass_primary->Write();
  hrpt->Write();
  hrquality->Write();
  hrdca3dxy->Write();
  hrdca3dz->Write();
  fout1->Close();

  cout << "Finished write to file " << fname << endl;

}
