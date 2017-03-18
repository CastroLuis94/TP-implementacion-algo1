#include "local.h"
#include <string.h>
#include "interfaz.h"

Local::Local(){
	vector <pair <Empleado,Energia> > es;
	this-> _bebidas.push_back(make_pair(FalsaNaranja,10));
	this-> _sandwiches.push_back(make_pair(McPato,20));
	this-> _ventas.clear();
	this-> _empleados=es;
}

Local::Local(const vector< pair <Bebida,Cantidad> > bs, const vector< pair <Hamburguesa,Cantidad> > hs, const vector<Empleado> es){
	vector<Pedido> ventas;
	this ->_sandwiches=hs;
	this ->_bebidas=bs;
	this ->_ventas=ventas;
	int i=0;
	vector<pair <Empleado,Energia> > res;
	Energia fullEnergy=100;
	while(i<es.size()){
		res.push_back(make_pair(es[i],fullEnergy));
		i=i+1;
	}
	this->_empleados=res;
}


Cantidad Local::stockBebidasL(const Bebida b) const{
	int i=0;
	Cantidad res;
	while(i<_bebidas.size()){
		if(_bebidas[i].first==b){
			res=_bebidas[i].second;
			i=_bebidas.size();
		}
		i=i+1;
	}
	return res;
}

Cantidad Local::stockSandwichesL(const Hamburguesa h) const{
	int i=0;
	Cantidad res;
	while(i<_sandwiches.size()){
		if(_sandwiches[i].first==h){
			res=_sandwiches[i].second;
			i=_sandwiches.size();
		}
		i=i+1;
	}
	return res;
}

vector<Bebida>       Local::bebidasDelLocalL() const{
	vector<Bebida> res;
	int i=0;
	while(i<_bebidas.size()){
		res.push_back(_bebidas[i].first);
		i++;
	}
	return res;
}

vector<Hamburguesa>  Local::sandwichesDelLocalL() const{
	vector<Hamburguesa> res;
	int i=0;
	while(i<_sandwiches.size()){
		res.push_back(_sandwiches[i].first);
		i++;
	}
	return res;
}

vector<Empleado>     Local::empleadosL() const{
	vector<Empleado> res;
	int i=0;
	while(i<_empleados.size()){
		if(_empleados[i].second>=0){
		res.push_back(_empleados[i].first);
		}
		i++;
	}
	return res;
}


vector<Empleado>     Local::desempleadosL() const{
	vector<Empleado> res;
	int i=0;
	while(i<_empleados.size()){
		if(_empleados[i].second <0){
			res.push_back(_empleados[i].first);
		}
		i++;
	}
	return res;
}

Energia  Local::energiaEmpleadoL(const Empleado e) const{
	Energia res;
	int i=0;
	while(i<_empleados.size()){
		if(_empleados[i].first==e){
			res=_empleados[i].second;
			i=_empleados.size();
		}
		i=i+1;
	}
	return res;
}

vector<Pedido>       Local::ventasL() const{
	return this->_ventas;
}

///////////////////////////////////////////////////////////////////
Bebida retraducirB(string b){
	
	if (b == "PestiCola") return PestiCola; 
	if (b == "FalsaNaranja") return FalsaNaranja; 
	if (b == "SeVeNada") return SeVeNada; 
	if (b == "AguaConGags") return AguaConGags; 
	if (b == "AguaSinGags") return AguaSinGags; 
	
}

Hamburguesa retraducirH(string h){
	
	if (h == "McGyver") return McGyver; 
	if (h == "CukiQueFresco") return CukiQueFresco; 
	if (h == "McPato") return McPato; 
	if (h == "BigMacabra") return BigMacabra; 
	
}

bool estaEmpleado(vector< pair <Empleado,Energia> > es,Empleado e){
	int i=0;
	bool res=false;
	while(i<es.size()){
		if(es[i].first==e and es[i].second>0){
			res=true;
		}
		i++;
	}
	return res;
}

int cuentaEmpleados(vector<pair <Empleado,Pedido> > es,Empleado e){
	int cuenta=0;
	int i=0;
	while(i<es.size()){
		if(es[i].first==e){
			cuenta++;
		}
		i++;
	}
	return cuenta;
}

