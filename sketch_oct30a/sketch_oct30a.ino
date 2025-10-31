float temperatura = 25.0; 
int presion = 1000;       

long tiempoAnterior = 0;
const int intervalo = 2000; 


void setup() {
  Serial.begin(9600); 
  
  randomSeed(analogRead(0));
}


void loop() {
  long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;

    
    temperatura += (float)(random(-5, 6)) / 10.0; 
    
   
    presion += random(-2, 3); 

    
    Serial.print("T-001,T,");
    Serial.print(temperatura, 2); 
    Serial.print('\n'); 

   
    Serial.print("P-105,P,"); 
    Serial.print(presion); 
    Serial.print('\n');
  }
}