#include "render_scene.h"

#include "forms/ogre_form.h"

#include <game_entity.h>

#include <iostream>

using namespace Baukasten;

void RenderScene::doAction( GameEntity *entity )
{
	Form *form = static_cast<Form*>( getSource()->getForm() );

	if ( !form )
		return;

	std::cout << "render scene." << std::endl;
}

