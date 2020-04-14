#include "TLorentzVector.h"
Double_t smearE(Double_t);
#include <math.h>

// This function generates smeared photon 4-momentum from the true one

TLorentzVector resolutionPhoton(TLorentzVector pTrue)
{
  // Get particle mass
  Double_t Mass = pTrue.M();
  Double_t Etrue = pTrue.E();
  // Get true energy from true 4-momentum and smear this energy
  Double_t Esmeared = smearE(pTrue.E());
  // Calculate true absolute 3-momentum
  Double_t p3True = sqrt(Etrue*Etrue - Mass*Mass);
  // Calculate smeared absolute 3-momentum
  Double_t p3Smeared = sqrt(Esmeared*Esmeared - Mass*Mass);
  // Calculate smeared components of 3-vector
  Double_t pxSmeared = pTrue.Px() * p3Smeared/p3True;
  Double_t pySmeared = pTrue.Py() * p3Smeared/p3True;
  Double_t pzSmeared = pTrue.Pz() * p3Smeared/p3True;
  // Construct new 4-momentum from smeared energy and 3-momentum
  TLorentzVector pSmeared(pxSmeared,pySmeared,pzSmeared,Esmeared);
  return pSmeared;
}
