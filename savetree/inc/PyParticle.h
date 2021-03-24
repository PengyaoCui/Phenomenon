#ifndef ALIPYPARTICLE_H
#define ALIPYPARTICLE_H

#include "TVector3.h"
#include "TObject.h"

class PyParticle : public TObject {

 public :

  //PyParticle() = default;
  PyParticle();
  PyParticle(Int_t ID,
	     Double_t dX,
	     Double_t dY,
	     Double_t dZ,
	     Double_t dPx,
	     Double_t dPy,
	     Double_t dPz,
	     Double_t dEta);
  PyParticle(const PyParticle &src);
  PyParticle& operator=(const PyParticle &src);
  virtual ~PyParticle();
//=============================================================================
  const TVector3 vP() const {return fvP;}


 protected :
  Int_t fID = 0;
  Double_t fX = 0.;
  Double_t fY = 0.;
  Double_t fZ = 0.;
  Double_t fPx = 0.;
  Double_t fPy = 0.;
  Double_t fPz = 0.;
  Double_t fEta = 0.;
  TVector3 fvP;

  ClassDef(PyParticle, 1);
};

#endif
