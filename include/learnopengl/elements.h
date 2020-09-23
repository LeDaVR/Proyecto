#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <learnopengl/dinamicarray.h>
#include <learnopengl/model.h>
#include <vector>
#include <string>

class Elements {
	protected:
		Elements();
		Model model;
		int elementID;
		std::string info;
	public:
		virtual Model* getModel() { return NULL; }
		int getSizeData();
		virtual std::string getInfo();
		//~Elements(){}
};

/*class Units : public Elements {
};

class Edificios : public Elements{

		void setID();
	public:
		std::string getInfo();
};
*/
class Resources : public Elements {
	protected:
		virtual Model* getModel() { return NULL; }
		virtual std::string getInfo();
};
class CampodeLino : public Resources {
	public:
		CampodeLino();

};

class Mina : public Resources {
	public:
		Mina();
};

class Arbol : public Resources {
	public:
		Arbol();
		Model* getModel() { return &model; };
};
/*
class Decorate_Elements : public Elements{
	public:
		std::string getInfo();
};*/
struct ElementData {
	Arbol arbol;
	std::vector<Elements> data;
public:
	ElementData();
	Elements* Begin();
};

#endif