#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "joueur.hpp"
#include <limits>


template<TJoueur joueur_actuel, unsigned int profondeur>
class IAJoueurMinMax : public Joueur<joueur_actuel> {

    /**
     * Le plateau actuel, conservé ici pour permettre de le modifier
     * lors du traitement de l'arbre
     */
    Plateau plateauActuel;

public:

    inline IAJoueurMinMax() {
        //this->nom = nom;
    }

    size_t effectuerCoup() {
        return effectuerCoup(profondeur);
    }

    inline int calculScore() {
        return 0;
    }

    inline bool isPartitFinit(size_t ligne, size_t colonne) {

    }

    inline size_t effectuerCoup(const unsigned int profondeurActuelle) {

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
                int score_temp =  min(profondeurActuelle, alpha, betaInitial);
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
            return calculScore();
        }

        if (plateauActuel.isPartieFinit()) {
            return calculScore();
        }

        for (size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
            if (!plateauActuel.colonneJouable(colonne)) {
                continue;
            }

            plateauActuel.addToColumn(colonne, (TCase) this->getJoueurAdverse());

            int scoreTemporaire = max(profondeurActuelle-1, alpha, beta);

            plateauActuel.supprimerCoup(colonne);

            if (beta > scoreTemporaire) {
                beta = profondeurActuelle;
            }

            if(beta <= alpha) {
                return beta;
            }
        }
    }

    inline int max(unsigned int profondeurActuelle, int alpha, const int beta) {

    }


    int evaluerGrille() {
        return 0;
    }

    inline virtual void prendreEnCompteCoupAdversaire(size_t colonne) {
        plateauActuel.addToColumn(colonne, (TCase) inverseJoueur(joueur_actuel));
    }

    inline virtual const string getJoueurInformations() {
        return JeuxPuissanceQuatre::playerToString(joueur_actuel) + " joueur de type IA";
    }
};

void machinQuiSertARienMaisQuiGenereDuCode() {
    IAJoueurMinMax<JOUEUR_BLEU, 256> joueur;
    IAJoueurMinMax<JOUEUR_ROUGE, 256> joueur2;
}
#endif // IA_H_INCLUDED
