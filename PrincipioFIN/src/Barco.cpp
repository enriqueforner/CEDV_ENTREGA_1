//Barco.cpp

#include "Barco.h"

Barco::Barco(int tipo){
	_tipo = tipo;
}
Barco::~Barco(){}

void Barco::agregarcasillas(Casilla nodo){
	_posiciones.push_back(nodo);
}

std::vector<Casilla> Barco::getPosiciones(){
	return _posiciones;
}
int Barco::getDamage()const{
	return _damage;
}

void Barco::setDamage(int damage){ 
	_damage = damage;
}