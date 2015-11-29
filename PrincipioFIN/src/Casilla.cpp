#include "Casilla.h"

Casilla::Casilla(){}

Casilla::Casilla(Ogre::SceneNode *casilla){
	_casilla = casilla;
	_id = casilla->getName();
}

Casilla::~Casilla(){}

Ogre::SceneNode Casilla::getSN() const{
	return *_casilla;
}

string Casilla::getEstado(){
	return _estado;
}

void Casilla::setEstado(string nestado){
	_estado = nestado;
}

string Casilla::getId() const{
	return _id;
}

void Casilla::setBarco(Barco barco){
	_barco = barco;
}
Barco Casilla::getBarco() const{
	return _barco;
}
