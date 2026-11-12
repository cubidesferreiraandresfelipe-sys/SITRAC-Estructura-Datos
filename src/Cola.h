#ifndef COLA_H
#define COLA_H

#include <string>

struct Solicitud {
    int idPasajero;
    std::string origen;
    std::string destino;
    Solicitud* siguiente;

    Solicitud(int id, const std::string& o, const std::string& d)
        : idPasajero(id), origen(o), destino(d), siguiente(nullptr) {}
};

class ColaSolicitudes {
private:
    Solicitud* frente;
    Solicitud* final;

public:
    ColaSolicitudes();
    ~ColaSolicitudes();

    void encolar(int idPasajero, const std::string& origen, const std::string& destino);
    bool atender(int& idPasajero, std::string& origen, std::string& destino); // true if success
    void mostrarFrente() const;
    bool estaVacia() const;
    int contar() const;
};

#endif
