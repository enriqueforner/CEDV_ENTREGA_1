
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
				 Ogre::Camera* cam,  Tablero *tabj, Tablero *tabm, MyScena *scena, 
				 Ogre::SceneManager *sceneManager,string estado, std::vector<int> *elegiblesInt) {
  OIS::ParamList param;
  size_t windowHandle;  std::ostringstream wHandleStr;
  _tabj = tabj;
  _tabm = tabm;
  _scena = scena;

  _camera = cam;  
  _selectedNode = NULL;
  _quit = false;
  _play = false;
  _ranking = false;
  _settings = false;
  _empezarjuego = true;
  _ponerbarco = false;
  _sceneManager = sceneManager;
  _win = win;
  _estado = estado;
  _currentShip = 5;
  _primer3 = true;
  _elegiblesInt = elegiblesInt;

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
  _atacar= false;
}

MyFrameListener::~MyFrameListener() {
  //  _inputManager->destroyInputObject(_keyboard);
  //  _inputManager->destroyInputObject(_mouse);
  //  OIS::InputManager::destroyInputSystem(_inputManager);
}

bool MyFrameListener::frameStarted(const Ogre::FrameEvent& evt) {
  _timeSinceLastFrame = evt.timeSinceLastFrame;

  bool botomizq;
  bool botomS;
  bool botomW;
  bool botomD;
  bool botomA;
  
  CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(_timeSinceLastFrame);

  _mouse->capture();
  _keyboard->capture();

  botomizq = _mouse->getMouseState().buttonDown(OIS::MB_Left);
  botomS = _keyboard->isKeyDown(OIS::KC_S);
  botomW = _keyboard->isKeyDown(OIS::KC_W);
  botomD = _keyboard->isKeyDown(OIS::KC_D);
  botomA = _keyboard->isKeyDown(OIS::KC_A);
  
  Ogre::RaySceneQuery* mRayScnQuery;
  
  mRayScnQuery = _sceneManager->createRayQuery(Ogre::Ray()); //Creo la rayquery

  CEGUI::Vector2f mousePos = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
  
  Ogre::Ray mouseRay = _camera->getCameraToViewportRay(mousePos.d_x/_win->getWidth(), mousePos.d_y/_win->getHeight());
  
  Ogre::Entity* mEntity;
  if (botomizq && (_estado.compare("PONIENDOBARCOS")==0 || _estado.compare("ATACANDO")==0)) { // Variables y codigo especifico si es izquierdo
    
    if(_selectedNode!= NULL && (_estado.compare("PONIENDOBARCOS")==0 ) && _selectedNode->getName().compare("ground") != 0 && _selectedNode->getName().substr(0,1) != "B"  ){
        mEntity = static_cast<Ogre::Entity*>(_selectedNode->getAttachedObject(0));
        mEntity->setMaterialName("Material.001");
        _selectedNode = NULL;  
    } 
    mRayScnQuery->setRay(mouseRay);  //add rayo
    //mRayScnQuery->setSortByDistance(true); //ordenar por distancia
 
    Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();  //obtener resultado
    Ogre::RaySceneQueryResult::iterator itr = result.begin();    //creo el iterador
    int i = 1;

    if (itr != result.end()){ //Iterar resultado de la rayscenequery
       _selectedNode = itr->movable->getParentSceneNode();
        mEntity = static_cast<Ogre::Entity*>(_selectedNode->getAttachedObject(0));
        if(_selectedNode->getName() != "ground" ){
          if (_selectedNode->getName().substr(0,1) == "J"){
            if(_estado.compare("PONIENDOBARCOS")==0 )
               mEntity->setMaterialName("MaterialVerde");
          }else {
            if(_estado.compare("PONIENDOBARCOS")==0 || _selectedNode->getName().substr(0,1) == "B" )
              _selectedNode = NULL;
          }
        }
        i++;
    }
          
  }
  if(_quit) return false;
  if(_empezarjuego){
    _estado = "PONIENDOBARCOS";
    _empezarjuego = false;
  } 
  if(_estado.compare("PONIENDOBARCOS") == 0){
    bool metido = false;
    if(_ponerbarco && _selectedNode != NULL){ 
      string name = _selectedNode->getName();
      string numero = name.substr(1,2);
      int x = atoi(numero.c_str());
      int d = (x/10)%10;
      int u = x%10;
      if (botomS&&x<(110 -_currentShip*10)){
        metido = _tabj -> colocarbarcosJUGADOR(x,_currentShip,'S');  
        if (metido){
          if(_currentShip == 3 && _primer3)
            _primer3 = false;
          else
            _currentShip --;
        }         
      }
      else if (botomW&&x>(9 + (_currentShip - 2)*10)){
        metido = _tabj -> colocarbarcosJUGADOR(x,_currentShip,'W');  
        if(metido){
          if(_currentShip == 3 && _primer3)
            _primer3 = false;
          else
            _currentShip --;  
        }
      }
      else if (botomD&&(u < (11-_currentShip))){
        metido = _tabj -> colocarbarcosJUGADOR(x,_currentShip,'D');  
        if(metido){
          if(_currentShip == 3 && _primer3)
            _primer3 = false;
          else
            _currentShip --;
        }  
      }
      else if (botomA&&(u > (_currentShip -2))){
        metido = _tabj -> colocarbarcosJUGADOR(x,_currentShip,'A'); 
        if(metido){
          if(_currentShip == 3 && _primer3)
            _primer3 = false;
          else
            _currentShip --;
        }  
      }
      if(_selectedNode->getName() != "ground"){
          mEntity = static_cast<Ogre::Entity*>(_selectedNode->getAttachedObject(0));
          mEntity->setMaterialName("Material.001");
      }
      if(_estado.compare("PONIENDOBARCOS") == 0 && _currentShip < 2){
        _estado = "ATACANDO";
      }
      cout << _estado << " " << _currentShip << endl;
      _ponerbarco = false;
      _selectedNode = NULL;
    }
  }
  if (_atacar && _estado.compare("ATACANDO") ==0 ){
        bool noAtacada = false;
        if (_estado.compare("WIN")==0 || _estado.compare("LOSE")==0){
         }else{
            if (_selectedNode!= NULL && _selectedNode->getName().substr(0,1) != "J"){
              mEntity = static_cast<Ogre::Entity*>(_selectedNode->getAttachedObject(0));
              noAtacada =  mEntity->getSubEntity(0)->getMaterialName().compare("MaterialRojo")!=0 && mEntity->getSubEntity(0)->getMaterialName().compare("MaterialAgua")!=0;
              cout << "Material: "<< mEntity->getSubEntity(0)->getMaterialName()<<endl;
              if(noAtacada){
               if(_selectedNode->getName() != "ground"){
                  string name = _selectedNode->getName();
                  string numero = name.substr(1,2);
                  int x = atoi(numero.c_str());
                 
                  _tabm-> atacarcasilla(x);  
                 cout << "Atacando YO" << endl;
               } 
              }  
            }

            _selectedNode = NULL;
            cout << "barcos hundidos de M: "<<_tabm->barcoshundidos() <<endl;
            std::vector<Barco>* barcos_M = _tabm->getBarcos();
            std::vector<Barco>::iterator it;
            for (it = barcos_M->begin(); it != barcos_M->end();++it){
              cout << "damage barco"<< it->getTipo() << " : "<<it->getDamage() <<endl;  
            }

            if(_tabm->barcoshundidos()==5){
              _estado="WIN";
              victoria();
              cout << "I win" <<endl;
            }

        }  
        if (_estado.compare("WIN")==0 || _estado.compare("LOSE")==0){
        }else{
          if(noAtacada){
            int ataque = _tabj->ataqueinteligente(_elegiblesInt);
            _tabj-> atacarcasilla(ataque);
            cout << "Atacando maquina" << endl;
            if(_tabj->barcoshundidos()==5){
              _estado="LOSE";
              derrota();
              cout << "I LOSe" <<endl;
            }
          }
        }
    
      _atacar = false;
  }
  return true;
}

