#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial ss(4, 3);
void setup()
{
  Serial.begin(9600);
  ss.begin(9600);
  Serial.println("Iniciando envío de coordenadas con TinyGPS v. "); Serial.println(TinyGPS::library_version());
}
void loop()
{
  bool nuevosDatos = false;
  unsigned long caracteres;
  unsigned short sentencias, fallas;

  
  for (unsigned long start = millis(); millis() - start < 5000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      if (gps.encode(c)) 
        nuevosDatos = true;
    }
  }
  if (nuevosDatos)
  {
    float flat, flon;
    gps.f_get_position(&flat, &flon);
    Serial.print("https://maps.google.com/maps?q=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(",");
    Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  }

  gps.stats(&caracteres, &sentencias, &fallas);
  if (caracteres == 0)
    Serial.println("*No se han recibido caracteres del GPS*");
}
