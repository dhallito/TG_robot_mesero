/*#include "com_wifi.h"
WiFiServer server(80);
WiFiClient client = server.available();

void Com_Wifi::wifi_setup(){
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    // Parpadear un led
    delay(500);
  }
  String LOCAL_IP = String(WiFi.localIP());
  Serial.print("Conectando con IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void Com_Wifi::wifi_request(){
  client = server.available();
  if (client){
    // Se indica que el cliente está haciendo un request
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          wifi_interpretar(header);
          header = "";
        }
        else if (c != '\r') {
          header += c;
        }
      }
    }
    client.stop();
  }
}

void Com_Wifi::wifi_interpretar(String header){
  if (header.indexOf("LUZ_ON") != -1){
    Serial.println("Luz Encendida");
    digitalWrite(32, HIGH);
    client.print("Luz ON");
  }
  else if (header.indexOf("LUZ_OFF") != -1){
    Serial.println("Luz Apagada");
    digitalWrite(32, LOW);
    client.print("Luz OFF");
  }
}*/
