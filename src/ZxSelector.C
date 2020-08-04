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
#include "Global.h"
//#include <TLatex.h>
#include <TH2.h>
#include <TStyle.h>

void ZxSelector::BuildEvent()
{
   // Get the electrons from the event
   Electrons.clear(); Elec_jetOverlap.clear();
   for (unsigned int i = 0; i < *nElectron; ++i)
   {	

	// create the lepton object
	LepObj elec(Electron_pt[i],Electron_eta[i],Electron_phi[i],
	Electron_mass[i], 0);
	
	// check for jet overlap candidate
	if (elec.m_lvec.Pt() > CUTS.Get<float>("lep_jetOverlap_pt") &&
	fabs(elec.m_lvec.Eta()) < CUTS.Get<float>("lep_jetOverlap_eta"))
	{
		int elecID = Electron_cutBased[i];
		if (elecID >= 2) Elec_jetOverlap.push_back(elec);
	}

	// skip the lepton if it doesn't mean our criteria
	if (elec.m_lvec.Pt() < CUTS.Get<float>("lep_pt1") || 
	fabs(elec.m_lvec.Eta()) > CUTS.Get<float>("lep_eta")) continue;

	// check the other criteria
	float etaSC = elec.m_lvec.Eta() - Electron_deltaEtaSC[i];
	if (fabs(etaSC) < 1.566 && fabs(etaSC) > 1.442) continue;

	int elecID = Electron_cutBased[i];
	if (elecID < 2) continue;
 	Electrons.push_back(elec);
   }

   // Get the muons from the event
   Muons.clear(); Muon_jetOverlap.clear();
   for (unsigned int i = 0; i < *nMuon; ++i)
   {
	// create the muon object
	LepObj muon(Muon_pt[i],Muon_eta[i],Muon_phi[i],Muon_mass[i],
	Muon_pfRelIso04_all[i]);

	// check for jet overlap
	if (muon.m_lvec.Pt() > CUTS.Get<float>("lep_jetOverlap_pt") && 
	fabs(muon.m_lvec.Eta()) < CUTS.Get<float>("lep_jetOverlap_eta"))
	{
		if (Muon_looseId[i] > 0 && Muon_pfRelIso04_all[i] < 
		CUTS.Get<float>("muon_iso"))
			Muon_jetOverlap.push_back(muon);
	}

	// skip the lepton if it doesn't meet our criteria
	if (muon.m_lvec.Pt() < CUTS.Get<float>("lep_pt1") ||
	fabs(muon.m_lvec.Eta()) > CUTS.Get<float>("lep_eta")) continue;

	if (Muon_looseId[i] <= 0) continue;
	if (muon.m_iso > CUTS.Get<float>("muon_iso")) continue;

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

	// check to see if the jet meets our criteria
	if (jet.m_lvec.Pt() < CUTS.Get<float>("jet_pt") || 
	fabs(jet.m_lvec.Eta()) > CUTS.Get<float>("jet_eta")) continue;

	// ignore jets that overlap with leptons
	if (jet.IsLepton(Elec_jetOverlap)) continue;
	if (jet.IsLepton(Muon_jetOverlap)) continue;

	if (Jet_jetId[i] <= 0) continue;

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
   h_nLJets->SetXTitle("nJets"); h_nLJets->SetYTitle("Events/2 GeV");
   lHists.push_back(h_nLJets);

   h_bMET = new TH1F("MET", "MET Analysis", 150, -0.5, 299.5);
   h_bMET->SetXTitle("MET [GeV]"); h_bMET->SetYTitle("Events/2 GeV");
   bHists.push_back(h_bMET);

   h_nBJets = new TH1F("nJets", "No. Jets", 10, -0.5, 9.5);
   h_nBJets->SetXTitle("nJets"); h_nBJets->SetYTitle("Events/2 GeV");
   bHists.push_back(h_nBJets);

   h_cMET = new TH1F("MET", "MET Analysis", 150, -0.5, 299.5);
   h_cMET->SetXTitle("MET [GeV]"); h_cMET->SetYTitle("Events/2 GeV");
   cHists.push_back(h_cMET);

   h_nCJets = new TH1F("nJets", "No. Jets", 10, -0.5, 9.5);
   h_nCJets->SetXTitle("nJets"); h_nCJets->SetYTitle("Events/2 GeV");
   cHists.push_back(h_nCJets);

   h_Zee_lJet = new TH1F("Z_ee_mass", "Di-electron mass", 25, 69.5, 119.5);
   h_Zee_lJet->SetXTitle("m_{ee} [GeV]"); h_Zee_lJet->SetYTitle("Events/2 GeV");
   lHists_noT.push_back(h_Zee_lJet);

   h_Zmm_lJet = new TH1F("Z_mm_mass", "Di-muon mass", 25, 69.5, 119.5);
   h_Zmm_lJet->SetXTitle("m_{#mu#mu} [GeV]"); h_Zmm_lJet->SetYTitle("Events/2 GeV");
   lHists_noT.push_back(h_Zmm_lJet);
   
   h_Zee_bJet = new TH1F("Z_ee_mass", "Di-electron mass", 25, 69.5, 119.5);
   h_Zee_bJet->SetXTitle("m_{ee} [GeV]"); h_Zee_bJet->SetYTitle("Events/2 GeV");
   bHists_noT.push_back(h_Zee_bJet);
            
   h_Zmm_bJet = new TH1F("Z_mm_mass", "Di-muon mass", 25, 69.5, 119.5);
   h_Zmm_bJet->SetXTitle("m_{#mu#mu} [GeV]"); h_Zmm_bJet->SetYTitle("Events/2 GeV"); 
   bHists_noT.push_back(h_Zmm_bJet);
            
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

   // Get the information from the event
   BuildEvent();
   if (Jets.size() == 0) return false;

   // Split the jets into categories
   std::vector<JetObj> bJets, lJets, cJets;

   for (int i = 0; i < Jets.size(); ++i)
   {
	float csv = Jets.at(i).m_deepCSV;
	if (csv >= CUTS.Get<float>("jet_deepCSVM_2016"))
		bJets.push_back(Jets.at(i));
	else lJets.push_back(Jets.at(i));
   }

   // Determine if we have electrons or muons
   bool elecTrig = false; bool muonTrig = false;
   if (*HLT_Ele27_WPTight_Gsf) elecTrig = true;
   if (*HLT_IsoMu24 || *HLT_IsoTkMu24) muonTrig = true;

   // //////////////////////////////////////////
   // Zee + jets
   // //////////////////////////////////////////
   if (elecTrig)
   {
	if (Electrons.size() >= 2 && Electrons[0].m_lvec.Pt() >= CUTS.Get<float>("lep_pt0"))
	{
		ZObj Z(Electrons[0], Electrons[1]);
		float mZ = Z.m_lvec.M();
		//if (mZ >= CUTS.Get<float>("ZMassL") && mZ <= CUTS.Get<float>("ZMassH"))
		//	h_Zee_mass->Fill(mZ);
	}
   }

   // /////////////////////////////////////////////
   // Zmumu + jets
   // /////////////////////////////////////////////

   if (muonTrig)
   {
		if (Muons.size() >= 2 && Muons[0].m_lvec.Pt() >= CUTS.Get<float>("lep_pt0"))
		{
			ZObj Z(Muons[0], Muons[1]);
			float mZ = Z.m_lvec.M();
			if (mZ >= CUTS.Get<float>("ZMassL") && mZ <= CUTS.Get<float>("ZMassH"))
			{
				if (bJets.size() > 0 && lJets.size() == 0) 
				{ h_Zmm_bJet->Fill(mZ); }
	 			else if (lJets.size() > 0 && bJets.size() == 0)
				{ h_Zmm_lJet->Fill(mZ); }
			}
		}	
   }

   // /////////////////////////////////////////////
   // MET Analysis (all combined for now)
   // /////////////////////////////////////////////

   if (bJets.size() > 0 && lJets.size() > 0) return false;
   
  	if (bJets.size() > 0) 
	{
   	h_bMET->Fill(*MET_pt);
	bData.push_back(*MET_pt);
   }
   else if (lJets.size() > 0)
   {
	h_lMET->Fill(*MET_pt);
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
