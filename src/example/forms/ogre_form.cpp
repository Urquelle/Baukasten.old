#include "ogre_form.h"

#include <OGRE/Ogre.h>


OgreForm::OgreForm( const std::string &id, Ogre::Root *root ) :
	Form( id ),
	mRoot( root )
{
}

OgreForm::~OgreForm()
{
}

Ogre::Root* OgreForm::getRoot() const
{
	return mRoot;
}

