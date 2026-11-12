#include "Grafo.h"
#include <iostream>
#include <algorithm>

Grafo::Grafo() {}

int Grafo::indiceCiudad(const std::string& nombre) const {
    for (size_t i = 0; i < ciudades.size(); ++i) {
        if (ciudades[i] == nombre) return static_cast<int>(i);
    }
    return -1;
}

bool Grafo::agregarCiudad(const std::string& nombre) {
    if (indiceCiudad(nombre) != -1) {
        std::cout << "Error: La ciudad '" << nombre << "' ya existe. No se permite duplicado.\n";
        return false;
    }
    ciudades.push_back(nombre);
    adyacencia.push_back(std::vector<std::pair<int, double>>());
    std::cout << "Ciudad '" << nombre << "' agregada correctamente.\n";
    return true;
}

bool Grafo::eliminarCiudad(const std::string& nombre) {
    int idx = indiceCiudad(nombre);
    if (idx == -1) {
        std::cout << "Error: Ciudad '" << nombre << "' no encontrada.\n";
        return false;
    }

    // Eliminar referencias a esta ciudad en otras listas de adyacencia
    for (size_t i = 0; i < adyacencia.size(); ++i) {
        if (static_cast<int>(i) == idx) continue;
        auto& vecinos = adyacencia[i];
        vecinos.erase(std::remove_if(vecinos.begin(), vecinos.end(),
            [idx](const std::pair<int, double>& p) { return p.first == idx; }), vecinos.end());
        // Ajustar índices mayores que idx
        for (auto& p : vecinos) {
            if (p.first > idx) p.first--;
        }
    }

    ciudades.erase(ciudades.begin() + idx);
    adyacencia.erase(adyacencia.begin() + idx);
    std::cout << "Ciudad '" << nombre << "' eliminada. Referencias actualizadas (sin colgantes).\n";
    return true;
}

bool Grafo::agregarRuta(const std::string& origen, const std::string& destino, double distancia) {
    if (distancia <= 0) {
        std::cout << "Error: Distancia inválida (" << distancia << "). Debe ser positiva.\n";
        return false;
    }
    int iOrig = indiceCiudad(origen);
    int iDest = indiceCiudad(destino);
    if (iOrig == -1 || iDest == -1) {
        std::cout << "Error: Una o ambas ciudades no existen.\n";
        return false;
    }
    if (iOrig == iDest) {
        std::cout << "Error: No se puede crear ruta a la misma ciudad.\n";
        return false;
    }

    // Verificar si ya existe
    for (const auto& p : adyacencia[iOrig]) {
        if (p.first == iDest) {
            std::cout << "Error: La ruta ya existe.\n";
            return false;
        }
    }

    adyacencia[iOrig].push_back({iDest, distancia});
    // Grafo no dirigido por simplicidad (rutas bidireccionales)
    adyacencia[iDest].push_back({iOrig, distancia});
    std::cout << "Ruta agregada: " << origen << " <-> " << destino << " (" << distancia << " km)\n";
    return true;
}

bool Grafo::eliminarRuta(const std::string& origen, const std::string& destino) {
    int iOrig = indiceCiudad(origen);
    int iDest = indiceCiudad(destino);
    if (iOrig == -1 || iDest == -1) {
        std::cout << "Error: Ciudad(es) no encontrada(s).\n";
        return false;
    }

    auto& vecOrig = adyacencia[iOrig];
    auto it = std::remove_if(vecOrig.begin(), vecOrig.end(),
        [iDest](const std::pair<int, double>& p) { return p.first == iDest; });
    if (it == vecOrig.end()) {
        std::cout << "Error: Ruta no encontrada.\n";
        return false;
    }
    vecOrig.erase(it, vecOrig.end());

    auto& vecDest = adyacencia[iDest];
    auto it2 = std::remove_if(vecDest.begin(), vecDest.end(),
        [iOrig](const std::pair<int, double>& p) { return p.first == iOrig; });
    vecDest.erase(it2, vecDest.end());

    std::cout << "Ruta eliminada correctamente.\n";
    return true;
}

void Grafo::listarCiudades() const {
    if (ciudades.empty()) {
        std::cout << "No hay ciudades registradas.\n";
        return;
    }
    std::cout << "\n=== CIUDADES REGISTRADAS ===\n";
    for (size_t i = 0; i < ciudades.size(); ++i) {
        std::cout << (i + 1) << ". " << ciudades[i] << "\n";
    }
    std::cout << "============================\n";
}

void Grafo::mostrarVecinos(const std::string& ciudad) const {
    int idx = indiceCiudad(ciudad);
    if (idx == -1) {
        std::cout << "Ciudad no encontrada.\n";
        return;
    }
    const auto& vecinos = adyacencia[idx];
    if (vecinos.empty()) {
        std::cout << "La ciudad '" << ciudad << "' no tiene rutas conectadas.\n";
        return;
    }
    std::cout << "Vecinos de '" << ciudad << "':\n";
    for (const auto& p : vecinos) {
        std::cout << "  -> " << ciudades[p.first] << " (" << p.second << " km)\n";
    }
}

void Grafo::mostrarTodasLasRutas() const {
    std::cout << "\n=== TODAS LAS RUTAS ===\n";
    bool alguna = false;
    for (size_t i = 0; i < adyacencia.size(); ++i) {
        for (const auto& p : adyacencia[i]) {
            if (static_cast<int>(i) < p.first) { // evitar duplicados
                std::cout << ciudades[i] << " <-> " << ciudades[p.first]
                          << " : " << p.second << " km\n";
                alguna = true;
            }
        }
    }
    if (!alguna) std::cout << "No hay rutas registradas.\n";
    std::cout << "=======================\n";
}

bool Grafo::existeCiudad(const std::string& nombre) const {
    return indiceCiudad(nombre) != -1;
}

int Grafo::numeroCiudades() const {
    return static_cast<int>(ciudades.size());
}
