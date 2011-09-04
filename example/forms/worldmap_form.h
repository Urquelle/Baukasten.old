#ifndef WORLDMAP_FORM_OPYB550X
#define WORLDMAP_FORM_OPYB550X

#include <form.h>

class SDL_Surface;

class WorldMapForm : public Baukasten::Form {
public:
	WorldMapForm( const std::string&, SDL_Surface* );
	virtual ~WorldMapForm();

private:
	SDL_Surface* mScreen;
};

#endif /* end of include guard: WORLDMAP_FORM_OPYB550X */
