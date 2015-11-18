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
  
  Ogre::RenderWindow* window = _root->initialise(true,"MyApp Example");
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
  
  Ogre::SceneNode *node = _sceneManager->getSceneNode("SinbadNode");
  
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
  Ogre::Entity* ent1 = _sceneManager->createEntity("Sinbad.mesh");
  Ogre::SceneNode* node1 = _sceneManager->createSceneNode("SinbadNode");
  node1->attachObject(ent1);
  _sceneManager->getRootSceneNode()->addChild(node1);

  // add two lights
  Ogre::Light* light1 = _sceneManager->createLight();
  light1->setType(Ogre::Light::LT_POINT);
  light1->setPosition(-10, 100, 100);
  light1->setSpecularColour(Ogre::ColourValue::White);
  node1->attachObject(light1);

  Ogre::Light* light2 = _sceneManager->createLight();
  light2->setType(Ogre::Light::LT_POINT);
  light2->setPosition(10, -100, -100);
  light2->setSpecularColour(Ogre::ColourValue::White);
  node1->attachObject(light2);
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

  CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
  CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-12");
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
  
  //Sheet
  CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","Ex1/Sheet");

  // //Play Button
  // CEGUI::Window* playButton = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button","Ex1/PlayButton");
  // playButton->setText("Play");
  // playButton->setSize(CEGUI::USize(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
  // playButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.2,0)));
  // playButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		// 	     CEGUI::Event::Subscriber(&MyFrameListener::play, 
		// 				      _framelistener));
  
  // //Ranking Button
  // CEGUI::Window* rankingButton = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button","Ex1/RankingButton");
  // rankingButton->setText("Ranking");
  // rankingButton->setSize(CEGUI::USize(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
  // rankingButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.2,50)));
  // rankingButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		// 	     CEGUI::Event::Subscriber(&MyFrameListener::ranking, 
		// 				      _framelistener));
	
  
  // //Settings button
  // CEGUI::Window* settingsButton = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button","Ex1/SettingsButton");
  // settingsButton->setText("Settings");
  // settingsButton->setSize(CEGUI::USize(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
  // settingsButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.2,100)));
  // settingsButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		// 	     CEGUI::Event::Subscriber(&MyFrameListener::settings, 
		// 				      _framelistener));
  			
  // //Quit button
  // CEGUI::Window* quitButton = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button","Ex1/QuitButton");
  // quitButton->setText("Quit");
  // quitButton->setSize(CEGUI::USize(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
  // quitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.2,150)));
  // quitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		// 	     CEGUI::Event::Subscriber(&MyFrameListener::quit, 
		// 				      _framelistener));
						      						      						      
  // //Attaching buttons
  // sheet->addChild(playButton);
  // sheet->addChild(rankingButton);
  // sheet->addChild(settingsButton);
  // sheet->addChild(quitButton);

  CEGUI::Window* vent = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MenuInicial.layout");

  //CEGUI::Window* formatWin = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MenuInicial.layout");

  sheet->addChild(vent);

  CEGUI::Window* exitButton = vent->getChild("ExitButton");
  exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&MyFrameListener::quit, 
                _framelistener));

  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

}

void MyApp::createGAME(CEGUI::Window* playButton) {
  printf("Hola estoy en el createGAME\n");
  playButton-> setText("Come");

}