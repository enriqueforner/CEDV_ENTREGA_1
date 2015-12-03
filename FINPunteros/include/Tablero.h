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
#include <time.h>
#define DIM 10
using namespace std;

class Tablero
{
public:
	Tablero(char tipo);
	~Tablero();
	
	Casilla** getCasillas();
	void setCasillas(Casilla** newcasillas);
	std::vector<Barco>*  getBarcos();
	void colocarbarcos(int tipo, std::vector<int> *v);
	void atacarcasilla(int id);
	
private:
	Casilla **_casillas;
	std::vector<Barco> *_barcos;
	char _tipo;
	
};

#endif