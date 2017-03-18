#ifndef LOCAL_H_INCLUDED
#define LOCAL_H_INCLUDED

#include <vector>
#include "pedido.h"

class Local{
    public:

        Local();
        Local(const vector< pair <Bebida,Cantidad> > bs, const vector< pair <Hamburguesa,Cantidad> > hs, const vector<Empleado> es);

        Cantidad            stockBebidasL(const Bebida b) const;
        Cantidad            stockSandwichesL(const Hamburguesa h) const;
        vector<Bebida>       bebidasDelLocalL() const;
        vector<Hamburguesa>  sandwichesDelLocalL() const;
        vector<Empleado>     empleadosL() const;
        vector<Empleado>     desempleadosL() const;
        Energia             energiaEmpleadoL(const Empleado e) const;
        vector<Pedido>       ventasL() const;
        bool                unaVentaCadaUnoL() const;
        void                venderL(const Pedido p);
        vector<Empleado>     candidatosAEmpleadosDelMesL() const;
        void                sancionL(const Empleado e, const Energia n);
        Empleado            elVagonetaL() const;
        void                anularPedidoL(int n);
        void                agregarComboAlPedidoL(const Combo c, int n);


        void mostrar(std::ostream& os) const;
	void guardar(std::ostream& os) const;
	void cargar (std::istream& is);

    private:
        vector< pair <Hamburguesa,Cantidad> > _sandwiches;
        vector< pair <Bebida,Cantidad> >      _bebidas;
        vector< pair <Empleado, Energia> >    _empleados;
        vector< Pedido >                      _ventas;

        enum {ENCABEZADO_ARCHIVO = 'L'};

};
#endif // LOCAL_H_INCLUDED
std::ostream & operator<<(std::ostream & os,const Local & c);
Bebida retraducirB(string);
Hamburguesa retraducirH(string);
