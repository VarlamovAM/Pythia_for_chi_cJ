DrawHistograms()

{

  TFile *file = new TFile("pythia_chic2.root","old");
  TH1F *hChiC2_pt_all     = (TH1F*)file->Get("hChiC2_pt_all");
  TH1F *hChiC0_pt_all     = (TH1F*)file->Get("hChiC0_pt_all");
  TH1F *hGamma_pt_all     = (TH1F*)file->Get("hGamma_pt_all");
  TH1F *hElectron_pt_all  = (TH1F*)file->Get("hElectron_pt_all"); 
  TH1F *hPositron_pt_all  = (TH1F*)file->Get("hPositron_pt_all");
  TH1F *hChiC2_pt_cndtn_1 = (TH1F*)file->Get("hChiC2_pt_cndtn_1");
  TH1F *hChiC2_y_cndtn_1  = (TH1F*)file->Get("hChiC2_y_cndtn_1");
  TH1F *hChiC2_pt_cndtn_2 = (TH1F*)file->Get("hChiC2_pt_cndtn_2");
  TH1F *hChiC2_y_cndtn_2  = (TH1F*)file->Get("hChiC2_y_cndtn_2");

  //hChiC2_pt_All

  hChiC2_pt_all        ->SetXTitle("p_{T}, GeV/c");
  hChiC2_pt_all        ->SetYTitle("d#sigma/dp_{T}, mb/(GeV/c)");
  hChiC2_pt_all        ->SetTitleOffset(1.4,"Y");
  // hChiC2_pt_all        ->SetStats(0);
  hChiC2_pt_all        ->SetAxisRange(0.,50.,"X");
  hChiC2_pt_all        ->SetMarkerStyle(20);
  hChiC2_pt_all        ->SetLineWidth(2);

  //hChiC0_pt_All

  hChiC0_pt_all        ->SetXTitle("p_{T}, GeV/c");
  hChiC0_pt_all        ->SetYTitle("d#sigma/dp_{T}, mb/(GeV/c)");
  hChiC0_pt_all        ->SetTitleOffset(1.4,"Y");
  //hChiC0_pt_all        ->SetStats(0);
  hChiC0_pt_all        ->SetAxisRange(0.,50.,"X");
  hChiC0_pt_all        ->SetMarkerStyle(20);
  hChiC0_pt_all        ->SetLineWidth(2);

  //hGamma
  
  hGamma_pt_all        ->SetXTitle("p_{T}, GeV/c");
  hGamma_pt_all        ->SetYTitle("d#sigma/dp_{T}, mb/(GeV/c)");
  hGamma_pt_all        ->SetAxisRange(0.,5.,"X");
  hGamma_pt_all        ->SetStats(0);
  hGamma_pt_all        ->SetTitleOffset(1.5,"Y");
  hGamma_pt_all        ->SetMarkerStyle(20);
  hGamma_pt_all        ->SetLineWidth(2);

 //hElectron

  hElectron_pt_all     ->SetXTitle("p_{T}, GeV/c");
  hElectron_pt_all     ->SetYTitle("d#sigma/dp_{T}, mb/(GeV/c)");
  hElectron_pt_all     ->SetStats(0);
  hElectron_pt_all     ->SetAxisRange(0.,15.,"X");
  hElectron_pt_all     ->SetTitleOffset(1.5,"Y");
  hElectron_pt_all     ->SetMarkerStyle(20);
  hElectron_pt_all     ->SetLineWidth(2);


  //hPositron

  hPositron_pt_all     ->SetXTitle("p_{T}, GeV/c");
  hPositron_pt_all     ->SetYTitle("d#sigma/dp_{T}, mb/(GeV/c)");
  //hPositron_pt_all     ->SetStats(0);
  hPositron_pt_all     ->SetAxisRange(0.,18.,"X");
  hPositron_pt_all     ->SetTitleOffset(1.5,"Y");
  hPositron_pt_all     ->SetMarkerStyle(20);
  hPositron_pt_all     ->SetLineWidth(2);

  //hChiC2_pt_cndtn_1
  
  hChiC2_pt_cndtn_1    ->SetXTitle("p_{T}, GeV/c");
  hChiC2_pt_cndtn_1    ->SetYTitle("d#sigma/dp_{T}, mb/(GeV/c)");
  hChiC2_pt_cndtn_1    ->SetStats(0);
  hChiC2_pt_cndtn_1    ->SetAxisRange(0.,25.,"X");
  hChiC2_pt_cndtn_1    ->SetTitleOffset(1.5,"Y");
  hChiC2_pt_cndtn_1    ->SetMarkerStyle(20);
  hChiC2_pt_cndtn_1    ->SetLineWidth(2);

  //hChic2_pt_cndnt_2

  hChiC2_pt_cndtn_2    ->SetXTitle("p_{T}, GeV/c");
  hChiC2_pt_cndtn_2    ->SetYTitle("d#sigma/dp_{T}, mb/(GeV/c)");
  hChiC2_pt_cndtn_2    ->SetStats(0);
  hChiC2_pt_cndtn_2    ->SetAxisRange(0.,50.,"X");
  hChiC2_pt_cndtn_2    ->SetTitleOffset(1.5,"Y");
  hChiC2_pt_cndtn_2    ->SetMarkerStyle(20);
  hChiC2_pt_cndtn_2    ->SetLineWidth(2);

  //hChiC2_y_cndnt_1
 
  hChiC2_y_cndtn_1     ->SetXTitle("y");
  hChiC2_y_cndtn_1     ->SetYTitle("d#sigma/dy");
  hChiC2_y_cndtn_1     ->SetStats(0);
  hChiC2_y_cndtn_1     ->SetAxisRange(0.,20,"X");
  hChiC2_y_cndtn_1     ->SetTitleOffset(1.5,"Y");
  hChiC2_y_cndtn_1     ->SetMarkerStyle(20);
  hChiC2_y_cndtn_1     ->SetLineWidth(2); 

  //hChiC2_y_cndtn_2

  hChiC2_y_cndtn_2     ->SetXTitle("y");
  hChiC2_y_cndtn_2     ->SetYTitle("d#sigma/dy");
  hChiC2_y_cndtn_2     ->SetStats(0);
  hChiC2_y_cndtn_2     ->SetAxisRange(0.,5,"X");
  hChiC2_y_cndtn_2     ->SetTitleOffset(1.5,"Y");
  hChiC2_y_cndtn_2     ->SetMarkerStyle(20);
  hChiC2_y_cndtn_2     ->SetLineWidth(2);


  //TCanvas *c1 = new TCanvas("c1","hChiC2_pt_all",0,0,800,600);
  //hChiC2_pt_all        ->Draw();
  //c1->Print("hChiC2_pt_all.pdf");

  //TCanvas *c2 = new TCanvas("c2","hgamma",0,0,800,600);
  //hGamma_pt_all        ->Draw();
  //c2->Print("hGamma_pt-all.pdf");

  //TCanvas *c3 = new TCanvas("c3","hElectron",0,0,800,600);
  //hElectron_pt_all     ->Draw();
  // c3->Print("hElectron_pt-all.pdf");

  //TCanvas *c4 = new TCanvas("c4","hPositron",0,0,800,600);
  //hPositron_pt_all     ->Draw();
  //c4->Print("hPositron_pt-all.pdf");

  //TCanvas *c5 = new TCanvas("c5","hChiC2_pt_cndtn_1",0,0,800,600);
  //hChiC2_pt_cndtn_1    ->Draw();
  //c5->Print("hChiC2_pt_cndtn_1.pdf");

  //TCanvas *c6 = new TCanvas("c6","hChiC2_pt_cndtn_2",0,0,800,600);
  // hChiC2_pt_cndtn_2    ->Draw();
  //c6->Print("hChiC2_pt_cndtn_2.pdf");

  // TCanvas *c7 = new TCanvas("c7","hChiC2_y_cndtn_1",0,0,800,600);
  //hChiC2_y_cndtn_1     ->Draw();
  //c7->Print("hChiC2_y_cndtn_1.pdf");

  //TCanvas *c8 = new TCanvas("c8","hChiC2_y_cndtn_2",0,0,800,600);
  //hChiC2_y_cndtn_2     ->Draw();
  //c8->Print("hChiC2_y_cndtn_2.pdf");

  //TCanvas *c9 = new TCanvas("c9","hChiC0_pt_all",0,0,800,600);
  //hChiC0_pt_all     ->Draw();
  //c9->Print("hChiC2_pt_all.pdf");

}
