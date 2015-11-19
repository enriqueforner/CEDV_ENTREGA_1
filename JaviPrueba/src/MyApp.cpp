/*********************************************************************
 * Módulo 2. Curso de Experto en Desarrollo de Videojuegos
 * Autor: Carlos González Morcillo     Carlos.Gonzalez@uclm.es
 *
 * You can redistribute and/or modify this file under the terms of the
 * GNU General Public License ad published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * and later version. See <http://www.gnu.org/licenses/>.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.  
 *********************************************************************/

#include "MyApp.h"


MyApp::MyApp() {
  _sceneManager = NULL;
  _framelistener = NULL;
}

MyApp::~MyApp() {
}

int MyApp::start() {
  _root = new Ogre::Root();
  
  if(!_root->restoreConfig()) {
    _root->showConfigDialog();
    _root->saveConfig();
  }
  
  Ogre::RenderWindow* window = _root->initialise(true,"Hundir La Flota");
  _sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);
  
  Ogre::Camera* cam = _sceneManager->createCamera("MainCamera");
  cam->setPosition(Ogre::Vector3(5,100,100));
  cam->lookAt(Ogre::Vector3(0,0,0));
  cam->setNearClipDistance(5);
  cam->setFarClipDistance(10000);
  
  Ogre::Viewport* viewport = window->addViewport(cam);
  viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
  double width = viewport->getActualWidth();
  double height = viewport->getActualHeight();
  cam->setAspectRatio(width / height);
  
  
  loadResources();
  createScene();
  
  Ogre::SceneNode *node = _sceneManager->getSceneNode("NodoReyBajo");
  
  _framelistener = new MyFrameListener(window, cam, node);
  _root->addFrameListener(_framelistener);
  
  createGUI();

  _root->startRendering();

  return 0;
}

void MyApp::loadResources() {
  Ogre::ConfigFile cf;
  cf.load("resources.cfg");
  
  Ogre::ConfigFile::SectionIterator sI = cf.getSectionIterator();
  Ogre::String sectionstr, typestr, datastr;
  while (sI.hasMoreElements()) {
    sectionstr = sI.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap *settings = sI.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i) {
      typestr = i->first;    datastr = i->second;
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation
            (datastr, typestr, sectionstr);	
    }
  }
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void MyApp::createScene() {
  Ogre::Entity* ent1 = _sceneManager->createEntity("Cube.mesh");
  Ogre::Entity* ent2 = _sceneManager->createEntity("Cube.mesh");
  Ogre::SceneNode* node1Bajo = _sceneManager->createSceneNode("NodoReyBajo");
  Ogre::SceneNode* node1Alto = _sceneManager->createSceneNode("NodoReyAlto");
  
  node1Bajo->attachObject(ent1);
  node1Alto -> attachObject(ent2);
  _sceneManager->getRootSceneNode()->addChild(node1Bajo);
  _sceneManager->getRootSceneNode()->addChild(node1Alto);

  node1Bajo-> scale(2.8,2.8,2.8);
  node1Bajo -> setPosition(-40,0,55);
  node1Bajo -> yaw(Ogre::Degree(2));
  node1Alto->  scale(2.8,2.8,2.8);
  node1Alto -> setPosition(-42,6,-2);
  node1Alto -> yaw(Ogre::Degree(2));
  
  //node1Alto -> roll(Ogre::Degree(45));
  // add two lights
  Ogre::Light* light1 = _sceneManager->createLight();
  light1->setType(Ogre::Light::LT_POINT);
  light1->setPosition(-10, 100, 100);
  light1->setSpecularColour(Ogre::ColourValue::White);
  node1Bajo->attachObject(light1);

  Ogre::Light* light2 = _sceneManager->createLight();
  light2->setType(Ogre::Light::LT_POINT);
  light2->setPosition(10, -100, -100);
  light2->setSpecularColour(Ogre::ColourValue::White);
  node1Bajo->attachObject(light2);
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
      node-> attachObject(ent);
      node1Bajo -> addChild(node);
      node -> setPosition(despL[i],0,-(despV[crearTableroBajo]));
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
      nodea-> attachObject(enta);
      node1Alto -> addChild(nodea);
      nodea -> setPosition(despL[b],0,-(despV[crearTableroAlto]));
    }
    crearTableroAlto++;    
  }


}

void MyApp::createGUI()
{
  //CEGUI
  renderer = &CEGUI::OgreRenderer::bootstrapSystem();
  CEGUI::Scheme::setDefaultResourceGroup("Schemes");
  CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
  CEGUI::Font::setDefaultResourceGroup("Fonts");
  CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
  //Para los botones
  CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
  //Para el Raton
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  //Para nada de momento
  CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
  
  CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-12");
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("OgreTrayImages/MouseArrow");
  
  //Sheet
  CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","Ex1/Sheet");

  //CEGUI::Window* vent = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MenuInicial.layout");

  //CEGUI::Window* formatWin = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MenuInicial.layout");

  // sheet->addChild(vent);

  // CEGUI::Window* exitButton = vent->getChild("ExitButton");
  // exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
  //         CEGUI::Event::Subscriber(&MyFrameListener::quit, 
  //               _framelistener));

  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

}

void MyApp::createGAME(CEGUI::Window* playButton) {
  printf("Hola estoy en el createGAME\n");
  playButton-> setText("Come");

}