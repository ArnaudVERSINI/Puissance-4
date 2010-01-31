#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "joueur.hpp"
#include <limits>

template<TJoueur joueur>
class IANode {

};

template<TJoueur joueur_actuel, unsigned int profondeur>
class IAJoueurMinMax : public Joueur<joueur_actuel> {



    /**
     * Le plateau actuel, conservé ici pour permettre de le modifier
     * lors du traitement de l'arbre
     */
    Plateau plateauActuel;

public:

    IAJoueurMinMax() {
        //this->nom = nom;
    }

    unsigned int effectuerCoup() {
        return effectuerCoup(profondeur);
    }

    int calculScore() {
        return 0;
    }

    size_t effectuerCoup(const unsigned int profondeurActuelle) {

        size_t max_colonne = 0;
        const int betaInitial = numeric_limits<int>::max();
        const int alphaInitial = - numeric_limits<int>::max();
        int alpha = alphaInitial;

        if (profondeur > 0 && !plateauActuel.isPartieFinit()) {
            for(size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
                if (plateauActuel.colonnePleine(colonne)) {
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

    inline int min(const unsigned int profondeurActuelle, const int alpha, const int beta) {
        if (profondeurActuelle == 0) {
            return calculScore();
        }

        if (plateauActuel.isPartieFinit()) {
            return calculScore();
        }
    }



    inline int max(unsigned int profondeurActuelle, const int alpha, const int beta) {

    }


    int evaluerGrille() {
        return 0;
    }

    virtual void prendreEnCompteCoupAdversaire(size_t colonne) {
        plateauActuel.addToColumn(colonne, (TCase) inverseJoueur(joueur_actuel));
    }

    virtual const string getJoueurInformations() {
        return JeuxPuissanceQuatre::playerToString(joueur_actuel) + " joueur de type IA";
    }


};

void machinQuiSertARienMaisQuiGenereDuCode() {
    IAJoueurMinMax<JOUEUR_BLEU, 256> joueur;
}
#endif // IA_H_INCLUDED
