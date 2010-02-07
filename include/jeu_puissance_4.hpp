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

inline TJoueur inverseJoueur(TJoueur joueur) {
    return joueur == JOUEUR_BLEU ? JOUEUR_ROUGE : JOUEUR_BLEU;
}


/**
 * Représentation d'un jeux de puissance 4  et gérant les actions des joueurs.
 */
class JeuxPuissanceQuatre {

    private:

    /**
     * Le joueur actuel (bleu ou rouge).
     */
    TJoueur joueurActuel;
    /**
     * Plateau de jeux permettant de conserver l'état de la partie.
     */
    Plateau plateau;

    /**
     * Flag indiquand si la partie est terminé, utile vu que le nul est possible.
      */
    bool partieFinie;

    /*
     * Joueur gagnant, information valide si la partie est finie.
      */
    TJoueur gagnant;

    /**
     * Procédure de changement de joueur, utile entre les tours.
    */
    inline void switchCurrentPlayer () {
        joueurActuel = joueurActuel == JOUEUR_BLEU ? JOUEUR_ROUGE : JOUEUR_BLEU;
    }

    public :

    /**
     * Tranformation d'un enum représentant une case en chaine de caractére.
     * @param case_ Case à tranformer.
     *  @return La chaine représentant la case.
     */
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

    /**
     * Tranformation d'un enum représentant un joueur en chaine de caractére.
     * @param case_ Joueur à tranformer.
     *  @return La chaine représentant le joueur.
     */
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

    /**
     * Construction d'un jeux avec plateau vide et joueur par defaut.
     */
    inline JeuxPuissanceQuatre() {
        partieFinie = false;
        joueurActuel = JOUEUR_BLEU;
        gagnant = JOUEUR_NUL;
    }

    inline void aGagner(size_t ligne, size_t colonne) {
        if (plateau.aGagner(ligne, colonne, (TCase) joueurActuel)) {
            gagnant = joueurActuel;
            partieFinie = true;
        }
    }

    /**
     * Fonction altérant l'état du jeux en jouant.
     * @param colonne Colonne à jouer
     * @return True si le jeux a été possible
     */
    inline bool jouer(size_t colonne) {
        if (partieFinie) {
            return false;
        }

        if (colonne >= Plateau::LARGEUR) {
            return false;
        }
        int ligne = plateau.addToColumn(colonne, (TCase) joueurActuel);

        if( ligne >= 0) {
            partieFinie = plateau.isPartieFinit();
            if (!partieFinie) {
                aGagner(ligne, colonne);
                switchCurrentPlayer();
            }
        }
    }

    /**
     * Retourne le joueur actuel.
     * @return Le joueur actuel.
     */
    inline TJoueur getJoueurActuel() const {
        return joueurActuel;
    }

    /**
     * Retourne le joueur actuel sous forme de chaine affichable.
     * @return Le joueur actuel sous forme de chaine de caractére.
     */
    inline const string getJoueurActuelStr() const {
        return playerToString(joueurActuel);
    }

    /**
     * @return true si la partie est terminé
     */
    inline bool isEnded() const {
        return partieFinie;
    }

    /**
     * Retourne la case dont les coordonnés ont été passés en parametres.
     * @param ligne Ligne de la case à retourner
     * @param  colonne Colonne de la ligne à afficher
     * @return La valeur de la case
     */
    inline TCase getCasePlateau(size_t ligne, size_t colonne) const {
        return plateau.get(ligne, colonne);
    }

    /**
     * Création d'une chaine de représentation du joueur actuel.
      * @return Chaine du joueur
      */
    inline const string getJoueurActuelGagnantStr() const {
        return playerToString(gagnant);
    }

    /**
     * Conversion du jeux en chaine de caractére pour affichage pour debugage.
     * @return Le plateau en string
     */
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

    /**
     * Retourne vrai ou faux selon si la colonne est jouable ou non.
     * @param colonne Colonne.
     * @return vrai si la colonne est jouable.
     */
    inline bool estColonneJouable(size_t colonne) const {
           return plateau.colonneJouable(colonne);
    }
};

#endif // JEU_PUISSANCE_4_HPP_INCLUDED
