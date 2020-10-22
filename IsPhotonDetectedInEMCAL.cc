#include "TLorentzVector.h"
#include <iostream>

bool IsPhotonDetectedInEMCAL(TLorentzVector p)
{
  
  bool flag = false;

  double px = p.Px();
  double py = p.Py();
  double pz = p.Pz();
  double p0 = p.E();

  double y = 0.5*log((p0 + pz)/(p0 - pz));

  double phi;
  

  phi = TMath::ATan(py/px);

  std::cout << "phi = " << TMath::RadToDeg() * phi << " y = " << y << " E = " << p0 << "\n";

  if (fabs(y) < 0.7                 &&
      (phi > 87./180. * TMath::Pi())   && 
      (phi < 187./180. * TMath::Pi())  &&
      p0 > 2.0                        ){
    flag = true;
  }  
  
  return flag;
}

