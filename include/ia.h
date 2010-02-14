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


    inline int calculScoreJoueurActuel () {
        unsigned int nbPoints = 0;
        unsigned int scoreIntermediaire = 0;
        for(int ligne = 0; ligne < Plateau::HAUTEUR; ligne++) {
            unsigned int nbCasesLibreAvant = 0;
            unsigned int nbCasesJoueur = 0;
            unsigned int nbCasesLibreApres = 0;
            for(int colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
                TCase caseActuelle = plateauActuel.get(ligne, colonne);
                if (caseActuelle == (TCase) joueur_actuel) {
                    nbCasesJoueur++;
                } else if (caseActuelle == NONE) {
                    if (nbCasesJoueur == 0) {
                        nbCasesLibreAvant++;
                    } else {
                        nbCasesLibreApres++;
                    }
                } else {
                    unsigned int facteur = 16;

                    if (nbCasesLibreAvant > 0 && nbCasesLibreApres > 0) {
                        facteur = 32;
                    }
                    if ((nbCasesLibreAvant + nbCasesLibreApres + nbCasesJoueur) < 4) {
                        //cout << "Pas assez de cases" << endl;
                        facteur = 0;
                    }
                    //On favorise les situations multiples
                    if (scoreIntermediaire > 100) {
                        facteur *= 4;
                    }
                    scoreIntermediaire += facteur * (nbCasesLibreAvant + nbCasesLibreApres + nbCasesJoueur);
                    nbCasesLibreAvant = nbCasesLibreApres = nbCasesJoueur = 0;
                }
            }
        }
        //cout << nbPoints << endl;
        nbPoints += scoreIntermediaire;
        if (nbPoints > 0) {
            //cout << "NbPoints " << nbPoints << endl;
        }
        return nbPoints;
    }

    inline int calculScoreJoueurAdverse () {
        unsigned int nbPoints = 0;
        unsigned int scoreIntermediaire = 0;
        for(int ligne = 0; ligne < Plateau::HAUTEUR; ligne++) {
            unsigned int nbCasesLibreAvant = 0;
            unsigned int nbCasesJoueurAdverse = 0;
            unsigned int nbCasesLibreApres = 0;
            for(int colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
                TCase caseActuelle = plateauActuel.get(ligne, colonne);
                if (caseActuelle == (TCase) this->getJoueurAdverse()) {
                    nbCasesJoueurAdverse++;
                } else if (caseActuelle == NONE) {
                    if (nbCasesJoueurAdverse == 0) {
                        nbCasesLibreAvant++;
                    } else {
                        nbCasesLibreApres++;
                    }
                } else {
                    unsigned int facteur = 16;

                    if (nbCasesLibreAvant > 0 && nbCasesLibreApres > 0) {
                        facteur = 32;
                    }
                    if ((nbCasesLibreAvant + nbCasesLibreApres + nbCasesJoueurAdverse) < 4) {
                        //cout << "Pas assez de cases" << endl;
                        facteur = 0;
                    }
                    //On favorise les situations multiples
                    if (scoreIntermediaire > 100) {
                        facteur *= 4;
                    }
                    scoreIntermediaire += facteur * (nbCasesLibreAvant + nbCasesLibreApres + nbCasesJoueurAdverse);
                    nbCasesLibreAvant = nbCasesLibreApres = nbCasesJoueurAdverse = 0;
                }
            }
        }
        //cout << nbPoints << endl;
        nbPoints += scoreIntermediaire;
        if (nbPoints > 0) {
            //cout << "NbPoints " << nbPoints << endl;
        }
        return nbPoints;
    }

    inline int calculScore() {
        int score = calculScoreJoueurActuel() - calculScoreJoueurAdverse();
        return score;
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
            if (plateauActuel.isPartieFinit()) {
                scoreTemporaire = max(profondeurActuelle-1, alpha, beta);
            }
            else if (plateauActuel.aGagner(ligne_actuelle, colonne, (TCase) this->getJoueurAdverse()) ) {
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
            if (plateauActuel.isPartieFinit()) {
                scoreTemporaire = max(profondeurActuelle-1, alpha, beta);
            } else if (plateauActuel.aGagner(ligne_actuelle, colonne, (TCase) joueur_actuel) ) {
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
        cout << "Retour de max " << alpha << endl;
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
