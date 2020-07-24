#define ZxSelector_cxx
// The class definition in ZxSelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("ZxSelector.C")
// root> T->Process("ZxSelector.C","some options")
// root> T->Process("ZxSelector.C+")
//


#include "ZxSelector.h"
#include <TH2.h>
#include <TStyle.h>

void ZxSelector::BuildEvent()
{
    // Get all of the muons from the event
   Muons.clear();
   for (Int_t i = 0; i < *nMuon; ++i)
   {
	MuonObj muon;
	muon.SetIsolation(Muon_jetRelIso[i]);
	muon.SetPtEtaPhiM(Muon_pt[i],Muon_eta[i],Muon_phi[i],Muon_mass[i]);
	muon.SetCharge(Muon_charge[i]);
	Muons.push_back(muon);
   }

   // Get all of the electrons from the event
   Electrons.clear();
   for (Int_t i = 0; i < *nElectron; ++i)
   {
	ElecObj elec;
	elec.SetPtEtaPhiM(Electron_pt[i],Electron_eta[i],Electron_phi[i],Electron_mass[i]);
	elec.SetCharge(Electron_charge[i]);
	Electrons.push_back(elec);
   }

   // Get all of the photons from the event
   Photons.clear();
   for (Int_t i = 0; i < *nPhoton; ++i)
   {
	PhotonObj photon;
	photon.SetPtEtaPhiM(Photon_pt[i],Photon_eta[i],Photon_phi[i],Photon_mass[i]);
	Photons.push_back(photon);
   }

   // Get all of the jets from the event
   Jets.clear();
   for (Int_t i = 0; i < *nJet; ++i)
   {
	JetObj jet;
	jet.SetJetID(Jet_jetId[i]);
	jet.SetPtEtaPhiM(Jet_pt[i],Jet_eta[i],Jet_phi[i],Jet_mass[i]);
	Jets.push_back(jet);
   }
}

void ZxSelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void ZxSelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   h_lMET = new TH1F("MET", "MET Analysis", 150, -0.5, 299.5);
   h_lMET->SetXTitle("MET [GeV]"); h_lMET->SetYTitle("Events/2 GeV");
   lHists.push_back(h_lMET);

   h_bMET = new TH1F("MET", "MET Analysis", 150, -0.5, 299.5);
   h_bMET->SetXTitle("MET [GeV]"); h_bMET->SetYTitle("Events/2 GeV");
   bHists.push_back(h_bMET);

   h_cMET = new TH1F("MET", "MET Analysis", 150, -0.5, 299.5);
   h_cMET->SetXTitle("MET [GeV]"); h_cMET->SetYTitle("Events/2 GeV");
   cHists.push_back(h_cMET);

}

Bool_t ZxSelector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fReader.SetLocalEntry(entry);
   GetEntry(entry);
   ++TotalEvent;

   if (TotalEvent % 10000 == 0)
	std::cout << "MILEMARKER --> at event #" << TotalEvent << std::endl;

   BuildEvent();
   if (Jets.size() == 0) return false;
   h_bMET->Fill(*MET_pt);

   return kTRUE;
}

void ZxSelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void ZxSelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
