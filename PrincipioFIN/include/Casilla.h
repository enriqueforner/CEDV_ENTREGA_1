//Casilla.h

#include <Ogre.h>
#include <CEGUI.h>
#include <string> 
#include <iostream>
#include <sstream>
using namespace std;
class Casilla
{
public:
	Casilla(Ogre::SceneNode *casilla);
	~Casilla();
	Ogre::SceneNode getSN() const;
	string getEstado();
	void setEstado(string nestado);
private:
	Ogre::SceneNode* _casilla;
	string _estado;
};