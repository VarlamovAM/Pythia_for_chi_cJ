void DrawChiC(const char *part = "ChiC2",const char *cpart = "#chi_{c2}")
{
  TFile *f = new TFile("pythia_chic2_6M_ptHatMin=7.root");

  TH1F * hChiC_pt_all = (TH1F*)f->Get(Form("h%s_pt_all",part));
  TH1F * hChiC_pt_cndtn_2 = (TH1F*)f->Get(Form("h%s_pt_cndtn_2",part));
  TH1F * hChiC_pt_cndtn_1 = (TH1F*)f->Get(Form("h%s_pt_cndtn_1",part));

  hChiC_pt_all    ->Rebin(5);
  hChiC_pt_cndtn_2->Rebin(5);
  hChiC_pt_cndtn_1->Rebin(5);
  hChiC_pt_all    ->SetLineWidth(2);
  hChiC_pt_cndtn_2->SetLineWidth(2);
  hChiC_pt_cndtn_1->SetLineWidth(2);
  hChiC_pt_all    ->SetLineColor(kBlue);
  hChiC_pt_cndtn_2->SetLineColor(kGreen+1);
  hChiC_pt_cndtn_1->SetLineColor(kRed);
  hChiC_pt_all    ->Scale(5./6.);
  hChiC_pt_cndtn_2->Scale(5./6.);
  hChiC_pt_cndtn_1->Scale(5./6.);

  gStyle->SetOptStat(0);
  TCanvas *cChiC = new TCanvas("cChiC");
  gPad->SetLogy();
  hChiC_pt_cndtn_2->SetMaximum(hChiC_pt_all->GetMaximum()*1.5);
  hChiC_pt_cndtn_2->SetXTitle("p_{T} (GeV/c)");
  hChiC_pt_cndtn_2->SetYTitle("d#sigma/dp_{T} (mb/(GeV/c))");
  hChiC_pt_cndtn_2->Draw();
  hChiC_pt_cndtn_1->Draw("same");
  hChiC_pt_all    ->Draw("same");

  TLegend *l1 = new TLegend(0.5,0.7,0.89,0.89);
  l1->AddEntry(hChiC_pt_all,Form("Produced %s#rightarrow#gammae^{+}e^{-}, |y|<0.5  ",cpart),"lp");
  l1->AddEntry(hChiC_pt_cndtn_1,Form("Detected %s, condition 1",cpart),"lp");
  l1->AddEntry(hChiC_pt_cndtn_2,Form("Detected %s, condition 2",cpart),"lp");
  l1->Draw();  
  cChiC->Print(Form("%s_pt.pdf",part));
}
//-----------------------------------------------------------------------------
void DrawChiCMB(const char *part = "ChiC2",const char *cpart = "#chi_{c2}")
{
  TFile *f = new TFile("pythia_chic2_6M_ptHatMin=0.root");

  TH1F * hChiC_pt_all = (TH1F*)f->Get(Form("h%s_pt_all",part));
  TH1F * hChiC_pt_cndtn_2 = (TH1F*)f->Get(Form("h%s_pt_cndtn_2",part));
  TH1F * hChiC_pt_cndtn_1 = (TH1F*)f->Get(Form("h%s_pt_cndtn_1",part));

  hChiC_pt_all    ->Rebin(5);
  hChiC_pt_cndtn_2->Rebin(5);
  hChiC_pt_cndtn_1->Rebin(5);
  hChiC_pt_all    ->SetLineWidth(2);
  hChiC_pt_cndtn_2->SetLineWidth(2);
  hChiC_pt_cndtn_1->SetLineWidth(2);
  hChiC_pt_all    ->SetLineColor(kBlue);
  hChiC_pt_cndtn_2->SetLineColor(kGreen+1);
  hChiC_pt_cndtn_1->SetLineColor(kRed);
  hChiC_pt_all    ->Scale(5./6.);
  hChiC_pt_cndtn_2->Scale(5./6.);
  hChiC_pt_cndtn_1->Scale(5./6.);

  gStyle->SetOptStat(0);
  TCanvas *cChiC = new TCanvas("cChiC");
  gPad->SetLogy();
  hChiC_pt_cndtn_1->SetMaximum(hChiC_pt_all->GetMaximum()*1.5);
  hChiC_pt_cndtn_1->SetXTitle("p_{T} (GeV/c)");
  hChiC_pt_cndtn_1->SetYTitle("d#sigma/dp_{T} (mb/(GeV/c))");
  // hChiC_pt_cndtn_2->Draw();
  hChiC_pt_cndtn_1->Draw();
  hChiC_pt_all    ->Draw("same");

  TLegend *l1 = new TLegend(0.5,0.76,0.89,0.89);
  l1->AddEntry(hChiC_pt_all,Form("Produced %s#rightarrow#gammae^{+}e^{-}, |y|<0.5  ",cpart),"lp");
  l1->AddEntry(hChiC_pt_cndtn_1,Form("Detected %s, condition 1",cpart),"lp");
  // l1->AddEntry(hChiC_pt_cndtn_2,Form("Detected %s, condition 2",cpart),"lp");
  l1->Draw();  
  cChiC->Print(Form("%s_pt_MB.pdf",part));
}
