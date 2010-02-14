/*
Programme qui ouvre une fen�tre SDL
Program that opens a SDL window
Copyright (C) 2006 BEYLER Jean Christophe

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <SDL/SDL.h>
#include <iostream>


const int WIDTH=640;
const int HEIGHT=480;

int main(int argc, char **argv)
{
    //D�claration des variables
    SDL_Event event;
    SDL_Surface *screen;
    int done = 0;

    //Initialisation de SDL
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        std::cerr << "Probleme pour initialiser SDL" << SDL_GetError() << std::endl;
        return 1;
    }

    //Mettre un titre � la fen�tre
    SDL_WM_SetCaption("Programme SDL de base", NULL);
    //Ouvrerture d'une surface pour l'affichage de la fen�tre
    screen = SDL_SetVideoMode(WIDTH,HEIGHT, 32,
                              SDL_DOUBLEBUF | SDL_HWSURFACE);
    if(screen==NULL)
        done = 1;
    //Boucle generale
    while(!done)
    {
        //Traiter les �v�nements
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                //Si on veut quitter, done=1 suffira
                case SDL_QUIT:
                done=1;
                break;
                //Si on vient de relacher une touche de clavier
                case SDL_KEYUP:
                //Et si c'est la lettre q
		/*
		 Attention, ceci ne fonctionne pas avec tous les Syst�mes d'exploitation et tous les claviers
		 Pour le rendre portable, il faudrait passer par les Unicodes, mais cela sort du cadre de ce tutoriel
		 d'introduction.
		 Si vous voulez utiliser la lettre 'q' pour quitter et ceci ne fonctionne pas, alors c'est la lettre
		 'a' qu'il faudra utiliser (c'est la place de la lettre 'q' sur le clavier QWERTY).
		 Si vous voulez vraiment la lettre 'q', remplacer SDLK_q par SDLK_a, cela devrait faire l'affaire
		 */
                if(event.key.keysym.sym==SDLK_q)
                    //On met done a 1 pour quitter
                    done=1;
                break;
                //Sinon on ne fait rien
                default:
                break;
            }
        }
    }

    SDL_Quit();
    return 0;
}
