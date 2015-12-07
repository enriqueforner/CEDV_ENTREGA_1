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
  cam->setPosition(Ogre::Vector3(4,100,100));
  cam->lookAt(Ogre::Vector3(0,0,0));
  cam->setNearClipDistance(3);
  cam->setFarClipDistance(10000);
  
  Ogre::Viewport* viewport = window->addViewport(cam);
  viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
  double width = viewport->getActualWidth();
  double height = viewport->getActualHeight();
  cam->setAspectRatio(width / height);
  
  
  loadResources();
  createScene();
  
  Ogre::SceneNode *node = _sceneManager->getSceneNode("NodoReyBajo");
  //Ogre::SceneNode *node2 = _sceneManager->getSceneNode("NodoReyAlto");
 
  _framelistener = new MyFrameListener(window, cam, node,_sceneManager,"INTRO");
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
  Tablero *tabj = new Tablero('J',_sceneManager);
  Tablero *tabm = new Tablero('M',_sceneManager);
  

  Ogre::Entity* ent1 = _sceneManager->createEntity("Cube.mesh");
  Ogre::Entity* ent2 = _sceneManager->createEntity("Cube.mesh");
  Ogre::SceneNode* node1Bajo = _sceneManager->createSceneNode("NodoReyBajo");
  Ogre::SceneNode* node1Alto = _sceneManager->createSceneNode("NodoReyAlto");
  
  node1Bajo->attachObject(ent1);
  node1Alto -> attachObject(ent2);
  _sceneManager->getRootSceneNode()->addChild(node1Bajo);
  _sceneManager->getRootSceneNode()->addChild(node1Alto);
  
  MyScena *escena = new MyScena(node1Bajo,node1Alto,_sceneManager, tabj, tabm);
  escena -> creartablero();
  
  // Casilla** casp = tabj-> getCasillas();

  // cout << casp[6][2].getId() << endl;

  // Tablero *tabpr = new Tablero('P',_sceneManager);
  
  // tabpr -> setCasillas(casp);
  // cout << tabpr -> getCasillas()[6][2].getId() << endl;
  // casp[1][2].setId(8999);  

  // cout << tabpr -> getCasillas()[1][2].getId() << endl;
  // bool repetir = true;
  // std::vector<int> *v = new std::vector<int>;
  // for (int i = 5; i > 1; --i){
  //   tabm->colocarbarcos(i,v);
  //   if (i == 3 && repetir){
  //       i++;
  //       repetir = false;
  //   }
  // }
  
  // std::vector<Barco> *vc = new std::vector<Barco>;
  // vc = tabm -> getBarcos();
  // std::vector<Barco>::iterator it;
  // for (it = vc->begin(); it != vc->end();++it){
  //      //cout << it->getId() << endl;
  // }
  // bool primer = true;
  // for (int i = 0; i <= 100; ++i){
  //   tabm->atacarcasilla(i);
  //   if (i>99 && primer){
  //       i=i-1;
  //       primer = false;
  //   }
  //   else if(i>99 && !primer){
  //     break;
  //   }
  //   int d = (i/10)%10;
  //   int u = i%10;
  //   if(primer){
  //       if(u==0){
  //         cout <<endl;
  //       }
  //       if(tabm->getCasillas()[d][u].getEstado() == "hundida"){
  //         cout << d<<u<<"H ";
  //       }
  //       else if(tabm->getCasillas()[d][u].getEstado() == "agua"){
  //         cout << d<<u<<"A ";
  //       }  
  //   }
  //   else{
  //     cout << endl;
  //   }
  //   //sleep(1);
  // }
  //Ogre::Entity* entab = _sceneManager->createEntity("Barco.mesh");
  Ogre::Entity* entab = _sceneManager->createEntity("Barco.mesh");
  Ogre::SceneNode* nodeb = _sceneManager->createSceneNode("barquitoPRUEBA");
  entab->setMaterialName("Materialbarco");
  nodeb->attachObject(entab);
  tabj-> getCasillas()[0][9].getSN()->addChild(nodeb);

  nodeb-> setPosition(0,2.5,0);
  //nodeb-> scale(1,1,1);
  //nodeb-> scale(0.4,0.4,0.4);  BARCO DE 2 CON BarcoP2B.mesh
  //nodeb-> scale(0.55,0.55,0.55);   BARCO DE 3 CON Barco.mesh
  //nodeb-> scale(0.75,0.75,0.75);  BARCO DE 4 CON Barco.mesh
  //nodeb-> scale(0.95,0.95,0.77);  //BARCO DE 5 CON Barco.mesh

  tabj -> colocarbarcosJUGADOR(44,2,'D');
  tabj -> colocarbarcosJUGADOR(55,3,'S');
  tabj -> colocarbarcosJUGADOR(56,4,'D');
  tabj -> colocarbarcosJUGADOR(33,5,'D');
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

  // CEGUI::Window* vent = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MenuInicial.layout");

  // //CEGUI::Window* formatWin = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MenuInicial.layout");

  // sheet->addChild(vent);

  // CEGUI::Window* exitButton = vent->getChild("ExitButton");
  // exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
  //         CEGUI::Event::Subscriber(&MyFrameListener::quit, 
  //               _framelistener));

  //CEGUI::ImageManager::getSingleton().addFromImageFile("SpaceBackgroundImage", "ojos-de-gato.jpg");
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

}

void MyApp::createGAME(CEGUI::Window* playButton) {
  printf("Hola estoy en el createGAME\n");
  playButton-> setText("Come");

}

// void MyApp::createOverlay() {
//   _overlayManager = OverlayManager::getSingletonPtr();
//   Overlay *overlay = _overlayManager->getByName("Info");
//   overlay->show();
// }
