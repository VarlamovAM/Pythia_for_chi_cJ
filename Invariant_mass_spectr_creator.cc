#include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"

void Invariant_mass_spectr_creator(TLorentzVector p_el, TLorentzVector p_pos, TLorentzVector p_gam,
				  TH2F *hMassElecPosi,
				  TH2F *hMassGamElecPosi,
				  TH2F *hMassGamElecPosi_cndtn_1,
				  TH2F *hMassGamElecPosi_cndtn_2,
				  TH2F *hMassGamElecPosi_mass_diff,
				  TH2F *hMassGamElecPosi_mass_diff_cndtn_1,
				  TH2F *hMassGamElecPosi_mass_diff_cndtn_2)
{
  
  hMassGamElecPosi->Fill((p_el + p_pos + p_gam).M(), (p_el + p_pos + p_gam).Pt());
  hMassElecPosi->Fill((p_el + p_pos).M(), (p_el + p_pos).Pt());
  hMassGamElecPosi_mass_diff->Fill((p_el + p_pos + p_gam).M() - (p_el + p_pos).M(), 
				   (p_el + p_pos + p_gam).Pt());
  
  if (true){//make condition checking function
    hMassGamElecPosi_cndtn_1->Fill((p_el + p_pos + p_gam).M(), (p_el + p_pos + p_gam).Pt());
    hMassGamElecPosi_mass_diff_cndtn_1->Fill((p_el + p_pos + p_gam).M() - (p_el + p_pos).M(),
					     (p_el + p_pos + p_gam).Pt());
  }
  
  if (true){//make condition checking function
    hMassGamElecPosi_cndtn_2->Fill((p_el + p_pos + p_gam).M(), (p_el + p_pos + p_gam).Pt());
    hMassGamElecPosi_mass_diff_cndtn_2->Fill((p_el + p_pos + p_gam).M() - (p_el + p_pos).M(), 
					     (p_el + p_pos + p_gam).Pt());
  }
  
  return;
}
