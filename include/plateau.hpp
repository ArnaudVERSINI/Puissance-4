#ifndef PLATEAU_HPP_INCLUDED
#define PLATEAU_HPP_INCLUDED

enum TCase {
    BLUE = 0,
    RED = 1,
    NONE = 2
};

class Plateau {

public :

    static const size_t LARGEUR = 6;
    static const size_t HAUTEUR = 7;

private:
    /**
     * Le plateau de jeux
     */
    TCase plateau[HAUTEUR][LARGEUR];

public:
    inline Plateau () {
        initPlateau();
    }

    inline void initPlateau () {
        for (size_t i = 0; i < LARGEUR; i++) {
            for (size_t j = 0; j < HAUTEUR; j++) {
                plateau [j][i] = NONE;
            }
        }
    }

    inline void set(size_t ligne, size_t colonne, TCase case_) {
        if (ligne < HAUTEUR && colonne < LARGEUR) {
            plateau[ligne][colonne] = case_;
        }
    }

    inline TCase get(size_t ligne, size_t colonne) const {
        TCase retValue = NONE;
        if ((ligne < LARGEUR) & (colonne < HAUTEUR)) {
            retValue = plateau[ligne][colonne];
        }
        return retValue;
    }

    int addToColumn(size_t column, TCase case_) {
        bool aJoue = false;

        for (size_t line = 0; line < Plateau::HAUTEUR && !aJoue; line ++) {
            if (get(line,column) == NONE) {
                set(line, column, case_);
                return line;
            }
        }
        return -1;
    }
};

#endif // PLATEAU_HPP_INCLUDED