bool elEmpleadoEsta(vector<Empleado> es,Empleado e){
	int i=0;
	bool res=false;
	while(i<es.size()){
		if(es[i]==e){
			res=true;
			i=es.size();
		}
		i++;
	}
	return res;
}
vector<Empleado> eliminaLasRep(vector<Empleado> es){
	int i=0;
	vector<Empleado> res;
	while(i<es.size()){
		if(not elEmpleadoEsta(res,es[i])){
			res.push_back(es[i]);
		}
		i++;
	}
	return res;
}

vector<Bebida> dameBebidasP(const Pedido p){
	vector<Bebida> res;
	int i=0;
	while(i<p.combosP().size()){
		res.push_back(p.combosP()[i].bebidaC());
			i++;
	}
	return res;
}
vector<Hamburguesa> damePatysP(const Pedido p){
	vector<Hamburguesa> res;
	int i=0;
	while(i<p.combosP().size()){
		res.push_back(p.combosP()[i].sandwichC());
		i++;
	}
	return res;
}
vector<Empleado> sonEmpleados(vector< pair <Empleado,Energia> > es){
	int i=0;
	vector<Empleado> res;
	while(i<es.size()){
		if(es[i].second>=0){
			res.push_back(es[i].first);
		}
		i++;
	}
	return res;
}
int empleadoYSuVenta(vector<Pedido> ps,Empleado e){
	int i=0;
	int contador=0;
	while(i<ps.size()){
		if(ps[i].atendioP()==e){
			contador++;
		}
		i++;
	}
	return contador;
}

vector<Empleado> losQueVendieronMasPedidos(vector<Pedido> ps, vector<pair<Empleado,Energia> > es){
	int i=0;
	int maximoAtendidos=0;
	vector<Empleado> res;
	vector<Empleado> em=sonEmpleados(es);
	while(i<em.size()){
		if(maximoAtendidos<empleadoYSuVenta(ps,em[i])){
			res.clear();
			res.push_back(em[i]);
			maximoAtendidos=empleadoYSuVenta(ps,em[i]);
		}
		if(maximoAtendidos==empleadoYSuVenta(ps,em[i])){
		  res.push_back(em[i]);
		}
		i++;
	}
	return res;
}
int cuentaCombosVendidos(vector<Pedido> ps, Empleado e){
	int i=0;
	int cuenta=0;
	while(i<ps.size()){
		if(ps[i].atendioP()==e){
			cuenta=cuenta+ps[i].combosP().size();
		}
		i++;
	}
	return cuenta;
}

//////////////////////////////////////////////////////////////////

vector<Empleado> Local::candidatosAEmpleadosDelMesL() const{
	vector<Empleado> res;
	if(_ventas.size()==0){
	   res=sonEmpleados(_empleados);
	}else{
		vector<Empleado> candidatos=losQueVendieronMasPedidos(_ventas,_empleados);
		int i=0;
		int maximaCantidadDeCombosVendidos=0;
		while(i<candidatos.size()){
			if(cuentaCombosVendidos(_ventas,candidatos[i])>maximaCantidadDeCombosVendidos){
				res.clear();
				res.push_back(candidatos[i]);
				maximaCantidadDeCombosVendidos=cuentaCombosVendidos(_ventas,candidatos[i]);
			}
			if(cuentaCombosVendidos(_ventas,candidatos[i])==maximaCantidadDeCombosVendidos){
				res.push_back(candidatos[i]);
			}
			i++;
		}
		
	}
	res=eliminaLasRep(res);
	return res;
}

void Local::venderL(const Pedido p){
		vector<Bebida> bs = dameBebidasP(p);
		vector<Hamburguesa> hs = damePatysP(p);
		int i=0;
		while(i<_empleados.size()){
			if(_empleados[i].first==p.atendioP()){
				if(_empleados[i].second-p.dificultadP()>0){
					_empleados[i].second=_empleados[i].second-p.dificultadP();
					int j=0;
					while(j<_bebidas.size()){
						int k=0;
						while(k<bs.size()){
							if(_bebidas[j].first==bs[k]){
								_bebidas[j]=make_pair(_bebidas[j].first,_bebidas[j].second-1);
							}
							k++;
						}
						j++;
					}
					j=0;
					while(j<_sandwiches.size()){
						int k=0;
						while(k<hs.size()){
							if(_sandwiches[j].first==hs[k]){
								_sandwiches[j].second=_sandwiches[j].second-1;
							}
							k++;
							}
						j++;
					}
					_ventas.push_back(p);
				}else{
					cout << "El empleado no puede atender el pedido y va a ser despedido"<< endl;
					_empleados[i].second=_empleados[i].second-p.dificultadP();
				}
			}
			i++;
		}
}

