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
   SVs.clear();
   for (unsigned int i = 0; i < *nSV; ++i)
   {
	TLorentzVector tmp;
        tmp.SetPtEtaPhiM(SV_pt[i],SV_eta[i],SV_phi[i],SV_mass[i]);
	SVs.push_back(tmp);
   }

   // ...Bennie and the Jets
   Jets.clear();
   for (unsigned int i = 0; i < *nJet; ++i)
   {
	JetObj jet(Jet_pt[i], Jet_eta[i], Jet_phi[i], Jet_mass[i],
	Jet_hadronFlavour[i], Jet_btagDeepB[i], Jet_btagDeepFlavB[i]);
	jet.SetSV(SVs);

	// ignore jets that overlap with leptons
	if (jet.IsLepton(Electrons)) continue;
	if (jet.IsLepton(Muons)) continue;

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

   h_nLJets = new TH1F("nJets", "No. Jets", 10, -0.5, 9.5);
   h_nLJets->SetXTitle("nJets"); h_nLJets->SetYTitle("Events");
   lHists.push_back(h_nLJets);

   h_bMET = new TH1F("MET", "MET Analysis", 150, -0.5, 299.5);
   h_bMET->SetXTitle("MET [GeV]"); h_bMET->SetYTitle("Events/2 GeV");
   bHists.push_back(h_bMET);

   h_nBJets = new TH1F("nJets", "No. Jets", 10, -0.5, 9.5);
   h_nBJets->SetXTitle("nJets"); h_nBJets->SetYTitle("Events");
   bHists.push_back(h_nBJets);

   h_cMET = new TH1F("MET", "MET Analysis", 150, -0.5, 299.5);
   h_cMET->SetXTitle("MET [GeV]"); h_cMET->SetYTitle("Events/2 GeV");
   cHists.push_back(h_cMET);

   h_nCJets = new TH1F("nJets", "No. Jets", 10, -0.5, 9.5);
   h_nCJets->SetXTitle("nJets"); h_nCJets->SetYTitle("Events");
   cHists.push_back(h_nCJets);

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
	std::cout << "Z+x MILEMARKER --> at event #" << TotalEvent << std::endl;

   BuildEvent();
   if (Jets.size() == 0) return false;
   
   // check the jet types
   bool isBtag = false;
   float csv = Jets.at(0).m_deepCSV;
   if (csv >= 0.6321) isBtag = true;
   

   if (isBtag){
	 h_bMET->Fill(*MET_pt);
	 h_nBJets->Fill(Jets.size());
 	 bData.push_back(*MET_pt);
   }
   else {
	h_lMET->Fill(*MET_pt);
	h_nLJets->Fill(Jets.size());
	lData.push_back(*MET_pt);
   }

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
