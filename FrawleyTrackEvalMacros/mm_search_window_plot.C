void search_window_plot()
{
  gStyle->SetOptStat(0);

  double interval[5] = {1, 1.5, 2, 3, 4};
  double eff_under3[5] = {10, 32, 43, 52, 58};
  double eff_under40[5] = {74,76, 77, 83, 96};
  double seed_tracks_increase_byten[5] = {15, 20, 30, 50, 80};
  double nmaps_zero_percent[5] = {2, 1, 2.5, 4.5, 4};

  TH1D *h = new TH1D("h","",100,0,5);
  h->SetMaximum(90);
  h->SetMinimum(0);
  h->GetXaxis()->SetTitle("window width multiplier (x(#Delta#phi, #Delta#eta) = (0.05, 0.2)");
  h->GetYaxis()->SetTitle("Track efficiency / seed increase x 10 / %maps missed");
  h->Draw();

  TGraph *grnmaps_zero = new TGraph(5, interval, nmaps_zero_percent);
  grnmaps_zero->SetMarkerStyle(20);
  grnmaps_zero->SetMarkerSize(1.4);
  grnmaps_zero->Draw("p");

  TGraph *grseeds_increase = new TGraph(5, interval, seed_tracks_increase_byten);
  grseeds_increase->SetMarkerStyle(20);
  grseeds_increase->SetMarkerSize(1.4);
  grseeds_increase->SetMarkerColor(kRed);
  grseeds_increase->Draw("p");

  TGraph *greff_under3 = new TGraph(5, interval, eff_under3);
  greff_under3->SetMarkerStyle(20);
  greff_under3->SetMarkerSize(1.4);
  greff_under3->SetMarkerColor(kBlue);
  greff_under3->Draw("p");

  TLegend *leg = new TLegend(0.12, 0.7, 0.55, 0.9, "");
  leg->AddEntry(greff_under3, "Track % efficiency < 3 GeV/c", "p");
  leg->AddEntry(grseeds_increase,"Seed tracks increase factor (x10)","p");
  leg ->AddEntry(grnmaps_zero,"% missed MVTX matches","p");
  leg->Draw();

  /*
Tests of search windows (phi, eta) for Tpc silicon track matching:
PHTpcTracker + PHSiliconTruthTrackSeeding +  PHSiliconTpcTrackMatching + PHActsTrkFitter:
Run 200 muons (2K equivalent occ.) into 0.1-0.3 in eta, 2pi in phi, pT = 0.2-3.0 GeV/c:
Use quality cuts: "gtrackID > 0 && ntpc > 20 && quality < 10"
0.05, 0.02  - 1x nominal - 10% eff, final tracks x1.3    gtrackID 0 repeats, 2% nmaps = 0
0.075, 0.03 - 1.5x nominal-32% eff, final tracks x1.6    gtrackID 1 repeat,  1% nmaps = 0
0.10, 0.04  - 2x nominal - 43% eff, final tracks x2.5    gtrackID 3 repeats, 2.5% nmaps = 0
0.15, 0.06  - 3x nominal - 52% eff, final tracks x5      gtrackID 4 repeats, 4.5% nmaps = 0
0.20, 0.08  - 4x nominal - 58% eff, final tracks x8      gtrackID 11 repeats, 4% nmaps = 0

Run 200 muons (2K equivalent occ.) into 0.1-0.3 in eta, 2pi in phi, pT = 0.2-40.0 GeV/c:
Use quality cuts: "gtrackID > 0 && ntpc > 20 && quality < 10"
0.05, 0.02  - 1x nominal - 74% eff, final tracks x1.5    gtrackID 0 repeats, 2% nmaps = 0
0.075, 0.03 - 1.5x nominal- 76% eff, final tracks x2     gtrackID 6 repeats,  1% nmaps = 0
0.10, 0.04  - 2x nominal - 77% eff, final tracks x3      gtrackID 3 repeats, 1% nmaps = 0
0.15, 0.06  - 3x nominal - 83% eff, final tracks x5      gtrackID 12 repeats, 5% nmaps = 0
0.20, 0.08  - 4x nominal - 96% eff, final tracks x8      gtrackID 24 repeats, 18% nmaps = 0!
Conclusion: 0.15, 0.06 seems best compromise for now.
*/

}
