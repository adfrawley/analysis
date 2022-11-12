void plot_arbitrary_mass()
{
  TFile fin("ntp_mass_out.root");
  //TFile fin("ntp_mass_out_kptcut_100_100.root");
  //TFile fin("ntp_mass_out_kptcut_500_500.root");

  TH1D *recomass, *recopt, *recopath,*recoctau;
  TH2D *recoeta, *recophi, *recodca,*recopath_z;
  fin.GetObject("recomass",recomass);
  fin.GetObject("recopt",recopt);
  fin.GetObject("recoeta",recoeta);
  fin.GetObject("recophi",recophi);
  fin.GetObject("recopath",recopath);
  fin.GetObject("recopath_z",recopath_z);
  fin.GetObject("recoctau",recoctau);
  fin.GetObject("recodca",recodca);

  recomass->GetXaxis()->SetTitle("Inv. mass (GeV/c^2");
  recopt->GetXaxis()->SetTitle("Resonance p_{T}");
  recopath->GetXaxis()->SetTitle("decay length");
  recoctau->GetXaxis()->SetTitle("c#tau");
  recopath_z->GetXaxis()->SetTitle("Path Z component (cm)");
  recopath_z->GetYaxis()->SetTitle("Path (cm)");
  recopath_z->GetYaxis()->SetTitleOffset(1.9);
  recodca->GetXaxis()->SetTitle("Resonance p({T}");
  recodca->GetYaxis()->SetTitle("Decay particle DCA");
  recodca->GetYaxis()->SetTitleOffset(1.9);
  recoeta->GetXaxis()->SetTitle("Resonance #eta");
  recoeta->GetYaxis()->SetTitle("Resonance mass");
  recoeta->GetYaxis()->SetTitleOffset(1.9);
  recophi->GetXaxis()->SetTitle("Resonance #phi");
  recophi->GetYaxis()->SetTitle("Resonance mass");
  recophi->GetYaxis()->SetTitleOffset(1.9);

  TCanvas *c1 = new TCanvas("c1","c1",5,5,800,800);
  c1->SetLeftMargin(0.12);
  recomass->DrawCopy();

  TCanvas *c2 = new TCanvas("c2","c2",50,50,2000,800);

  c2->Divide(3,1);
  c2->cd(1);
  gPad->SetLeftMargin(0.15);
  recopt->DrawCopy();
  c2->cd(2);
  gPad->SetLeftMargin(0.15);
  recoeta->DrawCopy();
  c2->cd(3);
  gPad->SetLeftMargin(0.15);
  recophi->DrawCopy();

  TCanvas *c3 = new TCanvas("c3","c3", 100,100, 2000,800);
  c3->Divide(4,1);
  c3->cd(1);
  gPad->SetLeftMargin(0.15);
  recodca->DrawCopy();
  c3->cd(2);
  gPad->SetLeftMargin(0.15);
  recopath_z->DrawCopy();
  c3->cd(3);
  gPad->SetLeftMargin(0.15);
  recopath->DrawCopy();
  c3->cd(4);
  gPad->SetLeftMargin(0.15);
  recoctau->DrawCopy();


  int binlo = recomass->FindBin(0.47);
  int binhi = recomass->FindBin(0.525);
  int foreground = recomass->Integral(binlo,binhi);
  int binrange = binhi-binlo+1;
    std::cout << " binlo " << binlo << " binhi " << binhi << " binrange " << binrange << std::endl;


  int bg1 = recomass->Integral(binlo-binrange,binlo-1);
  int bg2 = recomass->Integral(binhi+1,binhi+binrange);
  int bg = (bg1+bg2) / 2;
  int signal = foreground - bg;

  float error = sqrt(foreground + bg);

  std::cout << " foreground " << foreground << " bg1 " << bg1 << " bg2 " << bg2 << " bg " << bg << " signal " << signal << " +/- " << error << " percent error " << 100.0 * error/signal << std::endl;
}
