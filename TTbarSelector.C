#define TTbarSelector_cxx
// The class definition in TTbarSelector.h has been generated automatically
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
// root> T->Process("TTbarSelector.C")
// root> T->Process("TTbarSelector.C","some options")
// root> T->Process("TTbarSelector.C+")
//


#include "TTbarSelector.h"
#include <TH2.h>
#include <TStyle.h>

void TTbarSelector::BuildEvent()
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

void TTbarSelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void TTbarSelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF Slaven() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   TString option = GetOption();
 
   h_MET = new TH1F("MET", "MET Analysis", 150, -0.5, 299.5);
   h_MET->SetXTitle("MET [GeV]"); h_MET->SetYTitle("Events/2 GeV");
   h_MET->Sumw2(); histograms.push_back(h_MET);
}

Bool_t TTbarSelector::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);
   GetEntry(entry);
   ++TotalEvents;

   if (TotalEvents % 10000 == 0)
	std::cout << "MILEMARKER --> at event #" << TotalEvents << std::endl;

   BuildEvent();

   h_MET->Fill(*MET_pt);

   return kTRUE;
}

void TTbarSelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void TTbarSelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
