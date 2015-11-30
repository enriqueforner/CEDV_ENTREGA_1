//Tablero.h
#ifndef TABLERO_H
#define TABLERO_H

#include <Ogre.h>
#include <CEGUI.h>
#include <string> 
#include <iostream>
#include <sstream>
#include "Barco.h"
#include "Casilla.h"
#include <vector>
#define DIM 10
using namespace std;

class Tablero
{
public:
	Tablero(char tipo);
	~Tablero();
	// void agregarcasilla(Casilla casagregar);
	// void agregarbarco(Barco barcoagregar);
	// std::vector<Barco> getBarcos();
	// std::vector<Casilla> getCasillas();
	// void setCasillas(Casilla &casis[DIM][DIM]);
	//Casilla **getCasillas();
	
	Casilla **_casillas;

private:
	char _tipo;
	// std::vector<Casilla> _casillastablero;
	// std::vector<Barco> _barcostablero;
	//Casilla **_casillas;
};

#endif