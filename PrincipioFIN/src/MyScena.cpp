//MyScena.cpp
#include "MyScena.h"
#include "Casilla.h"
MyScena::MyScena(Ogre::SceneNode* nA,Ogre::SceneNode* nB,Ogre::SceneManager* sm){
	_nodoalto = nA;
	_nodobajo = nB;
	_sceneManager = sm; 

}

MyScena::~MyScena(){}

void MyScena::creartablero(){
  _nodobajo-> scale(2.5,2.5,2.5);
  //node1Bajo -> setPosition(-45,0,55);
  _nodobajo -> setPosition(-53,23,55);
  _nodobajo -> yaw(Ogre::Degree(2.4));
  _nodobajo -> pitch(Ogre::Degree(45));
  
  _nodoalto->  scale(2.5,2.5,2.5);
  //node1Alto -> setPosition(-47,6,-2);
  _nodoalto -> setPosition(3.2,24,55);
  _nodoalto -> yaw(Ogre::Degree(2.4));
  _nodoalto -> pitch(Ogre::Degree(45));
 
  //node1Alto -> roll(Ogre::Degree(45));
  // add two lights
  Ogre::Light* light1 = _sceneManager->createLight();
  light1->setType(Ogre::Light::LT_POINT);
  light1->setPosition(-10, 100, 100);
  light1->setSpecularColour(Ogre::ColourValue::White);
  _nodobajo->attachObject(light1);

  Ogre::Light* light2 = _sceneManager->createLight();
  light2->setType(Ogre::Light::LT_POINT);
  light2->setPosition(10, -100, -100);
  light2->setSpecularColour(Ogre::ColourValue::White);
  _nodobajo->attachObject(light2);
  // Comprobar despues estas luces

  //CREACION DE LOS TABLEROS (BAJO)
  int crearTableroBajo = 0;
  int crearTableroAlto = 0;
  char nombres[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i','j'};
  int despL[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20}; 
  int despV[10] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18}; 
  while (crearTableroBajo != 10){
    for (int i = 0; i < 10; ++i){
      ostringstream os;
      os << "Node" << (i+1) << nombres[crearTableroBajo];
      cout << os.str() << "...Creado" <<endl;
      Ogre::Entity* ent = _sceneManager->createEntity(os.str(), "Cube.mesh");
      Ogre::SceneNode* node = _sceneManager->createSceneNode(os.str());
      Casilla *cas = new Casilla(node);
      node-> attachObject(ent);
      //_nodebajo -> addChild(node);
      node -> setPosition(despL[i],0,-(despV[crearTableroBajo]));
      _nodobajo -> addChild(node);
    }
    crearTableroBajo++;    
  }
  char nombresA[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  //TABLERO ALTO
  while (crearTableroAlto != 10){
    for (int b = 0; b < 10; ++b){
      ostringstream osA;
      osA << "Node" << (b+1) << nombresA[crearTableroAlto];
      cout << osA.str() << "...Creado" <<endl;
      Ogre::Entity* enta = _sceneManager->createEntity(osA.str(), "Cube.mesh");
      Ogre::SceneNode* nodea = _sceneManager->createSceneNode(osA.str());
      Casilla *casb = new Casilla(nodea);
      nodea-> attachObject(enta);
      //_nodealto -> addChild(nodea);
      nodea -> setPosition(despL[b],0,-(despV[crearTableroAlto]));
      _nodoalto -> addChild(nodea);	
    }
    crearTableroAlto++;    
  }
  
  Ogre::Plane plane1(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("plane1",
  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane1,
  200,200,1,1,true,1,20,20,Ogre::Vector3::UNIT_Z);

  Ogre::SceneNode* node3 = _sceneManager->createSceneNode("ground");
  Ogre::Entity* groundEnt = _sceneManager->createEntity("planeEnt", "plane1");
  groundEnt->setMaterialName("Suelo");
  node3->attachObject(groundEnt);
  node3 -> setPosition(3.2,24,50);;
  node3 -> yaw(Ogre::Degree(2.4));
  node3 -> pitch(Ogre::Degree(45));
  _sceneManager->getRootSceneNode()->addChild(node3);

  Ogre::Entity* entab = _sceneManager->createEntity("Barco.mesh");
  Ogre::SceneNode* nodeb = _sceneManager->createSceneNode("barquito");
  entab->setMaterialName("Materialbarco");
  nodeb->attachObject(entab);
  nodeb-> scale(0.4,0.4,0.4);
  nodeb -> setPosition(-34,50,55);
  nodeb -> yaw(Ogre::Degree(2.4));
  nodeb -> pitch(Ogre::Degree(45));
  _sceneManager->getRootSceneNode()->addChild(nodeb);

}