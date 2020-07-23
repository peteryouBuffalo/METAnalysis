#ifndef JetObj_h
#define JetObj_h

#include <TLorentzVector.h>
#include <TRandom3.h>

class JetObj : public TLorentzVector
{
public:
	JetObj();
	JetObj(double px, double py, double pz, double e)
	{ SetPxPyPzE(px, py, pz, e); }
	virtual ~JetObj();

	void SetBTagDiscriminator(double x) { btag = x; };
	const double GetBTagDiscriminator() { return btag; };
	const bool IsBTagged(double th=1.74) { return (btag > th); };
	void SetJetID(bool id) { jetid = id; }
	const bool GetJetID() { return jetid; }

private:
	double btag;
	bool jetid;
};

#endif
