#ifndef PLATEAU_HPP_INCLUDED
#define PLATEAU_HPP_INCLUDED

#include <string>
#include <stdexcept>

using namespace std;

enum TCase {
    BLUE = 0,
    RED = 1,
    NONE = 2
};

/**
 * Représentation interne du plateau de jeux.
 */

 class TCoord {
    size_t x;
    size_t y;

public:

    inline TCoord() : x(0), y(0) {}
    inline TCoord(size_t x, size_t y) : x(x), y(y){}

    inline size_t getX() const { return x; }
    inline size_t getY() const { return y; }

    inline void setX(size_t x) { this->x = x; }
    inline void setY(size_t y) { this->y = y; }
    inline void set(size_t x, size_t y) { this->x = x; this->y = y; }
 };

class PlateauException : public runtime_error {


    public :
    PlateauException(const char* message) : runtime_error(message) {
        //int* pointeur = NULL;
        //*pointeur = 0;
    }
};

class Plateau {

public :

    /**
     * Largeur du plateau de jeux.
     */
    static const size_t LARGEUR = 7;

    /**
     * Hauteur du plateau de jeux.
     */
    static const size_t HAUTEUR = 6;

private:
    /**
     * Le plateau de jeux.
     */
    TCase plateau[HAUTEUR][LARGEUR];

   /**
     * Réinitilialisation du plateau.
     */
    inline void initPlateau () {
        for (size_t i = 0; i < LARGEUR; i++) {
            for (size_t j = 0; j < HAUTEUR; j++) {
                plateau [j][i] = NONE;
            }
        }
    }

public:

    inline Plateau () {
        initPlateau();
    }

    /**
     * Retourne la valeur de la case donné en paramétre.
     * @param ligne Ligne sur laquelle est la case à définir.
     * @param colonne Colonne sur laquelle est la case à définir.
     * @param case_ La valeur de la case à mettre.
     */
    inline void set(size_t ligne, size_t colonne, TCase case_) {
        if (ligne < HAUTEUR && colonne < LARGEUR) {
            plateau[ligne][colonne] = case_;
        }
    }

    /**
     * Retourne la valeur de la case donné en paramétre.
     * @param ligne Ligne sur laquelle est la case à retourner.
     * @param colonne Colonne sur laquelle est la case à retourner.
     * @return La valeur de la case ou NONE si case incorrecte.
     */
    inline TCase get(size_t ligne, size_t colonne) const {
        if ((ligne < HAUTEUR) & (colonne < LARGEUR)) {
            return plateau[ligne][colonne];
        }
        throw PlateauException("Case inconnu");
    }

    /**
     * Retourne vrai ou faux selon si la colonne est jouable ou non.
     * @param colonne Colonne.
     * @return vrai si la colonne est jouable.
     */
    inline bool colonneJouable(size_t colonne) const{
        bool jouable = false;
        for (size_t line = 0; line < Plateau::HAUTEUR && jouable == false; line ++) {
            if (get(line,colonne) == NONE) {
            	jouable = true;
            }
        }
        return jouable;
    }

    /**
     * Ajoute un pion dans la colonne.
     * @param column La colonne où ajouter le pion.
     * @param case_ Le pion à ajouter
     * @return Le numero de ligne où est le jeton
     * @throw PlateauException
     */
    inline size_t addToColumn(size_t column, TCase case_) {
        if (column > LARGEUR)
            throw PlateauException("Coordonnés impossibles");
        for (size_t line = 0; line < Plateau::HAUTEUR; line ++) {
            if (get(line,column) == NONE) {
                set(line, column, case_);
                return line;
            }
        }
        throw PlateauException("Ajout dans la colonne impossible");
    }

    inline bool isPartieFinit() const{
        bool partieFinie = true;
        for (size_t colonne_actuelle = 0; colonne_actuelle < LARGEUR; colonne_actuelle++) {
            if ( get(HAUTEUR - 1, colonne_actuelle) == NONE) {
                partieFinie = false;
            }
        }
        return partieFinie;
    }

    inline void supprimerCoup(size_t colonne) {
        if (colonne >= LARGEUR)
            throw PlateauException("paramétre inconnus");
        for(int ligne_actuelle = HAUTEUR - 1; ligne_actuelle >= 0; ligne_actuelle--) {
            if (get(ligne_actuelle,colonne) != NONE) {
                set(ligne_actuelle,colonne, NONE);
                return;
            }
        }
        throw PlateauException("Coup introuvable");
    }

    inline bool aGagner(TCoord coord, TCase caseActuelle) {
        return aGagner(coord.getX(), coord.getY(), caseActuelle);
    }

    inline bool aGagner(size_t ligne, size_t colonne, TCase caseActuel) {
        size_t nb_pions = 0;

        //Axe horizontal
        for (
            int colonne_actuelle = colonne - 1;
            colonne_actuelle >= 0 && get(ligne, colonne_actuelle) == (TCase) caseActuel;
            colonne_actuelle--) {
            nb_pions++;
        }
        for (
            size_t colonne_actuelle = colonne + 1;
            colonne_actuelle < LARGEUR && get(ligne, colonne_actuelle) == (TCase) caseActuel;
            colonne_actuelle++) {
            nb_pions++;
        }

        if (nb_pions >= 3) {
            return true;
        }

        nb_pions = 0;
        //Axe vertical
        for (
            int ligne_actuelle = ligne - 1;
            ligne_actuelle >= 0 && get(ligne_actuelle, colonne) == (TCase) caseActuel;
            ligne_actuelle--) {
            nb_pions++;
        }

        for (
            size_t ligne_actuelle = ligne + 1;
            ligne_actuelle < HAUTEUR && get(ligne_actuelle, colonne) == (TCase) caseActuel;
            ligne_actuelle++) {
            nb_pions++;
        }

        if (nb_pions >= 3) {
            return true;
        }

        //Axe diagonale
        nb_pions = 0;

        for (
            int ligne_actuelle = ligne - 1, colonne_actuelle = colonne - 1;
            ligne_actuelle >= 0 && colonne_actuelle >= 0 && get(ligne_actuelle, colonne_actuelle) == (TCase) caseActuel;
            ligne_actuelle--, colonne_actuelle--) {
            nb_pions++;
        }

        for (
            size_t ligne_actuelle = ligne - 1, colonne_actuelle = colonne + 1;
            ligne_actuelle < HAUTEUR && colonne_actuelle < LARGEUR && get(ligne_actuelle, colonne_actuelle)== (TCase) caseActuel;
            ligne_actuelle--, colonne_actuelle++) {
            nb_pions++;
        }

        if (nb_pions >= 3) {
            return true;
        }

    }
};

#endif // PLATEAU_HPP_INCLUDED
