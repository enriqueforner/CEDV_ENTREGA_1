
//Tablero.cpp
#include "Tablero.h"

Tablero::Tablero(char tipo){
	_tipo = tipo;
	_casillas = new Casilla*[DIM];
	for(int i = 0; i < DIM; ++i) {
    	_casillas[i] = new Casilla[DIM];
	}
	_barcos = new std::vector<Barco>;
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

std::vector<Barco>* Tablero::getBarcos(){
	return _barcos;
}

void Tablero::colocarbarcos(int tipo, std::vector<int> *v){

	srand(time(NULL));
	int vdir[4] = {-1*(tipo-1),1*(tipo-1),10*(tipo-1),-10*(tipo-1)};
	vector<int>::iterator it;
	bool meterbarco=true;
	bool salir = true;
	while(salir){
		int vposlugares[tipo];
		int num;
		num =rand()%(100);
		int dir;
		dir =rand()%(4);
		int d = (num/10)%10;
		int u = num%10;
		meterbarco=true;
		if (vdir[dir]==-1*(tipo-1)){
			int nuevonum = num;
			for (int i = 0; i < tipo; ++i){
				vposlugares[i] = nuevonum;
				nuevonum = nuevonum -1;
			}
		}	
		if (vdir[dir]==1*(tipo-1)){
			int nuevonum = num;
			for (int i = 0; i < tipo; ++i){
				vposlugares[i] = nuevonum;
				nuevonum = nuevonum +1;
			}
		}
		if (vdir[dir]==-10*(tipo-1)){
			int nuevonum = num;
			for (int i = 0; i < tipo; ++i){
				vposlugares[i] = nuevonum;
				nuevonum = nuevonum -10;
			}
		}
		if (vdir[dir]==10*(tipo-1)){
			int nuevonum = num;
			for (int i = 0; i < tipo; ++i){
				vposlugares[i] = nuevonum;
				nuevonum = nuevonum +10;
			}
		}
		for (int i = 0; i < tipo; ++i){
			for (it = v->begin(); it != v->end();++it){
				if (*it==vposlugares[i]){
					meterbarco=false;
				}
			}
		}
		if(vdir[dir]==-10*(tipo-1)||vdir[dir]==10*(tipo-1)){
			if((d+(tipo-1)) > 9)meterbarco=false;			
			if((d-(tipo-1)) < 0)meterbarco=false;
		}
		if(vdir[dir]==-1*(tipo-1)||vdir[dir]==1*(tipo-1)){
			if((u+(tipo-1)) > 9)meterbarco=false; 
			if((u-(tipo-1)) < 0)meterbarco=false;		
		}
		if (meterbarco){
			Barco *bm = new Barco(tipo);
			_barcos->push_back(*bm);
			for (int i = 0; i < tipo; ++i){
				int nummeter = vposlugares[i];
				int d = (nummeter/10)%10;
				int u = nummeter%10;
				_casillas[d][u].setBarco(bm);
				cout << _casillas[d][u].getId()<< "J  " << tipo <<endl;
				bm->addCasilla(nummeter);
				v->push_back(nummeter);
			}
			
			salir = false;
		}
		srand(time(NULL));	
	}
}

void Tablero::atacarcasilla(int id){
	int d = (id/10)%10;
	int u = id%10;
	Ogre::Entity * mEntity; 
	_casillas[d][u].setEstado("agua");
	// Cambiar material de la casilla (agua)
	mEntity= static_cast<Ogre::Entity *>(_casillas[d][u].getSN()->getAttachedObject(0));
	mEntity->setMaterialName("MaterialAgua");
	vector<int> *_casillasBarco = new std::vector<int> ;
	vector<Barco>::iterator it;
	vector<int>::iterator it2;
	for (it = _barcos->begin(); it != _barcos->end();++it){
		_casillasBarco = it->getIdCasillas();
		for (it2 = _casillasBarco->begin(); it2 != _casillasBarco->end();++it2){
			if(*it2 == id){
				_casillas[d][u].setEstado("hundida");
				// Cambiar material de la casilla (rojo)
				mEntity= static_cast<Ogre::Entity *>(_casillas[d][u].getSN()->getAttachedObject(0));
				mEntity->setMaterialName("MaterialRojo");
				it->setDamage(it->getDamage()+1);
			}
		}	
	}	
}
