#include "city.h"

#include "forms/city_form.h"
#include "../global.h"

#include <action_lambda.h>
#include <core_services.h>
#include <generic_state.h>
#include <virtual_space.h>

using namespace Baukasten;

DoActionFunction runScene( []( Action *action, GameEntity *entity ) {
	// set mode of the form to play
	Form * form = action->getSource()->getForm();
	form->getState<StateInt*>( "state:mode" )->setValue( Mode::MODE_RUNSCENE );

	// remove worldmap and group from the vspace
	GameEntity *worldMap = action->getSource()->getParent();
	GameEntity *game = worldMap->getParent();

	// remove worldmap from game's vspace
	game->getForm()->removeFromVSpace( worldMap->getForm()->getId() );

	// add current city to game's vspace
	game->getForm()->addToVSpace( form );

	// ... run cut scene

	// start fight, after the cut scene
	form->setSize( { 1024, 768 } );
	form->setPosition( { 0, 0, 0 } );
	action->getSource()->invokeAction( "action:battle" );
});

DoActionFunction battle( []( Action *action, GameEntity *entity ) {
	action->getSource()->getForm()->getState<StateInt*>( "state:mode" )->setValue( Mode::MODE_BATTLE );
});

City::City( const string &id, const string &filePath ) :
	GameEntity( id )
{
	CoreServices *services = CoreServices::instance();

	addAction( new ActionLambda( *this, "runScene", &runScene ) );
	addAction( new ActionLambda( *this, "action:battle", &battle ) );

	addState( new StateInt( "state:visited", 0 ) );
	addState( new StateString( "state:name", "<unknown>" ) );
	addState( new StateString( "state:cityUp" ) );
	addState( new StateString( "state:cityRight" ) );
	addState( new StateString( "state:cityDown" ) );
	addState( new StateString( "state:cityLeft" ) );

	setForm( new CityForm( "form:city", filePath, services->getVideoService()) );
}

City::~City()
{
}

