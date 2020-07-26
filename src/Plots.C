#include "Plots.h"
#include <TFile.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TLatex.h>

Plots::Plots() {} 
Plots::~Plots() {}

void Plots::PlotROC(string filename)
{
	TFile *f = new TFile("results/out.root", "UPDATE");
	
	// Generate the efficiencies of the background
	Int_t bgTotal = tData.size(), N = 22;
	Double_t cuts[N], bgEff[N];
	std::vector<std::vector<Double_t>> dataEff;

	for (Int_t i = 0; i < N; ++i)
	{
		cuts[i] = i*5;
		Int_t nBg = 0;

		for (Int_t t = 0; t < bgTotal; ++t)
		{ if (tData.at(t) < cuts[i]) ++nBg; }

		bgEff[i] = nBg/(bgTotal*1.0);

		std::vector<Double_t> effAtCutI;

		// generate the efficiencies for each Z+x set
		for (Int_t j = 0; j < zData.size(); ++j)
		{
			Int_t nSize = zData.at(j).size(), nZ = 0;
			for (Int_t t = 0; t < nSize; ++t)
			{ if (zData.at(j).at(t) < cuts[i]) ++nZ; }

			Double_t zEff = nZ/(nSize*1.0);
			effAtCutI.push_back(zEff);
		}

		dataEff.push_back(effAtCutI);
	}	

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
		Double_t data[N];
		for (Int_t j = 0; j < N; ++j)
			data[j] = dataEff.at(j).at(i);

		TGraph* gr = new TGraph(N, bgEff, data);
		if (i == 0) gr->SetLineColor(kGreen);
		else if (i == 1) gr->SetLineColor(kRed);
		else if (i == 2) gr->SetLineColor(kBlue);
		else gr->SetLineColor(kMagenta);

		// Add the cut values to the graph
		if (i == 0)
		{
		   for (Int_t j = 0; j < N; ++j)
		   {
			Double_t y = gr->GetY()[j]+0.1;
			if (cuts[j] > 40) y = gr->GetY()[j] - 0.1;
			TLatex *lt = new TLatex(gr->GetX()[j], y, Form("%.1f", cuts[j]));
			lt->SetTextSize(0.02);
			gr->GetListOfFunctions()->Add(lt);
		   }
		}

		mg->Add(gr, "c*");
		std::string str = names.at(i) + " vs. " + bgName;
		l->AddEntry(gr, str.c_str(), "f");
	}

	// Now that we have the entries made, let's draw everything together.
	TCanvas *cs = new TCanvas("ROC", "", 10, 10, 700, 900);
	mg->Draw("ac*"); l->Draw(); cs->SetGrid();
	gPad->Update(); gPad->Modified();

	cs->Write(); f->Close(); delete f;
	//cs->Print(filename.c_str());
}

void Plots::PlotAll(string filename)
{
	TFile *f = new TFile("results/out.root", "RECREATE");
	gROOT->Reset();

	TStyle *MyStyle = new TStyle("MyStyle","My Root Styles");
	MyStyle->SetStatColor(0);
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
	gROOT->SetStyle("MyStyle");

	for (Int_t i = 0; i < N_histos; ++i)
	{
		THStack *hs;
		TLegend *l;
		int Nset = data.size() + bg.size() + signal.size();
		l = new TLegend(0.76,0.95-0.8*Nset/20., 1.0, 0.95);
		l->SetFillStyle(1001);
		l->SetFillColor(kWhite);
		l->SetLineColor(kWhite);
		l->SetLineWidth(2);

		if (bg.size() > 0)
		{
		    hs = new THStack("hs", bg.at(0).at(i)->GetName());
		    int j = 0;
		    for (std::vector<std::vector<TH1F*>>::const_iterator it = bg.begin(); it != bg.end(); ++it)
		    {
			switch(j) {
			case 0:
				it->at(i)->SetFillColor(kRed); break;
			case 1:
				it->at(i)->SetFillColor(kOrange); break;
			case 2:
				it->at(i)->SetFillColor(kYellow); break;
			case 3:
				it->at(i)->SetFillColor(kGreen); break;
			case 4:
				it->at(i)->SetFillColor(kCyan); break;
			case 5:
				it->at(i)->SetFillColor(kBlue); break;
			case 6:
				it->at(i)->SetFillColor(kMagenta); break;
			case 7:
				it->at(i)->SetFillColor(kGray); break;
			case 8:
				it->at(i)->SetFillColor(kGray+2); break;
			default:
				it->at(i)->SetFillColor(kBlack); break;
			}//end-switch
			hs->Add(it->at(i));
			l->AddEntry(it->at(i), bg_names.at(j).c_str(),"f");
			++j;
		    }//end-for-loop
		}//end-if

		std::string name = "c" + std::to_string(i);
		TCanvas *c = new TCanvas(name.c_str(), "c", 800, 600);
		c->SetLogy(true);
		std::string plotname;
		if (data.size() == 0 && bg.size() > 0)
		{
		   plotname = std::string(bg.at(0).at(i)->GetName());
		   hs->Draw("hist");
		   hs->GetXaxis()->SetTitleOffset(1.3);
		   hs->GetXaxis()->SetNdivisions(505);
		   hs->GetYaxis()->SetTitleOffset(1.3);
		   if (bg.size() > 0)
			hs->GetXaxis()->SetTitle(bg.at(0).at(i)->GetXaxis()->GetTitle());
		   hs->GetYaxis()->SetTitle("Events");
		   l->Draw("same");
		}//end-if

		if (i == 0 && N_histos > 1)
		{ c->Print((filename+std::string("(")).c_str()); }
		else if (i > 0 && i == N_histos - 1)
		{ c->Print((filename+std::string(")")).c_str()); }
		else { c->Print(filename.c_str()); }

		c->Write();

	}//end-for-loop

	f->Close(); delete f;
}//end-method
