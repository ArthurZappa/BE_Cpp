#include "App.h"
#include "Screen.h"
#include "Micro.h"
#include "Note.h"

App app;

Screen screen;
Micro micro;
Note note;
  
  
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

  micro.Manage_Micro();
 
  screen.Recognize_Display(); // NE FONCTIONNE PAS --> on modifie la valeur de fondamental_frequency associé 
                              // à cet objet micro mais on déclare un autre objet micro dans le fichier Note donc on ne récupère pas la bonne valeur de fondamental_frequency
     
}
