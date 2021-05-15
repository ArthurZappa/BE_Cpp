#include "App.h"
#include "Screen.h"
#include "Micro.h"
#include "Note.h"
#include "Sheet.h"


App app;

Screen screen;
Micro micro;
Sheet sheet;
//Note note;

  
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //app.Init_Server();
  micro.Init_Micro();
  screen.Init_Screen();
}

void loop() {
  // put your main code here, to run repeatedly:
  //app.Start_Client_Connection();
  //app.Manage_App();
  //app.Close_Client_Connection();
  
while (analogRead(A0) < 250) {
  //do nothing --> wait until we detect the first note so that the software is coordinate with the user
}
  micro.Manage_Micro();
 
  screen.Recognize_Display(); 
  sheet.Recognize_Duration();

  //delay(500);
}
