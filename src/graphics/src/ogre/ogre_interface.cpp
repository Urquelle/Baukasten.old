#include "ogre/ogre_interface.h"

#include <iostream>

using namespace Baukasten;

OgreInterface::OgreInterface()
{
}

OgreInterface::~OgreInterface()
{
}

void OgreInterface::init()
{
}

void OgreInterface::renderForm( Form *form )
{
	std::cout << "in OgreInterface::renderForm" << std::endl;
}

