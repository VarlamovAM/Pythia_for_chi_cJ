#include "TLorentzVector.h"
#include "TRandom.h"
#include <math.h>

Double_t smearP(Double_t Ptrue)
{
  // Generate smeared track 3-momentum from the true 3-momentum
  const Double_t a=0.01, b=0.001;
  Double_t sigmaP = Ptrue * sqrt(a*a + b*Ptrue*b*Ptrue);
  Double_t Psmeared = gRandom->Gaus(Ptrue,sigmaP);
  if (Psmeared<0) Psmeared = 0;
  return Psmeared;
}
