#include "render_scene.h"

#include "forms/ogre_form.h"

#include <game_entity.h>
#include <virtual_space.h>

using namespace Baukasten;

void RenderScene::doAction( GameEntity *entity )
{
	Form *form = getSource()->getForm();

	if ( !form )
		return;

	EntityMap map = form->getVSpace()->getEntities();

	EntityMap::const_iterator it = map.begin();
	while( it != map.end() ) {
		Form *oForm = static_cast<Form*>( it->second );
		oForm->render();
		it++;
	}
}

