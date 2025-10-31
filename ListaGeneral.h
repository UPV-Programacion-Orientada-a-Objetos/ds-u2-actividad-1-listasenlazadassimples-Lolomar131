#include "SensorBase.h" 
#include <iostream>
#include <cstring>

#ifndef LISTAGENERAL_H
#define LISTAGENERAL_H

class ListaGeneral {
private:
    struct NodoGeneral {
        SensorBase* sensor; // ⬅Almacena punteros a la clase base 
        NodoGeneral* siguiente;
        NodoGeneral(SensorBase* s) : sensor(s), siguiente(nullptr) {}
    };

    NodoGeneral* _cabeza;

public:
    ListaGeneral() : _cabeza(nullptr) {}

    //  Responsable de liberar los nodos de la ListaGeneral Y los objetos SensorBase* que contienen.
    ~ListaGeneral() {
        NodoGeneral* actual = _cabeza;
        while (actual != nullptr) {
            NodoGeneral* aEliminar = actual;
            actual = actual->siguiente;
            
            std::cout << "[Destructor General] Liberando Nodo: " << aEliminar->sensor->getNombre() << ".\n";
            
            // Aquí se activa el POLIMORFISMO en el destructor.
            delete aEliminar->sensor; 
            
            // Libera el NodoGeneral de la ListaGeneral.
            delete aEliminar; 
        }
        _cabeza = nullptr;
    }

    // Método para insertar un puntero polimórfico a la lista.
    void insertar(SensorBase* nuevoSensor) {
        NodoGeneral* nuevoNodo = new NodoGeneral(nuevoSensor);
        nuevoNodo->siguiente = _cabeza; // Inserción simple al inicio
        _cabeza = nuevoNodo;
        std::cout << "Sensor '" << nuevoSensor->getNombre() << "' creado e insertado en la lista de gestión.\n";
    }

    // Método que demuestra el polimorfismo en acción.
    void procesarTodo() {
        std::cout << "\n--- Ejecutando Polimorfismo ---\n";
        NodoGeneral* actual = _cabeza;
        while (actual != nullptr) {
            // Se llama a la función 'procesarLectura' de la clase DERIVADA real, 
            // aunque el puntero sea de tipo SensorBase*.
            actual->sensor->procesarLectura(); 
            actual = actual->siguiente;
        }
    }
    
    // Método para buscar un sensor y acceder a sus métodos específicos 
    SensorBase* buscarPorNombre(const char* nombre) {
        NodoGeneral* actual = _cabeza;
        while (actual != nullptr) {
            if (strcmp(actual->sensor->getNombre(), nombre) == 0) {
                return actual->sensor; // Retorna el puntero base
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }
};

#endif // LISTAGENERAL_H