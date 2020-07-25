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
   	// Get the electrons from the event
	Electrons.clear();
	for (unsigned int i = 0; i < *nElectron; ++i)
	{
	LepObj elec(Electron_pt[i],Electron_eta[i],Electron_phi[i],
    	Electron_mass[i], 0);
    	Electrons.push_back(elec);	
	}

	// Get the muons from the event
	Muons.clear();
	for (unsigned int i = 0; i < *nMuon; ++i)
	{
	LepObj muon(Muon_pt[i],Muon_eta[i],Muon_phi[i],Muon_mass[i],
    	Muon_pfRelIso04_all[i]);
    	Muons.push_back(muon);
	}

	// Get the secondary vertex options
	for (unsigned int i = 0; i < *nSV; ++i)
	{
	TLorentzVector tmp;
	 tmp.SetPtEtaPhiM(SV_pt[i],SV_eta[i],SV_phi[i],SV_mass[i]);
   	 SVs.push_back(tmp);
	}

	// ...Bennie and the Jets
	for (unsigned int i = 0; i < *nJet; ++i)
	{
	JetObj jet(Jet_pt[i], Jet_eta[i], Jet_phi[i], Jet_mass[i],
	    Jet_hadronFlavour[i], Jet_btagDeepB[i], Jet_btagDeepFlavB[i]);
	    jet.SetSV(SVs);

    	// ignore jets that overlap with leptons
    	if (jet.IsLepton(Electrons)) continue;
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

   h_nJet = new TH1F("nJets", "No. Jets", 10, -0.5, 9.5);
   h_nJet->SetXTitle("nJets"); h_nJet->SetYTitle("Events");
   histograms.push_back(h_nJet);
}

Bool_t TTbarSelector::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);
   GetEntry(entry);
   ++TotalEvents;

   if (TotalEvents % 1000 == 0)
	std::cout << "TTBAR MILEMARKER --> at event #" << TotalEvents << std::endl;

   BuildEvent();
   if (Jets.size() == 0) return false;
   h_nJet->Fill(Jets.size());
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
