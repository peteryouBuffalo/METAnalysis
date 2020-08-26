#include "Plots.h"
#include <TFile.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TLatex.h>

Plots::Plots() {} 
Plots::~Plots() {}

void Plots::PlotGraphs()
{

}

void Plots::PlotStacks()
{
	TFile *f = new TFile("results/out.root", "UPDATE");
	
	for (Int_t i = 0; i < N_noT; ++i)
	{
		// for each unique histogram, let's make a stacked histogram
		// of all the data sets (Z+l, Z+b, Z+c)
		THStack *hs; TLegend *l;
			
		int Nset = noTdata.size();
		l = new TLegend(0.76, 0.95-0.8*Nset/20.,1.0,0.95);
		l->SetFillStyle(1001);
		l->SetFillColor(kWhite);
		l->SetLineColor(kWhite);
		l->SetLineWidth(2);
		
		if (noTdata.size() == 0) continue;
		
		float L_lJet;
		
		std::string n = "hs" + std::to_string(i);
		hs = new THStack(n.c_str(), noTdata.at(0).at(i)->GetName());
		for (int j = 0; j < noTdata.size(); ++j)
		{
			// for the j'th dataset, get the i'th histogram
			TH1F* hTemp = noTdata.at(j).at(i);
			
			// set the proper color
			switch(j) {
				case 0:
					hTemp->SetFillColor(kGreen); break;
				case 1:
					hTemp->SetFillColor(kRed); break;
				case 2:
					hTemp->SetFillColor(kBlue); break;
				default:
					hTemp->SetFillColor(kBlack); break;
			}
			
			// Scale as needed
			if (j == 0) L_lJet = hTemp->GetEntries()/(1.271e-06*0.427);
			else if (j == 1)
			{
				float lum = hTemp->GetEntries()/(1.271e-06*0.152);
				float scale = L_lJet / lum;
				hTemp->Scale(scale);
			} 
			else if (j == 2)
			{
				float lum = hTemp->GetEntries()/(1.271e-06*0.119);
				float scale = L_lJet / lum;
				hTemp->Scale(scale);
			}
			
			// add the historam to the stack & legend
			hs->Add(hTemp);
			l->AddEntry(hTemp, noT_names.at(j).c_str(), "f");
			
		}//end-for
		
		// Now that we have created the stack, let's output it
		// using a canvas.
		std::string name = "d" + std::to_string(i);
		TCanvas* c = new TCanvas(name.c_str(), "d", 800, 600);
		//c->SetLogy(true);
		std::string plotname;
		
		if (noTdata.size() > 0)
		{
			plotname = std::string(noTdata.at(0).at(i)->GetName());
			hs->Draw("hist");
			//hs->GetXaxis()->SetNdivisions(505);
			hs->GetXaxis()->SetTitle(noTdata.at(0).at(i)->GetXaxis()->GetTitle());
			hs->GetYaxis()->SetTitle("Events/2 GeV");
			l->Draw("same");
		}//end-if
		
		c->Write(); hs->Write();
	}	
	
	f->Close(); delete f;
}

