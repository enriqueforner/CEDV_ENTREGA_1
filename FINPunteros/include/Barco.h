//Barco.h
#ifndef BARCO_H
#define BARCO_H

#include <Ogre.h>
#include <CEGUI.h>
#include <string> 
#include <iostream>
#include <sstream>
using namespace std;
 class Barco
 {
 public:
 	Barco(int tipo);
 	Barco();
 	~Barco();
 	int getTipo() const;
 	int getDamage() const;
    void setDamage(int damage);
    string getId() const;
    void setId(string id);
 private:
 	int _tipo;
 	int _damage;
 	string _id;
 };

 #endif