void Local::sancionL(const Empleado e, const Energia n){
		int i=0;
		vector<pair <Empleado,Energia> > res;
		while(i<_empleados.size()){
			if(_empleados[i].first==e){
				_empleados[i].second=_empleados[i].second-n;
			}
			i++;
		}
}

void Local::anularPedidoL(int n){
	int i=0;
	vector<Pedido> res;
	Energia energiaRecuperada=0;
	while(i<_ventas.size()){
		if(_ventas[i].numeroP()<n){
			res.push_back(_ventas[i]);
		}
		if(_ventas[i].numeroP()>n){
			res.push_back(Pedido(_ventas[i].numeroP()-1,_ventas[i].atendioP(),_ventas[i].combosP()));
		}
		if(_ventas[i].numeroP()==n){
			int j=0;
			energiaRecuperada=energiaRecuperada+_ventas[i].dificultadP();
			while(j<_empleados.size()){
				if(_empleados[j].first==_ventas[i].atendioP()){
					_empleados[j].second=_empleados[j].second+energiaRecuperada;
					j=_empleados.size();
				}
				j++;
			}
			j=0;
			while(j<_bebidas.size()){
				 int k=0;
				 while(k<_ventas[i].combosP().size()){
					if(_bebidas[j].first==_ventas[i].combosP()[k].bebidaC()){
						_bebidas[j].second=_bebidas[j].second+1;
					}
					k++;
				 }
				 j++;
			}
			j=0;
			while(j<_sandwiches.size()){
				int k=0;
				while(k<_ventas[i].combosP().size()){
					if(_sandwiches[j].first==_ventas[i].combosP()[k].sandwichC()){
						_sandwiches[j].second=_sandwiches[j].second+1;
					}
					k++;
				}
				j++;
			}
		}
		i++;
	}
	_ventas=res;
}

////////////////////////////////////////////////////////
int minN(vector<Pedido> ps){
	int res=ps[0].numeroP();
	int i=0;
	while(i<ps.size()){
		if(ps[i].numeroP()<res){
			res=ps[i].numeroP();
		}
		i++;
	}
	return res;
}
void actualizaStockBebida(vector <pair <Bebida,Cantidad> > &bs, Bebida b){
	int i=0;
	while(i<bs.size()){
		if(bs[i].first==b){
			bs[i].second=bs[i].second-1;
		}
		i++;
	}
}
void actualizaStockPaty(vector <pair <Hamburguesa,Cantidad> > &hs, Hamburguesa h){
	int i=0;
	while(i<hs.size()){
		if(hs[i].first==h){
			hs[i].second=hs[i].second-1;
		}
		i++;
	}
}
void actualizaEmpleado(vector <pair <Empleado,Energia> > &es, Empleado e, Energia energy){
	int i=0;
	while(i<es.size()){
		if(es[i].first==e){
			es[i].second=es[i].second-energy;
		}
		i++;
	}
}

