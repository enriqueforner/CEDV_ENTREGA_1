//Casilla.h

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
	Casilla(Ogre::SceneNode *casilla);
	~Casilla();
	Ogre::SceneNode getSN() const;
	string getEstado();
	void setEstado(string nestado);
	string getId() const;
	void setBarco(Barco barco);
	Barco getBarco() const;
private:
	Ogre::SceneNode* _casilla;
	string _estado;
	string _id;
	Barco _barco;
};