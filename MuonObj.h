#ifndef MuonObj_h
#define MuonObj_h

#include <TLorentzVector.h>

class MuonObj : public TLorentzVector
{
public:
	MuonObj();
	MuonObj(double px, double py, double pz, double e)
	{ SetPxPyPzE(px, py, pz, e); }
	virtual ~MuonObj();

	void SetIsolation(double x) { iso = x; };
	void SetCharge(int q) { charge = q; };
	
	const double GetIsolation() { return iso; };
	const bool IsIsolated(double relcut = 0.05)
	{ return ((iso/Pt()) < relcut); }
	const int GetCharge() { return charge; }

private:
	double iso;
	int charge;
};

#endif
