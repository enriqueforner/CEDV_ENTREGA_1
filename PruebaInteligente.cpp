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

class PruebaInteligente{
	//vector<int> *aciertos;
	vector<int> *posibles;
	int *_pcasillas;

	public void main(){
		//aciertos = new vector<int>;
		posibles = new vector<int>;
		_pcasillas = new int[100];

	}
	//Esto iria dentro de tablero
	public int jugadaInteligente(_pcasillas,posibles){

		srand(time(NULL));
		int result = -1;
		int random = 0;
		int tens = 0;
		int units = 0;
		if (posibles->size() == 0){ //no tienes casillas posibles 
			random = rand()%(100);
			if(_pcasillas[i]!= -1){ //si no ha sido explorada
				_pcasillas[i]=-1; //la marcas como explorada
				result = _pcasillas[i]; //la preparas para devolverla
				tens = (random/10)%10;
				units = random%10;
				if(_casillas[tens][units].getBarco()!= NULL){ //si la casilla tiene barco
					
					if((tens -1)>=0){
						if(_pcasillas[random-10]!=-1){ //si no ha sido atacada
							posibles->push_back(_pcasillas[random-10]); //La metes en el vector de posibles
						} 
							
					}

					if((tens +1)<=9){
						if(_pcasillas[random+10]!=-1){ //si no ha sido atacada
							posibles->push_back(_pcasillas[random+10]); //La metes en el vector de posibles
						} 
							
					}

						
					if((units -1)>=0){
						if(_pcasillas[random-1]!=-1){ //si no ha sido atacada
							posibles->push_back(_pcasillas[random-1]); //La metes en el vector de posibles
						} 
							
					}

						
					if((units +1)<=9){
						if(_pcasillas[random+1]!=-1){ //si no ha sido atacada
							posibles->push_back(_pcasillas[random+1]); //La metes en el vector de posibles
						} 
							
					}
					
				}
			}
		}
		else{ //Hay alguna casilla en posibles
			result = posibles->at(0);            // coges la primera, por ejemplo
			posibles->erase(posibles->begin());	 //la borras de posibles
			_pcasillas[result]=-1;	             //la marcas como atacada;	
		}
		return result;
	}
}