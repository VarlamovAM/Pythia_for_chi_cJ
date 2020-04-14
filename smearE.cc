#include "TLorentzVector.h"
#include "TRandom.h"
#include <math.h>

Double_t smearE(Double_t Etrue)
{
  // Generate smeared photon energy from the true energy
  const Double_t a = 0.04, b = 0.036, c = 0.01;
  Double_t sigmaE = Etrue * sqrt(a*a/Etrue/Etrue + b*b/Etrue + c*c);
  Double_t Esmeared = gRandom->Gaus(Etrue,sigmaE);
  if (Esmeared<0) Esmeared = 0;
  return Esmeared;
}
