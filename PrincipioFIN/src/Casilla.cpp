#include "Casilla.h"

Casilla::Casilla(){}

Casilla::Casilla(Ogre::SceneNode *casilla){
	_casilla = casilla;
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