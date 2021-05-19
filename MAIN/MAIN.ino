#include "App.h"
#include "Screen.h"
#include "Note.h"
#include "Sheet.h"


App app;
Screen screen;
Sheet sheet;
Note note;

  
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  app.Init_Server();
  screen.Init_Screen();
}

void loop() {
  // put your main code here, to run repeatedly:

 if (app.Get_Tempo() == 0) {
  app.Start_Client_Connection();
  app.Manage_App();
  app.Close_Client_Connection();
 }
 else {
    float duration = app.Get_Time_Duration();
    while (analogRead(A0) < 250) {
      yield();
    //do nothing --> wait until we detect the first note so that the software is coordinate with the user 
    }
    while (1) {
      try{
          note.Recognize_Name(duration);
          note.Recognize_Duration(duration);
               
          screen.Display(); 
          
          sheet.Construct_Measure((uint16_t)duration);
          
          app.Start_Client_Connection();
          app.Manage_App();
          app.Close_Client_Connection();
      }
      
      catch (Note::Too_High high) {
        Serial.println("Note too high, try again");
      }
      catch (Note::Too_Low low) {
        Serial.println("Note too low, try again");
      }
      
    }
 }

}
