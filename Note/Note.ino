#include "App.h"
#include "Screen.h"

App app;
Screen screen;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  app.Init_Server();

  //screen.Init_Screen();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  app.Start_Client_Connection();
  app.Manage_App();
  app.Close_Client_Connection();
 
  //screen.Display_All_Notes();
     
}
