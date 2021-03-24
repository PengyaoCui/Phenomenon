#if !defined(__CINT__) || defined(__MAKECINT__) || !defined(__CLING__) || defined(__ROOTCLING__)
#include <TCanvas.h>
#include <TString.h>
#endif

TCanvas *MakeCanvas(const TString s)
{
  auto c(new TCanvas(Form("c%s",s.Data()), s.Data(), 700, 500));
  c->Range(0., 0., 1., 1.);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  c->SetRightMargin(0.03);
  c->SetLeftMargin(0.13);
  c->SetTopMargin(0.02);
  c->SetBottomMargin(0.15);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);

  return c;
}

//_____________________________________________________________________________
void CanvasEnd(TCanvas* const c)
{
  if (!c) return;

  c->Modified();
  c->cd();
  c->SetSelected(c);

  return;
}

TPad* MakePadT(TString sName)
{
  TPad *p = new TPad(Form("c%s_U",sName.Data()), Form("%s_U",sName.Data()), 0., 0.35, 1., 1.);
  p->Range(0., 0., 1., 1.);
  p->SetFillColor(0);
  p->SetBorderMode(0);
  p->SetBorderSize(0);
  p->SetRightMargin(0.03);
  p->SetLeftMargin(0.12);
  p->SetTopMargin(0.02);
  p->SetBottomMargin(0.);
  p->SetFrameFillStyle(0);
  p->SetFrameBorderMode(0);
  p->Draw();
  p->cd();

  return p;
}

//_____________________________________________________________________________
TPad* MakePadB(TString sName)
{
  TPad *p = new TPad(Form("c%s_D",sName.Data()), Form("%s_D",sName.Data()), 0., 0. , 1., 0.35);
  p->Range(0., 0., 1., 1.);
  p->SetFillColor(0);
  p->SetBorderMode(0);
  p->SetBorderSize(0);
  p->SetRightMargin(0.03);
  p->SetLeftMargin(0.12);
  p->SetTopMargin(0.);
  p->SetBottomMargin(0.28);
  p->SetFrameFillStyle(0);
  p->SetFrameBorderMode(0);
  p->Draw();
  p->cd();

  return p;
}

//_____________________________________________________________________________
TPad* MakePadTL(TString sName)
{
  TPad *p = new TPad(Form("c%s_TL",sName.Data()), Form("c%s_TL",sName.Data()), 0., 1., 0.52, 0.54);
  p->Range(0., 0., 1., 1.);
  p->SetFillColor(0);
  p->SetBorderMode(0);
  p->SetBorderSize(0);
  p->SetRightMargin(0.);
  p->SetLeftMargin(0.18);
  p->SetTopMargin(0.02);
  p->SetBottomMargin(0.);
  p->SetFrameFillStyle(0);
  p->SetFrameBorderMode(0);
  p->SetTickx();
  p->SetTicky();
  p->Draw();
  p->cd();

  return p;
}

//_____________________________________________________________________________
TPad* MakePadTR(TString sName)
{
  TPad *p = new TPad(Form("c%s_TR",sName.Data()), Form("c%s_TR",sName.Data()), 0.52, 1., 1., 0.54);
  p->Range(0., 0., 1., 1.);
  p->SetFillColor(0);
  p->SetBorderMode(0);
  p->SetBorderSize(0);
  p->SetRightMargin(0.03);
  p->SetLeftMargin(0.);
  p->SetTopMargin(0.02);
  p->SetBottomMargin(0.);
  p->SetFrameFillStyle(0);
  p->SetFrameBorderMode(0);
  p->SetTickx();
  p->SetTicky();
  p->Draw();
  p->cd();

  return p;
}

//_____________________________________________________________________________
TPad* MakePadBL(TString sName)
{
  TPad *p = new TPad(Form("c%s_BL",sName.Data()), Form("c%s_BL",sName.Data()), 0., 0.54, 0.52, 0.);
  p->Range(0., 0., 1., 1.);
  p->SetFillColor(0);
  p->SetBorderMode(0);
  p->SetBorderSize(0);
  p->SetRightMargin(0.);
  p->SetLeftMargin(0.18);
  p->SetTopMargin(0.0);
  p->SetBottomMargin(0.25);
  p->SetFrameFillStyle(0);
  p->SetFrameBorderMode(0);
  p->SetTickx();
  p->SetTicky();
  p->Draw();
  p->cd();

  return p;
}

//_____________________________________________________________________________
TPad* MakePadBR(TString sName)
{
  TPad *p = new TPad(Form("c%s_BR",sName.Data()), Form("c%s_BR",sName.Data()), 0.52, 0.54, 1., 0.);
  p->Range(0., 0., 1., 1.);
  p->SetFillColor(0);
  p->SetBorderMode(0);
  p->SetBorderSize(0);
  p->SetRightMargin(0.03);
  p->SetLeftMargin(0.);
  p->SetTopMargin(0.0);
  p->SetBottomMargin(0.25);
  p->SetFrameFillStyle(0);
  p->SetFrameBorderMode(0);
  p->SetTickx();
  p->SetTicky();
  p->Draw();
  p->cd();

  return p;
}

