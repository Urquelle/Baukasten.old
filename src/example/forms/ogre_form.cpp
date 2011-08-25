#include "ogre_form.h"

#include <OGRE/Ogre.h>


OgreForm::OgreForm( const std::string &id, Ogre::SceneManager *sm ) :
	Form( id ),
	mSceneManager( sm )
{
}

OgreForm::~OgreForm()
{
}

Ogre::SceneManager* OgreForm::getSceneManager() const
{
	return mSceneManager;
}

