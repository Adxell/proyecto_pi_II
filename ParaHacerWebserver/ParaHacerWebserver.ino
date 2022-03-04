#include <WiFi.h> 
#include <Wire.h>
String cadena;

#define RXD2 16
#define TXD2 17

const char* ssid = "TIGO-50CD"; 
const char* password = "";
WiFiServer server(80);
void setup() {
Serial.begin(9600);
Serial2.begin(9600,SERIAL_8N1,RXD2,TXD2);
//Nos conectamos a la red 
Serial.print("Conectando a la red WiFi");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("Conectado con éxito a la red WiFi.");
Serial.println("La dirección IP es: ");
Serial.println(WiFi.localIP());
server.begin();
Serial.println("Servidor iniciado");
delay(2000);
}
void loop()
{
   if (Serial2.available())  {
    cadena = String("");
    while (Serial2.available()) {
      cadena = cadena + char(Serial2.read());
      delay(1);
    }
   }

WiFiClient client = server.available();
if (client)
{ 
Serial.println("Cliente web conectado ");
String request = client.readStringUntil('\r'); 
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println("Refresh: 10");
client.println();
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");
client.println("</style></head><body><h1>Rastreador presentado por Adxell Arango y Carlos Padilla </h1>");
client.println("<h2>Tipo de GPS: GT-U7</h2>");
client.println("<table><tr><th>Datos Obtenidos</th><th>Ubicacion</th></tr>");
client.println("<tr><td>Latitud y longitud:</td><td><span class=\"sensor\">");
client.println("<a href=");
client.println(cadena);
client.println(">");
client.println(cadena);
client.println("</a>");
client.println("</span></td></tr>"); 
client.println("</body></html>"); 
client.stop();
client.println();
Serial.println("Client disconnected.");
Serial.println("");
}
}
