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

#include "MyFrameListener.h"

MyFrameListener::MyFrameListener(Ogre::RenderWindow* win, 
				 Ogre::Camera* cam, 
				 Ogre::SceneNode *node,Ogre::SceneManager *sceneManager) {
  OIS::ParamList param;
  size_t windowHandle;  std::ostringstream wHandleStr;

  _camera = cam;  _node = node;
  _selectedNode = NULL;
  _quit = false;
  _play = false;
  _ranking = false;
  _settings = false;
  _sceneManager = sceneManager;
  _win = win;

  win->getCustomAttribute("WINDOW", &windowHandle);
  wHandleStr << windowHandle;
  param.insert(std::make_pair("WINDOW", wHandleStr.str()));
  
  _inputManager = OIS::InputManager::createInputSystem(param);
  _keyboard = static_cast<OIS::Keyboard*>
    (_inputManager->createInputObject(OIS::OISKeyboard, true));
  _mouse = static_cast<OIS::Mouse*>
    (_inputManager->createInputObject(OIS::OISMouse, true));

  _keyboard->setEventCallback(this);
  _mouse->setEventCallback(this);
}

MyFrameListener::~MyFrameListener() {
  //  _inputManager->destroyInputObject(_keyboard);
  //  _inputManager->destroyInputObject(_mouse);
  //  OIS::InputManager::destroyInputSystem(_inputManager);
}

bool MyFrameListener::frameStarted(const Ogre::FrameEvent& evt) {
  _timeSinceLastFrame = evt.timeSinceLastFrame;
  
  bool botomizq;

  CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(_timeSinceLastFrame);

  _mouse->capture();
  _keyboard->capture();
  
  if(_quit) return false;

  //coger posicion del raton en cegui
  //CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();

  //int posx = _mouse->getMouseState().X.abs;   // Posicion del puntero
  //int posy = _mouse->getMouseState().Y.abs;   //  en pixeles.
  
  //printf("%d\n", posx);
  //printf("%d\n", posy);

  botomizq = _mouse->getMouseState().buttonDown(OIS::MB_Left);
  //uint32 mask;


  Ogre::RaySceneQuery* mRayScnQuery;
  
  mRayScnQuery = _sceneManager->createRayQuery(Ogre::Ray()); //Creo la rayquery

  CEGUI::Vector2f mousePos = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
  
  //printf("X: %f  Y: %f \n",mousePos.d_x,mousePos.d_y);
  //printf(" Width: %d  Height: %d", _win->getWidth(), _win->getHeight());
  //Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x / float(me.state.width), mousePos.d_y / float(me.state.height));
  Ogre::Ray mouseRay = _camera->getCameraToViewportRay(mousePos.d_x/_win->getWidth(), mousePos.d_y/_win->getHeight());
  

  if (botomizq) { // Variables y codigo especifico si es izquierdo
    printf("Boton izquierdo\n");  
    mRayScnQuery->setRay(mouseRay);  //add rayo
    //mRayScnQuery->setSortByDistance(true); //ordenar por distancia
 
    Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();  //obtener resultado
    Ogre::RaySceneQueryResult::iterator itr = result.begin();    //creo el iterador
    Ogre::Entity* mEntity;
    printf("Iterador creado\n");
    int i = 1;
    if (itr != result.end()){ //Iterar resultado de la rayscenequery
    	//ostringstream osa;       
        printf("Iterando objetos. Objeto %d\n", i); 
        _selectedNode = itr->movable->getParentSceneNode();
        //_selectedNode->showBoundingBox(true);
        mEntity = static_cast<Ogre::Entity*>(_selectedNode->getAttachedObject(0));
        if(_selectedNode->getName() != "ground"){
          mEntity->setMaterialName("MaterialVerde");
        }
        cout << _selectedNode->getName()+ "\n";
        i++;
    }

      //r = setRayQuery(posx, posy, MASK1);
      
      //RaySceneQueryResult &result = _raySceneQuery->execute();
      //RaySceneQueryResult::iterator it;
      //it = result.begin();

      //if (it != result.end()) {  
            //ostringstream osa;       
            //_selectedNode = it->movable->getParentSceneNode();
            //_selectedNode->showBoundingBox(true);
      //}
           
  }


  

  return true;
}

bool MyFrameListener::keyPressed(const OIS::KeyEvent& evt)
{
  if(evt.key==OIS::KC_ESCAPE) return _quit=true;
 
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(static_cast<CEGUI::Key::Scan>(evt.key));
  CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(evt.text);

  return true;
}

bool MyFrameListener::keyReleased(const OIS::KeyEvent& evt)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(static_cast<CEGUI::Key::Scan>(evt.key));
  return true;
}

bool MyFrameListener::mouseMoved(const OIS::MouseEvent& evt)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(evt.state.X.rel, evt.state.Y.rel);  
  return true;
}

bool MyFrameListener::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertMouseButton(id));
  return true;
}

bool MyFrameListener::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertMouseButton(id));
  return true;
}

CEGUI::MouseButton MyFrameListener::convertMouseButton(OIS::MouseButtonID id)
{
  CEGUI::MouseButton ceguiId;
  switch(id)
    {
    case OIS::MB_Left:
      ceguiId = CEGUI::LeftButton;
      break;
    case OIS::MB_Right:
      ceguiId = CEGUI::RightButton;
      break;
    case OIS::MB_Middle:
      ceguiId = CEGUI::MiddleButton;
      break;
    default:
      ceguiId = CEGUI::LeftButton;
    }
  return ceguiId;
}


bool MyFrameListener::quit(const CEGUI::EventArgs &e)
{
  _quit = true;
  return true;
}

bool MyFrameListener::play(const CEGUI::EventArgs &e)
{
 
  return true;
}

bool MyFrameListener::settings(const CEGUI::EventArgs &e)
{
  
  return true;
}

bool MyFrameListener::ranking(const CEGUI::EventArgs &e)
{
  printf("He pulsado ranking\n");
  
  return true;
}

//Ogre::Ray MyFrameListener::setRayQuery(int posx, int posy, Ogre::uint32 mask) {
Ogre::Ray MyFrameListener::setRayQuery(int posx, int posy, Ogre::uint32 mask) {
  /*Ray rayMouse = _camera->getCameraToViewportRay
    (posx/float(_win->getWidth()), posy/float(_win->getHeight()));*/
  printf("Antes de crear raymouse");
  Ray rayMouse = _camera->getCameraToViewportRay (posx, posy);  
  printf("Antes de asignar el rayo");
  _raySceneQuery->setRay(rayMouse);
  printf("Antes de asignar la mascara");
  //_raySceneQuery->setQueryMask(mask);
  printf("Antes de ordenar por distancia");
  _raySceneQuery->setSortByDistance(true);
  printf("Antes de devolver el rayo");
  return (rayMouse);
}