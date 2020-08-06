// include statements ////////////////////////////////////////////////////////////////////
#include "src/TTbarSelector.h"
#include "src/ZxSelector.h"
#include "src/Plots.h"
#include "src/Global.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <string>

// SetParameters method /////////////////////////////////////////////////////////////

void SetParameters(std::string fName, glob::Parameters& para)
{
	std::string line;
	std::ifstream myfile(fName);
	if(myfile.is_open())
	{
	   while(getline(myfile,line))
	   {
		//skip comment line start with "//"
		if(line.find("//") != std::string::npos) continue;

		std::vector<std::string> cont;
		std::vector<std::string> cont_no_space;
		std::string delim(" ");
		boost::split(cont, line, boost::is_any_of(delim));

		for (size_t i = 0; i < cont.size(); ++i) {
			if (cont[i].find_first_not_of(' ') != std::string::npos){
				cont_no_space.push_back(cont[i]);
			}
		}

		if (cont_no_space.size() != 3) {
		   std::cout << "\n Need name, value, value type. Will skip this \"" << line << "\"" << std::endl;
		}
		else {
		   std::string name = cont_no_space[0];
		   if (cont_no_space[2] == "int") para.Set(name, std::stoi(cont[1]));
		   if (cont_no_space[2] == "float") para.Set(name, std::stof(cont_no_space[1]));
		}
	   }

	   myfile.close();
	}

	else std::cout << "Unable to open file" << std::endl;
}

// main method ///////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	// Set the configuration values
	std::string cfgfilename = "Configs/inputParameters.txt";
	SetParameters(cfgfilename, CUTS);

	// Create the ttbar selector & have it read the data
	std::cout << "Entering the analysis..." << std::endl;
	TTbarSelector *ttbar = new TTbarSelector();
	TChain* ch = new TChain("Events");

	// Get the number of events from the command line
	if (argc < 3)
	{
		std::cout << "ERROR: Please run this program while including";
		std::cout << "\n the initial and final entry numbers in the ";
		std::cout << "\n command line. [END PROGRAM]" << std::endl;
		return -1;
	}

	Int_t initEntry = std::atoi(argv[1]);
	Int_t finalEntry = std::atoi(argv[2]);
	
	std::string line;
	std::ifstream myfile("files/ttbarData.txt");
	if (myfile.is_open())
	{
		Int_t nFiles = 0;
		while(getline(myfile,line)) {
			const char* cstr = line.c_str(); 
			ch->Add(cstr); ++nFiles;
		}
		myfile.close();
		std::cout << nFiles << " files added to TTbar analysis..." << std::endl;
	}
	else 
	{
		std::cout << "Unable to open files/ttbarData.txt" << std::endl;
		return -1;
	}

	ch->Process(ttbar, "", finalEntry, initEntry);

	// Create the reader for Z+x and add data to it
	ZxSelector *zhf = new ZxSelector();
	TChain* ch2 = new TChain("Events");

	std::ifstream myfile2("files/dyData.txt");
	if (myfile2.is_open())
	{
		Int_t nFiles = 0;
		while(getline(myfile2,line)) {
			const char* cstr = line.c_str();
			ch2->Add(cstr); ++nFiles;
		}
		myfile2.close();
		std::cout << nFiles << " files added to Z+x analysis..." << std::endl;
	}
	else
	{
		std::cout << "Unable to open files/dyData.txt" << std::endl;
		return -1;
	}

	ch2->Process(zhf, "", finalEntry, initEntry);

	// Plot the main histograms
	Plots p;
	p.AddBg(ttbar->histograms, std::string("TTbar"));
	p.AddBg(zhf->lHists, std::string("Z+l"));
	p.AddBg(zhf->bHists, std::string("Z+b"));
	p.AddBg(zhf->cHists, std::string("Z+c"));
	p.PlotAll(std::string("results/results.pdf"));

	// Generate the ROC curve
	p.AddBgData(ttbar->data, std::string("TTbar"));
	p.AddData(zhf->lData, std::string("Z+l"));
	p.AddData(zhf->bData, std::string("Z+b"));
	p.AddData(zhf->cData, std::string("Z+c"));
	p.PlotROC(std::string("results/results.pdf"));

	// Plot additional useful histograms
	p.AddNoT(zhf->lHists_noT, "Z+l");
	p.AddNoT(zhf->bHists_noT, "Z+b");
	p.AddNoT(zhf->cHists_noT, "Z+c");
	p.PlotStacks();
}