bool MyFrameListener::keyPressed(const OIS::KeyEvent& evt)
{
  if(evt.key==OIS::KC_ESCAPE) return _quit=true;
  if(evt.key==OIS::KC_S) return _ponerbarco=true;
  if(evt.key==OIS::KC_D) return _ponerbarco=true;
  if(evt.key==OIS::KC_W) return _ponerbarco=true;
  if(evt.key==OIS::KC_A) return _ponerbarco=true;
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
  _atacar = true;
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
  CEGUI::Window *sheet=  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  sheet -> setVisible(false);

  Ogre::SceneNode *nrb =_sceneManager-> getSceneNode("NodoReyBajo");
  nrb -> setVisible(true,true);
  
  _empezarjuego = true;
  
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

void MyFrameListener::derrota(){
    CEGUI::Window *sheet=  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
    CEGUI::Window *img = sheet->getChild("ventimagen");
    CEGUI::Window *imgV = sheet->getChild("ventimagenVict");
    CEGUI::Window *imgInicial = sheet->getChild("imageninicial");
    CEGUI::Window *menuinicial = sheet->getChild("MenuInicial");
    
    sheet -> setVisible(true);
    menuinicial -> setVisible(false);
    img -> setVisible(true);
    imgInicial-> setVisible(false);
    imgV-> setVisible(false);

}
void MyFrameListener::victoria(){
    CEGUI::Window *sheet=  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
    CEGUI::Window *img = sheet->getChild("ventimagen");
    CEGUI::Window *imgV = sheet->getChild("ventimagenVict");
    CEGUI::Window *imgInicial = sheet->getChild("imageninicial");
    CEGUI::Window *menuinicial = sheet->getChild("MenuInicial");
  
    sheet -> setVisible(true);
    menuinicial -> setVisible(false);
    img -> setVisible(false);
    imgInicial-> setVisible(false);
    imgV-> setVisible(true);
}
Ogre::Ray MyFrameListener::setRayQuery(int posx, int posy, Ogre::uint32 mask) {
  
  printf("Antes de crear raymouse");
  Ray rayMouse = _camera->getCameraToViewportRay (posx, posy);  
  printf("Antes de asignar el rayo");
  _raySceneQuery->setRay(rayMouse);
  printf("Antes de asignar la mascara");
  printf("Antes de ordenar por distancia");
  _raySceneQuery->setSortByDistance(true);
  printf("Antes de devolver el rayo");
  return (rayMouse);
}