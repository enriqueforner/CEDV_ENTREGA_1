#ifndef MYFRAMELISTENER_H
#define MYFRAMELISTENER_H

#include <Ogre.h>
#include <OIS.h>
#include <CEGUI.h>
#include <iostream>
#include <sstream>
#include <string> 
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
  Ogre::SceneManager *_sceneManager;

  Ogre::RaySceneQuery* mRayScnQuery;

  CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);
  //Ogre::Ray setRayQuery(int posx, int posy, uint32 mask);
  Ogre::Ray setRayQuery(int posx, int posy, uint32 mask);

public:
  MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, 
		  Ogre::SceneNode* node, Ogre::SceneManager* sceneManager);
  ~MyFrameListener();
  bool frameStarted(const Ogre::FrameEvent& evt);  
  bool quit(const CEGUI::EventArgs &e);
  bool play(const CEGUI::EventArgs &e);
  bool settings(const CEGUI::EventArgs &e);
  bool ranking(const CEGUI::EventArgs &e);

  //Ogre::RaySceneQuery *_createRayQuery(Ogre::Ray ray);
};

#endif