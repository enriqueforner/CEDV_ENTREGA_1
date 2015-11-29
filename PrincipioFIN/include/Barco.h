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
 	void agregarcasillas(string nodo);
 private:
 	int _tipo;
 	string _posiciones[];
 };