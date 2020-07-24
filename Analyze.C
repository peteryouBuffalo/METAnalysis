// include statements ////////////////////////////////////////////////////////////////////
#include "src/TTbarSelector.h"
#include "src/ZxSelector.h"
#include "src/Plots.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <string>

// main method ///////////////////////////////////////////////////////////////////////////

int main(int argc, char**argv)
{
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

	Plots p;
	p.AddBg(ttbar->histograms, std::string("TTbar"));
	p.AddBg(zhf->bHists, std::string("Z+b"));
	p.PlotAll(std::string("results/results.pdf"));
}
