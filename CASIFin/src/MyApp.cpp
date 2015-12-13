
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
  
  //Creacion de TABLERO
  Tablero *tabj = new Tablero('J',_sceneManager);
  Tablero *tabm = new Tablero('M',_sceneManager);
  
  Ogre::SceneNode* node1Bajo = _sceneManager->createSceneNode("NodoReyBajo");
  Ogre::SceneNode* node1Alto = _sceneManager->createSceneNode("NodoReyAlto");
  
  _sceneManager->getRootSceneNode()->addChild(node1Bajo);
  _sceneManager->getRootSceneNode()->addChild(node1Alto);

  MyScena *scena = new MyScena(node1Alto,node1Bajo,_sceneManager, tabj, tabm);
  scena -> creartablero();
  bool repetir = true;
  std::vector<int> *v = new std::vector<int>;
  for (int i = 5; i > 1; --i){
    //tabm->colocarbarcos(i,v);
    tabm->colocarbarcoQ(i,v);
    if (i == 3 && repetir){
        i++;
        repetir = false;
    }
  }
  
  std::vector<int> *_elegiblesInt = new std::vector<int>(100);
  initElegibles(_elegiblesInt);

  _framelistener = new MyFrameListener(window, cam, tabj, tabm, scena, _sceneManager,"INTRO",_elegiblesInt);
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
  CEGUI::Window* img = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","ventimagen");
  CEGUI::Window* imgV = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","ventimagenVict");
  CEGUI::Window* imgInicio = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","imageninicial");
  
  CEGUI::ImageManager::getSingleton().addFromImageFile("DerrotaDer","derrota.png");
  CEGUI::ImageManager::getSingleton().addFromImageFile("VictoriaVic","victoria.png");
  CEGUI::ImageManager::getSingleton().addFromImageFile("ImagenIni","inicio.jpg");
  
  img -> setProperty("Image","DerrotaDer");
  img -> setProperty("BackgroundEnabled","False");
  img -> setProperty("FrameEnabled","False");

  imgV -> setProperty("Image","VictoriaVic");
  imgV -> setProperty("BackgroundEnabled","False");
  imgV -> setProperty("FrameEnabled","False");
  
  imgInicio -> setProperty("Image","ImagenIni");
  imgInicio -> setProperty("BackgroundEnabled","False");
  imgInicio -> setProperty("FrameEnabled","False");

  CEGUI::Window* vent = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MenuInicial.layout");
  CEGUI::Window* derrota = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Derrota.layout");
  CEGUI::Window* victoria = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Victoria.layout");
 
  img-> setSize(CEGUI::USize(CEGUI::UDim(0.40f,0),CEGUI::UDim(0.40f,0)));  
  img->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30f,0),CEGUI::UDim(0.30f,0)));
  
  imgV-> setSize(CEGUI::USize(CEGUI::UDim(0.40f,0),CEGUI::UDim(0.40f,0)));  
  imgV->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30f,0),CEGUI::UDim(0.30f,0)));
  
  imgInicio-> setSize(CEGUI::USize(CEGUI::UDim(1,0),CEGUI::UDim(1,0)));  
  imgInicio->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
  
  derrota->setPosition(CEGUI::UVector2(CEGUI::UDim(0.20f,0),CEGUI::UDim(0.25f,0)));
  victoria->setPosition(CEGUI::UVector2(CEGUI::UDim(0.20f,0),CEGUI::UDim(0.25f,0)));
  vent->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f,0),CEGUI::UDim(0.10f,0)));
  
  
  CEGUI::Window* exitButton = vent->getChild("ExitButton");
  exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&MyFrameListener::quit, 
                _framelistener));

  CEGUI::Window* playButton = vent->getChild("PlayButton");
  playButton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&MyFrameListener::play, 
                _framelistener));

  CEGUI::Window* derrotaButton = derrota->getChild("ButtonD");
  derrotaButton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&MyFrameListener::quit, 
                _framelistener));

  CEGUI::Window* victoriaButton = victoria->getChild("ButtonD");
  victoriaButton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&MyFrameListener::quit, 
                _framelistener));
  
  imgInicio -> addChild(vent);
  imgV -> addChild(victoria);
  imgV -> setVisible(false);
  img  -> addChild(derrota);
  img -> setVisible(false);
  sheet->addChild(img); 
  sheet -> addChild(imgV);
  sheet -> addChild(imgInicio);
  
  sheet->addChild(vent); 
 
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

}

void MyApp::createGAME(CEGUI::Window* playButton) {
  printf("Hola estoy en el createGAME\n");
}


void MyApp::initElegibles(std::vector<int> *_elegiblesInt){
  srand(time(NULL));
  int arrayElegibles [100];
  for(int i=0; i<100; i++){ 
    arrayElegibles[i]=i;
  } 
  int j = 0;
  
  for(int i = 99; i > 0; i--) {
    j = rand() % i;
    swap(arrayElegibles[i], arrayElegibles[j]);
    _elegiblesInt->push_back(arrayElegibles[i]);
    cout<<arrayElegibles[i]<<endl;
  }
}


