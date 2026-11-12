#include "Pasajero.h"
#include <iostream>

ListaPasajeros::ListaPasajeros() : cabeza(nullptr) {}

ListaPasajeros::~ListaPasajeros() {
    while (cabeza != nullptr) {
        Pasajero* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

bool ListaPasajeros::insertar(int id, const std::string& nombre, const std::string& documento) {
    if (buscar(id) != nullptr) {
        std::cout << "Error: Ya existe un pasajero con ID " << id << ". No se permite duplicado.\n";
        return false;
    }

    Pasajero* nuevo = new Pasajero(id, nombre, documento);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    std::cout << "Pasajero registrado correctamente.\n";
    return true;
}

Pasajero* ListaPasajeros::buscar(int id) {
    Pasajero* actual = cabeza;
    while (actual != nullptr) {
        if (actual->id == id) return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

bool ListaPasajeros::actualizar(int id, const std::string& nuevoNombre, const std::string& nuevoDoc) {
    Pasajero* p = buscar(id);
    if (p == nullptr) {
        std::cout << "Error: Pasajero con ID " << id << " no encontrado.\n";
        return false;
    }
    p->nombre = nuevoNombre;
    p->documento = nuevoDoc;
    std::cout << "Pasajero actualizado correctamente.\n";
    return true;
}

bool ListaPasajeros::eliminar(int id) {
    if (cabeza == nullptr) {
        std::cout << "Lista de pasajeros vacía.\n";
        return false;
    }

    if (cabeza->id == id) {
        Pasajero* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        std::cout << "Pasajero eliminado correctamente.\n";
        return true;
    }

    Pasajero* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->id != id) {
        actual = actual->siguiente;
    }

    if (actual->siguiente == nullptr) {
        std::cout << "Error: Pasajero con ID " << id << " no encontrado. No se modificó la lista.\n";
        return false;
    }

    Pasajero* temp = actual->siguiente;
    actual->siguiente = temp->siguiente;
    delete temp;
    std::cout << "Pasajero eliminado correctamente.\n";
    return true;
}

void ListaPasajeros::listar() const {
    if (cabeza == nullptr) {
        std::cout << "No hay pasajeros registrados.\n";
        return;
    }
    std::cout << "\n=== LISTA DE PASAJEROS ===\n";
    Pasajero* actual = cabeza;
    int contador = 1;
    while (actual != nullptr) {
        std::cout << contador++ << ". ID: " << actual->id
                  << " | Nombre: " << actual->nombre
                  << " | Documento: " << actual->documento << "\n";
        actual = actual->siguiente;
    }
    std::cout << "==========================\n";
}

bool ListaPasajeros::estaVacia() const {
    return cabeza == nullptr;
}

int ListaPasajeros::contar() const {
    int c = 0;
    Pasajero* actual = cabeza;
    while (actual != nullptr) {
        c++;
        actual = actual->siguiente;
    }
    return c;
}
