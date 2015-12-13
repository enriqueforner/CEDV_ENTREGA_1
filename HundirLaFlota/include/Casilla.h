//Casilla.h
#ifndef CASILLA_H
#define CASILLA_H

#include <Ogre.h>
#include <CEGUI.h>
#include <string> 
#include <iostream>
#include <sstream>
#include "Barco.h"
using namespace std;
class Casilla
{
public:
	Casilla();
	Casilla(Ogre::SceneNode *casilla, int id);
	~Casilla();
	Ogre::SceneNode* getSN() ;
	string getEstado();
	void setEstado(string nestado);
	int getId() const;
	void setBarco(Barco *barco);
	Barco* getBarco() const;
	void setId(int newid);
	string getTienebarco();
private:
	Ogre::SceneNode *_casilla;
	string _estado;
	int _id;
	Barco *_barco;
	string _tienebarco;
};

#endif