#ifndef PLOTS_H
#define PLOTS_H

#include <vector>
#include <string>
#include <iostream>

#include <TH1F.h>
#include <TFile.h>
#include <TStyle.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TROOT.h>

using namespace std;

class Plots
{
public:
	Plots();
	virtual ~Plots();
	virtual void PlotRest(vector<TH1F*>& v);
	virtual void PlotAll(string filename);
	virtual void PlotROC(string filename);

	void AddBgData(vector<Float_t> v, string n)
	{
		tData = v;
		bgName = n;
	}

	void AddData(vector<Float_t> v, string n)
	{
		zData.push_back(v);
		names.push_back(n);
	}

	void SetData(vector<TH1F*> v, string n)
	{
		data.push_back(v);
		data_names.push_back(n);
		N_histos = v.size();
	}

	void ClearData()
	{
		data.clear();
		data_names.clear();
	}

	void AddBg(vector<TH1F*> v, string n)
	{
		bg.push_back(v);
		bg_names.push_back(n);
		N_histos = v.size();
	}

	void ClearBg()
	{
		bg.clear();
		bg_names.clear();
	}

	void AddSig(vector<TH1F*> v, string n)
	{
		signal.push_back(v);
		signal_names.push_back(n);
		N_histos = v.size();
	}

	void ClearSig()
	{
		signal.clear();
		signal_names.clear();
	}

private:
	vector<vector<TH1F*>> data;
	vector<vector<TH1F*>> bg;
	vector<vector<TH1F*>> signal;
	
	vector<string> data_names;
	vector<string> bg_names;
	vector<string> signal_names;

	int N_histos;

	vector<Float_t> tData;
	vector<vector<Float_t>> zData;
	string bgName;
	vector<string> names;
};

#endif
