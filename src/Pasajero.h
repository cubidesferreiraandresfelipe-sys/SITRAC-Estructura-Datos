#ifndef PASAJERO_H
#define PASAJERO_H

#include <string>

struct Pasajero {
    int id;
    std::string nombre;
    std::string documento;
    Pasajero* siguiente;

    Pasajero(int _id, const std::string& _nombre, const std::string& _doc)
        : id(_id), nombre(_nombre), documento(_doc), siguiente(nullptr) {}
};

class ListaPasajeros {
private:
    Pasajero* cabeza;

public:
    ListaPasajeros();
    ~ListaPasajeros();

    bool insertar(int id, const std::string& nombre, const std::string& documento);
    Pasajero* buscar(int id);
    bool actualizar(int id, const std::string& nuevoNombre, const std::string& nuevoDoc);
    bool eliminar(int id);
    void listar() const;
    bool estaVacia() const;
    int contar() const;
};

#endif
