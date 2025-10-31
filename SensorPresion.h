#include "SensorBase.h"
#include "ListaSensor.h" // Se necesita la definición de la lista genérica

#ifndef SENSORPRESION_H
#define SENSORPRESION_H

class SensorPresion : public SensorBase {
private:
    //  Historial específico para enteros (lecturas de presión)
    ListaSensor<int> historial; 

public:
    // Llama al constructor de la clase base.
    SensorPresion(const char* id) : SensorBase(id) {}

    // Destructor (Necesario para el log y para asegurar la liberación del historial)
    ~SensorPresion() override { 
        std::cout << "  [Destructor Sensor " << getNombre() << "] Liberando Lista Interna...\n";
    }

    // Método específico para agregar lecturas enteras
    void registrarLectura(int lectura) {
        historial.insertarAlFinal(lectura);
    }

    // Lógica específica para Sensores de Presión 
    void procesarLectura() override { 
        std::cout << "-> Procesando Sensor " << getNombre() << "...\n";
        
        if (historial.getTamano() > 0) {
            int suma = 0;
            auto* actual = historial.getCabeza(); 
            while (actual) {
                suma += actual->dato;
                actual = actual->siguiente;
            }
            float promedio = (float)suma / historial.getTamano();
            std::cout << "[Sensor Presion] Promedio calculado sobre " << historial.getTamano() << " lectura(s) (" << promedio << ").\n";
        } else {
            std::cout << "[Sensor Presion] No hay lecturas para procesar.\n";
        }
    }

    void imprimirInfo() const override {
        std::cout << "Sensor: " << getNombre() << " (Presión - INT)\n";
    }
};

#endif 