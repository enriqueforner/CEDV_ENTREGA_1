#include "Casilla.h"

Casilla::Casilla(){}

Casilla::Casilla(Ogre::SceneNode *casilla,int id){
	_casilla = casilla;
	_id = id;
}

Casilla::~Casilla(){}

Ogre::SceneNode* Casilla::getSN(){
	return _casilla;
}

string Casilla::getEstado(){
	return _estado;
}

void Casilla::setEstado(string nestado){
	_estado = nestado;
}

int Casilla::getId() const{
 	return _id;
}

void Casilla::setBarco(Barco *barco){
	_barco = barco;
}
Barco* Casilla::getBarco() const{
	return _barco;
}

void Casilla::setId(int newid){
	_id = newid;
}
