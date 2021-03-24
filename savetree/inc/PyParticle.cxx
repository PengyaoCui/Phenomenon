#include <TH2D.h>
#include <TMath.h>
#include <TLorentzVector.h>

#include "AliPicoV0RD.h"
#include "AliPicoV0MC.h"
#include "PyParticle.h"

ClassImp(PyParticle)

//_____________________________________________________________________________
PyParticle::PyParticle() :
TObject(),
Int_t ID(0),
dX(0.),
dY(0.),
dZ(0.),
dPx(0.),
dPy(0.),
dPz(0.),
dEta(0.)
{
//
//  PyParticle::PyParticle
//
}

PyParticle::PyParticle(Int_t ID,
                       Double_t dX,
                       Double_t dY,
                       Double_t dZ,
                       Double_t dPx,
                       Double_t dPy,
                       Double_t dPz,
                       Double_t dEta
                       ) :
TObject(),
fID(ID),
fX(dX),
fY(dY),
fZ(dZ),
fPx(dPx),
fPy(dPy),
fPz(dPz),
fEta(dEta),
fvP(dX, dY, dZ)
{
//
//  PyParticle::PyParticle
//
}

//_____________________________________________________________________________
PyParticle::PyParticle(const PyParticle &src) :
TObject(src),
fID(src.ID),
fX(src.fX),
fY(src.fY),
fZ(src.fZ),
fPx(src.fPx),
fPy(src.fPy),
fPz(src.fPz),
fEta(src.fEta),
fvP(src.fvP)
{
//
//  PyParticle::PyParticle
//
}

//_____________________________________________________________________________
PyParticle& PyParticle::operator=(const PyParticle &src)
{
//
//  PyParticle::operator=
//

  if (&src==this) return *this;

  TObject::operator=(src);
  fID  = src.ID;
  fX   = src.fX;
  fY   = src.fY;
  fZ   = src.fZ;
  fPx  = src.fPx;
  fPy  = src.fPy;
  fPz  = src.fPz;
  fEta = src.fEta;
  fvP  = src.fvP;
  return *this;
}

//_____________________________________________________________________________
PyParticle::~PyParticle()
{
//
//  PyParticle::~PyParticle
//
  if (fID) { delete fID; fID = 0; }
}



//_____________________________________________________________________________
//const TLorentzVector PyParticle::KineXi() const
//{
////
////  const TLorentzVector PyParticle::KineXi() const
////
//
//  TLorentzVector vt;
//  vt.SetVectM(fBachP3, AliPicoBaseDev::MassPion());
//
//  TLorentzVector vv;
//  vv.SetVectM(KineV0(), AliPicoBaseDev::MassLambda());
////=============================================================================
//
//  return (vt + vv);
//}
