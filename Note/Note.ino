#include "App.h"
//#include "Screen.h"
#include "Micro.h"
#include "Note.h"

//App app;

//Screen screen;
Micro micro;
Note note;
  
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //app.Init_Server();
  micro.pins_init();
  //screen.Init_Screen();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //app.Start_Client_Connection();
  //app.Manage_App();
  //app.Close_Client_Connection();

 micro.sampling();
 //micro.FFT();
 note.recognize(micro.FFT());
 
 
  //screen.Display_All_Notes();
     
}
