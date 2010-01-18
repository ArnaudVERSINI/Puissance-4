#ifndef PLATEAU_HPP_INCLUDED
#define PLATEAU_HPP_INCLUDED

enum TCase {
    BLUE = 0,
    RED = 1,
    NONE = 2
};

/**
 * Représentation interne du plateau de jeux.
 */
class Plateau {

public :

    /**
     * Largeur du plateau de jeux.
     */
    static const size_t LARGEUR = 6;

    /**
     * Hauteur du plateau de jeux.
     */
    static const size_t HAUTEUR = 7;

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
        TCase retValue = NONE;
        if ((ligne < LARGEUR) & (colonne < HAUTEUR)) {
            retValue = plateau[ligne][colonne];
        }
        return retValue;
    }

    /**
     * Ajoute un pion dans la colonne.
     * @param column La colonne où ajouter le pion.
     * @param case_ Le pion à ajouter
     * @return Le numero de ligne ou -1 en cas d'impossibilité.
     */
    int addToColumn(size_t column, TCase case_) {
        for (size_t line = 0; line < Plateau::HAUTEUR; line ++) {
            if (get(line,column) == NONE) {
                set(line, column, case_);
                return line;
            }
        }
        return -1;
    }
};

#endif // PLATEAU_HPP_INCLUDED
