Double_t Gaus3Sum(Double_t *, Double_t *);
Double_t Gaus(Double_t *, Double_t *);

void FitDeltaM(const Double_t ptMin=5., const Double_t ptMax=10.)
{
  TFile *f = new TFile("chi_cJ_with_modif_spectrum.root");
  TH2F *hMassGamElecPosi_mass_diff_cndtn_1 = (TH2F*)f->Get("hMassGamElecPosi_mass_diff_cndtn_1");
  Int_t iptMin = hMassGamElecPosi_mass_diff_cndtn_1->GetYaxis()->FindBin(ptMin+0.01);
  Int_t iptMax = hMassGamElecPosi_mass_diff_cndtn_1->GetYaxis()->FindBin(ptMax-0.01);
  TH1D *m05 = hMassGamElecPosi_mass_diff_cndtn_1->ProjectionX("m05", iptMin,iptMax);
  m05->SetTitle(Form("#DeltaM, %g<p_{T}<%g GeV/c",ptMin,ptMax));
  m05->SetXTitle("M(#gammae^{+}e^{-})-M(e^{+}e^{-}) (GeV/c^{2})");
  m05->SetYTitle("N events");
  m05->SetLineWidth(2);

  TF1 *fGaus3Sum = new TF1("fGaus3Sum",Gaus3Sum,0.,1.,9);
  fGaus3Sum->SetParName(0,"A_{0}") ;
  fGaus3Sum->SetParName(1,"m_{0}") ;
  fGaus3Sum->SetParName(2,"#sigma_{0}") ;
  fGaus3Sum->SetParName(3,"A_{1}") ;
  fGaus3Sum->SetParName(4,"m_{1}") ;
  fGaus3Sum->SetParName(5,"#sigma_{1}") ;
  fGaus3Sum->SetParName(6,"A_{2}") ;
  fGaus3Sum->SetParName(7,"m_{2}") ;
  fGaus3Sum->SetParName(8,"#sigma_{2}") ;
  fGaus3Sum->SetLineColor(kRed);

  fGaus3Sum->SetParameters(1e4,0.3192,0.015,
			   1e4,0.4148,0.014,
			   1e4,0.4584,0.015);

  fGaus3Sum->SetParLimits(1,0.313,0.318);
  fGaus3Sum->SetParLimits(2,0.012,0.02);

  fGaus3Sum->SetParLimits(4,0.408,0.420);
  fGaus3Sum->SetParLimits(5,0.010,0.020);

  fGaus3Sum->SetParLimits(7,0.455,0.465);
  fGaus3Sum->SetParLimits(8,0.010,0.020);

  gStyle->SetOptFit(111);
  gStyle->SetOptStat(0);
  TGaxis::SetMaxDigits(3);
  m05->SetMinimum(1);
  m05->SetAxisRange(0.21,0.69,"X");

  TCanvas *c1 = new TCanvas("c1","c1");
  m05->Fit(fGaus3Sum,"","",0.25,0.53);

  TF1 *fGausChiC0 = new TF1("fGausChiC0",Gaus,0.,1.,3);
  TF1 *fGausChiC1 = new TF1("fGausChiC1",Gaus,0.,1.,3);
  TF1 *fGausChiC2 = new TF1("fGausChiC2",Gaus,0.,1.,3);
  fGausChiC0->SetParameters(fGaus3Sum->GetParameters());
  fGausChiC1->SetParameters(fGaus3Sum->GetParameters()+3);
  fGausChiC2->SetParameters(fGaus3Sum->GetParameters()+6);
  fGausChiC0->SetLineColor(kBlue);
  fGausChiC1->SetLineColor(kGreen+1);
  fGausChiC2->SetLineColor(kOrange+1);
  
  fGausChiC0->Draw("same");
  fGausChiC1->Draw("same");
  fGausChiC2->Draw("same");
  fGaus3Sum ->Draw("same");
  
  // Find integrals under Gaussians N=sqrt(2pi)*A*sigma/delta(M)
  Double_t nChiC0 = TMath::Sqrt(TMath::TwoPi())*
    fGaus3Sum->GetParameter(0)*fGaus3Sum->GetParameter(2)/m05->GetBinWidth(1);
  Double_t nChiC1 = TMath::Sqrt(TMath::TwoPi())*
    fGaus3Sum->GetParameter(3)*fGaus3Sum->GetParameter(5)/m05->GetBinWidth(1);
  Double_t nChiC2 = TMath::Sqrt(TMath::TwoPi())*
    fGaus3Sum->GetParameter(6)*fGaus3Sum->GetParameter(8)/m05->GetBinWidth(1);

  printf("Number of chi_c0: = %.2e \n",nChiC0);
  printf("Number of chi_c1: = %.2e \n",nChiC1);
  printf("Number of chi_c2: = %.2e \n",nChiC2);
  c1->Print(Form("DeltaMassFit_pt=%g-%g.pdf",ptMin,ptMax));
  
}
//-----------------------------------------------------------------------------
Double_t Gaus3Sum(Double_t *x, Double_t *p)
{
  Double_t dM1 = (x[0]-p[1])/p[2];
  Double_t y1  = p[0]*exp(-dM1*dM1/2.);

  Double_t dM2 = (x[0]-p[4])/p[5];
  Double_t y2  = p[3]*exp(-dM2*dM2/2.);

  Double_t dM3 = (x[0]-p[7])/p[8];
  Double_t y3  = p[6]*exp(-dM3*dM3/2.);
  return y1+y2+y3;
}
//-----------------------------------------------------------------------------
Double_t Gaus(Double_t *x, Double_t *p)
{
  Double_t dM1 = (x[0]-p[1])/p[2];
  Double_t y1  = p[0]*exp(-dM1*dM1/2.);
  return y1;
}
