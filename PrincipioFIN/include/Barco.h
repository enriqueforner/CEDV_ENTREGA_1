//Barco.h
#include "Casilla.h"
#include <Ogre.h>
#include <CEGUI.h>
#include <string> 
#include <iostream>
#include <sstream>
using namespace std;
 class Barco
 {
 public:
 	Barco(int tipo);
 	~Barco();
 	int getTipo() const;
 	void agregarcasillas(Casilla nodo);
 	std::vector<Casilla> getPosiciones();
 	int getDamage() const;
    void setDamage(int damage);
 private:
 	int _tipo;
 	int _damage;
 	std::vector<Casilla> _posiciones;
 };