void Plots::PlotROC(string filename)
{
	TFile *f = new TFile("results/out.root", "UPDATE");
	
	// Generate the efficiencies of the background
	Int_t bgTotal = tData.size(), N = 22;
	Double_t cuts[N], bgEff[N];
	std::vector<std::vector<Double_t>> dataEff;
	std::vector<std::vector<Int_t>> nData;
	
	for (Int_t i = 0; i < N; ++i)
	{
		cuts[i] = i*5;
		Int_t nBg = 0;

		for (Int_t t = 0; t < bgTotal; ++t)
		{ if (tData.at(t) < cuts[i]) ++nBg; }

		bgEff[i] = nBg/(bgTotal*1.0);

		std::vector<Double_t> effAtCutI;
		std::vector<Int_t> nAtCutI;

		// generate the efficiencies for each Z+x set
		for (Int_t j = 0; j < zData.size(); ++j)
		{
			Int_t nSize = zData.at(j).size(), nZ = 0;
			for (Int_t t = 0; t < nSize; ++t)
			{ if (zData.at(j).at(t) < cuts[i]) ++nZ; }

			Double_t zEff = nZ/(nSize*1.0);
			effAtCutI.push_back(zEff);
			nAtCutI.push_back(nZ);
		}

		nData.push_back(nAtCutI);
		dataEff.push_back(effAtCutI);
	}	
	
	TMultiGraph *mg2 = new TMultiGraph("mg2", "Z+f Selection # vs. TTbar Selection #");

	// Now that the data has been calculated, let's appropriately move it 
	// into graphs to add to a canvas & multigraph
	TMultiGraph *mg = new TMultiGraph("mg", "Z+f Selection Eff. vs. TTbar Selection Eff.");
	mg->GetXaxis()->SetTitle("ttbar Selection Eff.");
	//mg->GetXaxis()->SetLimits(0.,1.);
	mg->GetYaxis()->SetTitle("Z+f Selection Eff.");
	//mg->GetYaxis()->SetLimits(0.,1.);	

	TLegend *l = new TLegend(0.68, 0.72, 0.98, 0.92);
	
	for (Int_t i = 0; i < zData.size(); ++i)
	{
		Double_t data[N], numData[N];
		for (Int_t j = 0; j < N; ++j) {
			data[j] = dataEff.at(j).at(i);
			numData[j] = nData.at(j).at(i); 	
		}

		TGraph* gr = new TGraph(N, bgEff, data);
		TGraph* gr2 = new TGraph(N, cuts, numData);
		if (i == 0){ gr->SetLineColor(kGreen); gr2->SetLineColor(kGreen); }
		else if (i == 1){ gr->SetLineColor(kRed); gr2->SetLineColor(kRed); }
		else if (i == 2){ gr->SetLineColor(kBlue); gr2->SetLineColor(kBlue); }
		else {gr->SetLineColor(kMagenta); gr2->SetLineColor(kMagenta); }

		// Add the cut values to the graph
		if (i == 0)
		{
		   for (Int_t j = 0; j < N; ++j)
		   {
			Double_t y = gr->GetY()[j]+0.1;
			if (cuts[j] > 40) y = gr->GetY()[j] - 0.1;
			TLatex *lt = new TLatex(gr->GetX()[j], y, Form("%.1f", cuts[j]));
			lt->SetTextSize(0.03);
			gr->GetListOfFunctions()->Add(lt);
		   }
		}

		mg->Add(gr, "c*"); mg2->Add(gr2, "c*");
		std::string str = names.at(i) + " vs. " + bgName;
		l->AddEntry(gr, str.c_str(), "f");
	}

	// Now that we have the entries made, let's draw everything together.
	TCanvas *cs = new TCanvas("ROC", "", 10, 10, 700, 900);
	mg->Draw("ac*"); l->Draw(); cs->SetGrid();
	gPad->Update(); gPad->Modified();

	cs->Write(); mg2->Write(); f->Close(); delete f;
	//cs->Print(filename.c_str());
}

