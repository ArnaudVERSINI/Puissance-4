#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "joueur.hpp"
#include <limits>
#include <cstdlib>

template<TJoueur joueur_actuel, unsigned int profondeur>
class IAJoueurMinMax : public Joueur<joueur_actuel> {

    /**
     * Le plateau actuel, conservé ici pour permettre de le modifier
     * lors du traitement de l'arbre
     */
    Plateau plateauActuel;

public:

    inline IAJoueurMinMax() {
    }

    inline int calculScore() {
        return 0;
    }

    inline bool isPartieFinit(size_t ligne, size_t colonne, TCase case_) {
        if (plateauActuel.isPartieFinit()) {
            return true;
        }

        if (plateauActuel.aGagner(ligne, colonne, case_)) {
            return true;
        }

        return false;
    }

    inline size_t effectuerCoup() {

        size_t max_colonne = 0;
        const int betaInitial = numeric_limits<int>::max();
        const int alphaInitial = - numeric_limits<int>::max();
        int alpha = alphaInitial;

        if (profondeur > 0 && !plateauActuel.isPartieFinit()) {
            for(size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
                if (plateauActuel.colonneJouable(colonne) == false) {
                    continue;
                }

                plateauActuel.addToColumn(colonne, (TCase) joueur_actuel);
                int score_temp =  min(profondeur, alpha, betaInitial);
                if (alpha < score_temp) {
                    max_colonne = colonne;
                    alpha = score_temp;
                }
                plateauActuel.supprimerCoup(colonne);
            }
        }
        return max_colonne;
    }

    inline int min(const unsigned int profondeurActuelle, const int alpha, int beta) {
        if (profondeurActuelle == 0) {
            int calculScoreResult = calculScore();
            return calculScoreResult;
        }

        for (size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
            if (!plateauActuel.colonneJouable(colonne)) {
                continue;
            }

            size_t ligne_actuelle = plateauActuel.addToColumn(colonne, (TCase) this->getJoueurAdverse());

            int scoreTemporaire;

            //Pour éviter un appel récursif inutil
            if (this->isPartieFinit(ligne_actuelle, colonne, (TCase) this->getJoueurAdverse())) {
                scoreTemporaire = - numeric_limits<int>::max();
            } else {
                scoreTemporaire = max(profondeurActuelle-1, alpha, beta);
            }

            plateauActuel.supprimerCoup(colonne);

            if (beta > scoreTemporaire) {
                beta = scoreTemporaire;
            }

            if(beta <= alpha) {
                return beta;
            }
        }
        return beta;
    }

    //Pas finit
    inline int max(unsigned int profondeurActuelle, int alpha, const int beta) {
        if (profondeurActuelle == 0) {
            int calculScoreResult = calculScore();
            return calculScoreResult;
        }

        for (size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
            if (!plateauActuel.colonneJouable(colonne)) {
                continue;
            }

            size_t ligne_actuelle = plateauActuel.addToColumn(colonne, (TCase) joueur_actuel);

            int scoreTemporaire;

            //Pour éviter un appel récursif inutil
            if (this->isPartieFinit(ligne_actuelle, colonne, (TCase) this->getJoueurAdverse())) {
                scoreTemporaire = numeric_limits<int>::max();
            } else {
                scoreTemporaire = min(profondeurActuelle-1, alpha, beta);
            }

            plateauActuel.supprimerCoup(colonne);

            if (alpha < scoreTemporaire) {
                alpha = scoreTemporaire;
            }

            if(beta <= alpha) {
                return alpha;
            }
        }
        return alpha;
    }


    inline virtual void prendreEnCompteCoupAdversaire(size_t colonne) {
        plateauActuel.addToColumn(colonne, (TCase) inverseJoueur(joueur_actuel));
    }

    inline virtual const string getJoueurInformations() {
        return JeuxPuissanceQuatre::playerToString(joueur_actuel) + " joueur de type IA";
    }
};
#endif // IA_H_INCLUDED
