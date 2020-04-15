#include "TLorentzVector.h"
#include "TRandom.h"
#include <math.h>

Double_t smearP(Double_t Ptrue)
{
  // Generate smeared track 3-momentum from the true 3-momentum
  const Double_t a=0.008, b=0.002; // Momentum resolution of ALICE treaking system
  // const Double_t a=0.00, b=0.000; // for studies ideal resolution
  Double_t sigmaP = Ptrue * sqrt(a*a + b*Ptrue*b*Ptrue);
  Double_t Psmeared = gRandom->Gaus(Ptrue,sigmaP);
  if (Psmeared<0) Psmeared = 0;
  return Psmeared;
}
