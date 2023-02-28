#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TFile.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TCanvas.h>
#include <Eigen/Dense>

void findPcaTwoTracks(Eigen::Vector3d a1, TLorentzVector v1, Eigen::Vector3d a2, TLorentzVector v2, 
			double &dca, Eigen::Vector3d &PCA1, Eigen::Vector3d &PCA2)
{
  Eigen::Vector3d b1(v1.Px(), v1.Py(), v1.Pz());
  Eigen::Vector3d b2(v2.Px(), v2.Py(), v2.Pz());

  // The shortest distance between two skew lines described by
  //  a1 + c * b1
  //  a2 + d * b2
  // where a1, a2, are vectors representing points on the lines, b1, b2 are direction vectors, and c and d are scalars
  // is:
  // dca = (b1 x b2) .(a2-a1) / |b1 x b2|

  // bcrossb/mag_bcrossb is a unit vector perpendicular to both direction vectors b1 and b2
  auto bcrossb = b1.cross(b2);
  auto mag_bcrossb = bcrossb.norm();
  // a2-a1 is the vector joining any arbitrary points on the two lines
  auto aminusa = a2-a1;

  // The DCA of these two lines is the projection of a2-a1 along the direction of the perpendicular to both 
  // remember that a2-a1 is longer than (or equal to) the dca by definition
  dca = 999;
  if( mag_bcrossb != 0)
    dca = bcrossb.dot(aminusa) / mag_bcrossb;
  else
    return;   // same track, skip combination
  
  // get the points at which the normal to the lines intersect the lines, where the lines are perpendicular

  double X =  b1.dot(b2) - b1.dot(b1) * b2.dot(b2) / b2.dot(b1);
  double Y =  (a2.dot(b2) - a1.dot(b2)) - (a2.dot(b1) - a1.dot(b1)) * b2.dot(b2) / b2.dot(b1) ;
  double c = Y/X;

  double F = b1.dot(b1) / b2.dot(b1); 
  double G = - (a2.dot(b1) - a1.dot(b1)) / b2.dot(b1);
  double d = c * F + G;

  // then the points of closest approach are:
  PCA1 = a1+c*b1;
  PCA2 = a2+d*b2;

  return;
}

