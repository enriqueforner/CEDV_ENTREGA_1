
//Tablero.cpp
#include "Tablero.h"

Tablero::Tablero(char tipo, Ogre::SceneManager* sm){
	_tipo = tipo;
	_casillas = new Casilla*[DIM];
	for(int i = 0; i < DIM; ++i) {
    	_casillas[i] = new Casilla[DIM];
	}
	_barcos = new std::vector<Barco>;
	_sceneManager = sm;
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

void Tablero::colocarbarcosJUGADOR(int id, int tipobar, char rotacion){
  int d = (id/10)%10;
  int u = id%10;
  Ogre::Entity* entab= _sceneManager->createEntity("Barco.mesh");
  if (tipobar==2 || tipobar ==3){
  	Ogre::Entity* entab = _sceneManager->createEntity("Barco.mesh");
  }else{
  	Ogre::Entity* entab = _sceneManager->createEntity("BarcoP2B.mesh");
  }
  int nuevonum=0;
  bool meterbarco = true;
  		if (rotacion=='W'){
  			nuevonum = id;
  			for (int i = 0; i < tipobar; ++i){
				int d = (nuevonum/10)%10;
  				int u = nuevonum%10;
				if (_casillas[d][u].getTienebarco()=="SB"){
				  	meterbarco = false;				
				} 	
				nuevonum = nuevonum -10;
			}
  		}	
  		if (rotacion=='D'){
  			nuevonum = id;
	  		for (int i = 0; i < tipobar; ++i){
				int d = (nuevonum/10)%10;
  				int u = nuevonum%10;
				if (_casillas[d][u].getTienebarco()=="SB"){
			  		meterbarco = false;				
				}  			
				nuevonum = nuevonum +1;
			}
  		}
  		if (rotacion=='S'){
  			nuevonum = id;
  			for (int i = 0; i < tipobar; ++i){
				int d = (nuevonum/10)%10;
  				int u = nuevonum%10;
				if (_casillas[d][u].getTienebarco()=="SB"){
				  		meterbarco = false;				
				} 		
				nuevonum = nuevonum +10;
			}
  		}
  		if (rotacion=='A'){
  			nuevonum = id;
  			for (int i = 0; i < tipobar; ++i){
				int d = (nuevonum/10)%10;
  				int u = nuevonum%10;
				if (_casillas[d][u].getTienebarco()=="SB"){
				  		meterbarco = false;				
				}  			
				nuevonum = nuevonum -1;
			}
  		}

  if (meterbarco){
  		ostringstream osA;
  		osA << tipobar << _casillas[d][u].getSN()->getName();
  		cout << osA.str() << "...Creado" <<endl;
  		Ogre::SceneNode* nodeb = _sceneManager->createSceneNode(osA.str());
  		entab->setMaterialName("Materialbarco");
  		Barco *bar = new Barco(tipobar,nodeb);
  		nodeb->attachObject(entab);
  		if(tipobar==2)nodeb-> scale(0.4,0.4,0.35);
  		if(tipobar==3)nodeb-> scale(0.55,0.55,0.45);
  		if(tipobar==4)nodeb-> scale(0.75,0.75,0.50);
  		if(tipobar==5)nodeb-> scale(0.95,0.95,0.55);
  		nodeb-> setPosition(0.5,2.5,0);
  		if(rotacion=='W')nodeb -> yaw(Ogre::Degree(-90));
  		if(rotacion=='S')nodeb -> yaw(Ogre::Degree(90));
  		if(rotacion=='D')nodeb -> yaw(Ogre::Degree(180));
  		nuevonum=0;
  		if (rotacion=='W'){
  			_barcos-> push_back(*bar);
  			_casillas[d][u].getSN()->addChild(nodeb);
  			nuevonum = id;
			for (int i = 0; i < tipobar; ++i){
				int d = (nuevonum/10)%10;
  				int u = nuevonum%10;

  				cout << d << endl;
  				cout << u << endl;

  				bar->addCasilla(nuevonum);
				_casillas[d][u].setBarco(bar);

				nuevonum = nuevonum -10;
			}
  		}	
  		if (rotacion=='D'){
  			_barcos-> push_back(*bar);
  			_casillas[d][u].getSN()->addChild(nodeb);
  			nuevonum = id;
			for (int i = 0; i < tipobar; ++i){
				int d = (nuevonum/10)%10;
  				int u = nuevonum%10;
					
  				cout << d << endl;
  				cout << u << endl;

  				bar->addCasilla(nuevonum);
				_casillas[d][u].setBarco(bar);
				nuevonum = nuevonum +1;
			}
  		}
  		if (rotacion=='S'){
  			_barcos-> push_back(*bar);
  			_casillas[d][u].getSN()->addChild(nodeb);
  			nuevonum = id;
			for (int i = 0; i < tipobar; ++i){
				int d = (nuevonum/10)%10;
  				int u = nuevonum%10;

  				cout << d << endl;
  				cout << u << endl;

  				bar->addCasilla(nuevonum);
				_casillas[d][u].setBarco(bar);
				nuevonum = nuevonum +10;
			}
  		}	
  		if (rotacion=='A'){
  			_barcos-> push_back(*bar);
  			_casillas[d][u].getSN()->addChild(nodeb);
  			nuevonum = id;
			for (int i = 0; i < tipobar; ++i){
				int d = (nuevonum/10)%10;
  				int u = nuevonum%10;
				
				cout << d << endl;
  				cout << u << endl;
  				bar->addCasilla(nuevonum);
				_casillas[d][u].setBarco(bar);
				nuevonum = nuevonum -1;
			}
  		}	
  	}
  
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
		if(meterbarco){
			if(vdir[dir]==-10*(tipo-1)){		
				if((d-(tipo-1)) < 0)meterbarco=false;
			}
			if(vdir[dir]==10*(tipo-1)){
				if((d+(tipo-1)) > 9)meterbarco=false;			
			}
			if(vdir[dir]==-1*(tipo-1)){
				if((u-(tipo-1)) < 0)meterbarco=false;		
			}
			if(vdir[dir]==1*(tipo-1)){
				if((u+(tipo-1)) > 9)meterbarco=false; 
			}
		}	
		if (meterbarco){
			Ogre::Entity* entab= _sceneManager->createEntity("Barco.mesh");
  			if (tipo==2 || tipo ==3){
  				Ogre::Entity* entab = _sceneManager->createEntity("Barco.mesh");
  			}else{
  				Ogre::Entity* entab = _sceneManager->createEntity("BarcoP2B.mesh");
  			}
  			ostringstream osA;
  			int d = (vposlugares[0]/10)%10;
			int u = vposlugares[0]%10;
  			osA << tipo << _casillas[d][u].getSN()->getName();
  			cout << osA.str() << "...Creado" <<endl;
  			Ogre::SceneNode* nodeb = _sceneManager->createSceneNode(osA.str());
  			nodeb->attachObject(entab);
  			entab-> setMaterialName("Materialbarco");
  			_casillas[d][u].getSN()-> addChild(nodeb);

  			if(tipo==2)nodeb-> scale(0.4,0.4,0.35);
  			else if(tipo==3)nodeb-> scale(0.55,0.55,0.45);
  			else if(tipo==4)nodeb-> scale(0.75,0.75,0.50);
  			else if(tipo==5)nodeb-> scale(0.95,0.95,0.55);
  			nodeb-> setPosition(0,2.7,0);
  			if(vdir[dir]==10*(tipo-1))nodeb -> yaw(Ogre::Degree(90));
  			else if(vdir[dir]==-10*(tipo-1))nodeb -> yaw(Ogre::Degree(-90));
  			else if(vdir[dir]==1*(tipo-1))nodeb -> yaw(Ogre::Degree(180));
  			
  			Barco *bm = new Barco(tipo,nodeb);
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


void Tablero::colocarbarco(int ship_type, std::vector<int> *v){ 
	//int ship_type = 5; //5,4,3,3,2
	//std::vector<int> *v = new std::vector<int>; //casillas que ya tienen barco
	vector<int>::iterator it;
	//bool primer3 = true; //es el primer barco de tipo 3 que se introduce
	srand(time(NULL));

	int num = 0;
	int num_tens = (num/10)%10;
	int num_units = num%10;

	std::vector<int> cas_up; //casillas del barco posicion arriba
	std::vector<int> cas_right; //casillas del barco posicion derecha
	std::vector<int> cas_down; //casillas del barco posicion abajo 
	std::vector<int> cas_left; //casillas del barco posicion izquierda

	bool up = false;
	bool right = false;
	bool down = false;
	bool left = false;
	bool put = false;

	int comp_up = 0;
	int comp_down = 0;
	int comp_left = 0;
	int comp_right = 0;


	//for(int i=ship_type; i>1; i--){

		//up = false;
	    //right = false;
		//down = false;
		//left = false;

		/*if(i ==3 && primer){
			primer = false;
		}*/
	while(!put){
		num =rand()%(100);
		num_tens = (num/10)%10;
		num_units = num%10;

		cout << "size: " << ship_type << endl;
		cout << "NUM: " << num << endl;
		cout << "tens: " << num_tens << endl;
		cout << "units: " << num_units << endl;

		//if(_casillas[num_tens][num_units].getBarco() == NULL){
		if(!(std::find(v->begin(), v->end(), num) != v->end())){
			//Si la casilla no tiene barco, podemos empezar 

			comp_up = num_tens + (ship_type - 1);
			comp_down = num_tens - (ship_type - 1);
			comp_left = num_units - (ship_type - 1);
			comp_right = num_units + (ship_type - 1);

			cout << "comp_up: " << comp_up << endl;
			cout << "comp_down: " << comp_down << endl;
			cout << "comp_left: " << comp_left << endl;
			cout << "comp_right: " << comp_right << endl;


			/*Metemos la casilla elegida en los vectores de casillas de las 4 direcciones
			cas_down.push_back(_casillas[num_tens][num_units].getId());
			cas_up.push_back(_casillas[num_tens][num_units].getId());
			cas_left.push_back(_casillas[num_tens][num_units].getId());
			cas_right.push_back(_casillas[num_tens][num_units].getId());*/

			int iden = 0;
			int n = 0;
			if(comp_up < 9){
				//De momento, para arriba se puede
				//Comprobamos que no haya barco en las casillas de arriba
				n = num;
				cout << "primer if: Arriba " << endl;

				for(int i=num_tens; i<=comp_up; i++){

					//iden = _casillas[i][num_units].getId();
					iden = n;
					//if(_casillas[i][num_units].getBarco() == NULL)
					if(!(std::find(v->begin(), v->end(), n) != v->end())){
						cas_up.push_back(iden);
						cout << " ID CASILLA: " << iden << endl;
						n = n + 10;
					}
					else{
						up = false;
						cas_up.clear();
						break;
					}	
					up = true;
				}
				
			}
			 
			else if(comp_down > 0){
				n = num;
				//De momento, para abajo se puede
				//Comprobamos que no haya barco en las casillas de abajo

				cout << "segundo if: Abajo " << endl;

				for(int i=num_tens; i>=comp_down; i--){
					//iden = _casillas[i][num_units].getId();
					iden = n;
					//if(_casillas[i][num_units].getBarco() == NULL)
					if(!(std::find(v->begin(), v->end(), n) != v->end())){
						cas_down.push_back(iden);
						cout << " ID CASILLA: " << iden << endl;
						n = n - 10;
					}
					else{
						down = false;
						cas_down.clear();
						break;
					}
					down = true;	
				}

			}
			
			else if(comp_left > 0){
				n = num;
				//De momento, a la izquierda se puede
				//Comprobamos que no haya barco en las casillas de la izquierda

				cout << "tercer if: Izquierda " << endl;

				for(int i=num_units; i<=comp_left; i--){
					//iden = _casillas[num_tens][i].getId();
					iden = n;
					//if(_casillas[num_tens][i].getBarco() == NULL)
					if(!(std::find(v->begin(), v->end(), n) != v->end())){
						cas_left.push_back(iden);
						cout << " ID CASILLA: " << iden << endl;
						n = n - 1;
					}
					else{
						left = false;
						cas_left.clear();
						break;
					}
					left = true;	
				}
			}
			
			else if(comp_right < 9){
				n = num;
				//De momento, a la derecha se puede
				//Comprobamos que no haya barco en las casillas de la derecha
				
				cout << "cuarto if: Derecha " << endl;

				for(int i=num_units; i>=comp_right; i++){
					//iden = _casillas[num_tens][i].getId();
					iden = n;
					//if(_casillas[num_tens][i].getBarco() == NULL)
					if(!(std::find(v->begin(), v->end(), n) != v->end())){
						cas_right.push_back(iden);
						cout << " ID CASILLA: " << iden << endl;
						n = n + 1;
					}
					else{
						right = false;
						cas_right.clear();
						break;
					}
					right = true;	
				}
			}

			if(up || right || down || left){
				Barco *bm = new Barco(ship_type);
				_barcos->push_back(*bm);

				int t = num_tens;
				int u = num_units;
			
				n = num;
				cout << "up: " << up << endl;
				cout << "down: " << down << endl;
				cout << "left: " << left << endl;
				cout << "right: " << right << endl;	

				for (int i = 0; i < ship_type; ++i){
					_casillas[t][u].setBarco(bm);
					//cout << _casillas[t][u].getId()<< "J  " << ship_type <<endl;
					cout << t << u << "J  " << ship_type <<endl;
					/*cout << _casillas[t-1][u].getId()<< "J  " << ship_type <<endl;
					cout << _casillas[t-2][u].getId()<< "J  " << ship_type <<endl;
					cout << _casillas[t-3][u].getId()<< "J  " << ship_type <<endl;
					cout << _casillas[t-4][u].getId()<< "J  " << ship_type <<endl;
					*/
					
					v->push_back(n);

					cout << " t: "<< t << " u: " << u << endl;

					//cout << "Meter "<< n << "J  " << ship_type <<endl;

					if(up){
						bm->addCasilla(cas_up[i]);
						cout << "Metido "<< cas_up[i] << "J  " << ship_type <<endl;
						t = t +1;
						n = n +10;
					}
					
					else if(right){
						bm->addCasilla(cas_right[i]);
						cout << "Metido "<< cas_right[i] << "J  " << ship_type <<endl;
						u = u + 1;
						n = n +1;
					}
					
					else if(down){
						bm->addCasilla(cas_down[i]);
						cout << "Metido "<< cas_down[i] << "J  " << ship_type <<endl;
						t = t - 1;
						n = n -10;
					}
					
					else if(left){
						bm->addCasilla(cas_left[i]);	
						cout << "Metido "<< cas_left[i] << "J  " << ship_type <<endl;
						u = u - 1;
						n = n -1;
					}		

				}

				std::vector<int> *cas_bar;

				cas_bar = bm->getIdCasillas();
			

				cout << "lista de casillas del barco "<< ship_type << endl;
				for(int j=0;j<ship_type;j++){
					cout << cas_bar->at(j) << endl;
				}
				put = true;
			}
			
		}

		else{
			put = false;
		}
		
	}		
		
		
}




void Tablero::colocarbarcoSeguridad(int ship_type, std::vector<int> *v){ 
	//int ship_type = 5; //5,4,3,3,2
	//std::vector<int> *v = new std::vector<int>; //casillas que ya tienen barco
	vector<int>::iterator it;
	//bool primer3 = true; //es el primer barco de tipo 3 que se introduce
	srand(time(NULL));

	int num = 0;
	int num_tens = (num/10)%10;
	int num_units = num%10;

	std::vector<int> cas_up; //casillas del barco posicion arriba
	std::vector<int> cas_right; //casillas del barco posicion derecha
	std::vector<int> cas_down; //casillas del barco posicion abajo 
	std::vector<int> cas_left; //casillas del barco posicion izquierda

	bool up = false;
	bool right = false;
	bool down = false;
	bool left = false;
	bool put = false;

	int comp_up = 0;
	int comp_down = 0;
	int comp_left = 0;
	int comp_right = 0;


	//for(int i=ship_type; i>1; i--){

		//up = false;
	    //right = false;
		//down = false;
		//left = false;

		/*if(i ==3 && primer){
			primer = false;
		}*/
	while(!put){
		num =rand()%(100);
		num_tens = (num/10)%10;
		num_units = num%10;

		cout << "size: " << ship_type << endl;
		cout << "NUM: " << num << endl;
		cout << "tens: " << num_tens << endl;
		cout << "units: " << num_units << endl;

		//if(_casillas[num_tens][num_units].getBarco() == NULL){
		if(!(std::find(v->begin(), v->end(), num) != v->end())){
			//Si la casilla no tiene barco, podemos empezar 

			comp_up = num_tens + (ship_type - 1);
			comp_down = num_tens - (ship_type - 1);
			comp_left = num_units - (ship_type - 1);
			comp_right = num_units + (ship_type - 1);

			cout << "comp_up: " << comp_up << endl;
			cout << "comp_down: " << comp_down << endl;
			cout << "comp_left: " << comp_left << endl;
			cout << "comp_right: " << comp_right << endl;


			/*Metemos la casilla elegida en los vectores de casillas de las 4 direcciones
			cas_down.push_back(_casillas[num_tens][num_units].getId());
			cas_up.push_back(_casillas[num_tens][num_units].getId());
			cas_left.push_back(_casillas[num_tens][num_units].getId());
			cas_right.push_back(_casillas[num_tens][num_units].getId());*/

			int iden = 0;
			int n = 0;
			if(comp_up < 9){
				//De momento, para arriba se puede
				//Comprobamos que no haya barco en las casillas de arriba
				n = num;
				cout << "primer if: Arriba " << endl;

				for(int i=num_tens; i<=comp_up; i++){

					//iden = _casillas[i][num_units].getId();
					iden = n;
					//if(_casillas[i][num_units].getBarco() == NULL)
					if(!(std::find(v->begin(), v->end(), n) != v->end())){
						cas_up.push_back(iden);
						cout << " ID CASILLA: " << iden << endl;
						n = n + 10;
					}
					else{
						up = false;
						cas_up.clear();
						break;
					}	
					up = true;
				}
				
			}
			 
			else if(comp_down > 0){
				n = num;
				//De momento, para abajo se puede
				//Comprobamos que no haya barco en las casillas de abajo

				cout << "segundo if: Abajo " << endl;

				for(int i=num_tens; i>=comp_down; i--){
					//iden = _casillas[i][num_units].getId();
					iden = n;
					//if(_casillas[i][num_units].getBarco() == NULL)
					if(!(std::find(v->begin(), v->end(), n) != v->end())){
						cas_down.push_back(iden);
						cout << " ID CASILLA: " << iden << endl;
						n = n - 10;
					}
					else{
						down = false;
						cas_down.clear();
						break;
					}
					down = true;	
				}

			}
			
			else if(comp_left > 0){
				n = num;
				//De momento, a la izquierda se puede
				//Comprobamos que no haya barco en las casillas de la izquierda

				cout << "tercer if: Izquierda " << endl;

				for(int i=num_units; i<=comp_left; i--){
					//iden = _casillas[num_tens][i].getId();
					iden = n;
					//if(_casillas[num_tens][i].getBarco() == NULL)
					if(!(std::find(v->begin(), v->end(), n) != v->end())){
						cas_left.push_back(iden);
						cout << " ID CASILLA: " << iden << endl;
						n = n - 1;
					}
					else{
						left = false;
						cas_left.clear();
						break;
					}
					left = true;	
				}
			}
			
			else if(comp_right < 9){
				n = num;
				//De momento, a la derecha se puede
				//Comprobamos que no haya barco en las casillas de la derecha
				
				cout << "cuarto if: Derecha " << endl;

				for(int i=num_units; i>=comp_right; i++){
					//iden = _casillas[num_tens][i].getId();
					iden = n;
					//if(_casillas[num_tens][i].getBarco() == NULL)
					if(!(std::find(v->begin(), v->end(), n) != v->end())){
						cas_right.push_back(iden);
						cout << " ID CASILLA: " << iden << endl;
						n = n + 1;
					}
					else{
						right = false;
						cas_right.clear();
						break;
					}
					right = true;	
				}
			}

			if(up || right || down || left){
				Barco *bm = new Barco(ship_type);
				_barcos->push_back(*bm);

				int t = num_tens;
				int u = num_units;
			
				n = num;
				cout << "up: " << up << endl;
				cout << "down: " << down << endl;
				cout << "left: " << left << endl;
				cout << "right: " << right << endl;	

				for (int i = 0; i < ship_type; ++i){
					_casillas[t][u].setBarco(bm);
					//cout << _casillas[t][u].getId()<< "J  " << ship_type <<endl;
					cout << t << u << "J  " << ship_type <<endl;
					/*cout << _casillas[t-1][u].getId()<< "J  " << ship_type <<endl;
					cout << _casillas[t-2][u].getId()<< "J  " << ship_type <<endl;
					cout << _casillas[t-3][u].getId()<< "J  " << ship_type <<endl;
					cout << _casillas[t-4][u].getId()<< "J  " << ship_type <<endl;
					*/
					
					v->push_back(n);

					cout << " t: "<< t << " u: " << u << endl;

					//cout << "Meter "<< n << "J  " << ship_type <<endl;

					if(up){
						bm->addCasilla(cas_up[i]);
						cout << "Metido "<< cas_up[i] << "J  " << ship_type <<endl;
						
						//Meto tambien como "con barco" la zona de seguridad
						if(u >0)
							v->push_back(n-1);
						if(u <9)
							v->push_back(n+1);
						if(t >0)
							v->push_back(n-10);
						
						//Poner zona de seguridad arriba del barco tambien
						if(i == ship_type -1)
							if(t < 9)
								v->push_back(n+10);
							if(u >0)
								v->push_back(n+9);
							if(u <9)
								v->push_back(n+11);

						//Poner zona de seguridad en las diagonales abajo del barco tambien
						if(i == 0)
							if(u >0)
							v->push_back(n-11);
							if(u <9)
								v->push_back(n-9);

						t = t +1;
						n = n +10;
	
					}
					
					else if(right){
						bm->addCasilla(cas_right[i]);
						cout << "Metido "<< cas_right[i] << "J  " << ship_type <<endl;
						
						//Meto tambien como "con barco" la zona de seguridad
						if(u >0)
							v->push_back(n-1);
						if(t >0)
							v->push_back(n-10);
						if(t <9)
							v->push_back(n+10);
						if(i == ship_type -1)
							if(u < 9)
								v->push_back(n+1);


						u = u + 1;
						n = n +1;

						
					}
					
					else if(down){
						bm->addCasilla(cas_down[i]);
						cout << "Metido "<< cas_down[i] << "J  " << ship_type <<endl;
						
						//Meto tambien como "con barco" la zona de seguridad
						if(u >0)
							v->push_back(n-1);
						if(u <9)
							v->push_back(n+1);
						if(t <9)
							v->push_back(n+10);
						if(i == ship_type -1)
							if(t > 0)
								v->push_back(n-10);


						t = t - 1;
						n = n -10;

						
					}
					
					else if(left){
						bm->addCasilla(cas_left[i]);	
						cout << "Metido "<< cas_left[i] << "J  " << ship_type <<endl;
						
						//Meto tambien como "con barco" la zona de seguridad
						if(u <9)
							v->push_back(n+1);
						if(t >0)
							v->push_back(n-10);
						if(t <9)
							v->push_back(n+10);
						if(i == ship_type -1)
							if(u >0)
								v->push_back(n-1);


						u = u - 1;
						n = n -1;

						
					}		

				}

				std::vector<int> *cas_bar;

				cas_bar = bm->getIdCasillas();
			

				cout << "lista de casillas del barco "<< ship_type << endl;
				for(int j=0;j<ship_type;j++){
					cout << cas_bar->at(j) << endl;
				}
				put = true;
			}
			
		}

		else{
			put = false;
		}
		
	}		
		
		
}

int Tablero::barcoshundidos(){
	vector<Barco>::iterator it;
	int res=0;
	for (it = _barcos->begin(); it != _barcos->end();++it){
 		if (it->getDamage()==it->getTipo()){
			res ++;
		}
	}
	return res;
}

// void Tablero::colocarbarcos(int tipo, std::vector<int> *v){

// 	srand(time(NULL));
// 	int vdir[4] = {-1*(tipo-1),1*(tipo-1),10*(tipo-1),-10*(tipo-1)};
// 	vector<int>::iterator it;
// 	bool meterbarco=true;
// 	bool salir = true;
// 	while(salir){
// 		int vposlugares[tipo];
// 		int num;
// 		num =rand()%(100);
// 		int dir;
// 		dir =rand()%(4);
// 		int d = (num/10)%10;
// 		int u = num%10;
// 		meterbarco=true;
// 		if (vdir[dir]==-1*(tipo-1)){
// 			int nuevonum = num;
// 			for (int i = 0; i < tipo; ++i){
// 				vposlugares[i] = nuevonum;
// 				nuevonum = nuevonum -1;
// 			}
// 		}	
// 		if (vdir[dir]==1*(tipo-1)){
// 			int nuevonum = num;
// 			for (int i = 0; i < tipo; ++i){
// 				vposlugares[i] = nuevonum;
// 				nuevonum = nuevonum +1;
// 			}
// 		}
// 		if (vdir[dir]==-10*(tipo-1)){
// 			int nuevonum = num;
// 			for (int i = 0; i < tipo; ++i){
// 				vposlugares[i] = nuevonum;
// 				nuevonum = nuevonum -10;
// 			}
// 		}
// 		if (vdir[dir]==10*(tipo-1)){
// 			int nuevonum = num;
// 			for (int i = 0; i < tipo; ++i){
// 				vposlugares[i] = nuevonum;
// 				nuevonum = nuevonum +10;
// 			}
// 		}
// 		for (int i = 0; i < tipo; ++i){
// 			for (it = v->begin(); it != v->end();++it){
// 				if (*it==vposlugares[i]){
// 					meterbarco=false;
// 				}
// 			}
// 		}
// 		if(meterbarco){
// 			if(vdir[dir]==-10*(tipo-1)){		
// 				if((d-(tipo-1)) < 0)meterbarco=false;
// 			}
// 			if(vdir[dir]==10*(tipo-1)){
// 				if((d+(tipo-1)) > 9)meterbarco=false;			
// 			}
// 			if(vdir[dir]==-1*(tipo-1)){
// 				if((u-(tipo-1)) < 0)meterbarco=false;		
// 			}
// 			if(vdir[dir]==1*(tipo-1)){
// 				if((u+(tipo-1)) > 9)meterbarco=false; 
// 			}
// 		}	
// 		if (meterbarco){
// 			Barco *bm = new Barco(tipo);
// 			_barcos->push_back(*bm);
// 			for (int i = 0; i < tipo; ++i){
// 				int nummeter = vposlugares[i];
// 				int d = (nummeter/10)%10;
// 				int u = nummeter%10;
// 				_casillas[d][u].setBarco(bm);
// 				cout << _casillas[d][u].getId()<< "J  " << tipo <<endl;
// 				bm->addCasilla(nummeter);
// 				v->push_back(nummeter);
// 			}
			
// 			salir = false;
// 		}
// 		srand(time(NULL));	
	
// 	}
// }
