
//Tablero.cpp
#include "Tablero.h"

Tablero::Tablero(char tipo, Ogre::SceneManager* sm){
	_tipo = tipo;
	_casillas = new Casilla*[DIM];
	_maquinapartida = new int*[DIM];
	for(int i = 0; i < DIM; ++i) {
    	_casillas[i] = new Casilla[DIM];
    	_maquinapartida[i] =  new int[DIM]; 
	}
	for (int h = 0; h < 10; ++h){
		for (int n = 0; n < 10; ++n){
			_maquinapartida[h][n] = 5;	
		}
	}
	_vpartida = new std::vector<int>;
	_barcos = new std::vector<Barco>;
	_sceneManager = sm;

}

Tablero::~Tablero(){
	for(int i = 0; i < DIM; ++i) {
    	delete [] _casillas[i];
		delete [] _maquinapartida[i];
	}
	delete [] _casillas;
	delete [] _maquinapartida;

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

bool Tablero::colocarbarcosJUGADOR(int id, int tipobar, char rotacion){
  bool metido = false;
  int d = (id/10)%10;
  int u = id%10;
  Ogre::Entity* entab= _sceneManager->createEntity("Barco.mesh");
  // if (tipobar==2 || tipobar ==3 ){
  // 	 entab = _sceneManager->createEntity("Barco.mesh");
  // }else{
  // 	 entab = _sceneManager->createEntity("BarcoP2B.mesh");
  // }
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
  		metido = true;
  		ostringstream osA;
  		osA <<"BAR"<< tipobar << _casillas[d][u].getSN()->getName();
  		cout << osA.str() << "...Creado" <<endl;
  		Ogre::SceneNode* nodeb = _sceneManager->createSceneNode(osA.str());
  		entab->setMaterialName("Materialbarco");
  		Barco *bar = new Barco(tipobar,nodeb);
  		nodeb->attachObject(entab);
  		if(tipobar==2)nodeb-> scale(0.4,0.4,0.35);
  		if(tipobar==3)nodeb-> scale(0.55,0.55,0.45);
  		if(tipobar==4)nodeb-> scale(0.75,0.75,0.50);
  		if(tipobar==5)nodeb-> scale(0.95,0.95,0.55);
  		nodeb-> setPosition(0.5,2.5,0.0);
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

  				cout << d<<u << endl;

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
					
  				cout << d<<u << endl;

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

  				cout << d<<u << endl;;

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
				
				cout << d<<u << endl;
  				
  				bar->addCasilla(nuevonum);
				_casillas[d][u].setBarco(bar);
				nuevonum = nuevonum -1;
			}
  		}	
  	}
  return metido;
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
				mEntity= static_cast<Ogre::Entity *>(_casillas[d][u].getSN()->getAttachedObject(0));
				mEntity->setMaterialName("MaterialRojo");
				it->setDamage(it->getDamage()+1);	
				if (it->getTipo()> it->getDamage()){
					Ogre::Entity * mEntitybarco;
					mEntitybarco= static_cast<Ogre::Entity *>(it->getSN()->getAttachedObject(0));
					mEntitybarco->setMaterialName("MaterialNaranja");
				} else if(it->getTipo() <= it->getDamage()){
					Ogre::Entity * mEntitybarco;
					mEntitybarco= static_cast<Ogre::Entity *>(it->getSN()->getAttachedObject(0));
					mEntitybarco->setMaterialName("MaterialRojo");
				}	
			}
		}	
	}	
}


