#include <iostream>
#include <cstring>
#include <typeinfo>
#include <vector>     
#include <sstream>   

// Incluye tus clases de cabecera
#include "ListaSensor.h"
#include "SensorBase.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "ListaGeneral.h" 



class SerialPortReader {
private:
    ListaGeneral& _listaGestion;

    // Función que simula el procesamiento y registro de datos recibidos por el serial
    void _procesarLinea(const std::string& linea) {
        // Formato esperado de la línea: ID,TIPO,VALOR (ej: T-001,T,45.3)
        std::stringstream ss(linea);
        std::string id, tipoStr, valorStr;
        
        // Deserialización: Separar los tres campos por comas
        std::getline(ss, id, ',');
        std::getline(ss, tipoStr, ',');
        std::getline(ss, valorStr, '\n');

        if (id.empty() || valorStr.empty()) return;

        // Busca el sensor en tu lista de gestión polimórfica
        SensorBase* sensor = _listaGestion.buscarPorNombre(id.c_str());

        if (sensor) {
            // Intenta registrar la lectura usando downcasting seguro
            if (tipoStr == "T") { // Temperatura (FLOAT)
                try {
                    float valor = std::stof(valorStr); 
                    SensorTemperatura* sTemp = dynamic_cast<SensorTemperatura*>(sensor);
                    if (sTemp) sTemp->registrarLectura(valor);
                } catch (const std::exception& e) {
                    std::cerr << "[Error Parsing] No se pudo convertir float para ID: " << id << "\n";
                }
            } else if (tipoStr == "P") { // Presión (INT)
                try {
                    int valor = std::stoi(valorStr); 
                    SensorPresion* sPres = dynamic_cast<SensorPresion*>(sensor);
                    if (sPres) sPres->registrarLectura(valor);
                } catch (const std::exception& e) {
                    std::cerr << "[Error Parsing] No se pudo convertir int para ID: " << id << "\n";
                }
            }
        }
    }

public:
    SerialPortReader(ListaGeneral& lista) : _listaGestion(lista) {
        std::cout << "[Serial Log] Lector serial inicializado.\n";
    }
    
    // Función de lectura simulada (cumple el requisito simulando la entrada serial)
    void leerDatosSimulados(const std::vector<std::string>& lineasSimuladas) {
        std::cout << "\nOpción 3: Registrar Lecturas (Simulación Serial)\n";
        for (const auto& linea : lineasSimuladas) {
            _procesarLinea(linea);
        }
    }
};



void registrarLectura(ListaGeneral& lista, const char* id, float valor) {
    SensorBase* sensor = lista.buscarPorNombre(id);

    if (!sensor) {
        std::cerr << "Error: Sensor con ID '" << id << "' no encontrado.\n";
        return;
    }

    // Intenta hacer un downcast seguro a SensorTemperatura
    SensorTemperatura* sTemp = dynamic_cast<SensorTemperatura*>(sensor);
    if (sTemp) {
        sTemp->registrarLectura(valor);
        return;
    }

    // Intenta hacer un downcast seguro a SensorPresion
    SensorPresion* sPres = dynamic_cast<SensorPresion*>(sensor);
    if (sPres) {
        // Nota: Si el valor es float (ej. 82.5), lo convertimos a int (82)
        sPres->registrarLectura(static_cast<int>(valor)); 
        return;
    }

    std::cerr << "Error: El tipo de sensor para ID '" << id << "' no coincide con la lectura.\n";
}




int main() {
    std::cout << "--- Sistema IoT de Monitoreo Polimórfico ---\n\n";

    
    ListaGeneral listaGestion;

  
    std::cout << "Opción 1: Crear Sensores\n";
    
    SensorTemperatura* temp = new SensorTemperatura("T-001");
    SensorPresion* pres = new SensorPresion("P-105");

    listaGestion.insertar(temp);
    listaGestion.insertar(pres);
    
    std::cout << "\n-------------------------------------------\n";
    
    
    std::vector<std::string> datosSimulados = {
        "T-001,T,45.3",
        "P-105,P,80",
        "T-001,T,42.1",
        "P-105,P,85",
        "T-001,T,46.5"
    };
    
    SerialPortReader lector(listaGestion);
    lector.leerDatosSimulados(datosSimulados); 

    std::cout << "\n-------------------------------------------\n";

  
    std::cout << "Opción 4: Ejecutar Procesamiento Polimórfico\n";
    listaGestion.procesarTodo(); // Llamada polimórfica a procesarLectura()
    
    std::cout << "\n-------------------------------------------\n";

  
    std::cout << "Opción 5: Cerrar Sistema (Liberar Memoria)\n";
   

    std::cout << "\n--- Liberación de Memoria en Cascada ---\n";
    
    return 0;
}