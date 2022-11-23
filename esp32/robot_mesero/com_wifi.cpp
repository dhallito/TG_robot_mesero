#include "com_wifi.h"

AsyncWebServer server(80);

void setup_server(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    
    int paramsNr = request->params();
    if (paramsNr == 1){
      String json = "{\"nodo_actual\": \"" + String(nodo_actual) + "\", \"angulo_absoluto\": \"" + String(angulo_absoluto) + "\"}"; 
      request->send(200, "text/plain", json);
    }else if(paramsNr == 3){
      AsyncWebParameter* cantidad; 
      cantidad = request->getParam(1);
      ruta_size = (cantidad->value().toInt());
      
      AsyncWebParameter* recorrido;
      recorrido = request->getParam(2);
      for (int i = 0; i < ruta_size; i++) {
        ruta[i] = recorrido->value()[i];
      }
      iniciando_robot = true;
      nueva_ruta = true;
      Serial.println("Nueva Ruta");
      request->send(200, "text/plain", "ok");
    } 
  });
 
  server.begin();
}
