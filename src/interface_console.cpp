#include "jeu_puissance_4.hpp"
#include "joueur.hpp"
#include <iostream>
#include <cstdlib>

namespace Console {
    static const string CLEAR = "\x1b[2J";
    static const string BLUE = "\x1b[44m";
    static const string RED = "\x1b[41m";
    static const string BLACK = "\x1b[40m";
    static const string RESET = "\x1b[0m";
};

class InterfaceConsole {

    JeuxPuissanceQuatre jeux;

public :

    inline void printCase(TCase case_) {
        switch(case_) {
            case BLUE:
            cout << Console::BLUE;
            break;

            case RED:
            cout << Console::RED;
            break;

            default:
            cout << Console::BLACK;
        }
        cout << " ";
    }

    inline void print() {
        cout << Console::CLEAR;
        for(int ligne = Plateau::HAUTEUR - 1; ligne >= 0; ligne--) {
                cout << "\t";
            for(size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
                printCase(jeux.getCasePlateau(ligne, colonne));
            }
            cout << Console::RESET;
            cout << endl;
        }
    }

    inline InterfaceConsole() {
        jeux.jouer(2);
        print();
    }

    inline ~InterfaceConsole() {
        cout << Console::RESET;
        cout << endl;
        cout << endl;
    }
};

int main()
{
    JoueurHumain<JOUEUR_BLEU> joueur("toto");
    cout << joueur.getJoueurInformations();

    //InterfaceConsole console;
}
