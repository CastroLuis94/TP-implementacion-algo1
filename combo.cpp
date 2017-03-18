#include "combo.h"
#include "interfaz.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "local.h"

using namespace std;

Combo::Combo(){
	Bebida b;
	Hamburguesa h;
	Energia d;
	this ->_bebida=b;
	this ->_sandwich=h;
	this ->_dificultad=d;
}

Combo::Combo(const Bebida b, const Hamburguesa h, const Energia d ){
	this ->_bebida=b;
	this ->_sandwich=h;
	this ->_dificultad=d;
}

Bebida Combo::bebidaC() const{
    return this -> _bebida;
}

Hamburguesa Combo::sandwichC() const{
	return this -> _sandwich;
}

Energia Combo::dificultadC() const{
	return this -> _dificultad;
}

void Combo::mostrar(std::ostream& os) const{
	os << "{ C " << _bebida << _sandwich << _dificultad<< " }";
}

void Combo::guardar(std::ostream& os) const{
	os << "{ C " << _bebida << _sandwich << _dificultad<< " }";
}

void Combo::cargar (std::istream& is){

		string texto;
		is.ignore(4);

		is >> texto;
		_bebida = retraducirB(texto);

		is >> texto;
		_sandwich = retraducirH(texto);

		is >> texto;
		_dificultad = atoi(texto.c_str());
		is.ignore(2);

}

bool Combo::operator==(const Combo& otroCombo) const{
	return (_sandwich == otroCombo.sandwichC()) && (_bebida == otroCombo.bebidaC()) && (_dificultad == otroCombo.dificultadC());
}

std::ostream & operator<<(std::ostream & os,const Combo & c){
	os << "{ C " << c.bebidaC() << c.sandwichC() << c.dificultadC() << " }";
	return os;
}

std::ostream & operator<<(std::ostream & os,const Hamburguesa & h){

	os << traducir(h) << " ";
	return os;
}

std::ostream & operator<<(std::ostream & os,const Bebida & b){
	os << traducir(b) << " ";
	return os;
}

