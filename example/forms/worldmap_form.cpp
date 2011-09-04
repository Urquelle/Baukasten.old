#include "worldmap_form.h"

#include <SDL/SDL.h>

#include <iostream>

using namespace Baukasten;

WorldMapForm::WorldMapForm( const std::string &id, SDL_Surface *screen ) :
	Form( id ),
	mScreen( screen )
{
	SDL_Surface *t_surface = SDL_LoadBMP( "worldmap.bmp" );
	if ( t_surface == 0 ) {
		std::cout << SDL_GetError() << std::endl;
	}

	SDL_Surface *surface = SDL_DisplayFormat( t_surface );
	SDL_FreeSurface( t_surface );

	SDL_BlitSurface( surface, 0, mScreen, 0 );
	SDL_Flip( mScreen );
}

WorldMapForm::~WorldMapForm()
{
}

