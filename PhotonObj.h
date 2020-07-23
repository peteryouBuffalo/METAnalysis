#ifndef PhotonObj_h
#define PhotonObj_h

#include <TLorentzVector.h>

class PhotonObj : public TLorentzVector
{
public:
	PhotonObj();
	PhotonObj(double px, double py, double pz, double e)
	{ SetPxPyPzE(px, py, pz, e); }
	virtual ~PhotonObj();

	void SetIsolation(double x) { iso = x; };
	const double GetIsolation() { return iso; };
	const bool IsIsolated() { return (iso < 1.); };
private:
	double iso;
};

#endif
