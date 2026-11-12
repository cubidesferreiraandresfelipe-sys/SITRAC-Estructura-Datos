#include <iostream>
#include <limits>
#include <string>
#include "Pasajero.h"
#include "Cola.h"
#include "Grafo.h"

// Utilidad para limpiar entrada errónea
void limpiarEntrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int leerEntero(const std::string& mensaje) {
    int valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor) {
            limpiarEntrada(); // limpiar resto de línea
            return valor;
        } else {
            std::cout << "Entrada inválida. Por favor ingrese un número.\n";
            limpiarEntrada();
        }
    }
}

double leerDouble(const std::string& mensaje) {
    double valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor) {
            limpiarEntrada();
            return valor;
        } else {
            std::cout << "Entrada inválida. Por favor ingrese un número.\n";
            limpiarEntrada();
        }
    }
}

std::string leerCadena(const std::string& mensaje) {
    std::string s;
    std::cout << mensaje;
    std::getline(std::cin, s);
    return s;
}

// Submenús
void menuCiudades(Grafo& grafo) {
    int opcion;
    do {
        std::cout << "\n--- SUBMENÚ CIUDADES ---\n";
        std::cout << "1. Agregar ciudad\n";
        std::cout << "2. Eliminar ciudad\n";
        std::cout << "3. Listar ciudades\n";
        std::cout << "4. Mostrar vecinos de una ciudad\n";
        std::cout << "0. Volver\n";
        opcion = leerEntero("Seleccione: ");

        switch (opcion) {
            case 1: {
                std::string nombre = leerCadena("Nombre de la ciudad: ");
                grafo.agregarCiudad(nombre);
                break;
            }
            case 2: {
                std::string nombre = leerCadena("Nombre de la ciudad a eliminar: ");
                grafo.eliminarCiudad(nombre);
                break;
            }
            case 3:
                grafo.listarCiudades();
                break;
            case 4: {
                std::string nombre = leerCadena("Nombre de la ciudad: ");
                grafo.mostrarVecinos(nombre);
                break;
            }
            case 0:
                std::cout << "Volviendo al menú principal...\n";
                break;
            default:
                std::cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

void menuRutas(Grafo& grafo) {
    int opcion;
    do {
        std::cout << "\n--- SUBMENÚ RUTAS ---\n";
        std::cout << "1. Agregar ruta\n";
        std::cout << "2. Eliminar ruta\n";
        std::cout << "3. Mostrar todas las rutas\n";
        std::cout << "0. Volver\n";
        opcion = leerEntero("Seleccione: ");

        switch (opcion) {
            case 1: {
                std::string orig = leerCadena("Ciudad origen: ");
                std::string dest = leerCadena("Ciudad destino: ");
                double dist = leerDouble("Distancia (km, positiva): ");
                grafo.agregarRuta(orig, dest, dist);
                break;
            }
            case 2: {
                std::string orig = leerCadena("Ciudad origen: ");
                std::string dest = leerCadena("Ciudad destino: ");
                grafo.eliminarRuta(orig, dest);
                break;
            }
            case 3:
                grafo.mostrarTodasLasRutas();
                break;
            case 0:
                std::cout << "Volviendo al menú principal...\n";
                break;
            default:
                std::cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

void menuPasajeros(ListaPasajeros& lista) {
    int opcion;
    do {
        std::cout << "\n--- SUBMENÚ PASAJEROS ---\n";
        std::cout << "1. Registrar pasajero\n";
        std::cout << "2. Buscar pasajero\n";
        std::cout << "3. Actualizar pasajero\n";
        std::cout << "4. Eliminar pasajero\n";
        std::cout << "5. Listar todos\n";
        std::cout << "0. Volver\n";
        opcion = leerEntero("Seleccione: ");

        switch (opcion) {
            case 1: {
                int id = leerEntero("ID del pasajero: ");
                std::string nombre = leerCadena("Nombre: ");
                std::string doc = leerCadena("Documento: ");
                lista.insertar(id, nombre, doc);
                break;
            }
            case 2: {
                int id = leerEntero("ID a buscar: ");
                Pasajero* p = lista.buscar(id);
                if (p) {
                    std::cout << "Encontrado: " << p->nombre << " | Doc: " << p->documento << "\n";
                } else {
                    std::cout << "Pasajero no encontrado.\n";
                }
                break;
            }
            case 3: {
                int id = leerEntero("ID a actualizar: ");
                std::string nombre = leerCadena("Nuevo nombre: ");
                std::string doc = leerCadena("Nuevo documento: ");
                lista.actualizar(id, nombre, doc);
                break;
            }
            case 4: {
                int id = leerEntero("ID a eliminar: ");
                lista.eliminar(id);
                break;
            }
            case 5:
                lista.listar();
                break;
            case 0:
                std::cout << "Volviendo al menú principal...\n";
                break;
            default:
                std::cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

void menuCola(ColaSolicitudes& cola, const Grafo& grafo) {
    int opcion;
    do {
        std::cout << "\n--- SUBMENÚ COLA DE SOLICITUDES ---\n";
        std::cout << "1. Encolar solicitud de viaje\n";
        std::cout << "2. Atender (desencolar) solicitud\n";
        std::cout << "3. Mostrar frente\n";
        std::cout << "0. Volver\n";
        opcion = leerEntero("Seleccione: ");

        switch (opcion) {
            case 1: {
                int id = leerEntero("ID del pasajero: ");
                std::string orig = leerCadena("Ciudad origen: ");
                std::string dest = leerCadena("Ciudad destino: ");
                if (!grafo.existeCiudad(orig) || !grafo.existeCiudad(dest)) {
                    std::cout << "Error: Una o ambas ciudades no existen en el sistema.\n";
                } else {
                    cola.encolar(id, orig, dest);
                }
                break;
            }
            case 2: {
                int id;
                std::string orig, dest;
                cola.atender(id, orig, dest);
                break;
            }
            case 3:
                cola.mostrarFrente();
                break;
            case 0:
                std::cout << "Volviendo al menú principal...\n";
                break;
            default:
                std::cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

// Menús pendientes (stubs funcionales básicos)
void menuHistorial() {
    std::cout << "\n--- HISTORIAL ---\n";
    std::cout << "Funcionalidad pendiente: registro de viajes atendidos.\n";
    std::cout << "Presione Enter para volver...";
    std::cin.get();
}

void menuBusquedas(const Grafo& grafo, const ListaPasajeros& lista) {
    std::cout << "\n--- BÚSQUEDAS ---\n";
    std::cout << "1. Buscar ciudad\n2. Buscar pasajero\n0. Volver\n";
    int op = leerEntero("Seleccione: ");
    if (op == 1) {
        std::string c = leerCadena("Ciudad: ");
        std::cout << (grafo.existeCiudad(c) ? "Existe.\n" : "No existe.\n");
    } else if (op == 2) {
        // Nota: buscar requiere no const, pero para demo
        std::cout << "Use el submenú Pasajeros para búsquedas detalladas.\n";
    }
}

void menuReportes(const Grafo& grafo, const ListaPasajeros& lista, const ColaSolicitudes& cola) {
    std::cout << "\n=== REPORTES ===\n";
    std::cout << "Ciudades registradas: " << grafo.numeroCiudades() << "\n";
    std::cout << "Pasajeros registrados: " << lista.contar() << "\n";
    std::cout << "Solicitudes en cola: " << cola.contar() << "\n";
    std::cout << "=================\n";
}

void menuArchivos() {
    std::cout << "\n--- GUARDAR / CARGAR ---\n";
    std::cout << "Funcionalidad de persistencia pendiente (se puede implementar con archivos de texto).\n";
    std::cout << "Presione Enter para volver...";
    std::cin.get();
}

int main() {
    Grafo grafo;
    ListaPasajeros pasajeros;
    ColaSolicitudes cola;

    // Datos de ejemplo para pruebas rápidas (opcional)
    grafo.agregarCiudad("Bogotá");
    grafo.agregarCiudad("Medellín");
    grafo.agregarRuta("Bogotá", "Medellín", 250.0);

    int opcion;
    do {
        std::cout << "\n========== SITRAC - MENÚ PRINCIPAL ==========\n";
        std::cout << "1. Ciudades\n";
        std::cout << "2. Rutas\n";
        std::cout << "3. Pasajeros\n";
        std::cout << "4. Cola\n";
        std::cout << "5. Historial\n";
        std::cout << "6. Búsquedas\n";
        std::cout << "7. Reportes\n";
        std::cout << "8. Guardar/Cargar\n";
        std::cout << "0. Salir\n";
        std::cout << "============================================\n";
        opcion = leerEntero("Seleccione una opción: ");

        switch (opcion) {
            case 1: menuCiudades(grafo); break;
            case 2: menuRutas(grafo); break;
            case 3: menuPasajeros(pasajeros); break;
            case 4: menuCola(cola, grafo); break;
            case 5: menuHistorial(); break;
            case 6: menuBusquedas(grafo, pasajeros); break;
            case 7: menuReportes(grafo, pasajeros, cola); break;
            case 8: menuArchivos(); break;
            case 0: std::cout << "Saliendo del sistema. ¡Hasta pronto!\n"; break;
            default: std::cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}
