#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>
#include <utility> // for pair

// Justificación: Lista de adyacencia usando vector de vectores de pares (destino, distancia).
// Estructura propia justificada para el grafo de ciudades y rutas. No se usa std::list ni std::queue.

class Grafo {
private:
    std::vector<std::string> ciudades;
    std::vector<std::vector<std::pair<int, double>>> adyacencia; // index -> list of (neighbor_index, distancia)

    int indiceCiudad(const std::string& nombre) const;

public:
    Grafo();

    bool agregarCiudad(const std::string& nombre);
    bool eliminarCiudad(const std::string& nombre);
    bool agregarRuta(const std::string& origen, const std::string& destino, double distancia);
    bool eliminarRuta(const std::string& origen, const std::string& destino);
    void listarCiudades() const;
    void mostrarVecinos(const std::string& ciudad) const;
    void mostrarTodasLasRutas() const;
    bool existeCiudad(const std::string& nombre) const;
    int numeroCiudades() const;
};

#endif
