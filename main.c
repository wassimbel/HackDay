#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

void set_pos(SDL_Rect *cp, int limit)
{
	int i = 0;

	for (; i < limit; i++)
	{
		cp[i].x = 80;
		cp[i].y = 100 + (i * 75);
	}
}

void pos(SDL_Rect *cc, int limit)
{
	int i = 0, j = 0, k, x = 250, y = 450;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 4; j++)
		{
			k = ((i * 4) + i + j);
			cc[k].x = 250 + (j * 50);
			cc[k].y = 100 + (i * 50);
		}
	}
}

int main(int argc, char *argv[])
{
    int i = 0;
    SDL_Surface *screen = NULL, *surface = NULL;
    SDL_Rect position, cp[6], square_2, psquare_36[36];
    SDL_Event event;
    position.x = 0;
    position.y = 0;
    square_2.x = 200;
    square_2.y = 50;
    SDL_Surface *colors[6], *square_36[36], *bg;
    /* red, green, blue, yellow, white,  orange */
    int color_code[] = {204, 0, 0, 0, 102, 34, 0, 51, 102, 255, 255, 102, 255, 255, 255, 255, 102, 0};

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) // Démarrage de la SDL. Si erreur :
        {
            fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
            exit(EXIT_FAILURE); // On quitte le programme
        }

    screen = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    surface = SDL_LoadBMP("external.bmp");
    SDL_bool run = SDL_TRUE;

	bg = SDL_CreateRGBSurface(SDL_HWSURFACE, 340, 500, 32, 0, 0, 0, 0);
        SDL_FillRect(bg, NULL, SDL_MapRGB(bg->format, 102, 153, 153));


	for (i = 0; i < 36; i++)
	{
		square_36[i] = 	SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 30, 32, 0, 0, 0, 0);
		SDL_FillRect(square_36[i], NULL, SDL_MapRGB(square_36[i]->format, 0, 0, 0));
	}
	pos(psquare_36, 36);

	for (i = 0; i < 6; i++)
	{
		colors[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 25, 25, 32, 0, 0, 0, 0);
		SDL_FillRect(colors[i], NULL, SDL_MapRGB(colors[i]->format, color_code[i * 3], color_code[(i * 3) + 1], color_code[(i * 3) + 2]));
	}
	set_pos(cp, 6);


    while (run)
    {
	SDL_BlitSurface(surface, NULL, screen, &position);
	SDL_BlitSurface(bg, NULL, screen, &square_2);
	for (i = 0; i < 36; i++)
	{
		SDL_BlitSurface(square_36[i], NULL, screen, &psquare_36[i]);
		SDL_Flip(screen);
	}
		for (i = 0; i < 6; i++)
		{
			SDL_BlitSurface(colors[i], NULL, screen, &cp[i]);
			SDL_Flip(screen);
		}
        SDL_WaitEvent(&event);
        switch(event.type)
	{
		case SDL_QUIT:
			run = SDL_FALSE;
	}
	SDL_Flip(screen);
    }
    SDL_FreeSurface(screen);
   	SDL_FreeSurface(surface);
    SDL_Quit();
    return EXIT_SUCCESS;
}
