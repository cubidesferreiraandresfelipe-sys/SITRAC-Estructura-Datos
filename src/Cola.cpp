#include "Cola.h"
#include <iostream>

ColaSolicitudes::ColaSolicitudes() : frente(nullptr), final(nullptr) {}

ColaSolicitudes::~ColaSolicitudes() {
    while (frente != nullptr) {
        Solicitud* temp = frente;
        frente = frente->siguiente;
        delete temp;
    }
}

void ColaSolicitudes::encolar(int idPasajero, const std::string& origen, const std::string& destino) {
    Solicitud* nueva = new Solicitud(idPasajero, origen, destino);
    if (estaVacia()) {
        frente = final = nueva;
    } else {
        final->siguiente = nueva;
        final = nueva;
    }
    std::cout << "Solicitud de viaje encolada correctamente.\n";
}

bool ColaSolicitudes::atender(int& idPasajero, std::string& origen, std::string& destino) {
    if (estaVacia()) {
        std::cout << "Error: Cola vacía. No hay solicitudes para atender (subdesbordamiento).\n";
        return false;
    }

    idPasajero = frente->idPasajero;
    origen = frente->origen;
    destino = frente->destino;

    Solicitud* temp = frente;
    frente = frente->siguiente;
    if (frente == nullptr) final = nullptr;
    delete temp;

    std::cout << "Solicitud atendida: Pasajero " << idPasajero
              << " de " << origen << " a " << destino << "\n";
    return true;
}

void ColaSolicitudes::mostrarFrente() const {
    if (estaVacia()) {
        std::cout << "La cola está vacía. No hay solicitudes pendientes.\n";
        return;
    }
    std::cout << "Frente de la cola: Pasajero ID " << frente->idPasajero
              << " | Origen: " << frente->origen
              << " | Destino: " << frente->destino << "\n";
}

bool ColaSolicitudes::estaVacia() const {
    return frente == nullptr;
}

int ColaSolicitudes::contar() const {
    int c = 0;
    Solicitud* actual = frente;
    while (actual != nullptr) {
        c++;
        actual = actual->siguiente;
    }
    return c;
}
