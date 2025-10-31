#include <iostream>
#include <typeinfo>

#ifndef LISTASENSOR_H
#define LISTASENSOR_H

template <typename T> // es el indicador de la plantilla que este sera remplasado por un tipo real
class ListaSensor
{
private:
    // Aqui es la estructura del Nodo anidad y privada. Y que solo es accesible desde ListaSensor <T>

    struct Nodo // 
    {
        T dato;             // dato génerico ya que puede ser cuaquie tipo que se defina
        Nodo *siguiente;

        // constrcutor simple del nodo usando const t& que es una referencia de constante para evitar copias innecesarias del dato
        Nodo(const T &val) : dato(val), siguiente(nullptr) {}
    };

    // Puntero privado a la cabeza de la lista es el primer nodo
    Nodo *_cabeza; 
    int _tamano; 

    // Funciones auxiliares

    // Funcion que nos ayudara a limpiar la memoria de todos los nodos misma
    // que es llamada por el destructor y el operadr de asignación

    void _liberarMemoria()
    {
        Nodo *actual = _cabeza; 
        while (actual != nullptr)
        {                                // Itera mientras haya nodos en la lista
            Nodo *aEliminar = actual; 
            actual = actual->siguiente;  // Avanza al siguiente ANTES de eliminar el actual

            // Muestra un mensaje de log detallado sobre lo que se está liberando.
          
            std::cout << "[Log] Nodo<" << typeid(T).name() << "> " << aEliminar->dato << " liberado.\n";
            delete aEliminar;
        }
        _cabeza = nullptr; // Reinicia la lista a un estado limpio (vacío)
        _tamano = 0;
    }

    // Función que nos ayudara a realizar una copia mas profunda de otra lista
    void _copiaProfunda(const ListaSensor &otra)
    {
        _cabeza = nullptr;
        _tamano = 0;
        Nodo *actualOtra = otra._cabeza; 
        while (actualOtra != nullptr)
        {
            // Inserta el DATO de la lista 'otra' en la lista actual.
            // Esto crea NUEVOS NODOS en la memoria (deep copy).
            this->insertarAlFinal(actualOtra->dato);
            actualOtra = actualOtra->siguiente;
        }
    }

public:
    // Constructor por defecto que inicializa la lista vacia

    ListaSensor() : _cabeza(nullptr), _tamano(0) {} 
  

    ~ListaSensor()
    {
        _liberarMemoria(); // Llama a la función auxiliar para limpiar la memoria de todos los nodos.
    }

    // 2. Constructor de copia
    ListaSensor(const ListaSensor &otra)
    {
        _copiaProfunda(otra); // Asegura que la copia crea NUEVOS NODOS y no solo copia punteros.
    }

    //3. Operador de asignación se encarga de la reaisgnacion de objetos existentes 
    ListaSensor& operator=(const ListaSensor& otra) {
        if (this != &otra) { 
            _liberarMemoria(); // Primero, elimina todos los nodos de la lista actual (listaA).
            _copiaProfunda(otra); // Luego, copia profundamente los nodos de la lista de origen (listaB).
        }
        return *this; // Devuelve una referencia al objeto actual para permitir el encadenamiento (a = b = c).
    }


    //Funciones principales 
    void insertarAlFinal(const T& valor) {
        Nodo* nuevoNodo = new Nodo(valor);
        if (_cabeza == nullptr) {
            _cabeza = nuevoNodo;
        } else { 
            Nodo* actual = _cabeza; 
            while (actual->siguiente != nullptr) { // Recorre la lista hasta el último nodo
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo; // El último nodo ahora apunta al nuevo nodo
        }
        _tamano++;
        std::cout << "[Log] Insertando Nodo<" << typeid(T).name() << "> " << valor << ".\n";
    }
    
    // Métodos para acceder al estado de la lista
    Nodo* getCabeza() const { return _cabeza; } 
    int getTamano() const { return _tamano; }
};

#endif 