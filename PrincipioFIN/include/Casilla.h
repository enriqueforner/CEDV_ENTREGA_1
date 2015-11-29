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
	Casilla();
	Casilla(Ogre::SceneNode *casilla);
	~Casilla();
	Ogre::SceneNode getSN() const;
	string getEstado();
	void setEstado(string nestado);
	string getId() const;
private:
	Ogre::SceneNode* _casilla;
	string _estado;
	string _id;
};