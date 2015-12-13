//MyScena.h
#ifndef MYSCENA_H
#define MYSCENA_H

#include <iostream>
#include <sstream>
#include <string> 
#include <Ogre.h>
#include <CEGUI.h>
#include "Tablero.h"
using namespace std;

class MyScena
{
	private:
		Ogre::SceneNode* _nodoalto;
		Ogre::SceneNode* _nodobajo;
		Ogre::SceneManager* _sceneManager;
		Tablero *_tabj;
		Tablero *_tabm;
	public:
		MyScena(Ogre::SceneNode* nA,Ogre::SceneNode* nB,Ogre::SceneManager* sm, Tablero *tabj, Tablero *tabm);
		~MyScena();
		void creartablero();
};

#endif