vector<Pedido> OrdenaVentas(vector<Pedido> ps){
	int i=minN(ps);
	int x=0;
	vector <Pedido> res;
	while(x<ps.size()){
		if(ps[x].numeroP()==i){
			res.push_back(ps[x]);
			i++;
			x=0;
		}else{
			x++;
		}
	}
	return res;
}
//////////////////////////////////////////////////////
void Local::agregarComboAlPedidoL(const Combo c, int n){
		_ventas = OrdenaVentas(_ventas);
	
		int i= minN(_ventas);
		int primeraVenta = i;
		int ultimaVenta = i + _ventas.size() - 1;
		while(i<= ultimaVenta){
			if(i==n){				
				vector<Combo> cs=_ventas[(i-primeraVenta)].combosP();
				cs.push_back(c);
				_ventas[(i - primeraVenta)]=Pedido(n,_ventas[(i-primeraVenta)].atendioP(),cs);
				actualizaEmpleado(_empleados,_ventas[(i - primeraVenta)].atendioP(),c.dificultadC());
				actualizaStockBebida(_bebidas,c.bebidaC());
				actualizaStockPaty(_sandwiches,c.sandwichC());
			}
			i++;
		}
}

	///////////////////////////////////////////////////////
	
	int maxN(vector<Pedido> ps){
		int res=ps[0].numeroP();
		int i=0;
		while(i<ps.size()){
			if(ps[i].numeroP()>res){
				res=ps[i].numeroP();
			}
			i++;
		}
		return res;
	}
	vector<Empleado> esEmpleado(vector<Empleado> es,vector<pair <Empleado,Energia> > es2){
		int i=0;
		vector<Empleado> res;
		while(i<es.size()){
			int j=0;
			while(j<es2.size()){
				if(es[i]==es2[j].first and es2[j].second>0){
					res.push_back(es[i]);
				}
				j++;				
			}
			i++;
		}
		return res;
	}
	
	
	/////////////////////////////////////////////////////////////////////////

bool Local::unaVentaCadaUnoL() const{
	bool res=true;
		if(_ventas.size()>0){
			int nro=minN(_ventas);
			int i=0;
			vector<Empleado> empleadosQueTrabajaron;
			while(i<_ventas.size()){
				if(_ventas[i].numeroP()==nro){
					empleadosQueTrabajaron.push_back(_ventas[i].atendioP());
					nro++;
					i=0;
				}
				i++;
			}
			empleadosQueTrabajaron=esEmpleado(empleadosQueTrabajaron,_empleados);
			int cantidadQueTrabajo=eliminaLasRep(empleadosQueTrabajaron).size();
			i=0;
			int k=cantidadQueTrabajo;
			while(k<empleadosQueTrabajaron.size()){
				if(empleadosQueTrabajaron[i]!=empleadosQueTrabajaron[k]){
					res=false;
				}
				i++;
				k++;
			}
		}
		return res;	
}
////////////////////////////////////////////////////////////////////////

int descansoMasLargo(vector<Pedido> ps, Empleado e){
	int i=0;
	int cuentaDescanso=0;
	int descansoMaximo=0;
	while(i<ps.size()){
		if(ps[i].atendioP()==e){
			if(descansoMaximo<cuentaDescanso){
				descansoMaximo=cuentaDescanso;
			}
			cuentaDescanso=0;
		}else{
			cuentaDescanso++;
		}
		if(i==ps.size()-1){
			if(descansoMaximo<cuentaDescanso){
				descansoMaximo=cuentaDescanso;
			}
		}
		i++;
	}
	return descansoMaximo;
}
Empleado dameUnEmpleado(vector<pair <Empleado,Energia> > es){
	Empleado res;    
	int i=0;
	while(i<es.size()){
		if(es[i].second>=0){
			res=es[i].first;
			i=es.size();
		}
		i++;
	}
	return res;
}

///////////////////////////////////////////////////////////////////////
Empleado Local::elVagonetaL() const{
	Empleado res = _empleados[0].first;
		if(_ventas.size()>0){
			vector<Pedido> ventas=OrdenaVentas(_ventas);
			int descansoMaximo=0;
			int i=0;
			while(i<_empleados.size()){
				if(descansoMaximo<=descansoMasLargo(ventas,_empleados[i].first)){
					descansoMaximo=descansoMasLargo(ventas,_empleados[i].first);
					res=_empleados[i].first;
				}
				i++;
			}
		}
		return res;
	}

void Local::mostrar(std::ostream& os) const{
	os << "{ L " << "[ ";
			unsigned int i = 0;
			while (i < _bebidas.size()){
				os << "( " << _bebidas[i].first;
				os << _bebidas[i].second << " ) ";
				i++;
			}
			os << "] [ ";
			unsigned int j = 0;
			while (j < _sandwiches.size()){
				os << "( " << _sandwiches[j].first;
				os << _sandwiches[j].second << " ) ";
				j++;
			}
			os << "] [ ";
			unsigned int k = 0;
			while (k < _empleados.size()){
				os << "( " << _empleados[k].first;
				os << " ";
				os << _empleados[k].second << " ) ";
				k++;
			}
			os << "] [";
			unsigned int l = 0;
			vector<Pedido> ventas = _ventas;
			while (l < ventas.size()){
				os << " ";
				ventas[l].mostrar(os);
				l++;
			}
			os << " ] }";
		}

