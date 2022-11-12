#include "TH2D.h"
#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TLine.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TF1.h"
#include <fstream>

void tracking_memory_stats()
{
  double cum_memory = 0;
  double cum_wt = 0;

  //ifstream fin("/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/joe_phtpctracker_memory.txt");   // 5 evts/job
  //ifstream fin("/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/joe_caseeder_memory.txt");  // 5 evts/job
  //ifstream fin("/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/joe_libraries_caseeder_10evts_eval_output/caseeder_memory_use.txt");
  //ifstream fin("/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/joe_libraries_caseeder_10evts_eval_output/caseeder_memory_use.txt");
  //ifstream fin("/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/joe_libraries_caseeder_1evts_eval_output/caseeder_memory_use.txt");
  //ifstream fin("/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/eval_output_MB/tpctracker_memory_use.txt");  // 1 evt/job
  //ifstream fin("/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/repo_libraries_caseeder_1evts_dst_eval_output/caseeder_memory_use.txt");  // 1 evt/job
  ifstream fin("/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/repo_libraries_tpctracker_1evts_dst_eval_output/tpctracker_memory_use.txt");  // 1 evt/job

  TH1D *hmem = new TH1D("hmem","MB tracking memory use",1000,10,10000);

  std::string substring= {"Memory" };

  for(int i=0;i<996;++i)
    {
      char in1[500];
      char in2[500];
      char in3[500];
      char in4[500];
      char dummy[500];

      double memory;

      fin >> in1 >> in2 >> in3 >> in4 >> memory >> dummy >> dummy;
      std::cout << "i = " << i << " Input line " << in1 << "  " << in2 << "  " << in3 << "  " << in4 << "  " << memory << std::endl;
      // joe_libraries_phtpctracker_eval_output/g4svx_eval.log.987:         Memory (MB)          :  3522       12288     12288 

      // add to the average
      cum_memory += memory;
      cum_wt  += 1;
      std::cout << "       adding memory " << memory << std::endl; 
      hmem->Fill(memory);

    } 
    
  std::cout << substring << " wt " << cum_wt << " cum_memory " << cum_memory << " avge  " << cum_memory / cum_wt << std::endl;
  //  hmem->SetLogx(1);
  hmem->Draw();
}
