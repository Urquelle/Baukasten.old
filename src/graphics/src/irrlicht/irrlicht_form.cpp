#include "irrlicht/irrlicht_form.h"

#include <irrlicht/irrlicht.h>

using namespace Baukasten;

using namespace irr;
using namespace scene;

IrrlichtForm::IrrlichtForm( const std::string &id, IrrlichtGraphics *graphics ) :
	Form( id ),
	mGraphics( graphics )
{
}

IrrlichtForm::~IrrlichtForm()
{
}

