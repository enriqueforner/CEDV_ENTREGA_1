#ifndef MYAPP_H
#define MYAPP_H
#include "Tablero.h"
#include <Ogre.h>
#include "MyFrameListener.h"
#include "MyScena.h"
#include "Casilla.h"
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>
#include <iostream>
#include <sstream>
#include <string> 
#include <vector>

using namespace std;

class MyApp {
  
private:
  Ogre::SceneManager* _sceneManager;
  Ogre::Root* _root;
  CEGUI::OgreRenderer* renderer; 
  MyFrameListener* _framelistener;
 // Ogre::OverlayManager* _overlayManager;
  
public:
  MyApp();
  ~MyApp();  
  int start();
  void loadResources();
  void createScene();
  void createGUI();
  void initUI();
  void createGAME(CEGUI::Window* sheet);
 // void createOverlay();
};

#endif