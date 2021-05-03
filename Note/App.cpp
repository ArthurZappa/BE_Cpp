#include "App.h"

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
  Open_Wifi_Server("Amélies6", "amelie99");
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

void App::Get_Tempo(void) {
  index_tempo = header.indexOf("?") + 7;  // get the index of the first character of the tempo (?Tempo=..)
  Serial.println("tempo = ");
  while (header[index_tempo] != 'A') {    // get tempo value until we are on the next line (which start by 'A')
    char_tempo += header[index_tempo];
    index_tempo ++;
  }
  
  tempo=atoi(char_tempo.c_str());          // convert string to int 
  Serial.println(tempo);
}


void App::Html_Display(void){

  if ((this->choose_file==0) && (this->new_sheet ==0) && (this->start_record ==0)) {
    
      // Display the HTML web page
    this->client.println("<!DOCTYPE html><html>");
    this->client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    this->client.println("<link rel=\"icon\" href=\"data:,\">");
    // CSS to style the on/off buttons 
    // Feel free to change the background-color and font-size attributes to fit your preferences
    this->client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
    this->client.println(".button { background-color: #FDD017; border: none; color: white; padding: 16px 40px;");
    this->client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
    this->client.println(".button2 {background-color: #FFFFFF; border: solid; color: black; padding: 16px 40px;");
    this->client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>");
    
    // Web Page Heading
    this->client.println("<body><h1>Sheet Writer</h1>");
    
    // Display OPEN FILE button
    this->client.println("<p>Open a record</p>");    
    this->client.println("<p><a href=\"/CHOOSE\"><button class=\"button\">OPEN</button></a></p>");
    
    // Display START NEW RECORD button
    this->client.println("<p>Create new record</p>");
    this->client.println("<p><a href=\"/NEW\"><button class=\"button\">START</button></a></p>");
  }
  
  else if (this->new_sheet == 1) {   // create a new record 
    this->client.println("<!DOCTYPE html><html>");
    this->client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
    this->client.println(".button { background-color: #FDD017; border: none; color: white; padding: 16px 40px;");
    this->client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
    this->client.println(".button2 {background-color: #FFFFFF; border: solid; color: black; padding: 16px 40px;");
    this->client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>");
    this->client.println("<body><h1>Create a new sheet</h1>");
    this->client.println("<form><label for=\"Tempo\">Enter your tempo here and press \"enter\" touch on your keyboard :</label> <input type=\"text\" id=\"Tempo\" name=\"Tempo\"></form><br>"); // enter tempo
    this->client.println("<p> Tempo chosen = " + char_tempo + "</p>"); 
    this->client.println("<p>Start Recording<br><a href=\"/START \"><button class=\"button\">START</button></a></p></body></html>");
    }

  else if (this->start_record == 1) { // start the record and download it when finish
    this->client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
    this->client.println(".button { background-color: #FFE87C; border: none; color: white; padding: 16px 40px;");
    this->client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
    this->client.println(".button2 {background-color: #FFFFFF; border: solid; color: black; padding: 16px 40px;");
    this->client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
    this->client.println("body{background-color : #FFEBCD};}</head></style>");
    this->client.println("<body><h1>mySheet</h1>");
    this->client.println("<a href=\"http://" + WiFi.localIP().toString() + "/START\" download=\"mySheet\"><button class=\"button2\">DOWNLOAD</button></a></p></body></html>");
  }

  else if (this->choose_file == 1){
     this->client.println("<!DOCTYPE html><html>");
     this->client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
     this->client.println("<link rel=\"icon\" href=\"data:,\">");
     this->client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
     this->client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
     this->client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
     this->client.println(".button2 {background-color: #77878A;}</style></head>");
     
     this->client.println("<body><input type=\"file\" id=\"new_sheet\" multiple accept=\".html, .pdf\">");      // select a file
     this->client.println("<div id = \"list_sheet\"> <p>No record selected</p> </div>");
     

     this->client.println("<iframe id = \"viewer\" width = \"1500\" height = \"1000\" ></iframe>");             // set display screen
     
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
     this->client.println("const sheet_URL = URL.createObjectURL(this.files[i]);");     //create URL for the file selected before
     this->client.println("const iframe = document.getElementById('viewer');");
     this->client.println("iframe.setAttribute('src', sheet_URL);");                    // display file
     this->client.println("URL.revokeObjectURL(sheet_URL);");                           // free URL
     this->client.println("li.appendChild(this_sheet);}}}</script></body></html>");
   
  }
  
}


void App::Get_URL(void){
  
  if (header.indexOf("GET /NEW") >= 0) {
    Serial.println("Create a new sheet");
    this->new_sheet = 1;
    this->choose_file = 0;    
  } else if (header.indexOf("?") >= 0) {      // get tempo value and put it in tempo_char -> we detect the "?" in the page URL : "?Tempo=.."
    Get_Tempo();
  } else if (header.indexOf("GET /START") >= 0) {
    Serial.println("Start recording");
    this->start_record = 1;
    this->new_sheet = 0;
  } else if (header.indexOf("GET /CHOOSE") >= 0) {
    Serial.println("Choose a file");
    this->choose_file = 1;
    this->new_sheet = 0;
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
            
            Get_URL();

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
