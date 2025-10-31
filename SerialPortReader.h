// Archivo: SerialPortReader.h

#include "ListaGeneral.h" // Para acceder a los sensores


class SerialPortReader {
private:
    ListaGeneral& _listaGestion; // Referencia a tu lista de sensores
    


    void _procesarLinea(const std::string& linea) {
       
        std::stringstream ss(linea);
        std::string id, tipoStr, valorStr;
        
     
        std::getline(ss, id, ',');
        std::getline(ss, tipoStr, ',');
        std::getline(ss, valorStr, '\n');

        
        SensorBase* sensor = _listaGestion.buscarPorNombre(id.c_str());

        if (sensor) {
            if (tipoStr == "T") {
                // Es temperatura (float)
                float valor = std::stof(valorStr); 
                SensorTemperatura* sTemp = dynamic_cast<SensorTemperatura*>(sensor);
                if (sTemp) sTemp->registrarLectura(valor);
            } else if (tipoStr == "P") {
                // Es presión (int)
                int valor = std::stoi(valorStr);
                SensorPresion* sPres = dynamic_cast<SensorPresion*>(sensor);
                if (sPres) sPres->registrarLectura(valor);
            }
        }
    }

public:
    SerialPortReader(ListaGeneral& lista) : _listaGestion(lista) {
        
    }
    
    // Función de lectura simulada (para evitar dependencias externas)
    void leerDatosSimulados(const std::vector<std::string>& lineasSimuladas) {
        std::cout << "\n--- SIMULACIÓN DE LECTURA SERIAL ---\n";
        for (const auto& linea : lineasSimuladas) {
            _procesarLinea(linea);
        }
    }
    
    
};