void project_arbitrary_mass()
{
  //SetsPhenixStyle();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptTitle(0);

  bool muons  = false;  // electrons by default
  bool pions  = true;
  TFile *fout = new TFile("ntp_mass_out.root","recreate");

 TH1D *recomass = new TH1D("recomass","Reconstructed mass",500,0.3,0.7);
 TH1D *recopt = new TH1D("recopt","Resonance p_{T}",500,0,5.0);
 TH1D *recorap = new TH1D("recorap","Resonance rapidity",200,-3,3);
 TH1D *recopath = new TH1D("recopath","Decay length",200, 0, 5.0);
 TH1D *recoctau = new TH1D("recoctau","Decay c#tau",200, 0, 3.0);
 TH2D *recodca = new TH2D("recodca","DCA of decay tracks",200, 0, 5, 200, -0.1, 0.1);
 TH2D *recoeta = new TH2D("recoeta","mass vs resonance #eta",500,-1.5,1.5,500,0.3,0.7);
 TH2D *recophi = new TH2D("recophi","mass vs resonance #phi",500,-4.0,4.0, 500,0.3,0.7);
 TH2D *recopath_z = new TH2D("recopath_z","Decay length vs z component",200,-5,5,200,0,5);

  TH2D *hdca3dxy   = new TH2D("hdca3dxy","hdca3dxy", 200, 0.0, 10.0, 1000, -0.05, 0.05);
  TH2D *hdca3dz    = new TH2D("hdca3dz","hdca3dz",200, 0.0, 10.0, 1000,-0.1,0.1);
  TH1D *hz       = new TH1D("hz","hz",200, -15,15);
  TH1D *hquality = new TH1D("hquality","hquality", 100, 0, 20);
  TH1D *heta     = new TH1D("heta","heta", 100, -1.5, 1.5);
  TH1D *hnmaps   = new TH1D("hnmaps","hnmaps", 50, 0.0, 5.0);

  Float_t event;
  Float_t px;
  Float_t py;
  Float_t pz;
  Float_t pt;
  Float_t vx;
  Float_t vy;
  Float_t vz;
  Float_t pcax;
  Float_t pcay;
  Float_t pcaz;
  Float_t quality;
  Float_t charge;
  Float_t dca2d;
  Float_t dca3dxy;
  Float_t dca3dz;
  Float_t ntpc;
  Float_t nmaps;
  Float_t eta;
  //  Float_t gvx;
  //  Float_t gvy;
  //  Float_t gvz;
  //  Float_t gembed;

  Float_t decaymass = 0.000511;
  if(muons){decaymass = 0.1057;}
  if(pions){decaymass = 0.13957;}

  // Cut on DCA to event vertex to eliminate most prompt tracks
  float dca3dxy_cut = 0.010; // 100 microns
  float dca3dz_cut = 0.010; // 100 microns

  // Cut on the DCA of the two decay tracks to eliminate bad matches 
  double decay_vertex_dca_cut = 0.05;

  double quality_cut  = 10;  // track chisq/degree of freedom cut

  int nfiles          = 2000;
  for(int ifile = 0; ifile < nfiles; ifile++)
    { 
      char name[2000];
      sprintf(name,"/sphenix/user/frawley/jan20_2023/macros/detectors/sPHENIX/eval_out/proc_%i_g4svtx_eval.root",ifile);

      TChain* ntp_vertex = new TChain("ntp_vertex","reco events");
      ntp_vertex->Add(name);

      if(ntp_vertex->GetEntries() < 1) continue;

      TChain* ntp_track = new TChain("ntp_track","reco tracks");  
      ntp_track->Add(name);

      ntp_track->SetBranchAddress("event",&event);
      ntp_track->SetBranchAddress("px",&px);
      ntp_track->SetBranchAddress("py",&py);
      ntp_track->SetBranchAddress("pz",&pz);
      ntp_track->SetBranchAddress("vx",&vx);
      ntp_track->SetBranchAddress("vy",&vy);
      ntp_track->SetBranchAddress("vz",&vz);
      ntp_track->SetBranchAddress("pcax",&pcax);
      ntp_track->SetBranchAddress("pcay",&pcay);
      ntp_track->SetBranchAddress("pcaz",&pcaz);
      ntp_track->SetBranchAddress("pt",&pt);
      ntp_track->SetBranchAddress("charge",&charge);
      ntp_track->SetBranchAddress("dca3dxy",&dca3dxy);
      ntp_track->SetBranchAddress("dca3dz",&dca3dz);
      ntp_track->SetBranchAddress("quality",&quality);
      ntp_track->SetBranchAddress("ntpc",&ntpc);
      ntp_track->SetBranchAddress("nmaps",&nmaps);
      ntp_track->SetBranchAddress("eta",&eta);
      //ntp_track->SetBranchAddress("gvx",&gvx);
      //ntp_track->SetBranchAddress("gvy",&gvy);
      //ntp_track->SetBranchAddress("gvz",&gvz);
      //ntp_track->SetBranchAddress("gembed",&gembed);

      int ntracks = ntp_track->GetEntries();

      // capture the quality, eta, nmaps, dcaxy and dcaz histograms
      for(int i=0; i<ntracks; i++)
	{
	  ntp_track->GetEntry(i);

	  hdca3dxy->Fill(pt, dca3dxy);
	  hdca3dz->Fill(pt, dca3dz);
	  hquality->Fill(quality);
	  heta->Fill(eta);
	  hnmaps->Fill(nmaps);
	}
      
      int events_per_file = ntp_vertex->GetEntries();      
      std::cout << " file number " << ifile << " has " << events_per_file << " vertices and " << ntracks  << " tracks " << std::endl;

      // these store the parameters of the candidate positive and negative tracks, and 
      // the associated event vertex positions
      std::vector<TLorentzVector> v1;
      std::vector<TLorentzVector> v2;
      std::vector<Eigen::Vector3d> p1;
      std::vector<Eigen::Vector3d> p2;
      std::vector<Eigen::Vector3d> vertex_vec1;
      std::vector<Eigen::Vector3d> vertex_vec2;

      int event_keep = -1;	  
      for(int i=0; i<ntracks; i++)
	{
	  ntp_track->GetEntry(i);
	  
	  if(isnan(px)) continue;  // should not be necessary
	  
	  if(event != event_keep || i == ntracks -1)
	    {
	      event_keep = event;
	      
	      //close out the last event
	      if(v1.size() > 0 && v2.size() > 0)
		{
		  for(unsigned int i2 = 0; i2<v2.size(); ++i2)
		    {
		      for(unsigned int i1 = 0; i1<v1.size(); ++i1)
			{
			  TLorentzVector tsum;
			  tsum = v1[i1]+v2[i2];

			  if(tsum.Pt() > 0.1)  // this eliminates a broad peak from pairs with zero pT
			    {			  
			      // get the DCA for the pair, and the PCA for these two tracks
			      // This is the point on track 1 that is closest to track 2 and vice-versa
			      Eigen::Vector3d PCA1(0,0,0);
			      Eigen::Vector3d PCA2(0,0,0);
			      double dca = 0.0;
			      findPcaTwoTracks(p1[i1], v1[i1], p2[i2], v2[i2], dca, PCA1, PCA2);

			      // fill the mass histogram for decay pairs with small DCA
			      if(fabs(dca) < decay_vertex_dca_cut) 
				recomass->Fill(tsum.M());

			      // Fill some informative histograms

			      recodca->Fill(tsum.Pt(), dca);			      

			      // difference from the event vertex
			      Eigen::Vector3d VTX(vertex_vec1[i1](0),vertex_vec1[i1](1),vertex_vec1[i1](2));  // asssociated event vertex
			      Eigen::Vector3d PCA = (PCA1+PCA2) / 2.0;  // average the PCA of the track pair
			      Eigen::Vector3d path = PCA - VTX;
			      if(tsum.M() > 0.48 && tsum.M() < 0.52 && fabs(dca) < decay_vertex_dca_cut)
				{
				  recorap->Fill(tsum.Rapidity());
				  recopath->Fill(path.norm());
				  recopath_z->Fill(path(2), path.norm());
				  double gamma = tsum.E() /tsum.M();
				  recoctau->Fill(path.norm()/gamma);
				  recopt->Fill(tsum.Pt());
				  recoeta->Fill(tsum.Eta(), tsum.M());
				  recophi->Fill(tsum.Phi(),tsum.M());
				}
			    }
			}
		    }
		}  // end make mass
	      
	      // reset
	      v1.clear();
	      v2.clear();
	      p1.clear();
	      p2.clear();
	      vertex_vec1.clear();
	      vertex_vec2.clear();
	    }  // finish closing out the last event
	  
	  if(quality > quality_cut)
	    continue;
	  
	  if(nmaps < 3)
	    continue;

	  if(ntpc < 20)
	    continue;

	  if(fabs(dca3dxy) < dca3dxy_cut)
	    continue;

	  if(fabs(dca3dz) < dca3dz_cut)
	    continue;

	  TLorentzVector t;
	      	  
	  Float_t E = sqrt(pow(px,2) + pow(py,2) + pow(pz,2) + pow(decaymass,2));
	  t.SetPxPyPzE(px,py,pz,E);	

	  Eigen::Vector3d pos(pcax, pcay, pcaz);  // the track position at the beamline

	  Eigen::Vector3d vertex(vx,vy,vz);

	  if(charge == 1)
	    {
	      v1.push_back(t);
	      p1.push_back(pos);
	      vertex_vec1.push_back(vertex);
	    }
	  else
	    {
	      v2.push_back(t);
	      p2.push_back(pos);
	      vertex_vec2.push_back(vertex);
	    }

	}  // end loop over tracks
      
      delete ntp_track; 
      delete ntp_vertex;      
    }
  
  recomass->Write();
  recopt->Write();
  recorap->Write();
  recoeta->Write();
  recophi->Write();
  recopath->Write();
  recopath_z->Write();
  recoctau->Write();
  recodca->Write();
  hdca3dxy->Write();
  hdca3dz->Write();
  hz->Write();
  hquality->Write();
  heta->Write();
  hnmaps->Write();

  fout->Close();

}


