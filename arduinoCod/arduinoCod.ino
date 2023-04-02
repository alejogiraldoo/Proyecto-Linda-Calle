// Permite trabajar con el hardware directamente del MODULO-GPS
#include<SoftwareSerial.h>
// Permite interpretar los datos enviados por el GPS(los datos son enviados en codigo NMEA -> National Marine Electronics Asociation)
#include<TinyGPS.h>// TYNYGPS

#include <WiFiManager.h> // Hace que el ESP8266 se convierta en una "access Point" para configurar la red Wifi 
#include <ESP8266HTTPClient.h> // Libreria para enviar la información al localhost
#include <WiFiClient.h>
WiFiClient client; // Creamos un objeto de tipo WifiClient para realizar la conexion al localhost (Sin el cliente ('La peticíon') no podemos acceder)

#include <Ticker.h> // LIBRERIA PARA CREAR PROCESOS (Temporizador)
#define pinLedWifi D4 // LED SENTINELA DE LA CONEXION WIFI
Ticker ticker; // CREAMOS UN OBJETO PARA REALIZAR UN PROCESO

// FUNCIÓN PARA EL LED SENTINELA
void blinkLed(){
  // Cambia el estado del LED
  byte estado = digitalRead(pinLedWifi);
  digitalWrite(pinLedWifi, !estado);
}

// VARIABLES
float flat, flon;
String userId = "1234"; // IDENTIFICACIÓN DEL DISPOSITIVO EN LA BASE DE DATOS

// ____________________FORMATO DE LA URL____________________
String protocol = "http://";
String host = "lindacalle.000webhostapp.com";
String resource = "/servidoriot/save.php";
int port = 80;

// GUARDAMOS LA URL QUE DIRECCIÓNA AL RECURSO DE LA PAGINA GUARDADA EN EL HOST LOCAL (COMPUTADOR)
String url = protocol + host + resource;

// ____________________MODULO GPS____________________
// DECLARAMOS UN OBJETO DE TIPO SOFTWARE-SERIAL
SoftwareSerial ss(D2,D1); // TX/RX
// DECLARAMOS UN OBJETO DE TIPO TINY-GPS
TinyGPS gps;

void setup() {
  // MODULO GPS
  Serial.begin(115200);
  // LE DECIMOS AL MODULO GPS QUE ME ENVIE LOS DATOS A LA VELOCIDAD DE 9600 baudios
  ss.begin(9600);

  // MODULO ESP8266
  // Modo del pin
  pinMode(pinLedWifi, OUTPUT);
  // Empezamos el temporizador que hará parpadear el LED
  ticker.attach(0.2, blinkLed); // SE EJECUTA CADA 200ms

  // ESP8266
  WiFiManager wifiManager; // Creamos un objeto de tipo WiFiManager
  // BORRA LAS CREDENCIALES DE LA RED WIFI 
  // wifiManager.resetSettings();
  // Creamos AP y portal cautivo
                          // (nombre, contraseña -> 8 a 64 caracteres)
  if (!wifiManager.autoConnect("ESP8266")){// Busca la RED WIFI que el ESP8266 se habia conectado la ultima vez para conectarse nuevamente
    Serial.println("Fallo en la conexión (timeout)");
    ESP.reset();
    delay(1000);
  } 
  // Nota: El modulo NodeMCU guarda los datos de la red a la cual el dispositivo se conecto la ultima vez (CREDENCIALES); Si no se conecta va a levantar un acces point en la red
  Serial.println("Ya estás conectado");
  // Eliminamos el temporizador
  ticker.detach();

  // Apagamos el LED
  digitalWrite(pinLedWifi, HIGH);
}

void loop() {
  // ____________________OBJETO DE COMUNICACIÓN____________________
  HTTPClient http; // Creamos un objeto de tipo HTTPClient
  http.begin(client,url); // Destino del mensaje 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  if(ss.available()>0){
    // VERIFICA LA CONVERCIÓN DE INFORMACIÓN DE NMEA A COORDENADAS POLARES LEIBLES(LAT,LNG)
    if(gps.encode(ss.read())){
      // VARIABLES (LAT,LON)
      gps.f_get_position(&flat, &flon);
      Serial.println(String(flat,15) + "," + String(flon,15));

      String postData = "userId=" + userId + "&longitud=" + String(flon,15) + "&latitud=" + String(flat,15);
      int httpCode= http.POST(postData); // Envia los datos
      String answer = http.getString(); // obtiene la respuesta del servidor

      Serial.println(httpCode);
      Serial.println(answer);

      http.end(); // Cerramos la conexion
    }
  }
}
