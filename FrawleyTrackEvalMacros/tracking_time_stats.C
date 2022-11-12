void tracking_time_stats()
{

  //ifstream fin("mb_time_stats.txt");
  //ifstream fin("/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/joe_phtpctracker.txt");
  //ifstream fin("/sphenix/user/frawley/new_dec21/macros/detectors/sPHENIX/joe_caseeder_time.txt");

  ifstream fin("HWTest_time_stats.txt");

  static const int NSTR = 15;
  std::string substring[NSTR] = {
    "MvtxClusterizer",
    "InttClusterizer",
    "MakeActsGeometry",
    "TpcClusterizer",
    "TpcSpaceChargeCorrection",
    "TpcClusterCleaner",
    "PHTpcClusterMover",
     "PHCASeeding",
     "PHTpcTrackSeedVertexAssoc",
    "PHSiliconTpcTrackMatching",
    "PHMicromegasTpcTrackMatching",
    "PHTpcResiduals",
    "PHActsSiliconSeeding",
    "PHActsInitialVertexFinder",
    //    "PHActsVertexFinder",     // pass 2 only
    "PHActsFirstTrkFitter",
    //   "PHActsSecondTrKFitter",       // pass 2 only
  };

  double cum_time[NSTR] = {0};
  double cum_wt[NSTR] = {0};

  for(int i=0;i<50000;++i)
    {
      char in1[500];
      char in2[500];
      char in3[500];
      char in4[500];
      char in5[500];

      double time;

      fin >> in1 >> in2 >> in3 >> in4 >> in5 >> time;
      std::cout << "i = " << i << " Input line " << in1 << in2 << "  " << in3 << " " << in4 << " " << in5 << time << std::endl;

      /* Text input file obtained with:
	grep "per event time" /sphenix/sim/sim01/sphnxpro/MDC1/sHijing_HepMC/HWTest/log/fm_0_20/hwpass1/condor-0000000001-0*.out > HWTest_time_stats.txt
       */

      //sphenix/sim/sim01/sphnxpro/MDC1/sHijing_HepMC/HWTest/log/fm_0_20/hwpass1/condor-0000000001-00000.out:InttClusterizer_TOP: per event time (ms):    14.1907

      //   joe_libraries_phypctracker_eval_output/g4svx_eval.out.0:InttClusterizer_TOP: per event time (ms):    80.5792

      std::string str1 = in1;

      for(int istr=0;istr<NSTR;++istr)
	{      
	  int index = str1.find(substring[istr]);
	  //std::cout << "Try:  in1 " << in1 << " in2 " << in2 << " in3 " << in3 << " in4 " << in4 << " in5 " << in5 << " substring " << substring[istr] << " index " << index << " time " << time << std::endl;

	  if (index > 0) 
	    {
	      std::cout << "Substring found "  << "  in1 " << in1 << " substring " << substring[istr] << " time " << time << std::endl;
	      // add to the average
	      cum_time[istr] += time;
	      cum_wt[istr] += 1;
	    } 
	  else
	    {
	      //std::cout << "Substring not found at all in parent string" << std::endl;
	    }
	}
    }


  for(int istr = 0; istr<NSTR;++istr)
    {
      std::cout << " module " <<  substring[istr]  << " # of jobs " << cum_wt[istr] << " avge time/event " << cum_time[istr] / cum_wt[istr] / 1000.0 << std::endl;
    }

  double cluster_time = 0;
  for(int istr = 0; istr<4;++istr)
    {
      cluster_time += cum_time[istr] / cum_wt[istr] / 1000.0;     
    }
  std::cout << "Clustering time: " << cluster_time << std::endl;

  double track_time = 0;
  for(int istr = 4; istr<NSTR;++istr)
    {
      track_time += cum_time[istr] / cum_wt[istr] / 1000.0;     
    }
  std::cout << "Tracking time: " << track_time << std::endl;

}
