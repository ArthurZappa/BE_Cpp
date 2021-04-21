#include "App.h"

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
int new_sheet = 0;
int choose_file = 0;
int open_file = 0;

App::App():server(80){}//constructor who initializes server http : port 80


void App::Open_Wifi_Server(char* id, char* pw){

  // Replace with your network credentials
  this->ssid = id ;
  Serial.println(this->ssid);
  this->password = pw;
}


void App::Connect_To_Wifi_Network(void){

  Serial.print("Connecting to ");
  Serial.println(this->ssid);
  WiFi.begin(this->ssid, this->password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
}

void App::Start_Wifi_Server(void){
   // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  this->server.begin();
  
  
  
}


void App::Start_Client_Connection(void){
   this->client = this->server.available();   // Listen for incoming client

  if (this->client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port          
    this->currentTime = millis();
    this->previousTime = this->currentTime;

  }

}

void App::Init_Server(void){
  Open_Wifi_Server("iPhone de Arthur", "lemotdepasse");
  Connect_To_Wifi_Network();
  Start_Wifi_Server();
}



void App::Close_Client_Connection(void){

 if (this->client){
   // Clear the header variable
    header = "";
    // Close the connection
    this->client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
 }
}

void App::Html_Display(void){

  if (choose_file==0 && new_sheet ==0) {
    
      // Display the HTML web page
    this->client.println("<!DOCTYPE html><html>");
    this->client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    this->client.println("<link rel=\"icon\" href=\"data:,\">");
    // CSS to style the on/off buttons 
    // Feel free to change the background-color and font-size attributes to fit your preferences
    this->client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
    this->client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
    this->client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
    this->client.println(".button2 {background-color: #77878A;}</style></head>");
    
    // Web Page Heading
    this->client.println("<body><h1>ESP8266 Web Server</h1>");
    
    // Display OPEN FILE button
    this->client.println("<p>Open a record</p>");    
    this->client.println("<p><a href=\"/CHOOSE\"><button class=\"button\">OPEN</button></a></p>");
    
    // Display START NEW RECORD button
    this->client.println("<p>Create new record</p>");
    this->client.println("<p><a href=\"/NEW\"><button class=\"button\">START</button></a></p>");
  }
  
  else if (new_sheet == 1) {   
    this->client.println("<!DOCTYPE html><html>");
    this->client.println("<head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" /><style>input[type=text]{width: 60%;  padding: 12px 18px;  margin: 7px 0;  box-sizing: border-box; border: 3px solid #ccc;}</style>");
    this->client.println("<FONT size=\"6pt\"><center><p><U>Create a new sheet </p><br><br></center></head> </U></FONT>");
    this->client.println("<body><body style=\"background-color:#1E90FF;\">");
    this->client.println("<form><label for=\"lname\">Tempo :</label> <input type=\"text\" id=\"lname\" name=\"lname\"></form><br><br><br><br><br><br><br><br><br>");
    this->client.println("<p>Start Recording<br><a href=\"/START RECORDING\"><button class=\"button\">START</button></a></p></body></html>");
  }

  else if (choose_file == 1){
     this->client.println("<!DOCTYPE html><html>");
     this->client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
     this->client.println("<link rel=\"icon\" href=\"data:,\">");
     this->client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
     this->client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
     this->client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
     this->client.println(".button2 {background-color: #77878A;}</style></head>");
     
     this->client.println("<body><input type=\"file\" id=\"new_sheet\" multiple accept=\".html, .pdf\">"); // select a file
     this->client.println("<div id = \"list_sheet\"> <p>No record selected</p> </div>");
     

     this->client.println("<iframe id = \"viewer\" width = \"1500\" height = \"1000\" ></iframe>"); // set display screen
     
     this->client.println("<script>const new_sheet = document.getElementById(\"new_sheet\"), list_sheet = document.getElementById(\"list_sheet\");");
     
     this->client.println("new_sheet.addEventListener(\"change\", handleFiles, false);");

     this->client.println("function handleFiles() {");
     this->client.println("if (!this.files.length) {list_sheet.innerHTML = \"<p>No record selected</p>\";} else {");
     this->client.println("list_sheet.innerHTML = \"\";");
     this->client.println("const list = document.createElement(\"ul\");");
     this->client.println("list_sheet.appendChild(list);");
     this->client.println("for (let i = 0; i < this.files.length; i++) {");
     this->client.println("const li = document.createElement(\"li\");");
     this->client.println("list.appendChild(li);");
     this->client.println("const this_sheet = document.createElement(\"file\");");
     this->client.println("const sheet_URL = URL.createObjectURL(this.files[i]);"); //create URL for the file selected before
     this->client.println("const iframe = document.getElementById('viewer');");
     this->client.println("iframe.setAttribute('src', sheet_URL);"); // display file
     this->client.println("URL.revokeObjectURL(sheet_URL);"); // free URL
     this->client.println("li.appendChild(this_sheet);}}}</script></body></html>");
   
  }
  
}


void App::Manage_Gpio(void){
  
  // turns the GPIOs on and off
  if (header.indexOf("GET /NEW") >= 0) {
    Serial.println("Create a new sheet");
    new_sheet = 1;
  } else if (header.indexOf("GET /CHOOSE") >= 0) {
    Serial.println("Choose a file");
    choose_file = 1;
    new_sheet = 0;
  } else if (header.indexOf("GET /CHOOSE#") >= 0) {
    Serial.println("Open the file choosen");
    open_file = 1;
  }
}
  
void App::Manage_App(void){

   if (client) {    

     while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();  
             
      if (client.available()) {             // if there's bytes to read from the client,
        
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
      
        if (c == '\n') {                    // if the byte is a newline character
         
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
       
          if (currentLine.length() == 0) {
          
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            Manage_Gpio();

            Html_Display();
         
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
  }

  
}
