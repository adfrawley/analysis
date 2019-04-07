#ifndef __HFFastSim_H__
#define __HFFastSim_H__

// --- need to check all these includes...
#include <fun4all/SubsysReco.h>
#include <limits.h>
#include <cmath>
#include <string>
#include <vector>

class TTree;
class TFile;
class TH2D;
class TH2F;
class TH1D;

class PHCompositeNode;
class Jet;
namespace HepMC
{
class GenEvent;
}

class HFFastSim : public SubsysReco
{
 public:
  HFFastSim(std::string filename, int flavor = 5, int maxevent = INT_MAX);

  int Init(PHCompositeNode *);
  int process_event(PHCompositeNode *);
  int End(PHCompositeNode *);

  double
  get_eta_max() const
  {
    return _eta_max;
  }

  void
  set_eta_max(double etaMax)
  {
    _eta_max = etaMax;
  }

  double
  get_eta_min() const
  {
    return _eta_min;
  }

  void
  set_eta_min(double etaMin)
  {
    _eta_min = etaMin;
  }

  double
  get_pt_max() const
  {
    return _pt_max;
  }

  void
  set_pt_max(double ptMax)
  {
    _pt_max = ptMax;
  }

  double
  get_pt_min() const
  {
    return _pt_min;
  }

  void
  set_pt_min(double ptMin)
  {
    _pt_min = ptMin;
  }

  //! action to take if no jet fitting _flavor requirement found. Action defined in <fun4all/Fun4AllReturnCodes.h>
  //! Default action is DISCARDEVENT for DST level filtering, one can further choose ABORTEVENT to use it as processing level filtering
  void
  set_rejection_action(int action)
  {
    _rejection_action = action;
  }

  //! The embedding ID for the HepMC subevent to be analyzed.
  //! embedding ID for the event
  //! positive ID is the embedded event of interest, e.g. jetty event from pythia
  //! negative IDs are backgrounds, .e.g out of time pile up collisions
  //! Usually, ID = 0 means the primary Au+Au collision background
  int get_embedding_id() const { return _embedding_id; }
  //
  //! The embedding ID for the HepMC subevent to be analyzed.
  //! embedding ID for the event
  //! positive ID is the embedded event of interest, e.g. jetty event from pythia
  //! negative IDs are backgrounds, .e.g out of time pile up collisions
  //! Usually, ID = 0 means the primary Au+Au collision background
  void set_embedding_id(int id) { _embedding_id = id; }

  bool process_D02PiK(HepMC::GenEvent* theEvent);

  struct D02PiK
  {
    int pid;
    double y;
  };

 private:
  bool _verbose;

  int _ievent;
  int _total_pass;

  TFile *_f;

  TH2D *_h2;
  TH2D *_h2all;
  TH2D *_h2_b;
  TH2D *_h2_c;

  TH1D *m_hNorm;
  TH2F *m_DRapidity;

  TTree *m_tSingleD;
  D02PiK m_singleD;

  std::string _foutname;

  int _flavor;
  int _maxevent;

  double _pt_min;
  double _pt_max;

  double _eta_min;
  double _eta_max;

  std::string _jet_name;

  //! action to take if no jet fitting _flavor requirement found. Action defined in <fun4all/Fun4AllReturnCodes.h>
  int _rejection_action;

  //! The embedding ID for the HepMC subevent to be analyzed.
  //! positive ID is the embedded event of interest, e.g. jetty event from pythia
  //! negative IDs are backgrounds, .e.g out of time pile up collisions
  //! Usually, ID = 0 means the primary Au+Au collision background
  int _embedding_id;
};

#endif  // __HFFastSim_H__
