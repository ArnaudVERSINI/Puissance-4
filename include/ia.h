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

    inline size_t effectuerCoup() {
        effectuerCoup(profondeur);
    }
    inline size_t effectuerCoup(int profondeurActuelle) {

        size_t max_colonne = 0;
        int alpha = - std::numeric_limits<int>::max();
        int beta = std::numeric_limits<int>::max();
        if (profondeur > 0 && !plateauActuel.isPartieFinit()) {
            for(size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
                if (plateauActuel.colonnePleine(colonne)) {
                    continue;
                }

            }
        }
        return max_colonne;
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

    inline int calculScore() {
        return 0;
    }
};

void machinQuiSertARienMaisQuiGenereDuCode() {
    IAJoueurMinMax<JOUEUR_BLEU, 256> joueur;
}
#endif // IA_H_INCLUDED
