#include "TMath.h"
#include "TLorentzVector.h"

bool IsPhotonDetectedInPHOS(TLorentzVector p){
  bool flag = false;

  double px = p.Px();
  double py = p.Py();
  double pz = p.Pz();
  double p0 = p.E();

  double y = 0.5*log((p0 + pz)/(p0 - pz));
  double phi;
  //use modiff funtion of atan();

  if (px > 0. && py > 0.){
    phi = atan(py/px);
  }

  if (px > 0. && py < 0.){
    phi = atan(py/px);
  }

  if (px < 0. && py > 0.){
    phi = TMath::Pi() + atan(py/px);
  }

  if (px < 0. && py < 0.){
    phi = atan(py/px) - TMath::Pi();
  }

  if (px == 0. && py > 0.){
    phi = TMath::Pi()/2;
  }

  if (px == 0. && py < 0.){
    phi = -1 * TMath::Pi()/2;
  }

  if (fabs(y) < 0.12              &&
      (phi > -11./9. * TMath::Pi()) && 
      (phi < -4./9. * TMath::Pi())  &&
      p0 > 1.0                    ){
    flag = true;
  }  
  
  return flag;
}
