#include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"

bool IsElectronDetectedInCTS(TLorentzVector);
bool IsPhotonDetectedInEMCAL(TLorentzVector);
bool IsPhotonDetectedInPHOS(TLorentzVector); 

void Invariant_mass_spectr_creator(TLorentzVector p_el, TLorentzVector p_pos, TLorentzVector p_gam,
				  TH2F *hMassElecPosi,
				  TH2F *hMassGamElecPosi,
				  TH2F *hMassGamElecPosi_cndtn_1,
				  TH2F *hMassGamElecPosi_cndtn_2,
				  TH2F *hMassGamElecPosi_cndtn_3,
				  TH2F *hMassGamElecPosi_mass_diff,
				  TH2F *hMassGamElecPosi_mass_diff_cndtn_1,
				  TH2F *hMassGamElecPosi_mass_diff_cndtn_2,
				  TH2F *hMassGamElecPosi_mass_diff_cndtn_3, double br)
{
  
  hMassGamElecPosi->Fill((p_el + p_pos + p_gam).M(), (p_el + p_pos + p_gam).Pt(), br);
  hMassElecPosi->Fill((p_el + p_pos).M(), (p_el + p_pos).Pt(), br);
  hMassGamElecPosi_mass_diff->Fill((p_el + p_pos + p_gam).M() - (p_el + p_pos).M(), 
				   (p_el + p_pos + p_gam).Pt(), br);
  
  if (IsElectronDetectedInCTS(p_el)  &&
      IsElectronDetectedInCTS(p_pos) &&
      IsPhotonDetectedInPHOS(p_gam))
    {
      
      hMassGamElecPosi_cndtn_1->Fill((p_el + p_pos + p_gam).M(), (p_el + p_pos + p_gam).Pt(), br);
      hMassGamElecPosi_mass_diff_cndtn_1->Fill((p_el + p_pos + p_gam).M() - (p_el + p_pos).M(),
					       (p_el + p_pos + p_gam).Pt(), br);
    }
  
  if (IsElectronDetectedInCTS(p_el)   &&
      IsElectronDetectedInCTS(p_pos) &&
      IsPhotonDetectedInPHOS(p_gam)   &&
      p_gam.E() > 5.0)
    {
      
      hMassGamElecPosi_cndtn_2->Fill((p_el + p_pos + p_gam).M(), (p_el + p_pos + p_gam).Pt(), br);
      hMassGamElecPosi_mass_diff_cndtn_2->Fill((p_el + p_pos + p_gam).M() - (p_el + p_pos).M(), 
					       (p_el + p_pos + p_gam).Pt(), br);
    }

  if (IsPhotonDetectedInEMCAL(p_el)  &&
      IsPhotonDetectedInEMCAL(p_pos) &&
      IsPhotonDetectedInPHOS(p_gam)  &&
      p_gam.E() > 2.0)
    {
      
      hMassGamElecPosi_cndtn_3->Fill((p_el + p_pos + p_gam).M(), (p_el + p_pos + p_gam).Pt(), br);
      hMassGamElecPosi_mass_diff_cndtn_3->Fill((p_el + p_pos + p_gam).M() - (p_el + p_pos).M(), 
					       (p_el + p_pos + p_gam).Pt(), br);
    }
  
  
  return;
}
