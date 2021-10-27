#include <TH2D.h>
#include <TMath.h>

#include "./PyParticle.h"

ClassImp(PyParticle)

//_____________________________________________________________________________
PyParticle::PyParticle() :
TObject(),
fID(0),
fCharge(0.),
fX(0.),
fY(0.),
fZ(0.),
fPx(0.),
fPy(0.),
fPz(0.),
fEta(0.)
{
//
//  PyParticle::PyParticle
//
}

PyParticle::PyParticle(Int_t ID,
                       Double_t dCharge,
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
fCharge(dCharge),
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
fID(src.fID),
fCharge(src.fCharge),
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
  fID     = src.fID;
  fCharge = src.fCharge;
  fX      = src.fX;
  fY      = src.fY;
  fZ      = src.fZ;
  fPx     = src.fPx;
  fPy     = src.fPy;
  fPz     = src.fPz;
  fEta    = src.fEta;
  fvP     = src.fvP;
  return *this;
}

//_____________________________________________________________________________
PyParticle::~PyParticle()
{
//
//  PyParticle::~PyParticle
//
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
