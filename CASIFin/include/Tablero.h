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
	Tablero(char tipo,Ogre::SceneManager* sm);
	~Tablero();
	
	Casilla** getCasillas();
	void setCasillas(Casilla** newcasillas);
	std::vector<Barco>*  getBarcos();
	//void colocarbarcos(int tipo, std::vector<int> *v);
	void atacarcasilla(int id);
	void colocarbarcos(int ship_type, std::vector<int> *v);
	void colocarbarcoQ(int ship_type, std::vector<int> *v);
	bool colocarbarcosJUGADOR(int id, int tipobar,char rotacion);
	int barcoshundidos();
	int ataqueinteligente(std::vector<int> *_elegiblesInt);
	
private:
	Casilla **_casillas;
	int **_maquinapartida;
	std::vector<int> *_vpartida;
	
	std::vector<Barco> *_barcos;
	char _tipo;
	Ogre::SceneManager* _sceneManager;
};

#endif
