//Barco.cpp

#include "Barco.h"

Barco::Barco(int tipo){
	_tipo = tipo;
}
Barco::Barco(){}
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