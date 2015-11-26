//MyScena.h
#include <iostream>
#include <sstream>
#include <string> 
#include <Ogre.h>
#include <CEGUI.h>

using namespace std;


class MyScena
{
	private:
		Ogre::SceneNode* _nodoalto;
		Ogre::SceneNode* _nodobajo;
		Ogre::SceneManager* _sceneManager;
	public:
		MyScena(Ogre::SceneNode* nA,Ogre::SceneNode* nB,Ogre::SceneManager* sm);
		~MyScena();
		void creartablero();
};