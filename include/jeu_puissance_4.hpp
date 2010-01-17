#ifndef JEU_PUISSANCE_4_HPP_INCLUDED
#define JEU_PUISSANCE_4_HPP_INCLUDED
#include <iostream>
#include "plateau.hpp"

using namespace std;



enum TJoueur {
    JOUEUR_BLEU = 0,
    JOUEUR_ROUGE = 1,
    JOUEUR_NUL = 2
};

class JeuxPuissanceQuatre {

    private:

    TJoueur joueurActuel;
    Plateau plateau;

    bool partieFinie;

    TJoueur gagnant;


    inline void switchCurrentPlayer () {
        joueurActuel = joueurActuel == JOUEUR_BLEU ? JOUEUR_ROUGE : JOUEUR_BLEU;
    }

    public :

    static inline const string caseToString(TCase case_) {
        const char* chaine = NULL;
        switch (case_) {
         case BLUE:
            chaine = "X";
            break;
        case RED:
            chaine = "0";
            break;
        default :
            chaine = " ";
            break;
        }
        return chaine;
    }

    static inline const string playerToString(TJoueur joueur) {
        const char* chaine = NULL;
        switch (joueur) {
         case JOUEUR_BLEU:
            chaine = "Joueur bleu";
            break;
        case JOUEUR_ROUGE:
            chaine = "Joueur rouge";
            break;
        default :
            chaine = "";
            break;
        }
        return chaine;
    }

    inline JeuxPuissanceQuatre() {
        partieFinie = false;
        joueurActuel = JOUEUR_BLEU;
        gagnant = JOUEUR_NUL;
    }

    inline void aGagner(size_t ligne, size_t colonne) {
        size_t nb_pions = 0;

        if (ligne == Plateau::HAUTEUR - 1) {
            for (size_t colonne_actuelle = 0; colonne_actuelle < Plateau::LARGEUR && !partieFinie; colonne_actuelle++) {
                if ( plateau.get(Plateau::HAUTEUR - 1, colonne_actuelle) == NONE) {
                    partieFinie = true;
                }
            }
        }

        //Axe horizontal
        for (
            int colonne_actuelle = colonne - 1;
            colonne_actuelle >= 0 && plateau.get(ligne, colonne_actuelle) == (TCase) joueurActuel;
            colonne_actuelle--) {
            nb_pions++;
        }
        for (
            size_t colonne_actuelle = colonne + 1;
            colonne_actuelle < Plateau::LARGEUR && plateau.get(ligne, colonne_actuelle) == (TCase) joueurActuel;
            colonne_actuelle++) {
            nb_pions++;
        }

        if (nb_pions >= 3) {
            gagnant = joueurActuel;
            partieFinie = true;
            return;
        }

        nb_pions = 0;
        //Axe vertical
        for (
            int ligne_actuelle = ligne - 1;
            ligne_actuelle >= 0 && plateau.get(ligne_actuelle, colonne) == (TCase) joueurActuel;
            ligne_actuelle--) {
            nb_pions++;
        }

        for (
            size_t ligne_actuelle = ligne + 1;
            ligne_actuelle < Plateau::HAUTEUR && plateau.get(ligne_actuelle, colonne) == (TCase) joueurActuel;
            ligne_actuelle++) {
            nb_pions++;
        }

        if (nb_pions >= 3) {
            gagnant = joueurActuel;
            partieFinie = true;
            return;
        }

        //Axe diagonale
        nb_pions = 0;

        for (
            int ligne_actuelle = ligne - 1, colonne_actuelle = colonne - 1;
            ligne_actuelle >= 0 && colonne_actuelle >= 0 && plateau.get(ligne_actuelle, colonne) == (TCase) joueurActuel;
            ligne_actuelle--, colonne_actuelle--) {
            nb_pions++;
        }

        for (
            size_t ligne_actuelle = ligne + 1, colonne_actuelle = colonne + 1;
            ligne_actuelle < Plateau::HAUTEUR && colonne_actuelle < Plateau::LARGEUR && plateau.get(ligne_actuelle, colonne)== (TCase) joueurActuel;
            ligne_actuelle++, colonne_actuelle++) {
            nb_pions++;
        }

        if (nb_pions >= 3) {
            gagnant = joueurActuel;
            partieFinie = true;
            return;
        }
    }

    inline bool jouer(size_t colonne) {
        if (partieFinie) {
            return false;
        }

        if (colonne >= Plateau::LARGEUR) {
            return false;
        }
        int ligne = plateau.addToColumn(colonne, (TCase) joueurActuel);
        if( ligne > 0) {
            aGagner(ligne, colonne);
            switchCurrentPlayer();
        }
    }

    inline TJoueur getJoueurActuel() const {
        return joueurActuel;
    }

    inline const string getJoueurActuelStr() const {
        return playerToString(joueurActuel);
    }

    inline bool isEnded() const {
        return partieFinie;
    }

    inline TCase getCasePlateau(size_t ligne, size_t colonne) const {
        return plateau.get(ligne, colonne);
    }

    inline const string getJoueurActuelGagnantStr() const {
        return playerToString(gagnant);
    }

    inline const string toString() const {
        string retValue;

        for(int ligne_actuelle = Plateau::HAUTEUR - 1; ligne_actuelle >= 0; ligne_actuelle--) {
            for(size_t i = 0; i < (Plateau::LARGEUR * 2) + 1; i++) {
                retValue += "-";
            }
            retValue += "\n";

            for(size_t colonne_actuelle = 0; colonne_actuelle <  Plateau::LARGEUR; colonne_actuelle++) {
                retValue += "|";
                retValue += caseToString(plateau.get(ligne_actuelle, colonne_actuelle));
            }
            retValue += "|\n";
        }
        return retValue;
    }
};

#endif // JEU_PUISSANCE_4_HPP_INCLUDED
