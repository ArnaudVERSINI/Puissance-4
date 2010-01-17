#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "joueur.h"

template<TJoueur joueur>
class IAJoueur : public Joueur<joueur> {

public:
    IAJoueur() {
        this->nom = nom;
    }

    inline size_t effectuerCoup() {
        return 0;
    }

    inline virtual void prendreEnCompteCoupAdversaire(size_t colonne) {

    }

    inline virtual const string getJoueurInformations() {
        return JeuxPuissanceQuatre::playerToString(joueur) + " joueur de type IA";
    }

}
#endif // IA_H_INCLUDED
