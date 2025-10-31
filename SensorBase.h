#include <cstring> // Necesario para strncpy

#ifndef SENSORBASE_H         
#define SENSORBASE_H         
 
class SensorBase {

protected: 
 char nombre[50];//Atributo protegido (solo accesible por derivados) para el identificador.

public:
//Constructor: Inicializa el nombre del sensor.
    SensorBase(const char* id) {
        strncpy(nombre, id, 49); // Copia segura del string, max 49 chars
        nombre[49] = '\0'; // Asegura la terminación nula
    }

    //destructor virtual crititico:

    virtual ~SensorBase() {}

    //Metodos virtuales puros:
    virtual void procesarLectura() = 0; // Lógica específica (ej. calcular promedio, eliminar mínimo)
    virtual void imprimirInfo() const = 0; // Información de identificación
    
    // Método común
    const char* getNombre() const { return nombre; }


};
#endif // SENSORBASE_H