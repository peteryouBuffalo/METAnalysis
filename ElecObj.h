#ifndef ElecObj_h
#define ElecObj_h

#include <TLorentzVector.h>

class ElecObj : public TLorentzVector
{
public:
	ElecObj();
	ElecObj(double px, double py, double pz, double e)
	{ SetPxPyPzE(px, py, pz, e); }
	virtual ~ElecObj();

	void SetIsolation(double x) { iso = x; };
	void SetCharge(int q) { charge = q; };

	const double GetIsolation() { return iso; };
	const bool IsIsolated() { return (iso < 1.); };
	const int GetCharge() { return charge; };
private:
	double iso;
	int charge;
};

#endif