void Local::guardar(std::ostream& os) const{
	os << "{ L " << "[ ";
		unsigned int i = 0;
		while (i < _bebidas.size()){
			os << "( " << _bebidas[i].first;
			os << _bebidas[i].second << " ) ";
			i++;
		}
		os << "] [ ";
		unsigned int j = 0;
		while (j < _sandwiches.size()){
			os << "( " << _sandwiches[j].first;
			os << _sandwiches[j].second << " ) ";
			j++;
		}
		os << "] [ ";
		unsigned int k = 0;
		while (k < _empleados.size()){
			os << "( " << _empleados[k].first;
			os << " ";
			os << _empleados[k].second << " ) ";
			k++;
		}
		os << "] [";
		unsigned int l = 0;
		vector<Pedido> ventas = _ventas;
		while (l < ventas.size()){
			os << " ";
			ventas[l].mostrar(os);
			l++;
		}
		os << " ] }";
	}

void Local::cargar (std::istream& is){
	is.ignore(6);
	string texto;
	vector <pair <Bebida,Cantidad> > bebsCants;
	pair <Bebida,Cantidad> bebCant;
	char c = is.peek();
	while ( c != ']' ){
		is.ignore(2);
		is >> texto;
		bebCant.first = retraducirB(texto);
		is >> texto;
		bebCant.second = atoi(texto.c_str());
		bebsCants.push_back(bebCant);
		is.ignore(3);
		c = is.peek();
		}
	_bebidas = bebsCants;
	is.ignore(4);
	vector <pair <Hamburguesa,Cantidad> > hamsCants;
	hamsCants.clear();
	pair <Hamburguesa,Cantidad> hamCant;
	c = is.peek();
	while ( c != ']' ){
			is.ignore(2);
			is >> texto;
			hamCant.first = retraducirH(texto);
			is >> texto;
			hamCant.second = atoi(texto.c_str());
			hamsCants.push_back(hamCant);
			is.ignore(3);
			c = is.peek();
			}
	_sandwiches = hamsCants;
	is.ignore(4);
		vector <pair <Empleado,Energia> > empsEns;
		pair <Empleado,Energia> empEn;
		c = is.peek();
		while ( c != ']' ){
				is.ignore(2);
				is >> texto;
				empEn.first = texto;
				is >> texto;
				empEn.second = atoi(texto.c_str());
				empsEns.push_back(empEn);
				is.ignore(3);
				c = is.peek();
				}
		is.ignore(4);
		_empleados = empsEns;
		vector <Pedido> ventas;
		Pedido p;
		c = is.peek();
		while ( c != ']' ){
			p.cargar(is);
			is.ignore(1);
			c = is.peek();
			ventas.push_back(p);
			}
		_ventas = ventas;
}


std::ostream & operator<<(std::ostream & os,const Local & l){
	os << "{ L " << "[ ";
				unsigned int i = 0;
				vector<Bebida> bebidas = l.bebidasDelLocalL();
				while (i < bebidas.size()){
					os << "( " << traducir(bebidas[i]);
					os << l.stockBebidasL(bebidas[i]) << " ) ";
					i++;
				}
				os << "] [ ";
				unsigned int j = 0;
				vector <Hamburguesa> hamburguesas = l.sandwichesDelLocalL();
				while (j < hamburguesas.size()){
					os << "( " << traducir(hamburguesas[j]);
					os << l.stockSandwichesL(hamburguesas[j]) << " ) ";
					j++;
				}
				os << "] [ ";
				unsigned int k = 0;
				vector <Empleado> emp = l.empleadosL();
				while (k < emp.size()){
					os << "( " << emp[k];
					os << " ";
					os << l.energiaEmpleadoL(emp[k])<< " ) ";
					k++;
				}
				os << "] [";
				unsigned int m = 0;
				vector<Pedido> ventas = l.ventasL();
				while (m < ventas.size()){
					os << " ";
					ventas[m].mostrar(os);
					m++;
				}
				os << " ] }";

				return os;

}
