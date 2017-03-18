#include "pedido.h"
#include <algorithm>
#include <math.h>

Pedido::Pedido(){
	Empleado e;
	vector<Combo> combos;
	this ->_numero=1;
	this ->_atendio=e;
	this-> _combos.push_back(Combo());
}

Pedido::Pedido(const int nro, const Empleado e, const vector<Combo> combos){
	this ->_numero=nro;
	this ->_atendio=e;
	this ->_combos=combos;
}

/*auxiliares*///////////////////////////////////////////////////////////////////
vector <Hamburguesa> damePatys(vector <Combo> c){
	int i=0;
	vector <Hamburguesa> res;	
	while(i<c.size()){
		res.push_back(c[i].sandwichC());
		i=i+1;
	}
	return res;
}
vector <Bebida> dameBebida(vector <Combo> c){
	int i=0;
	vector <Bebida> res;	
	while(i<c.size()){
		res.push_back(c[i].bebidaC());
		i=i+1;
	}
	return res;
}
bool laHamburguesaEsta(vector <Hamburguesa> hs,Hamburguesa h){
	bool res=false;
	int i=0;
	while(i<hs.size()){
		if(hs[i]==h){
			res=true;
		}
		i=i+1;
	}
	return res;		
}
bool laBebidaEsta(vector <Bebida> bs,Bebida b){
	bool res=false;
	int i=0;
	while(i<bs.size()){
		if(bs[i]==b){
			res=true;
		}
		i=i+1;
	}
	return res;		
}
vector<Hamburguesa> PatysNoRepetidos(vector<Hamburguesa> hs){
	vector <Hamburguesa> res;
	int i=0;
	while(i<hs.size()){
		if(not laHamburguesaEsta(res,hs[i])){
			res.push_back(hs[i]);
		}
		i=i+1;	
	}
	return res;
}
vector <Bebida> BebidasNoRepetidas(vector <Bebida> bs){
	vector <Bebida> res;
	int i=0;
	while(i<bs.size()){
		if(not laBebidaEsta(res,bs[i])){
			res.push_back(bs[i]);
		}
		i=i+1;	
	}
	return res;
}

bool elComboEsta (vector<Combo> c, Combo combo){
	bool res=false;
	int i=0;
	while(i<c.size()){
		if( c[i].sandwichC()== combo.sandwichC() and c[i].bebidaC()==combo.bebidaC()){
			res=true;
			i=c.size();
		}
		i=i+1;
	}
	return res;
}
bool comboNoRepetido(vector<Combo> cs,Combo c){
	int i=0;
	int cuenta=0;
	while(i<cs.size() and cuenta<2){
		if(cs[i].sandwichC()==c.sandwichC() and cs[i].bebidaC()==c.bebidaC()){
			cuenta=cuenta+1;
		}
		i=i+1;
	}
	return cuenta<2;
}

vector<Combo> listaCombosPosibles(vector<Combo> combosOriginales) {
	vector<Combo> res;
	vector<Hamburguesa> hs;
	vector<Bebida> bs;
	hs=PatysNoRepetidos(damePatys(combosOriginales));
	bs=BebidasNoRepetidas(dameBebida(combosOriginales));
	int j = 0;
	int i = 0;
	while (i < hs.size()){
		while (j < bs.size()){
			Combo c = Combo(bs[j], hs[i], 50);
			res.push_back(c);
			j++;
		}
		j = 0;
		i++;
	}
	
	return res;
}


///////////////////////////////////////////////////////////////////////////////
int Pedido::numeroP() const{
	return this->_numero;
}

Empleado Pedido::atendioP() const{
	return this->_atendio;
}

vector<Combo> Pedido::combosP() const{
	return this->_combos;
}

Energia Pedido::dificultadP() const{
	int i=0;
	Energia dificultad=0;
	vector<Combo> c;
	c= _combos;
	while(i<c.size()){
		dificultad=dificultad+c[i].dificultadC();
		i=i+1;
	}
	return dificultad;
}

void  Pedido::agregarComboP(const Combo c){
	this->_combos.push_back(c);
}

void  Pedido::anularComboP(int i){
	int j=0;
	vector<Combo> filtradoDeCombos;
	while(j<_combos.size()){
		if(j!=i){
			filtradoDeCombos.push_back(_combos.at(j));
		}
		j++;
	}
	_combos=filtradoDeCombos;
}

void  Pedido::cambiarBebidaComboP(const Bebida b, int i){
	Combo c=_combos[i];
	_combos[i]=Combo(b,c.sandwichC(),c.dificultadC());
}

void  Pedido::elMezcladitoP(){
	vector<Combo> res = _combos;
	vector<Combo> combosPosibles = listaCombosPosibles(_combos);
	Combo comboNuevo = combosPosibles[0];
	unsigned int i = 0;
	unsigned int j = 0;
	
	while (i < res.size()){
		if (not comboNoRepetido(res, res[i])){
			while (elComboEsta(res, comboNuevo)){
				j++;
				comboNuevo = combosPosibles[j];
			}
			res[i] = comboNuevo;
		}
		i++;
	}
	
	_combos=res;
}




void mostrarC(ostream& os, vector <Combo> combos){
	unsigned int i=0;
	while(i< combos.size()){
		combos[i].mostrar(os);
		i++;
		os << " ";
		}
}

void Pedido::mostrar(std::ostream& os) const{
	vector<Combo> combos = _combos;
	os << "{ P "<< _numero << " "<< _atendio <<" [ ";
	mostrarC(os, combos);
	os << "] }";
}

void Pedido::guardar(std::ostream& os) const{
	vector<Combo> combos = _combos;
	os << "{ P "<< _numero << " "<< _atendio <<" [ ";
	mostrarC(os, combos);
	os << "] }";
}



void Pedido::cargar (std::istream& is){
	string texto;
	is.ignore(4);

	is >> texto;
	_numero = atoi(texto.c_str());
	
	is >> texto;
	_atendio = texto;
	
	vector<Combo> listaCombos;
	Combo c;

	is.ignore(3);
	char k = is.peek();
	while ( k != ']' ){
			c.cargar(is);
			is.ignore(1);
			k = is.peek();
			listaCombos.push_back(c);

	}
  _combos = listaCombos;
  is.ignore(3);
}

bool Pedido::operator==(const Pedido& otroPedido) const{
	bool res;
	res = ( _atendio == otroPedido.atendioP() ) && (_numero == otroPedido.numeroP() );
	int i = 0;
	res = ( _combos.size() == (otroPedido.combosP()).size() ) && res;
	while ( res && ( i < _combos.size()) ){
		res = ( _combos[i] == (otroPedido.combosP())[i] );
		i++;
	}
	return res;

}

std::ostream & operator<<(std::ostream & os,const Pedido& p){
	vector<Combo> combos = p.combosP();
	os << "{ P "<< p.numeroP() << " "<< p.atendioP() <<" [ ";
	mostrarC(os, combos);
	os << "] }";
	return os;
}
