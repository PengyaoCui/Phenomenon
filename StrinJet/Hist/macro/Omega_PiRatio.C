void Omega_PiRatio()
{
//=========Macro generated from canvas: Omega_PiRatio/Omega_PiRatio
//=========  (Tue Nov 16 16:47:38 2021) by ROOT version 6.16/00
   TCanvas *Omega_PiRatio = new TCanvas("Omega_PiRatio", "Omega_PiRatio",87,85,700,500);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   Omega_PiRatio->Range(-3.869047,-0.0001626506,25.89286,0.0009216867);
   Omega_PiRatio->SetFillColor(0);
   Omega_PiRatio->SetBorderMode(0);
   Omega_PiRatio->SetBorderSize(0);
   Omega_PiRatio->SetTickx(1);
   Omega_PiRatio->SetTicky(1);
   Omega_PiRatio->SetLeftMargin(0.13);
   Omega_PiRatio->SetRightMargin(0.03);
   Omega_PiRatio->SetTopMargin(0.02);
   Omega_PiRatio->SetBottomMargin(0.15);
   Omega_PiRatio->SetFrameFillStyle(0);
   Omega_PiRatio->SetFrameBorderMode(0);
   Omega_PiRatio->SetFrameFillStyle(0);
   Omega_PiRatio->SetFrameBorderMode(0);
   
   TH1F *hframe__1 = new TH1F("hframe__1","",1000,0,25);
   hframe__1->SetMinimum(0);
   hframe__1->SetMaximum(0.0009);
   hframe__1->SetDirectory(0);
   hframe__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   hframe__1->SetLineColor(ci);
   hframe__1->GetXaxis()->SetTitle("<d#it{N}_{ch}/d#eta>_{|#eta|<0.5}");
   hframe__1->GetXaxis()->SetNdivisions(505);
   hframe__1->GetXaxis()->SetLabelFont(42);
   hframe__1->GetXaxis()->SetLabelOffset(0.01);
   hframe__1->GetXaxis()->SetLabelSize(0.05);
   hframe__1->GetXaxis()->SetTitleSize(0.05);
   hframe__1->GetXaxis()->SetTitleOffset(1.3);
   hframe__1->GetXaxis()->SetTitleFont(42);
   hframe__1->GetYaxis()->SetTitle("#Omega/#pi");
   hframe__1->GetYaxis()->SetNdivisions(505);
   hframe__1->GetYaxis()->SetLabelFont(42);
   hframe__1->GetYaxis()->SetLabelOffset(0.01);
   hframe__1->GetYaxis()->SetLabelSize(0.05);
   hframe__1->GetYaxis()->SetTitleSize(0.05);
   hframe__1->GetYaxis()->SetTitleOffset(1.1);
   hframe__1->GetYaxis()->SetTitleFont(42);
   hframe__1->GetZaxis()->SetLabelFont(42);
   hframe__1->GetZaxis()->SetLabelSize(0.045);
   hframe__1->GetZaxis()->SetTitleSize(0.05);
   hframe__1->GetZaxis()->SetTitleOffset(1);
   hframe__1->GetZaxis()->SetTitleFont(42);
   hframe__1->Draw(" ");
   Double_t xAxis1[10] = {2.75, 3.03, 5.87, 6.25, 8.72, 9.26, 12.11, 12.85, 16.95, 17.99}; 
   
   TH1F *Hist1D_y1_copy__2 = new TH1F("Hist1D_y1_copy__2","doi:10.17182/hepdata.77284.v1/t39",9, xAxis1);
   Hist1D_y1_copy__2->SetBinContent(1,0.0001912);
   Hist1D_y1_copy__2->SetBinContent(3,0.0003093);
   Hist1D_y1_copy__2->SetBinContent(5,0.0003376);
   Hist1D_y1_copy__2->SetBinContent(7,0.0004221);
   Hist1D_y1_copy__2->SetBinContent(9,0.0004976);
   Hist1D_y1_copy__2->SetBinError(1,1.998e-05);
   Hist1D_y1_copy__2->SetBinError(3,1.958e-05);
   Hist1D_y1_copy__2->SetBinError(5,1.079e-05);
   Hist1D_y1_copy__2->SetBinError(7,1.62e-05);
   Hist1D_y1_copy__2->SetBinError(9,1.588e-05);
   Hist1D_y1_copy__2->SetEntries(5);
   Hist1D_y1_copy__2->SetDirectory(0);
   Hist1D_y1_copy__2->SetFillStyle(0);
   Hist1D_y1_copy__2->SetLineWidth(2);
   Hist1D_y1_copy__2->SetMarkerStyle(20);
   Hist1D_y1_copy__2->GetXaxis()->SetTitle("$\\langle dN_{ch}/d\\eta \\rangle_{|\\eta|<0.5}$");
   Hist1D_y1_copy__2->GetXaxis()->SetLabelFont(42);
   Hist1D_y1_copy__2->GetXaxis()->SetLabelSize(0.035);
   Hist1D_y1_copy__2->GetXaxis()->SetTitleSize(0.035);
   Hist1D_y1_copy__2->GetXaxis()->SetTitleOffset(1);
   Hist1D_y1_copy__2->GetXaxis()->SetTitleFont(42);
   Hist1D_y1_copy__2->GetYaxis()->SetTitle("Ratios of yields to $(\\pi^{+}+\\pi^{-})$");
   Hist1D_y1_copy__2->GetYaxis()->SetLabelFont(42);
   Hist1D_y1_copy__2->GetYaxis()->SetLabelSize(0.035);
   Hist1D_y1_copy__2->GetYaxis()->SetTitleSize(0.035);
   Hist1D_y1_copy__2->GetYaxis()->SetTitleFont(42);
   Hist1D_y1_copy__2->GetZaxis()->SetLabelFont(42);
   Hist1D_y1_copy__2->GetZaxis()->SetLabelSize(0.035);
   Hist1D_y1_copy__2->GetZaxis()->SetTitleSize(0.035);
   Hist1D_y1_copy__2->GetZaxis()->SetTitleOffset(1);
   Hist1D_y1_copy__2->GetZaxis()->SetTitleFont(42);
   Hist1D_y1_copy__2->Draw("same");
   
   Double_t Graph1D_y1_fx3001[5] = {
   17.47,
   12.48,
   8.99,
   6.06,
   2.89};
   Double_t Graph1D_y1_fy3001[5] = {
   0.0004976,
   0.0004221,
   0.0003376,
   0.0003093,
   0.0001912};
   Double_t Graph1D_y1_felx3001[5] = {
   0.52,
   0.37,
   0.27,
   0.19,
   0.14};
   Double_t Graph1D_y1_fely3001[5] = {
   5.745576e-05,
   5.576653e-05,
   4.238418e-05,
   5.479474e-05,
   4.987493e-05};
   Double_t Graph1D_y1_fehx3001[5] = {
   0.52,
   0.37,
   0.27,
   0.19,
   0.14};
   Double_t Graph1D_y1_fehy3001[5] = {
   5.745576e-05,
   5.576653e-05,
   4.238418e-05,
   5.479474e-05,
   4.987493e-05};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(5,Graph1D_y1_fx3001,Graph1D_y1_fy3001,Graph1D_y1_felx3001,Graph1D_y1_fehx3001,Graph1D_y1_fely3001,Graph1D_y1_fehy3001);
   grae->SetName("Graph1D_y1");
   grae->SetTitle("doi:10.17182/hepdata.77284.v1/t39");
   grae->SetFillColor(1);
   grae->SetFillStyle(0);
   grae->SetLineWidth(2);
   
   TH1F *Graph_Graph1D_y13001 = new TH1F("Graph_Graph1D_y13001","doi:10.17182/hepdata.77284.v1/t39",100,1.226,19.514);
   Graph_Graph1D_y13001->SetMinimum(9.9952e-05);
   Graph_Graph1D_y13001->SetMaximum(0.0005964288);
   Graph_Graph1D_y13001->SetDirectory(0);
   Graph_Graph1D_y13001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1D_y13001->SetLineColor(ci);
   Graph_Graph1D_y13001->GetXaxis()->SetTitle("$\\langle dN_{ch}/d\\eta \\rangle_{|\\eta|<0.5}$");
   Graph_Graph1D_y13001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleFont(42);
   Graph_Graph1D_y13001->GetYaxis()->SetTitle("Ratios of yields to $(\\pi^{+}+\\pi^{-})$");
   Graph_Graph1D_y13001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1D_y13001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1D_y13001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1D_y13001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph1D_y13001);
   
   grae->Draw("e2");
   
   Double_t Graph0_fx1001[10] = {
   2.25,
   3.45,
   5.15,
   6.65,
   8.45,
   10.05,
   11.45,
   13.05,
   15.65,
   19.25};
   Double_t Graph0_fy1001[10] = {
   0.06694963,
   0.06641083,
   0.06703075,
   0.0670206,
   0.06705296,
   0.06698426,
   0.0672475,
   0.06743896,
   0.06754859,
   0.06750889};
   Double_t Graph0_fex1001[10] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1001[10] = {
   0.0001849288,
   0.0001764364,
   0.0002143106,
   0.0001786698,
   0.0001728537,
   0.0002232102,
   0.000207209,
   0.0001937807,
   0.0002041529,
   0.0003621373};
   TGraphErrors *gre = new TGraphErrors(10,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetFillStyle(0);
   gre->SetLineStyle(0);
   gre->SetLineWidth(2);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","Graph",100,0.55,20.95);
   Graph_Graph01001->SetMinimum(0.06607072);
   Graph_Graph01001->SetMaximum(0.0680347);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01001->GetXaxis()->SetLabelSize(0.045);
   Graph_Graph01001->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01001->GetYaxis()->SetLabelSize(0.045);
   Graph_Graph01001->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph01001->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelSize(0.045);
   Graph_Graph01001->GetZaxis()->SetTitleSize(0.05);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("l");
   
   Double_t Graph1_fx1002[10] = {
   2.15,
   3.85,
   5.35,
   6.75,
   8.55,
   10.25,
   11.55,
   13.25,
   15.55,
   18.85};
   Double_t Graph1_fy1002[10] = {
   0.08918596,
   0.1121252,
   0.1296076,
   0.1433651,
   0.1590902,
   0.1709533,
   0.1786546,
   0.1869742,
   0.1965163,
   0.2032165};
   Double_t Graph1_fex1002[10] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1002[10] = {
   0.0002167251,
   0.0002193724,
   0.0002912395,
   0.0002696307,
   0.0002608089,
   0.0003283464,
   0.0003536609,
   0.0003185081,
   0.0003545409,
   0.0006533504};
   gre = new TGraphErrors(10,Graph1_fx1002,Graph1_fy1002,Graph1_fex1002,Graph1_fey1002);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#cc0000");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);
   gre->SetLineStyle(2);
   gre->SetLineWidth(2);
   
   TH1F *Graph_Graph11002 = new TH1F("Graph_Graph11002","Graph",100,0.48,20.52);
   Graph_Graph11002->SetMinimum(0.07747917);
   Graph_Graph11002->SetMaximum(0.2153599);
   Graph_Graph11002->SetDirectory(0);
   Graph_Graph11002->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph11002->SetLineColor(ci);
   Graph_Graph11002->GetXaxis()->SetLabelFont(42);
   Graph_Graph11002->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph11002->GetXaxis()->SetLabelSize(0.045);
   Graph_Graph11002->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph11002->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph11002->GetXaxis()->SetTitleFont(42);
   Graph_Graph11002->GetYaxis()->SetLabelFont(42);
   Graph_Graph11002->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph11002->GetYaxis()->SetLabelSize(0.045);
   Graph_Graph11002->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph11002->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph11002->GetYaxis()->SetTitleFont(42);
   Graph_Graph11002->GetZaxis()->SetLabelFont(42);
   Graph_Graph11002->GetZaxis()->SetLabelSize(0.045);
   Graph_Graph11002->GetZaxis()->SetTitleSize(0.05);
   Graph_Graph11002->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11002);
   
   gre->Draw("l");
   
   Double_t Graph2_fx1003[10] = {
   2.65,
   4.35,
   5.85,
   7.45,
   9.25,
   10.85,
   12.25,
   13.95,
   16.65,
   20.35};
   Double_t Graph2_fy1003[10] = {
   0.07350833,
   0.07694729,
   0.08058451,
   0.08254596,
   0.08467065,
   0.08618265,
   0.08676391,
   0.08834307,
   0.09067227,
   0.09376083};
   Double_t Graph2_fex1003[10] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1003[10] = {
   0.0001781851,
   0.0001678094,
   0.0002195127,
   0.0001874163,
   0.0001851118,
   0.0002431415,
   0.0002273385,
   0.0002153671,
   0.0002270681,
   0.0004208783};
   gre = new TGraphErrors(10,Graph2_fx1003,Graph2_fy1003,Graph2_fex1003,Graph2_fey1003);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#0000cc");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);
   gre->SetLineStyle(3);
   gre->SetLineWidth(2);
   
   TH1F *Graph_Graph21003 = new TH1F("Graph_Graph21003","Graph",100,0.88,22.12);
   Graph_Graph21003->SetMinimum(0.07124499);
   Graph_Graph21003->SetMaximum(0.09626686);
   Graph_Graph21003->SetDirectory(0);
   Graph_Graph21003->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph21003->SetLineColor(ci);
   Graph_Graph21003->GetXaxis()->SetLabelFont(42);
   Graph_Graph21003->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph21003->GetXaxis()->SetLabelSize(0.045);
   Graph_Graph21003->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph21003->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph21003->GetXaxis()->SetTitleFont(42);
   Graph_Graph21003->GetYaxis()->SetLabelFont(42);
   Graph_Graph21003->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph21003->GetYaxis()->SetLabelSize(0.045);
   Graph_Graph21003->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph21003->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph21003->GetYaxis()->SetTitleFont(42);
   Graph_Graph21003->GetZaxis()->SetLabelFont(42);
   Graph_Graph21003->GetZaxis()->SetLabelSize(0.045);
   Graph_Graph21003->GetZaxis()->SetTitleSize(0.05);
   Graph_Graph21003->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21003);
   
   gre->Draw("l");
   
   Double_t Graph3_fx1004[10] = {
   2.45,
   4.05,
   5.45,
   6.75,
   8.55,
   9.95,
   11.35,
   12.95,
   15.15,
   18.35};
   Double_t Graph3_fy1004[10] = {
   0.1236193,
   0.1710221,
   0.2203609,
   0.2570262,
   0.2961525,
   0.3261034,
   0.3452164,
   0.3669141,
   0.3913114,
   0.4146549};
   Double_t Graph3_fex1004[10] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1004[10] = {
   0.0002364306,
   0.0002627394,
   0.0003642368,
   0.0003750336,
   0.0003531697,
   0.0004840136,
   0.0004654482,
   0.0004695817,
   0.0005068708,
   0.0009675297};
   gre = new TGraphErrors(10,Graph3_fx1004,Graph3_fy1004,Graph3_fex1004,Graph3_fey1004);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#006600");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#006600");
   gre->SetLineColor(ci);
   gre->SetLineStyle(5);
   gre->SetLineWidth(2);
   
   TH1F *Graph_Graph31004 = new TH1F("Graph_Graph31004","Graph",100,0.86,19.94);
   Graph_Graph31004->SetMinimum(0.09415897);
   Graph_Graph31004->SetMaximum(0.4448463);
   Graph_Graph31004->SetDirectory(0);
   Graph_Graph31004->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph31004->SetLineColor(ci);
   Graph_Graph31004->GetXaxis()->SetLabelFont(42);
   Graph_Graph31004->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph31004->GetXaxis()->SetLabelSize(0.045);
   Graph_Graph31004->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph31004->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph31004->GetXaxis()->SetTitleFont(42);
   Graph_Graph31004->GetYaxis()->SetLabelFont(42);
   Graph_Graph31004->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph31004->GetYaxis()->SetLabelSize(0.045);
   Graph_Graph31004->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph31004->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph31004->GetYaxis()->SetTitleFont(42);
   Graph_Graph31004->GetZaxis()->SetLabelFont(42);
   Graph_Graph31004->GetZaxis()->SetLabelSize(0.045);
   Graph_Graph31004->GetZaxis()->SetTitleSize(0.05);
   Graph_Graph31004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31004);
   
   gre->Draw("l");
   
   TLegend *leg = new TLegend(0.73,0.68,0.95,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("Graph0","Monash","L");
   entry->SetLineColor(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry->SetTextSize(0.05095541);
   entry=leg->AddEntry("Graph1","CR","L");

   ci = TColor::GetColor("#cc0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry->SetTextSize(0.05095541);
   entry=leg->AddEntry("Graph2","Rope","L");

   ci = TColor::GetColor("#0000cc");
   entry->SetLineColor(ci);
   entry->SetLineStyle(3);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry->SetTextSize(0.05095541);
   entry=leg->AddEntry("Graph3","CR + Rope","L");

   ci = TColor::GetColor("#006600");
   entry->SetLineColor(ci);
   entry->SetLineStyle(5);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry->SetTextSize(0.05095541);
   leg->Draw();
   
   leg = new TLegend(0.16,0.73,0.5,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("Hist1D_y1","Exp data","PF");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry->SetTextSize(0.05095541);
   leg->Draw();
   TLatex *   tex = new TLatex(0.16,0.86,"pp #sqrt{#it{s}} = 7 TeV");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.05095541);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.5,0.05,"(f)");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.07218684);
   tex->SetLineWidth(2);
   tex->Draw();
   Omega_PiRatio->Modified();
   Omega_PiRatio->cd();
   Omega_PiRatio->SetSelected(Omega_PiRatio);
}
