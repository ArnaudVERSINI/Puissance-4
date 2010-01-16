#ifndef JEU_PUISSANCE_4_HPP_INCLUDED
#define JEU_PUISSANCE_4_HPP_INCLUDED
#include <iostream>

using namespace std;

enum Case {
    BLUE = 0,
    RED = 1,
    NONE = 2
};

enum Joueur {
    JOUEUR_BLEU = 0,
    JOUEUR_ROUGE = 1,
    JOUEUR_NUL = 2
};

class JeuxPuissanceQuatre {
    public:
    static const size_t LARGEUR = 6;
    static const size_t HAUTEUR = 7;
    private:
    /**
     * Le plateau de jeux
     */
    Case plateau[HAUTEUR][LARGEUR];

    Joueur joueurActuel;

    bool partieFinie;

    Joueur gagnant;


    inline void switchCurrentPlayer () {
        joueurActuel = joueurActuel == JOUEUR_BLEU ? JOUEUR_ROUGE : JOUEUR_BLEU;
    }

    static inline const string caseToString(Case case_) {
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

    static inline const string playerToString(Joueur joueur) {
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

    public :

    inline JeuxPuissanceQuatre() {
        partieFinie = false;
        for (size_t i = 0; i < LARGEUR; i++) {
            for (size_t j = 0; j < HAUTEUR; j++) {
                plateau [j][i] = NONE;
            }
        }
        joueurActuel = JOUEUR_BLEU;
        gagnant = JOUEUR_NUL;
    }

    inline void aGagner(size_t ligne, size_t colonne) {
        size_t nb_pions = 0;

        if (ligne == HAUTEUR - 1) {
            for (size_t colonne_actuelle = 0; colonne_actuelle < LARGEUR && !partieFinie; colonne_actuelle++) {
                if ( plateau[HAUTEUR - 1][colonne_actuelle] == NONE) {
                    partieFinie = true;
                }
            }
        }

        //Axe horizontal
        for (
            int colonne_actuelle = colonne - 1;
            colonne_actuelle >= 0 && plateau[ligne][colonne_actuelle] == (Case) joueurActuel;
            colonne_actuelle--) {
            nb_pions++;
        }
        for (
            size_t colonne_actuelle = colonne + 1;
            colonne_actuelle < LARGEUR && plateau[ligne][colonne_actuelle] == (Case) joueurActuel;
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
            ligne_actuelle >= 0 && plateau[ligne_actuelle][colonne] == (Case) joueurActuel;
            ligne_actuelle--) {
            nb_pions++;
        }

        for (
            size_t ligne_actuelle = ligne + 1;
            ligne_actuelle < HAUTEUR && plateau[ligne_actuelle][colonne] == (Case) joueurActuel;
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
            ligne_actuelle >= 0 && colonne_actuelle >= 0 && plateau[ligne_actuelle][colonne] == (Case) joueurActuel;
            ligne_actuelle--, colonne_actuelle--) {
            nb_pions++;
        }

        for (
            size_t ligne_actuelle = ligne + 1, colonne_actuelle = colonne + 1;
            ligne_actuelle < HAUTEUR && colonne_actuelle < LARGEUR && plateau[ligne_actuelle][colonne] == (Case) joueurActuel;
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

        if (colonne >= LARGEUR) {
            return false;
        }

        bool aJoue = false;
        for (size_t ligne = 0; ligne < HAUTEUR && !aJoue; ligne ++) {
            if (plateau[ligne][colonne] == NONE) {
                plateau[ligne][colonne] = (Case) joueurActuel;
                aGagner(ligne, colonne);
                switchCurrentPlayer();
                aJoue = true;
            }
        }
        return aJoue;
    }

    inline Joueur getJoueurActuel() const {
        return joueurActuel;
    }

    inline const string getJoueurActuelStr() const {
        return playerToString(joueurActuel);
    }

    inline bool isEnded() const {
        return partieFinie;
    }

    inline Case getCasePlateau(size_t ligne, size_t colonne) {
        Case retValue = NONE;
        if ((ligne < LARGEUR) & (colonne < HAUTEUR)) {
            retValue = plateau[ligne][colonne];
        }
        return retValue;
    }

    inline const string getJoueurActuelGagnantStr() const {
        return playerToString(gagnant);
    }

    inline const string toString() const {
        string retValue;

        for(int ligne_actuelle = HAUTEUR - 1; ligne_actuelle >= 0; ligne_actuelle--) {
            for(size_t i = 0; i < (LARGEUR * 2) + 1; i++) {
                retValue += "-";
            }
            retValue += "\n";

            for(size_t colonne_actuelle = 0; colonne_actuelle <  LARGEUR; colonne_actuelle++) {
                retValue += "|";
                retValue += caseToString(plateau[ligne_actuelle][colonne_actuelle]);
            }
            retValue += "|\n";
        }
        return retValue;
    }
};

#endif // JEU_PUISSANCE_4_HPP_INCLUDED
