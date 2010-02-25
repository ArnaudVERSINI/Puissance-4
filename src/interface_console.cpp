#include "interface_console.h"
#include "ia.h"
#include "controler.hpp"


int main()
{
    JoueurHumain<JOUEUR_BLEU> humain;
    IAJoueurMinMax<JOUEUR_ROUGE, 10> ia;
    Controler controler(humain, ia);
    controler.launchGame();
    JoueurHumain<JOUEUR_BLEU> joueur();
    //cout << joueur.getJoueurInformations();

    //InterfaceConsole console;
}
