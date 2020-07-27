#ifndef Global_h
#define Global_h

#include <iostream>
#include <algorithm>
#include <vector>

namespace glob{
   const float M_ELEC(0.000511);	//GeV
   const float M_MUON(0.105658);	//GeV

   class Parameters {

	public:
	   Parameters() {
		parameterNames.push_back("lep_pt0");
		parameterNames.push_back("lep_pt1");
		parameterNames.push_back("muon_iso");
		parameterNames.push_back("lep_eta");
		parameterNames.push_back("ZMassL");
		parameterNames.push_back("ZMassH");
		parameterNames.push_back("lep_jetOverlap_pt") ;
        	parameterNames.push_back("lep_jetOverlap_eta") ;
        	parameterNames.push_back("jet_pt") ;
        	parameterNames.push_back("jet_eta") ;
        	parameterNames.push_back("jet_deepCSVM_2016") ;
        	parameterNames.push_back("jet_deepCSVM_2017") ;
        	parameterNames.push_back("jet_deepCSVM_2018") ;
        	parameterNames.push_back("jet_deepJetM_2016") ;
       	 	parameterNames.push_back("jet_deepJetM_2017") ;
        	parameterNames.push_back("jet_deepJetM_2018") ;
	   };

	   template<class T> T Get(const std::string& name) {
		if (std::count(parameterNames.begin(), parameterNames.end(),name)) {
		   if (name == "lep_pt0") return lep_pt0 ;
          	   if (name == "lep_pt1") return lep_pt1 ;
          	   if (name == "muon_iso") return muon_iso ;
          	   if (name == "lep_eta") return lep_eta ;
          	   if (name == "ZMassL") return ZMassL ;
          	   if (name == "ZMassH") return ZMassH ;
          	   if (name == "lep_jetOverlap_pt") return lep_jetOverlap_pt ;
          	   if (name == "lep_jetOverlap_eta") return lep_jetOverlap_eta ;
          	   if (name == "lep_eta") return lep_eta ;
          	   if (name == "jet_pt") return jet_pt ;
          	   if (name == "jet_eta") return jet_eta ;
          	   if (name == "jet_deepCSVM_2016") return jet_deepCSVM_2016 ;
          	   if (name == "jet_deepCSVM_2017") return jet_deepCSVM_2017 ;
         	   if (name == "jet_deepCSVM_2018") return jet_deepCSVM_2018 ;
          	   if (name == "jet_deepJetM_2016") return jet_deepJetM_2016 ;
           	   if (name == "jet_deepJetM_2017") return jet_deepJetM_2017 ;
          	   if (name == "jet_deepJetM_2018") return jet_deepJetM_2018 ;
		}
		else {
		   std::cout << "\n There is no parameter " << name << ". Will terminate" << std::endl;
		   exit(1);
		}
		return 0;
	   };

	   template<class T> void Set(const std::string& name, T val) {
		if (std::count(parameterNames.begin(),parameterNames.end(),name)) {
          		if (name == "lep_pt0") lep_pt0 = val;
          		if (name == "lep_pt1") lep_pt1 = val;
          		if (name == "muon_iso") muon_iso = val;
          		if (name == "lep_eta") lep_eta = val;
          		if (name == "ZMassL") ZMassL = val;
          		if (name == "ZMassH") ZMassH = val;
          		if (name == "lep_jetOverlap_pt") lep_jetOverlap_pt = val;
          		if (name == "lep_jetOverlap_eta") lep_jetOverlap_eta = val;
          		if (name == "jet_pt") jet_pt = val;
          		if (name == "jet_eta") jet_eta = val;
          		if (name == "jet_deepCSVM_2016") jet_deepCSVM_2016 = val;
          		if (name == "jet_deepCSVM_2017") jet_deepCSVM_2017 = val;
          		if (name == "jet_deepCSVM_2018") jet_deepCSVM_2018 = val;
          		if (name == "jet_deepJetM_2016") jet_deepJetM_2016 = val;
          		if (name == "jet_deepJetM_2017") jet_deepJetM_2017 = val;
          		if (name == "jet_deepJetM_2018") jet_deepJetM_2018 = val;
        	}
        	else std::cout << "\n Can not set value for parameter named: " << name << ". Not exist in list of parameters " << std::endl; 	
	   };

	private:
		float lep_pt0;
		float lep_pt1;
		float muon_iso;
		float lep_eta;
		float ZMassL;
		float ZMassH;
		float lep_jetOverlap_pt;
		float lep_jetOverlap_eta;
		float jet_pt;
		float jet_eta;
		float jet_deepCSVM_2016 ;
      		float jet_deepCSVM_2017 ;
      		float jet_deepCSVM_2018 ;
      		float jet_deepJetM_2016 ;
      		float jet_deepJetM_2017 ;
      		float jet_deepJetM_2018 ;
		std::vector<std::string> initializedVars;
		std::vector<std::string> parameterNames;
	};
}

extern glob::Parameters CUTS;

#endif
