#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "joueur.hpp"

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
        return 0;
    }

    inline virtual void prendreEnCompteCoupAdversaire(size_t colonne) {
        plateauActuel.addToColumn(colonne, (TCase) inverseJoueur(joueur_actuel));
    }

    inline virtual const string getJoueurInformations() {
        return JeuxPuissanceQuatre::playerToString(joueur_actuel) + " joueur de type IA";
    }

};

void machinQuiSertARien() {
    IAJoueurMinMax<JOUEUR_BLEU, 256> joueur;
}
#endif // IA_H_INCLUDED
