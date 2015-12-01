//Barco.cpp

#include "Barco.h"

Barco::Barco(){}
Barco::Barco(int tipo, Ogre::SceneNode *barco){
	_tipo = tipo;
	_barco = barco;
}

Barco::~Barco(){}

int Barco::getDamage()const{
	return _damage;
}

void Barco::setDamage(int damage){ 
	_damage = damage;
}

string Barco::getId()const{
	return _id;
}

void Barco::setId(string id){ 
	_id = id;
}

int Barco::getTipo() const{
	return _tipo;
}

void Barco::addCasilla(int id){
	if ( std::find(_idcasillas.begin(),_idcasillas.end(),id) != _idcasillas.end()){
	}else{
		_idcasillas.push_back(id);
	}
}

std::vector<int> Barco::getIdCasillas(){
	return _idcasillas;
}

Ogre::SceneNode* Barco::getSN(){
	return _barco;
}