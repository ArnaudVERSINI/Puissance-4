#ifndef JOUEUR_HPP_INCLUDED
#define JOUEUR_HPP_INCLUDED
#include "jeu_puissance_4.hpp"

/**
 * Classe virtuelle pure de gestion d'un joueur
 * @argument joueur Dit si le joueur est le joueur bleu ou rouge
 */
template<TJoueur joueur>
class Joueur {
public:
    inline Joueur() {
    }

    virtual size_t effectuerCoup()=0;
    virtual void prendreEnCompteCoupAdversaire(size_t colonne)=0;
    virtual const string getJoueurInformations()=0;
};


template<TJoueur joueur>
class JoueurHumain : public Joueur<joueur> {
    string nom;

public:
    JoueurHumain(string nom) {
        this->nom = nom;
    }

    inline size_t effectuerCoup() {
        return 0;
    }

    inline virtual void prendreEnCompteCoupAdversaire(size_t colonne) {

    }

    inline virtual const string getJoueurInformations() {
        return JeuxPuissanceQuatre::playerToString(joueur) + " joueur humain nommé " + nom;
    }
};
#endif
