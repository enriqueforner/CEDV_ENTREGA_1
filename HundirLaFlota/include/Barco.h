//Barco.h
#ifndef BARCO_H
#define BARCO_H

#include <Ogre.h>
#include <CEGUI.h>
#include <string> 
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
 class Barco
 {
 public:
 	Barco();
 	Barco(int tipo);
 	Barco(int tipo, Ogre::SceneNode *barco);
 	~Barco();
 	Ogre::SceneNode* getSN();
 	void setSN(Ogre::SceneNode *barco);
 	int getTipo() const;
 	int getDamage() const;
    void setDamage(int damage);
    string getId() const;
    void setId(string id);
    std::vector<int>* getIdCasillas();
    void addCasilla(int id);
 private:
 	Ogre::SceneNode *_barco;
 	int _tipo;
 	int _damage;
 	string _id;
 	std::vector<int> *_idcasillas;
 };

 #endif