// File: hist.cc
// This is a simple test program.
// It studies the charged multiplicity distribution at the LHC.
// Modified by Rene Brun, Axel Naumann and Bernhard Meirose 
// to use ROOT for histogramming.
// Copyright (C) 2013 Torbjorn Sjostrand

// Define environment variable PYTHIA8DATA for xlmdoc directory
// for example:
// export PYTHIA8DATA=$ALICE_ROOT/PYTHIA8/pythia8210/xmldoc/

// Stdlib header file for input and output.
#include <iostream>

// Header file to access Pythia 8 program elements.
// #include "Pythia8/Pythia.h"
#include "Pythia8/Pythia.h"

// ROOT, for histogramming.
#include "TH1.h"
#include "TH2.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, to set random seed (Pythia random seed based on tume does not work!)
#include "TRandom.h"
#include "TMath.h"

// ROOT, for saving file.
#include "TFile.h"

#include "TLorentzVector.h"



using namespace Pythia8;

int main(int argc, char* argv[]) {

  // read input parameters
  printf("argc = %d, argv[0] = %s\n",argc,argv[0]);
  if (argc != 2) {
    printf("Usage: %s <nEvents>\n",argv[0]);
    printf("       <nEvents>=0 is the number of events to generate.\n");
    return 1;
  }
  int nEvents = atoi(argv[1]);
  cout << "nEvents = " << nEvents << endl;

  // Create the ROOT application environment. 
  TApplication theApp("hist", &argc, argv);

  Pythia pythia;

  

  // randon seed
  TRandom rndm;
  rndm.SetSeed(0);
  int pythiaSeed = rndm.Integer(1000000);
  char processLine[80];
  sprintf(processLine, "Random:Seed = %d",pythiaSeed);

  pythia.readString("Random:setSeed = on");
    pythia.readString(processLine); 

  // Set process type and collision energy
  pythia.readString("Charmonium:all  = on");;
  pythia.readString("Beams:eCM = 13000.");

  // Switch off all J/psi decays but J/psi -> e+ e-
  pythia.readString("443:onMode = off");
  pythia.readString("443:onIfAny = 11 -11");

  // Switch off all chi_c2 decays but chi_c2 -> J/psi gamma
  pythia.readString("445:onMode = off");
  pythia.readString("445:onIfAny = 443 22");

  pythia.init();

  cout << "List all decays of particle 10443, 20443, 445\n";
  pythia.particleData.list(10443);
  pythia.particleData.list(20443);
  pythia.particleData.list(445);

  double ptMin = 0.;
  double ptMax = 50.;  //GeV
  double yMin  = 0.; 
  double yMax  = 0.5; 
  

  const int nPtBins = 250;
  const int nyBins = 250; 

  // rapidity range
  double ymax = 0.5;
  
  // create histograms
  TH1F *hChiC2_pt_all     = new TH1F("hChiC2_pt_all"     ,"All #chi_{c2} p_{T} spectrum" , nPtBins, ptMin, ptMax);
  hChiC2_pt_all->Sumw2();

  TH1F *hChiC2_pt_cndtn_1 = new TH1F("hChiC2_pt_cndtn_1" ,"#chi_{c2} p_{T} spectrum"  ,nPtBins, ptMin, ptMax);
  hChiC2_pt_cndtn_1->Sumw2();

  TH1F *hChiC2_y_cndtn_1  = new TH1F("hChiC2_y_cndtn_1"  ,"#chi_{c2} y spectrum"  ,nyBins, yMin, yMax);
  hChiC2_y_cndtn_1->Sumw2(); 

  TH1F *hChiC2_pt_cndtn_2 = new TH1F("hChiC2_pt_cndtn_2" ,"#chi_{c2} p_{T} spectrum"  ,nPtBins, ptMin, ptMax);
  hChiC2_pt_cndtn_2->Sumw2();

  TH1F *hChiC2_y_cndtn_2  = new TH1F("hChiC2_y_cndtn_2"  ,"#chi_{c2} y spectrum"  ,nyBins, yMin, yMax);
  hChiC2_y_cndtn_2->Sumw2();

  TH1F *hGamma_pt_all     = new TH1F("hGamma_pt_all"     ,"#gamma p_{T} spectrum ", nPtBins, ptMin, ptMax);
  hGamma_pt_all->Sumw2();       
  
  TH1F *hPositron_pt_all  = new TH1F("hPositron_pt_all"  ,"e_{+}  p_{T} spectrum", nPtBins, ptMin, ptMax);
  hPositron_pt_all ->Sumw2();

  TH1F *hElectron_pt_all  = new TH1F("hElectron_pt_all"  ,"e_{-}  p_{T} spectrum", nPtBins, ptMin, ptMax);
  hElectron_pt_all ->Sumw2();

  TH1F *hChiC0_pt_all     = new TH1F("hChiC0_pt_all"     ,"All #chi_{c0} p_{T} spectrum" , nPtBins, ptMin, ptMax);
  hChiC0_pt_all->Sumw2();

  TH1F *hChiC0_pt_cndtn_1 = new TH1F("hChiC0_pt_cndtn_1" ,"#chi_{c0} p_{T} spectrum"  ,nPtBins, ptMin, ptMax);
  hChiC0_pt_cndtn_1->Sumw2();

  TH1F *hChiC0_y_cndtn_1  = new TH1F("hChiC0_y_cndtn_1"  ,"#chi_{c0} y spectrum"  ,nyBins, yMin, yMax);
  hChiC0_y_cndtn_1->Sumw2(); 

  TH1F *hChiC0_pt_cndtn_2 = new TH1F("hChiC0_pt_cndtn_2" ,"#chi_{c0} p_{T} spectrum"  ,nPtBins, ptMin, ptMax);
  hChiC0_pt_cndtn_2->Sumw2();

  TH1F *hChiC0_y_cndtn_2  = new TH1F("hChiC0_y_cndtn_2"  ,"#chi_{c0} y spectrum"  ,nyBins, yMin, yMax);
  hChiC0_y_cndtn_2->Sumw2();

  TH1F *hGamma_chic0_pt_all     = new TH1F("hGamma_chic0_pt_all"     ,"#gamma p_{T} spectrum ", nPtBins, ptMin, ptMax);
  hGamma_chic0_pt_all->Sumw2();       
  
  TH1F *hPositron_chic0_pt_all  = new TH1F("hPositron_chic0_pt_all"  ,"e^{+}  p_{T} spectrum", nPtBins, ptMin, ptMax);
  hPositron_chic0_pt_all ->Sumw2();

  TH1F *hElectron_chic0_pt_all  = new TH1F("hElectron_chic0_pt_all"  ,"e^{-}  p_{T} spectrum", nPtBins, ptMin, ptMax);
  hElectron_chic0_pt_all ->Sumw2();

  TH1F *hChiC1_pt_all     = new TH1F("hChiC1_pt_all"     ,"All #chi_{c1} p_{T} spectrum" , nPtBins, ptMin, ptMax);
  hChiC1_pt_all->Sumw2();

  TH1F *hChiC1_pt_cndtn_1 = new TH1F("hChiC1_pt_cndtn_1" ,"#chi_{c1} p_{T} spectrum"  ,nPtBins, ptMin, ptMax);
  hChiC1_pt_cndtn_1->Sumw2();

  TH1F *hChiC1_y_cndtn_1  = new TH1F("hChiC1_y_cndtn_1"  ,"#chi_{c1} y spectrum"  ,nyBins, yMin, yMax);
  hChiC1_y_cndtn_1->Sumw2(); 

  TH1F *hChiC1_pt_cndtn_2 = new TH1F("hChiC1_pt_cndtn_2" ,"#chi_{c1} p_{T} spectrum"  ,nPtBins, ptMin, ptMax);
  hChiC1_pt_cndtn_2->Sumw2();

  TH1F *hChiC1_y_cndtn_2  = new TH1F("hChiC1_y_cndtn_2"  ,"#chi_{c1} y spectrum"  ,nyBins, yMin, yMax);
  hChiC1_y_cndtn_2->Sumw2();

  TH1F *hGamma_chic1_pt_all     = new TH1F("hGamma_chic1_pt_all"     ,"#gamma p_{T} spectrum ", nPtBins, ptMin, ptMax);
  hGamma_chic1_pt_all->Sumw2();       
  
  TH1F *hPositron_chic1_pt_all  = new TH1F("hPositron_chic1_pt_all"  ,"e^{+}  p_{T} spectrum", nPtBins, ptMin, ptMax);
  hPositron_chic1_pt_all ->Sumw2();

  TH1F *hElectron_chic1_pt_all  = new TH1F("hElectron_chic1_pt_all"  ,"e^{-}  p_{T} spectrum", nPtBins, ptMin, ptMax);
  hElectron_chic1_pt_all ->Sumw2();

  TH2F *hMassGamElecPosi = new TH2F("hMassGamElecPosi","M(#gamma e^{+}e^{-}) vs p_{T}",200.,3.,4.,50,0.,50.);

  const int idChic0        =  10441;
  const int idChic1        =  20443;
  const int idChic2        =  445;
  const int idJpsi         =  443;
  const int idElectron     =  11;
  const int idPositron     = -11;
  const int idPhoton       =  22;


  

  // block of constants to Gauss distribution
  
  double a_gam_energy = 0.04;
  double b_gam_energy = 0.036;
  double c_gam_energy = 0.01;

  double a_el_pos_momentum = 0.01;
  double b_el_pos_momentum = 0.001;

  int nEvent2Print = 10;

  // Begin event loop. Generate event

  int iEvent2Print = 0;
  for (int iEvent = 0; iEvent < nEvents; ++iEvent) {
    if (!pythia.next()) continue;

    // Loop over all particles in the generated event
    double px,py,pz,p0,sigma_p0;
    
    for (int i = 0; i < pythia.event.size(); ++i) {
      // Select final-state chi_c2 within |y|<0.5
      if (pythia.event[i].id() == idChic2 &&
	  pythia.event[i].status() == -62 &&
	   fabs(pythia.event[i].y()) <= ymax) {

	// print first nEvent2Print events
	if (iEvent2Print < nEvent2Print) pythia.event.list();
	iEvent2Print++;

	Double_t pt = pythia.event[i].pT(); // transverse momentum
	hChiC2_pt_all->Fill(pt);
	Double_t y  = pythia.event[i].y();

 

	// Find daughters of chi_c2
	int dghtChi1 = pythia.event[i].daughter1(); // first daughter
	int dghtChi2 = pythia.event[i].daughter2(); // last  daughter

	// skip event if the number of chi_c2 daughters is not 2
	if (dghtChi2 - dghtChi1 != 1) continue;

	// select decay chi_c2 -> J/psi gamma
	if ( pythia.event[dghtChi1].id() == idJpsi    &&
	     pythia.event[dghtChi2].id() == idPhoton)  {

	  px = pythia.event[dghtChi2].px();
	  py = pythia.event[dghtChi2].py();
	  pz = pythia.event[dghtChi2].pz();
	  p0 = pythia.event[dghtChi2].e();

	  sigma_p0 = p0 * sqrt(( a_gam_energy * a_gam_energy)/(p0 * p0) + (b_gam_energy*b_gam_energy)/(p0) + (c_gam_energy * c_gam_energy));
	  
	  double p0_rand;

	  p0_rand = rndm.Gaus(p0,sigma_p0);
	  
	  TLorentzVector pGam(px,py,pz,p0_rand);
	  
	  int dghtJ1 = pythia.event[dghtChi1].daughter1();
	  int dghtJ2 = pythia.event[dghtChi1].daughter2();

	  // skip event if the number of J/psi daughters is not 2
	  if (dghtJ2 - dghtJ1 != 1) continue;

	  Double_t pt_gamma = pythia.event[dghtChi2].pT();
	  Double_t eta_gamma = pythia.event[dghtChi2].eta();

	  hGamma_pt_all->Fill(pt_gamma);


	  // select decay J/psi -> e+ e-
	  if (abs(pythia.event[dghtJ1].id()) == idElectron &&
	      abs(pythia.event[dghtJ2].id()) == idElectron) {
              
	    if (pythia.event[dghtJ1].id() == idElectron)  {
	        px = pythia.event[dghtJ1].px();
	        py = pythia.event[dghtJ1].py();
	        pz = pythia.event[dghtJ1].pz();
	        p0 = pythia.event[dghtJ1].e();

		double sigma_p_elec;
		
		double px_rand, py_rand, pz_rand;

		//define sigma for Gauss to electron

		sigma_p_elec = sqrt((px * px) + (py * py) + (pz * pz)) * sqrt(a_el_pos_momentum * a_el_pos_momentum + (b_el_pos_momentum * b_el_pos_momentum) * sqrt((px * px) + (py * py) + (pz * pz)));

		//define random momentum

		px_rand = rndm.Gaus(px,sigma_p_elec);
		py_rand = rndm.Gaus(py,sigma_p_elec);
		pz_rand = rndm.Gaus(pz,sigma_p_elec);


	        TLorentzVector pElec(px_rand,py_rand,pz_rand,p0);

		
	        px = pythia.event[dghtJ2].px();
	        py = pythia.event[dghtJ2].py();
	        pz = pythia.event[dghtJ2].pz();
	        p0 = pythia.event[dghtJ2].e();

		double sigma_p_posi;
		
		//define sigma for Gauss to positron

		sigma_p_posi = sqrt((px * px) + (py * py) + (pz * pz)) * sqrt(a_el_pos_momentum * a_el_pos_momentum + (b_el_pos_momentum * b_el_pos_momentum) * sqrt((px * px) + (py * py) + (pz * pz)));

		//define random momentum

		px_rand = rndm.Gaus(px,sigma_p_elec);
		py_rand = rndm.Gaus(py,sigma_p_elec);
		pz_rand = rndm.Gaus(pz,sigma_p_elec);


	        TLorentzVector pPosi(px_rand,py_rand,pz_rand,p0);

		Double_t massGamElecPosi = (pGam + pElec + pPosi).M();
		Double_t ptGamElecPosi   = (pGam + pElec + pPosi).Pt();
		hMassGamElecPosi->Fill(massGamElecPosi,ptGamElecPosi);
		
	        Double_t pt_positron = pythia.event[dghtJ2].pT();
	        Double_t pt_electron = pythia.event[dghtJ1].pT();

                Double_t eta_positron = pythia.event[dghtJ2].eta();
                Double_t eta_electron = pythia.event[dghtJ1].eta();
                

		hPositron_pt_all->Fill(pt_positron);
	        hElectron_pt_all->Fill(pt_electron);


		if (abs(eta_positron) < 0.8  &&
                    abs(eta_electron) < 0.8  &&
                    abs(eta_gamma)    < 0.12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 1.0) 
		 
		  {  
		  
		    hChiC2_pt_cndtn_1 ->Fill(pt);
		    hChiC2_y_cndtn_1  ->Fill(y);

		  }


		if (abs(eta_positron) < 0.8  &&
                    abs(eta_electron) < 0.8  &&
                    abs(eta_gamma)    < 0.12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 5.0)  
		  
		  { 
		  
		    hChiC2_pt_cndtn_2 ->Fill(pt);
		    hChiC2_y_cndtn_2  ->Fill(y);

		  }
	    }
 

	     if (pythia.event[dghtJ2].id() == idElectron)  {

	       px = pythia.event[dghtJ1].px();
	        py = pythia.event[dghtJ1].py();
	        pz = pythia.event[dghtJ1].pz();
	        p0 = pythia.event[dghtJ1].e();

		double sigma_p_elec;
		
		double px_rand, py_rand, pz_rand;

		//define sigma for Gauss to electron

		sigma_p_elec = sqrt((px * px) + (py * py) + (pz * pz)) * sqrt(a_el_pos_momentum * a_el_pos_momentum + (b_el_pos_momentum * b_el_pos_momentum) * sqrt((px * px) + (py * py) + (pz * pz)));

		//define random momentum

		px_rand = rndm.Gaus(px,sigma_p_elec);
		py_rand = rndm.Gaus(py,sigma_p_elec);
		pz_rand = rndm.Gaus(pz,sigma_p_elec);


	        TLorentzVector pElec(px_rand,py_rand,pz_rand,p0);

		
	        px = pythia.event[dghtJ2].px();
	        py = pythia.event[dghtJ2].py();
	        pz = pythia.event[dghtJ2].pz();
	        p0 = pythia.event[dghtJ2].e();

		double sigma_p_posi;
		
		//define sigma for Gauss to positron

		sigma_p_posi = sqrt((px * px) + (py * py) + (pz * pz)) * sqrt(a_el_pos_momentum * a_el_pos_momentum + (b_el_pos_momentum * b_el_pos_momentum) * sqrt((px * px) + (py * py) + (pz * pz)));

		//define random momentum

		px_rand = rndm.Gaus(px,sigma_p_elec);
		py_rand = rndm.Gaus(py,sigma_p_elec);
		pz_rand = rndm.Gaus(pz,sigma_p_elec);


	        TLorentzVector pPosi(px_rand,py_rand,pz_rand,p0);

		Double_t massGamElecPosi = (pGam + pElec + pPosi).M();
		Double_t ptGamElecPosi   = (pGam + pElec + pPosi).Pt();
		hMassGamElecPosi->Fill(massGamElecPosi,ptGamElecPosi);



	        Double_t pt_positron =pythia.event[dghtJ1].pT();
                Double_t pt_electron = pythia.event[dghtJ2].pT();
       
                Double_t eta_positron = pythia.event[dghtJ1].eta();
                Double_t eta_electron = pythia.event[dghtJ2].eta();

	        hPositron_pt_all->Fill(pt_positron);
		hElectron_pt_all->Fill(pt_electron);
	
		if (abs(eta_positron) < 0.8  &&
                    abs(eta_electron) < 0.8  &&
                    abs(eta_gamma)    < 0.12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 1.0)   

		  { 
		  
		    hChiC2_pt_cndtn_1 ->Fill(pt);
		    hChiC2_y_cndtn_1  ->Fill(y);
		 
		  }
		
		if (abs(eta_positron) < 0.8  &&
                    abs(eta_electron) < 0.8  &&
                    abs(eta_gamma)    < 0.12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 5.0)


		  { 
		  
		    hChiC2_pt_cndtn_2 ->Fill(pt);
		    hChiC2_y_cndtn_2  ->Fill(y);

		  }
 	     }
	  }
	}
      }

      if (pythia.event[i].id() == idChic0 &&
	  pythia.event[i].status() ==-62 &&
	  fabs(pythia.event[i].y()) <= ymax) {

	Double_t pt = pythia.event[i].pT(); // transverse momentum
	hChiC0_pt_all->Fill(pt);
	Double_t y  = pythia.event[i].y(); 



	// Find daughters of chi_c0
	int dghtChi1 = pythia.event[i].daughter1(); // first daughter
	int dghtChi2 = pythia.event[i].daughter2(); // last  daughter

	// skip event if the number of chi_c0 daughters is not 2
	if (dghtChi2 - dghtChi1 != 1) continue;

	// select decay chi_c0 -> J/psi gamma
	if ( pythia.event[dghtChi1].id() == idJpsi    &&
	     pythia.event[dghtChi2].id() == idPhoton)  {

	  px = pythia.event[dghtChi2].px();
	  py = pythia.event[dghtChi2].py();
	  pz = pythia.event[dghtChi2].pz();
	  p0 = pythia.event[dghtChi2].e();

	  sigma_p0 = p0 * sqrt(( a_gam_energy * a_gam_energy)/(p0 * p0) + (b_gam_energy*b_gam_energy)/(p0) + (c_gam_energy * c_gam_energy));
	  
	  double p0_rand;

	  p0_rand = rndm.Gaus(p0,sigma_p0);
	  
	  TLorentzVector pGam(px,py,pz,p0_rand);

	  int dghtJ1 = pythia.event[dghtChi1].daughter1();
	  int dghtJ2 = pythia.event[dghtChi1].daughter2();

	  
	  // skip event if the number of J/psi daughters is not 2
	  if (dghtJ2 - dghtJ1 != 1) continue;

	  Double_t pt_gamma = pythia.event[dghtChi2].pT();
	  Double_t eta_gamma = pythia.event[dghtChi2].eta();

	  hGamma_chic0_pt_all->Fill(pt_gamma);


	  // select decay J/psi -> e+ e-
	  if (abs(pythia.event[dghtJ1].id()) == idElectron &&
	      abs(pythia.event[dghtJ2].id()) == idElectron) {
              
	    if (pythia.event[dghtJ1].id() == idElectron)  {


	        px = pythia.event[dghtJ1].px();
	        py = pythia.event[dghtJ1].py();
	        pz = pythia.event[dghtJ1].pz();
	        p0 = pythia.event[dghtJ1].e();

		double sigma_p_elec;
		
		double px_rand, py_rand, pz_rand;

		//define sigma for Gauss to electron

		sigma_p_elec = sqrt((px * px) + (py * py) + (pz * pz)) * sqrt(a_el_pos_momentum * a_el_pos_momentum + (b_el_pos_momentum * b_el_pos_momentum) * sqrt((px * px) + (py * py) + (pz * pz)));

		//define random momentum

		px_rand = rndm.Gaus(px,sigma_p_elec);
		py_rand = rndm.Gaus(py,sigma_p_elec);
		pz_rand = rndm.Gaus(pz,sigma_p_elec);


	        TLorentzVector pElec(px_rand,py_rand,pz_rand,p0);

		
	        px = pythia.event[dghtJ2].px();
	        py = pythia.event[dghtJ2].py();
	        pz = pythia.event[dghtJ2].pz();
	        p0 = pythia.event[dghtJ2].e();

		double sigma_p_posi;
		
		//define sigma for Gauss to positron

		sigma_p_posi = sqrt((px * px) + (py * py) + (pz * pz)) * sqrt(a_el_pos_momentum * a_el_pos_momentum + (b_el_pos_momentum * b_el_pos_momentum) * sqrt((px * px) + (py * py) + (pz * pz)));

		//define random momentum

		px_rand = rndm.Gaus(px,sigma_p_elec);
		py_rand = rndm.Gaus(py,sigma_p_elec);
		pz_rand = rndm.Gaus(pz,sigma_p_elec);


	        TLorentzVector pPosi(px_rand,py_rand,pz_rand,p0);

		Double_t massGamElecPosi = (pGam + pElec + pPosi).M();
		Double_t ptGamElecPosi   = (pGam + pElec + pPosi).Pt();
		hMassGamElecPosi->Fill(massGamElecPosi,ptGamElecPosi);
		
		Double_t pt_positron = pythia.event[dghtJ2].pT();
                Double_t pt_electron = pythia.event[dghtJ1].pT();

                Double_t eta_positron = pythia.event[dghtJ2].eta();
                Double_t eta_electron = pythia.event[dghtJ1].eta();

		hPositron_chic0_pt_all->Fill(pt_positron);
	        hElectron_chic0_pt_all->Fill(pt_electron);

		if (abs(eta_positron) < 0.8  &&
                    abs(eta_electron) < 0.8  &&
                    abs(eta_gamma)    < 0.12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 1.0) 
		 
		  {  
		  
		    hChiC0_pt_cndtn_1 ->Fill(pt);
		    hChiC0_y_cndtn_1  ->Fill(y);

		  }

		if (abs(eta_positron) < 0.8  &&
                    abs(eta_electron) < 0.8  &&
                    abs(eta_gamma)    < 0.12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 5.0)  
		  
		  { 
		  
		    hChiC0_pt_cndtn_2 ->Fill(pt);
		    hChiC0_y_cndtn_2  ->Fill(y);

		  }

	    }


		 if (pythia.event[dghtJ2].id() == idElectron)  {

		px = pythia.event[dghtJ1].px();
	        py = pythia.event[dghtJ1].py();
	        pz = pythia.event[dghtJ1].pz();
	        p0 = pythia.event[dghtJ1].e();

		double sigma_p_elec;
		
		double px_rand, py_rand, pz_rand;

		//define sigma for Gauss to electron

		sigma_p_elec = sqrt((px * px) + (py * py) + (pz * pz)) * sqrt(a_el_pos_momentum * a_el_pos_momentum + (b_el_pos_momentum * b_el_pos_momentum) * sqrt((px * px) + (py * py) + (pz * pz)));

		//define random momentum

		px_rand = rndm.Gaus(px,sigma_p_elec);
		py_rand = rndm.Gaus(py,sigma_p_elec);
		pz_rand = rndm.Gaus(pz,sigma_p_elec);


	        TLorentzVector pElec(px_rand,py_rand,pz_rand,p0);

		
	        px = pythia.event[dghtJ2].px();
	        py = pythia.event[dghtJ2].py();
	        pz = pythia.event[dghtJ2].pz();
	        p0 = pythia.event[dghtJ2].e();

		double sigma_p_posi;
		
		//define sigma for Gauss to positron

		sigma_p_posi = sqrt((px * px) + (py * py) + (pz * pz)) * sqrt(a_el_pos_momentum * a_el_pos_momentum + (b_el_pos_momentum * b_el_pos_momentum) * sqrt((px * px) + (py * py) + (pz * pz)));

		//define random momentum

		px_rand = rndm.Gaus(px,sigma_p_elec);
		py_rand = rndm.Gaus(py,sigma_p_elec);
		pz_rand = rndm.Gaus(pz,sigma_p_elec);


	        TLorentzVector pPosi(px_rand,py_rand,pz_rand,p0);

		Double_t massGamElecPosi = (pGam + pElec + pPosi).M();
		Double_t ptGamElecPosi   = (pGam + pElec + pPosi).Pt();
		hMassGamElecPosi->Fill(massGamElecPosi,ptGamElecPosi);

	        Double_t pt_positron =pythia.event[dghtJ1].pT();
                Double_t pt_electron = pythia.event[dghtJ2].pT();
       
                Double_t eta_positron = pythia.event[dghtJ1].eta();
                Double_t eta_electron = pythia.event[dghtJ2].eta();


	        hPositron_pt_all->Fill(pt_positron);
		hElectron_pt_all->Fill(pt_electron);
	
		if (abs(eta_positron) < 0.8  &&
                    abs(eta_electron) < 0.8  &&
                    abs(eta_gamma)    < 0.12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 1.0)   

		  { 
		  
		    hChiC0_pt_cndtn_1 ->Fill(pt);
		    hChiC0_y_cndtn_1  ->Fill(y);
		 
		  }
		
		if (abs(eta_positron) < 0.8  &&
                    abs(eta_electron) < 0.8  &&
                    abs(eta_gamma)    < 0.12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 5.0)


		  { 
		  
		    hChiC0_pt_cndtn_2 ->Fill(pt);
		    hChiC0_y_cndtn_2  ->Fill(y);

		  }
		 }
	  }
	}
      }

    if (pythia.event[i].id() == idChic1 &&
	  pythia.event[i].status() ==-62 &&
	  fabs(pythia.event[i].y()) <= ymax) {

	Double_t pt = pythia.event[i].pT(); // transverse momentum
	hChiC1_pt_all->Fill(pt);
	Double_t y  = pythia.event[i].y(); 



	// Find daughters of chi_c1
	int dghtChi1 = pythia.event[i].daughter1(); // first daughter
	int dghtChi2 = pythia.event[i].daughter2(); // last  daughter

	// skip event if the number of chi_c0 daughters is not 2
	if (dghtChi2 - dghtChi1 != 1) continue;

	// select decay chi_c1 -> J/psi gamma
	if ( pythia.event[dghtChi1].id() == idJpsi    &&
	     pythia.event[dghtChi2].id() == idPhoton)  {

	  px = pythia.event[dghtChi2].px();
	  py = pythia.event[dghtChi2].py();
	  pz = pythia.event[dghtChi2].pz();
	  p0 = pythia.event[dghtChi2].e();

	  sigma_p0 = p0 * sqrt(( a_gam_energy * a_gam_energy)/(p0 * p0) + (b_gam_energy*b_gam_energy)/(p0) + (c_gam_energy * c_gam_energy)); 
	  
	  double p0_rand;

	  p0_rand = rndm.Gaus(p0,sigma_p0);
	  
	  TLorentzVector pGam(px,py,pz,p0_rand);

	  int dghtJ1 = pythia.event[dghtChi1].daughter1();
	  int dghtJ2 = pythia.event[dghtChi1].daughter2();

	  
	  // skip event if the number of J/psi daughters is not 2
	  if (dghtJ2 - dghtJ1 != 1) continue;

	  Double_t pt_gamma = pythia.event[dghtChi2].pT();
	  Double_t eta_gamma = pythia.event[dghtChi2].eta();

	  hGamma_chic1_pt_all->Fill(pt_gamma);


	  // select decay J/psi -> e+ e-
	  if (abs(pythia.event[dghtJ1].id()) == idElectron &&
	      abs(pythia.event[dghtJ2].id()) == idElectron) {
              
	    if (pythia.event[dghtJ1].id() == idElectron)  {

	        px = pythia.event[dghtJ1].px();
	        py = pythia.event[dghtJ1].py();
	        pz = pythia.event[dghtJ1].pz();
	        p0 = pythia.event[dghtJ1].e();

		double sigma_p_elec;
		
		double px_rand, py_rand, pz_rand;

		//define sigma for Gauss to electron

		sigma_p_elec = sqrt((px * px) + (py * py) + (pz * pz)) * sqrt(a_el_pos_momentum * a_el_pos_momentum + (b_el_pos_momentum * b_el_pos_momentum) * sqrt((px * px) + (py * py) + (pz * pz)));

		//define random momentum

		px_rand = rndm.Gaus(px,sigma_p_elec);
		py_rand = rndm.Gaus(py,sigma_p_elec);
		pz_rand = rndm.Gaus(pz,sigma_p_elec);


	        TLorentzVector pElec(px_rand,py_rand,pz_rand,p0);

		
	        px = pythia.event[dghtJ2].px();
	        py = pythia.event[dghtJ2].py();
	        pz = pythia.event[dghtJ2].pz();
	        p0 = pythia.event[dghtJ2].e();

		double sigma_p_posi;
		
		//define sigma for Gauss to positron

		sigma_p_posi = sqrt((px * px) + (py * py) + (pz * pz)) * sqrt(a_el_pos_momentum * a_el_pos_momentum + (b_el_pos_momentum * b_el_pos_momentum) * sqrt((px * px) + (py * py) + (pz * pz)));

		//define random momentum

		px_rand = rndm.Gaus(px,sigma_p_elec);
		py_rand = rndm.Gaus(py,sigma_p_elec);
		pz_rand = rndm.Gaus(pz,sigma_p_elec);


	        TLorentzVector pPosi(px_rand,py_rand,pz_rand,p0);

		Double_t massGamElecPosi = (pGam + pElec + pPosi).M();
		Double_t ptGamElecPosi   = (pGam + pElec + pPosi).Pt();
		hMassGamElecPosi->Fill(massGamElecPosi,ptGamElecPosi);

		Double_t pt_positron = pythia.event[dghtJ2].pT();
                Double_t pt_electron = pythia.event[dghtJ1].pT();

                Double_t eta_positron = pythia.event[dghtJ2].eta();
                Double_t eta_electron = pythia.event[dghtJ1].eta();
                

		hPositron_chic1_pt_all->Fill(pt_positron);
	        hElectron_chic1_pt_all->Fill(pt_electron);

		if (abs(eta_positron) < 0.8  &&
                    abs(eta_electron) < 0.8  &&
                    abs(eta_gamma)    < 0.12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 1.0) 
		 
		  {  
		  
		    hChiC1_pt_cndtn_1 ->Fill(pt);
		    hChiC1_y_cndtn_1  ->Fill(y);

		  }

		if (abs(eta_positron) < 0.8  &&
                    abs(eta_electron) < 0.8  &&
                    abs(eta_gamma)    < 0.12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 5.0)  
		  
		  { 
		  
		    hChiC1_pt_cndtn_2 ->Fill(pt);
		    hChiC1_y_cndtn_2  ->Fill(y);

		  }

	    }


		 if (pythia.event[dghtJ2].id() == idElectron)  {

	        px = pythia.event[dghtJ1].px();
	        py = pythia.event[dghtJ1].py();
	        pz = pythia.event[dghtJ1].pz();
	        p0 = pythia.event[dghtJ1].e();

		double sigma_p_elec;
		
		double px_rand, py_rand, pz_rand;

		//define sigma for Gauss to electron

		sigma_p_elec = sqrt((px * px) + (py * py) + (pz * pz)) * sqrt(a_el_pos_momentum * a_el_pos_momentum + (b_el_pos_momentum * b_el_pos_momentum) * sqrt((px * px) + (py * py) + (pz * pz)));

		//define random momentum

		px_rand = rndm.Gaus(px,sigma_p_elec);
		py_rand = rndm.Gaus(py,sigma_p_elec);
		pz_rand = rndm.Gaus(pz,sigma_p_elec);


	        TLorentzVector pElec(px_rand,py_rand,pz_rand,p0);

		
	        px = pythia.event[dghtJ2].px();
	        py = pythia.event[dghtJ2].py();
	        pz = pythia.event[dghtJ2].pz();
	        p0 = pythia.event[dghtJ2].e();

		double sigma_p_posi;
		
		//define sigma for Gauss to positron

		sigma_p_posi = sqrt((px * px) + (py * py) + (pz * pz)) * sqrt(a_el_pos_momentum * a_el_pos_momentum + (b_el_pos_momentum * b_el_pos_momentum) * sqrt((px * px) + (py * py) + (pz * pz)));

		//define random momentum

		px_rand = rndm.Gaus(px,sigma_p_elec);
		py_rand = rndm.Gaus(py,sigma_p_elec);
		pz_rand = rndm.Gaus(pz,sigma_p_elec);


	        TLorentzVector pPosi(px_rand,py_rand,pz_rand,p0);

		Double_t massGamElecPosi = (pGam + pElec + pPosi).M();
		Double_t ptGamElecPosi   = (pGam + pElec + pPosi).Pt();
		hMassGamElecPosi->Fill(massGamElecPosi,ptGamElecPosi);

	        Double_t pt_positron =pythia.event[dghtJ1].pT();
                Double_t pt_electron = pythia.event[dghtJ2].pT();
       
                Double_t eta_positron = pythia.event[dghtJ1].eta();
                Double_t eta_electron = pythia.event[dghtJ2].eta();

	        hPositron_pt_all->Fill(pt_positron);
		hElectron_pt_all->Fill(pt_electron);
	
		if (abs(eta_positron) < 0.8  &&
                    abs(eta_electron) < 0.8  &&
                    abs(eta_gamma)    < 0.12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 1.0)   

		  { 
		  
		    hChiC1_pt_cndtn_1 ->Fill(pt);
		    hChiC1_y_cndtn_1  ->Fill(y);
		 
		  }
		
		if (abs(eta_positron) < 0.8  &&
                    abs(eta_electron) < 0.8  &&
                    abs(eta_gamma)    < 0.12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 5.0)


		  { 
		  
		    hChiC1_pt_cndtn_2 ->Fill(pt);
		    hChiC1_y_cndtn_2  ->Fill(y);

		  }
		 }
	  }
	}
    }
    }
    

    
    // Fill charged multiplicity in histogram. End event loop.
  }

  // Statistics on event generation.
  pythia.stat();

  // Convert histograms to differential cross sections
  double xsection = pythia.info.sigmaGen();
  int ntrials  = pythia.info.nAccepted();
  double sigmaweight = xsection/ntrials;
  

  // normalize pT spectra
  double ptBinSize = (ptMax-ptMin) / nPtBins;
  double yBinSize  = (yMax-yMin) / nyBins;

  hChiC2_pt_all            ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hChiC0_pt_all            ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hChiC1_pt_all            ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hGamma_pt_all            ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hGamma_chic0_pt_all      ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hGamma_chic1_pt_all      ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hElectron_pt_all         ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hElectron_chic0_pt_all   ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hElectron_chic1_pt_all   ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hPositron_pt_all         ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hPositron_chic0_pt_all   ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hPositron_chic1_pt_all   ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hChiC2_pt_cndtn_1        ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hChiC0_pt_cndtn_1        ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hChiC1_pt_cndtn_1        ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hChiC2_pt_cndtn_2        ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hChiC0_pt_cndtn_2        ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hChiC1_pt_cndtn_2        ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hChiC2_y_cndtn_1         ->Scale(sigmaweight/(yBinSize * 2. * ymax));
  hChiC0_y_cndtn_1         ->Scale(sigmaweight/(yBinSize * 2. * ymax));
  hChiC1_y_cndtn_1         ->Scale(sigmaweight/(yBinSize * 2. * ymax));
  hChiC2_y_cndtn_2         ->Scale(sigmaweight/(yBinSize * 2. * ymax)); 
  hChiC0_y_cndtn_2         ->Scale(sigmaweight/(yBinSize * 2. * ymax));
  hChiC1_y_cndtn_2         ->Scale(sigmaweight/(yBinSize * 2. * ymax));

  // Save histogram on file and close file.
  char fn[1024];
  sprintf(fn, "%s", "pythia_chic2.root");
  TFile* outFile = new TFile(fn, "RECREATE");
 
  hChiC2_pt_all           ->Write();
  hChiC0_pt_all           ->Write();
  hChiC1_pt_all           ->Write();
  hChiC2_pt_cndtn_1       ->Write();
  hChiC0_pt_cndtn_1       ->Write();
  hChiC1_pt_cndtn_1       ->Write();
  hChiC2_y_cndtn_1        ->Write();
  hChiC0_y_cndtn_1        ->Write();
  hChiC1_y_cndtn_1        ->Write();
  hChiC2_pt_cndtn_2       ->Write();
  hChiC0_pt_cndtn_2       ->Write();
  hChiC1_pt_cndtn_2       ->Write();
  hChiC2_y_cndtn_2        ->Write();
  hChiC0_y_cndtn_2        ->Write();
  hChiC1_y_cndtn_2        ->Write();
  hGamma_pt_all           ->Write();
  hGamma_chic0_pt_all     ->Write();
  hGamma_chic1_pt_all     ->Write();
  hElectron_pt_all        ->Write();
  hElectron_chic0_pt_all  ->Write();
  hElectron_chic1_pt_all  ->Write();
  hPositron_pt_all        ->Write();
  hPositron_chic0_pt_all  ->Write();
  hPositron_chic1_pt_all  ->Write();
  hMassGamElecPosi        ->Write();
 
  outFile->Close();
  delete outFile;





  return 0;
}
