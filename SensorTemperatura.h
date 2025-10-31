#include "SensorBase.h"
#include "ListaSensor.h" 

#ifndef SENSORTEMPERATURA_H
#define SENSORTEMPERATURA_H

class SensorTemperatura : public SensorBase {
private:
    //  Historial específico para floats (lecturas de temperatura)
    ListaSensor<float> historial; 

public:
    // Llama al constructor de la clase base.
    SensorTemperatura(const char* id) : SensorBase(id) {}


    ~SensorTemperatura() override { 
        std::cout << "  [Destructor Sensor " << getNombre() << "] Liberando Lista Interna...\n";
    }

    void registrarLectura(float lectura) {
        historial.insertarAlFinal(lectura); // Usa la ListaSensor<float>
    }

    void procesarLectura() override { 
       
        std::cout << "-> Procesando Sensor " << getNombre() << "...\n";
        
        if (historial.getTamano() > 0) {
            float suma = 0.0;
            auto* actual = historial.getCabeza(); // Acceso al nodo inicial
            while (actual) {
                suma += actual->dato;
                actual = actual->siguiente;
            }
            float promedio = suma / historial.getTamano();
            std::cout << "[Sensor Temp] Promedio calculado sobre " << historial.getTamano() << " lectura(s) (" << promedio << ").\n";
        } else {
            std::cout << "[Sensor Temp] No hay lecturas para procesar.\n";
        }
    }

    void imprimirInfo() const override {
        std::cout << "Sensor: " << getNombre() << " (Temperatura - FLOAT)\n";
    }
};

#endif 