void Plots::PlotAll(string filename)
{
	// Get the file & update the style so that it meets what we want
	TFile *f = new TFile("results/out.root", "RECREATE");
	//gROOT->Reset();

	//TStyle *MyStyle = new TStyle("MyStyle","My Root Styles");
	/*MyStyle->SetStatColor(0);
	MyStyle->SetCanvasColor(0);
	MyStyle->SetPadColor(0);
	MyStyle->SetPadBorderMode(0);
	MyStyle->SetCanvasBorderMode(0);
	MyStyle->SetFrameBorderMode(0);
	MyStyle->SetOptStat(0);
	MyStyle->SetStatBorderSize(2);
	MyStyle->SetOptTitle(0);
	MyStyle->SetPadTickX(1);
	MyStyle->SetPadTickY(1);
	MyStyle->SetPadBorderSize(2);
	MyStyle->SetPalette(51, 0);
	MyStyle->SetPadBottomMargin(0.15);
	MyStyle->SetPadTopMargin(0.05);
	MyStyle->SetPadLeftMargin(0.15);
	MyStyle->SetPadRightMargin(0.25);
	MyStyle->SetTitleColor(1);
	MyStyle->SetTitleFillColor(0);
	MyStyle->SetTitleFontSize(0.05);
	MyStyle->SetTitleBorderSize(0);
	MyStyle->SetLineWidth(1);
	MyStyle->SetHistLineWidth(3);
	MyStyle->SetLegendBorderSize(0);
	MyStyle->SetNdivisions(502, "x");
	MyStyle->SetMarkerSize(0.8);
	MyStyle->SetTickLength(0.03);
	MyStyle->SetTitleOffset(1.5, "x");
	MyStyle->SetTitleOffset(1.5, "y");
	MyStyle->SetTitleOffset(1.0, "z");
	MyStyle->SetLabelSize(0.05, "x");
	MyStyle->SetLabelSize(0.05, "y");
	MyStyle->SetLabelSize(0.05, "z");
	MyStyle->SetLabelOffset(0.03, "x");
	MyStyle->SetLabelOffset(0.03, "y");
	MyStyle->SetLabelOffset(0.03, "z");
	MyStyle->SetTitleSize(0.05, "x");
	MyStyle->SetTitleSize(0.05, "y");
	MyStyle->SetTitleSize(0.05, "z");
	gROOT->SetStyle("MyStyle");*/

	for (Int_t i = 0; i < N_histos; ++i)
	{
		// for each unique histogram, let's make a stacked histogram
		// of all the data sets (ttbar, Z+l, Z+b, Z+c)
		THStack *hs; TLegend *l;
		int Nset = data.size() + bg.size() + signal.size();
		l = new TLegend(0.76,0.95-0.8*Nset/20.,1.0,0.95);
		l->SetFillStyle(1001);
		l->SetFillColor(kWhite);
		l->SetLineColor(kWhite);
		l->SetLineWidth(2);

		if (bg.size() == 0) continue;

		std::string n = "hsAll" + std::to_string(i);
		hs = new THStack(n.c_str(), bg.at(0).at(i)->GetName());
		for (int j = 0; j < bg.size(); ++j)
		{
			// for the j'th dataset, get the i'th histogram
			TH1F* hTemp = bg.at(j).at(i);

			// set the proper colors
			switch(j) {
			case 0:
				hTemp->SetFillColor(kYellow); break;
			case 1:
				hTemp->SetFillColor(kGreen); break;
			case 2:
				hTemp->SetFillColor(kRed); break;
			case 3: 
				hTemp->SetFillColor(kBlue); break;
			default:
				hTemp->SetFillColor(kBlack); break;
			}

			// determine the proper scale
			double scale = 1;
			double L_ttbar = 20000/8.794e-08;
			double L_lJet = hTemp->GetEntries()/(1.271e-06*0.427);
			double L_bJet = hTemp->GetEntries()/(1.271e-06*0.152);
			double L_cJet = hTemp->GetEntries()/(1.271e-06*0.119);

			switch(j) {
			case 0:
				scale = 1; break;
			case 1:
				scale = L_ttbar / L_lJet; break;
			case 2:
				scale = L_ttbar / L_bJet; break;
			case 3: 
				scale = L_ttbar / L_cJet; break;
			default:
				scale = 1; break;
			}

			hTemp->Scale(scale);
			
			// add the histogram to the stack & legend
			hs->Add(hTemp);
			l->AddEntry(hTemp, bg_names.at(j).c_str(), "f");
		}//end-for

		// now that we have created the stack, let's output it
		// using a canvas.
		std::string name = "c"+ std::to_string(i);
		TCanvas* c = new TCanvas(name.c_str(), "c", 800, 600);
		c->SetLogy(true);
		std::string plotname;

		if (data.size() == 0 && bg.size() > 0)
		{
			plotname = std::string(bg.at(0).at(i)->GetName());
			hs->Draw("hist");
			hs->GetXaxis()->SetNdivisions(505);
			hs->GetXaxis()->SetTitle(bg.at(0).at(i)->GetXaxis()->GetTitle());
			hs->GetYaxis()->SetTitle("Events/2 GeV");
			l->Draw("same");
		}//end-if
		
		c->Write(); hs->Write();
	}
	f->Close(); delete f;
}//end-method
