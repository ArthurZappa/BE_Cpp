#include "App.h"
#include "Screen.h"
//#include "Micro.h"
#include "Note.h"
//#include "Sheet.h"


App app;
Screen screen;
//Micro micro;
//Sheet sheet;
Note note;

  
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  app.Init_Server();
  //micro.Init_Micro();
  screen.Init_Screen();
}

void loop() {
  // put your main code here, to run repeatedly:

 if (app.Get_Tempo() == 0) {
  app.Start_Client_Connection();
  app.Manage_App(note.Get_Name(0), note.Get_Duration());
  app.Close_Client_Connection();
 }
 else {
    while (analogRead(A0) < 250) {
    //do nothing --> wait until we detect the first note so that the software is coordinate with the user 
    }
    while (1) {
      //micro.Manage_Micro();
      note.Recognize_Name();
      note.Recognize_Duration();
      
      screen.Display(); 
      
      app.Start_Client_Connection();
      app.Manage_App(note.Get_Name(0), note.Get_Duration());
      app.Close_Client_Connection();
    }
 }

}
