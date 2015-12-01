
//Tablero.cpp
#include "Tablero.h"

Tablero::Tablero(char tipo){
	_tipo = tipo;
	_casillas = new Casilla*[DIM];
	for(int i = 0; i < DIM; ++i) {
    	_casillas[i] = new Casilla[DIM];
	}
}

Tablero::~Tablero(){
	for(int i = 0; i < DIM; ++i) {
    	delete [] _casillas[i];
	}
	delete [] _casillas;
}

Casilla** Tablero::getCasillas(){
	return _casillas;
}

void Tablero::setCasillas(Casilla** newcasillas){
	_casillas = newcasillas;
}
// void setCasillas(Casilla &casis[DIM][DIM]){

// }

// Casilla** Tablero::getCasillas(){

// }
// void Tablero::agregarcasilla(Casilla casagregar){
// 	_casillastablero.push_back(casagregar);
// }

// void Tablero::agregarbarco(Barco barcoagregar){
// 	_barcostablero.push_back(barcoagregar);
// }

// std::vector<Barco> Tablero::getBarcos(){
// 	return _barcostablero;
// }

// std::vector<Casilla> Tablero::getCasillas(){
// 	return  _casillastablero;
// }