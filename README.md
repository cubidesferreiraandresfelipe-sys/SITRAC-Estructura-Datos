# SITRAC - Sistema Inteligente de Transporte y Gestión de Rutas

**Taller de Estructura de Datos | C++ | 12 de noviembre de 2026**

Implementación modular del núcleo funcional del sistema SITRAC con estructuras de datos propias.

## Compilación

Desde la carpeta raíz del proyecto:

```bash
g++ -std=c++17 -o sitrac src/main.cpp src/Pasajero.cpp src/Cola.cpp src/Grafo.cpp
```

O usar el Makefile incluido:

```bash
make
./sitrac
```

## Diagrama modular (texto)

```
main()
  ├── Menú Principal (loop persistente)
  │     ├── 1. menuCiudades() → Grafo
  │     ├── 2. menuRutas() → Grafo
  │     ├── 3. menuPasajeros() → ListaPasajeros
  │     ├── 4. menuCola() → ColaSolicitudes + Grafo
  │     ├── 5. menuHistorial() (pendiente)
  │     ├── 6. menuBusquedas()
  │     ├── 7. menuReportes()
  │     └── 8. menuArchivos() (pendiente)
  └── Estructuras:
        ├── ListaPasajeros (lista enlazada propia)
        ├── ColaSolicitudes (cola enlazada propia)
        └── Grafo (lista de adyacencia)
```

## Tabla de estructuras

| Operación                  | Estructura usada     | Justificación |
|---------------------------|----------------------|---------------|
| Insertar/Buscar/Actualizar/Eliminar/Listar pasajeros | Lista enlazada propia (ListaPasajeros) | Requerimiento explícito: sin std::list. Insertar al frente, búsqueda lineal, eliminación segura. |
| Encolar / Atender / Mostrar frente solicitudes | Cola enlazada propia (ColaSolicitudes) | Requerimiento: sin std::queue. FIFO con punteros frente/final. |
| Alta ciudad, alta/baja ruta, vecinos | Grafo con lista de adyacencia (vector de vectores de pares) | Estructura justificada para grafo no dirigido ponderado. Eliminación de ciudad actualiza índices y elimina referencias (CP-05). |
| Validación de entradas    | Funciones leerEntero/leerDouble + cin.clear/ignore | Manejo de letras donde se espera número (CP-06). |

## Funcionalidades terminadas

- [x] Menú principal persistente con submenús y opción Volver
- [x] Lista enlazada propia de pasajeros (insertar, buscar, actualizar, eliminar, listar) — sin std::list
- [x] Grafo con lista de adyacencia: agregar/eliminar ciudad, agregar/eliminar ruta, vecinos, listados
- [x] Cola enlazada propia de solicitudes (encolar, atender, mostrar frente) — sin std::queue
- [x] Manejo de errores: duplicados (CP-01), pasajero inexistente (CP-02), cola vacía (CP-03), distancia negativa (CP-04), eliminación de ciudad conectada sin referencias colgantes (CP-05), entradas no numéricas (CP-06)
- [x] Reportes básicos y búsquedas simples
- [x] El sistema no termina ante operaciones fallidas

## Funcionalidades pendientes

- [ ] Historial completo de viajes atendidos (estructura sugerida: lista o pila)
- [ ] Persistencia en archivos (guardar/cargar ciudades, pasajeros, rutas, cola)
- [ ] Búsquedas avanzadas (por nombre parcial, rutas más cortas con Dijkstra, etc.)
- [ ] Validación de existencia de pasajero al encolar solicitud
- [ ] Interfaz más pulida y más reportes

## Casos de prueba obligatorios (cómo probarlos)

| Caso | Cómo probarlo | Resultado esperado |
|------|---------------|--------------------|
| CP-01 | Ciudades → Agregar "Bogotá" dos veces | Rechaza el duplicado |
| CP-02 | Pasajeros → Eliminar un ID que no existe | Informa sin romper la lista |
| CP-03 | Cola → Atender cuando está vacía | Mensaje de subdesbordamiento |
| CP-04 | Rutas → Agregar ruta con distancia -5 | Rechaza el peso inválido |
| CP-05 | Agregar ciudad + ruta → Eliminar la ciudad | No quedan referencias colgantes |
| CP-06 | En cualquier menú escribir "abc" donde se pide número | Recupera y pide de nuevo sin ciclo infinito |

## Uso de IA

Este código fue generado con asistencia de Grok (xAI). Se revisó y corrigió:

- Manejo correcto de punteros y memoria en listas y cola.
- Actualización de índices al eliminar ciudades en el grafo.
- Limpieza de buffer de entrada para evitar ciclos infinitos.
- Separación modular de menús y estructuras.

## Estructura del repositorio

```
README.md
Makefile
src/
  main.cpp
  Pasajero.h / Pasajero.cpp
  Cola.h / Cola.cpp
  Grafo.h / Grafo.cpp
```

---

**Criterio de salida de la sesión cumplido**: Menú compila, regresa a submenús, operaciones reales en Ciudades, Rutas, Pasajeros y Cola, supera CP-01/02/03, y tiene commit verificable.
