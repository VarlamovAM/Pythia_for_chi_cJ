#include "TRandom.h"
#include <math.h>

Double_t smearX(Double_t xTrue, Double_t E)
{
  // Generate smeared photon coordinate from the true one xTrue [cm]
  // E is the photon energy
  // const Double_t a = 0.096, b = 0.229; // PPR vol.II, tab.5.17
  const Double_t a = 0.15, b = 0.25; // realistic coordinate resolution in PHOS
  Double_t sigmaX = sqrt(a*a + b*b/E);
  Double_t xSmeared = gRandom->Gaus(xTrue,sigmaX);
  return xSmeared;
}
