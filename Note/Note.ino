#include "App.h"

App app;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  app.Init_Server();
}

void loop() {
  // put your main code here, to run repeatedly:
 app.Manage_App();
 app.Close_Client_Connection();
 
// while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
     // currentTime = millis();  
     
}
