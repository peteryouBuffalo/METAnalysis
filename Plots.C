#include "Plots.h"
#include <TFile.h>

Plots::Plots() {} 
Plots::~Plots() {}

void Plots::PlotAll(string filename)
{
	TFile *f = new TFile("out.root", "RECREATE");
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
