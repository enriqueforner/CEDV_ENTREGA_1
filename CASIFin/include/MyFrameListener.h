
#ifndef MYFRAMELISTENER_H
#define MYFRAMELISTENER_H

#include <Ogre.h>
#include <OIS.h>
#include <CEGUI.h>
#include <iostream>
#include <sstream>
#include <string>
#include "MyScena.h"
#include "Tablero.h" 
using namespace std;
using namespace Ogre;
//#define STAGE 1 << 0  // Mascara para el escenario
#define MASK1 1 << 0  //Mascara de prueba

class MyFrameListener : public Ogre::FrameListener, OIS::KeyListener, OIS::MouseListener {
private:
  OIS::InputManager* _inputManager;
  OIS::Keyboard* _keyboard;
  OIS::Mouse* _mouse;
  Ogre::Camera* _camera;
  Ogre::SceneNode *_node;
  Ogre::RaySceneQuery *_raySceneQuery;
  RenderWindow* _win;
  Ogre::SceneNode* _selectedNode;

  Tablero *_tabm;
  Tablero *_tabj;
  MyScena *_scena;

  bool keyPressed(const OIS::KeyEvent& evt);
  bool keyReleased(const OIS::KeyEvent& evt);
  bool mouseMoved(const OIS::MouseEvent& evt);
  bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
  bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);

  bool _quit;
  bool _play;
  bool _settings;
  bool _ranking;
  float _timeSinceLastFrame;

  bool _empezarjuego;
  bool _ponerbarco;
  int _currentShip;

  bool _primer3;
  std::vector<int> *_elegiblesInt;

  bool _atacar;
  Ogre::SceneManager *_sceneManager;
  string _estado;
  Ogre::RaySceneQuery* mRayScnQuery;

  CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);
  //Ogre::Ray setRayQuery(int posx, int posy, uint32 mask);
  Ogre::Ray setRayQuery(int posx, int posy, uint32 mask);


public:
  MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, 
		  Tablero *tabj, Tablero *tabm, MyScena *scena, Ogre::SceneManager* sceneManager,string estado, std::vector<int> *elegiblesInt);
  ~MyFrameListener();
  bool frameStarted(const Ogre::FrameEvent& evt);  
  bool quit(const CEGUI::EventArgs &e);
  bool play(const CEGUI::EventArgs &e);
  bool settings(const CEGUI::EventArgs &e);
  bool ranking(const CEGUI::EventArgs &e);
  void derrota();
  void victoria();
  //Ogre::RaySceneQuery *_createRayQuery(Ogre::Ray ray);
};

#endif