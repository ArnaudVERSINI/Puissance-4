#ifndef IHM_CONSOLE_H_INCLUDED
#define IHM_CONSOLE_H_INCLUDED

#include "jeu_puissance_4.hpp"
#include "joueur.hpp"

// include C++
#include <iostream>
#include <cstdlib>

using namespace std;

namespace ConsoleBase {
    static const string CLEAR = "\x1b[2J";
    static const string BLUE = "\x1b[44m";
    static const string RED = "\x1b[41m";
    static const string BLACK = "\x1b[40m";
    static const string RESET = "\x1b[0m";
};

class IHMConsole {

public :

    inline void printCase(TCase case_) {
        switch(case_) {
            case BLUE:
            cout << "X";
            break;

            case RED:
            cout << "O";
            break;

            default:
            cout << "-";
        }
        cout << " ";
    }

    inline void print(JeuxPuissanceQuatre _jeux) {
    	cout << ConsoleBase::CLEAR;
           for(int ligne = Plateau::HAUTEUR - 1; ligne >= 0; ligne--) {
                   cout << "\t";
                   cout << ligne << " ";
               for(size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
                   printCase(_jeux.getCasePlateau(ligne, colonne));

                   //cout << " ";
               }
               //cout << ConsoleBase::RESET ;
				  cout << endl;
           }
           cout << "\t  0 1 2 3 4 5 6" << endl;
       }



    inline IHMConsole(){

/*    	jeux.jouer(2);
    	print();
    	sleep(3);
    	jeux.jouer(3);
    	print();*/
    }

    inline ~IHMConsole() {

    }
};



#endif // IHM_CONSOLE_H_INCLUDED
