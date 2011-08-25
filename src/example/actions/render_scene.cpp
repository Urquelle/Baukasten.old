#include "render_scene.h"

#include "forms/ogre_form.h"

#include <game_entity.h>
#include <logical_space.h>

#include <iostream>

using namespace Baukasten;

void RenderScene::doAction( GameEntity *entity )
{
	Form *form = static_cast<Form*>( getSource()->getForm() );

	if ( !form )
		return;

	EntityMap map = form->getLSpace( "objects" )->getEntities();

	EntityMap::const_iterator it = map.begin();
	while( it != map.end() ) {
		GameEntity *entity = static_cast<GameEntity*>( it->second );
		OgreForm *oForm = static_cast<OgreForm*>( entity->getForm() );
		oForm->renderScene();
		it++;
	}
}

