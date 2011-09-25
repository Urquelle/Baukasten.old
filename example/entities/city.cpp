#include "city.h"

#include "forms/city_form.h"
#include "../global.h"

#include <action_lambda.h>
#include <core_services.h>
#include <generic_state.h>

using namespace Baukasten;

DoActionFunction runScene( []( Action *action, GameEntity *entity ) {
	// set mode of the form to play
	Form * form = action->getSource()->getForm();
	form->getState<StateInt*>( "state:mode" )->setValue( Mode::MODE_RUNSCENE );
});

City::City( const string &id, const string &filePath ) :
	GameEntity( id )
{
	CoreServices *services = CoreServices::instance();

	addAction( new ActionLambda( *this, "runScene", &runScene ) );

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

