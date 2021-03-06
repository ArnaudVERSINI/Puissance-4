#ifndef JOUEUR_HPP_INCLUDED
#define JOUEUR_HPP_INCLUDED
#include "jeu_puissance_4.hpp"
#include <iostream>

using namespace std;

/**
 * Classe virtuelle pure de gestion d'un joueur
 * @argument joueur Dit si le joueur est le joueur bleu ou rouge
 */
template<TJoueur joueur>
class Joueur {
public:

    /**
     * Constructeur par defaut faisant... ben pas grand chose.
    */
    inline Joueur() {
    }

    /**
     * Méthode de demande de coup du joueur.
     * @return La colonne que le joueur a choisi.
    */
    virtual size_t effectuerCoup()=0;

    /**
     * Méthode appellé a chaque coup de l'adversaire pour le prendre en compte.
     * @param Le coup à prendre en compte
     */
    virtual void prendreEnCompteCoupAdversaire(size_t colonne)=0;

    /**
     * Retourne les informations sur le joueur comme ses réglages ou son nom.
     @return Informations sur le joueur.
     */
    virtual const string getJoueurInformations()=0;

    /**
     * Fonction utilitaire renvoyant le joueur adverse
     * @return Le joueur adverse
     */
     inline TJoueur getJoueurAdverse() {
        return inverseJoueur(joueur);
     }
};


template<TJoueur joueur>
class JoueurHumain : public Joueur<joueur> {
    string nom;
    Plateau plateau;

    inline string getName() {
        return JeuxPuissanceQuatre::playerToString(joueur);
    }

public:
    JoueurHumain() {
        cout << "Veuillez entrez le nom du joueur " << getName() << " : " ;
        cin >> nom;
    }

    inline virtual size_t effectuerCoup() {
        size_t colonne = Plateau::LARGEUR;
        do {
            cout << "Coup du joueur " << getName() << " nommé " << nom << endl;
            cout << "Veuillez saisir le numero de colonne où jouer : ";
            cin >> colonne;
            cout << endl;
            if (colonne >= Plateau::LARGEUR) {
                cout << "Merci de saisir un numero entre 0 et " << Plateau::LARGEUR - 1 << endl;
                colonne = Plateau::LARGEUR;
            }
            if (!plateau.colonneJouable(colonne)) {
                cout << "Merci de saisir une colonne nonpleine" << endl;
                colonne = Plateau::LARGEUR;
            }
        } while (colonne >= Plateau::LARGEUR);
        plateau.addToColumn(colonne, (TCase) joueur);
        return colonne;
    }

    inline virtual void prendreEnCompteCoupAdversaire(size_t colonne) {
        plateau.addToColumn(colonne, (TCase) this->getJoueurAdverse());
    }

    inline virtual const string getJoueurInformations() {
        return getName() + " joueur humain nommé " + nom;
    }
};
#endif