void Tablero::colocarbarcoQ(int ship_type, std::vector<int> *v){ 
	
	vector<int>::iterator it;
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

	int choice = 0;
	
	while(!put){
		num =rand()%(100);
		num_tens = (num/10)%10;
		num_units = num%10;

		cout << "size: " << ship_type << endl;
		cout << "NUM: " << num << endl;
		cout << "tens: " << num_tens << endl;
		cout << "units: " << num_units << endl;

		if(!(std::find(v->begin(), v->end(), num) != v->end())){
			//Si la casilla no tiene barco, podemos empezar 

			comp_down = num_tens + (ship_type - 1);
			comp_up = num_tens - (ship_type - 1);
			comp_left = num_units - (ship_type - 1);
			comp_right = num_units + (ship_type - 1);

			cout << "comp_up: " << comp_up << endl;
			cout << "comp_down: " << comp_down << endl;
			cout << "comp_left: " << comp_left << endl;
			cout << "comp_right: " << comp_right << endl;

			if((comp_up >= 0 || comp_down <= 9)&&(comp_left >= 0 || comp_right <= 9)){ //si se puede en vertical y en horizontal
				choice = rand()%(2);	
				cout << "se puede en los 2. Choice es: "<<choice<<endl;
			}
			else if(comp_up >= 0 || comp_down <= 9){ //si se puede solo en vertical
				choice = 0;
			}
			else if(comp_left >= 0 || comp_right <= 9){ //si se puede solo en horizontal
				choice = 1;
			}
			
			cout << "CHOICE: "<<choice<<endl;

			int iden = 0;
			int n = 0;
			if(comp_up >= 0 && choice==0){
				//De momento, para arriba se puede
				//Comprobamos que no haya barco en las casillas de arriba
				n = num;
				cout << "primer if: Arriba " << endl;

				for(int i=num_tens; i<=comp_up; i--){
					iden = n;
					if(!(std::find(v->begin(), v->end(), n) != v->end())){
						cas_up.push_back(iden);
						cout << " ID CASILLA: " << iden << endl;
						n = n - 10;
					}
					else{
						up = false;
						cas_up.clear();
						break;
					}	
					up = true;
				}
				
			}
			 
			if(comp_down <= 9 && choice==0){
				n = num;
				//De momento, para abajo se puede
				//Comprobamos que no haya barco en las casillas de abajo

				cout << "segundo if: Abajo " << endl;

				for(int i=num_tens; i<=comp_down; i++){
					iden = n;
					if(!(std::find(v->begin(), v->end(), n) != v->end())){
						cas_down.push_back(iden);
						cout << " ID CASILLA: " << iden << endl;
						n = n + 10;
					}
					else{
						down = false;
						cas_down.clear();
						break;
					}
					down = true;	
				}

			}
			
			if(comp_left >= 0 &&choice==1){
				n = num;
				//De momento, a la izquierda se puede
				//Comprobamos que no haya barco en las casillas de la izquierda

				cout << "tercer if: Izquierda " << endl;

				for(int i=num_units; i>=comp_left; i--){
					
					iden = n;
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
			
			if(comp_right <= 9 && choice==1){
				n = num;
				//De momento, a la derecha se puede
				//Comprobamos que no haya barco en las casillas de la derecha
				
				cout << "cuarto if: Derecha " << endl;

				for(int i=num_units; i<=comp_right; i++){
					iden = n;
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
			cout<<"u: "<<up<<" r: "<<right<<" d: "<<down<<" l: "<<left<<endl;

			if(up || right || down || left){
				cout<<"En algun lado se puede poner-> u: "<<up<<" r: "<<right<<" d: "<<down<<" l: "<<left<<endl;

				int t = num_tens;
				int u = num_units;
			
				n = num;
				
				Ogre::Entity* entab= _sceneManager->createEntity("Barco.mesh");
 				
 				//if (ship_type==2 || ship_type ==3){
  				//	 entab = _sceneManager->createEntity("Barco.mesh");
  				// }
  				// else{
  				// 	 entab = _sceneManager->createEntity("BarcoP2B.mesh");
  				// }


  				ostringstream osA;
  				osA <<"BAR"<< ship_type << _casillas[t][u].getSN()->getName();
  				cout << osA.str() << "...Creado" <<endl;
  				Ogre::SceneNode* nodeb = _sceneManager->createSceneNode(osA.str());
  				entab->setMaterialName("MaterialRojo");
  				entab->setVisible(true);
  				nodeb->attachObject(entab);
  				nodeb -> setVisible(false);
  				Barco *bm = new Barco(ship_type, nodeb);
  				_casillas[t][u].getSN()-> addChild(nodeb);
  		
  				if(ship_type==2)nodeb-> scale(0.4,0.4,0.35);
		  		if(ship_type==3)nodeb-> scale(0.55,0.55,0.45);
		  		if(ship_type==4)nodeb-> scale(0.75,0.75,0.50);
		  		if(ship_type==5)nodeb-> scale(0.95,0.95,0.55);
		  		nodeb-> setPosition(-0.15,2.7,0);
				if(down)nodeb -> yaw(Ogre::Degree(90));
  				else if(up)nodeb -> yaw(Ogre::Degree(-90));
  				else if(right)nodeb -> yaw(Ogre::Degree(180));
  				else if(left) nodeb-> setPosition(-0.3,2.7,0); 
				_barcos->push_back(*bm);

				
				cout << "up: " << up << endl;
				cout << "down: " << down << endl;
				cout << "left: " << left << endl;
				cout << "right: " << right << endl;	


				for (int i = 0; i < ship_type; ++i){
					_casillas[t][u].setBarco(bm);
					cout << t << u << "J  " << ship_type <<endl;
					
					v->push_back(n);

					cout << " t: "<< t << " u: " << u << endl;

					if(up && choice ==0){
						bm->addCasilla(cas_up[i]);
						cout << "Metido "<< cas_up[i] << "J  " << ship_type <<endl;
						
						t = t -1;
						n = n -10;
	
					}
					
					else if(right && choice ==1){
						bm->addCasilla(cas_right[i]);
						cout << "Metido "<< cas_right[i] << "J  " << ship_type <<endl;

						u = u + 1;
						n = n +1;

						
					}
					
					else if(down && choice==0){
						bm->addCasilla(cas_down[i]);
						cout << "Metido "<< cas_down[i] << "J  " << ship_type <<endl;
						t = t + 1;
						n = n +10;

						
					}
					
					else if(left && choice==1){
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
				bm->setDamage(0);
				cout << "Damage del barco: " << bm->getDamage() << endl;
				cout << "Entidad del barco: " << bm->getSN()->getAttachedObject(0)->getName()<<endl;
				cout << "SceneNode del barco: " << bm->getSN()->getName()<<endl;
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
			it->getSN()->setVisible(true);
		}
	}
	return res;
}


int Tablero::ataqueinteligente(std::vector<int> *_elegiblesInt){
	srand(time(NULL));
	bool devataque = true;
	int d=0;
	int u=0;
	int ataque = 0;
	while(devataque){
		if (_vpartida->size()> 0){
			ataque = _vpartida->at(0); 
			d = (ataque/10)%10;
			u = ataque%10;
			_vpartida-> erase(_vpartida->begin());
			_maquinapartida[d][u] = 0;
			if (_casillas[d][u].getTienebarco().compare("SB")==0){
				
				if((d -1)>=0){
					if(_maquinapartida[d-1][u]!=0){ //si no ha sido atacada
						_vpartida->push_back(ataque -10); //La metes en el vector de posibles
						_maquinapartida[d-1][u]=0;
					} 			
				}
				if((d +1)<=9){
					if(_maquinapartida[d+1][u]!=0){ //si no ha sido atacada
						_vpartida->push_back(ataque +10); //La metes en el vector de posibles
						_maquinapartida[d+1][u]=0;
					} 		
				}
				if((u -1)>=0){
					if(_maquinapartida[d][u-1]!=0){ //si no ha sido atacada
						_vpartida->push_back(ataque-1); //La metes en el vector de posibles
						_maquinapartida[d][u-1]=0;
					} 
				}
				if((u +1)<=9){
					if(_maquinapartida[d][u+1]!=0){ //si no ha sido atacada
						_vpartida->push_back(ataque+1); //La metes en el vector de posibles
						_maquinapartida[d][u+1]=0;
					} 			
				}
			}
			devataque = false;
		}else{
			bool generarataque = true;
			while(generarataque){
				ataque = _elegiblesInt->at(0); //cojo el primero
				_elegiblesInt->erase(_elegiblesInt->begin());  //lo elimino de elegibles
				d = (ataque/10)%10;
				u = ataque%10;
				if (_maquinapartida[d][u]==5){
					if (_casillas[d][u].getTienebarco().compare("SB")==0){
						_maquinapartida[d][u] = 0;
						
						if((d -1)>=0){
							if(_maquinapartida[d-1][u]!=0){ //si no ha sido atacada
								_vpartida->push_back(ataque -10); //La metes en el vector de posibles
								_maquinapartida[d-1][u]=0;
							} 			
						}
						if((d +1)<=9){
							if(_maquinapartida[d+1][u]!=0){ //si no ha sido atacada
								_vpartida->push_back(ataque+10); //La metes en el vector de posibles
								_maquinapartida[d+1][u]=0;
							} 		
						}
						if((u -1)>=0){
							if(_maquinapartida[d][u-1]!=0){ //si no ha sido atacada
								_vpartida->push_back(ataque-1); //La metes en el vector de posibles
								_maquinapartida[d][u-1]=0;
							} 	
						}
						if((u +1)<=9){
							if(_maquinapartida[d][u+1]!=0){ //si no ha sido atacada
								_vpartida->push_back(ataque+1); //La metes en el vector de posibles
								_maquinapartida[d][u+1]=0;
							} 
						}	
					}else{
						_maquinapartida[d][u] = 0;	
					}	
					generarataque = false;
					devataque = false;
				}
			}
		}
	}
	return ataque;	
}
