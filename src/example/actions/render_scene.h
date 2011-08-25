#ifndef RENDER_SCENE_CO4O36JO
#define RENDER_SCENE_CO4O36JO

#include <action.h>

class RenderScene : public Baukasten::Action {
public:
	RenderScene( Baukasten::GameEntity &source ) :
		Baukasten::Action( source, "renderScene" )
	{
	}

	virtual ~RenderScene()
	{
	}

	void doAction( Baukasten::GameEntity* );
};

#endif /* end of include guard: RENDER_SCENE_CO4O36JO */
