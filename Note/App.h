// Load Wi-Fi library

#ifndef APP_H
#define APP_H

#include <ESP8266WiFi.h>
#include "Sheet.h"

class App{
  
  private : 
  
  Sheet sheet;
  char *ssid;
  char *password;
  WiFiServer server;
  WiFiClient client;
  String currentLine = "";// make a String to hold incoming data from the client

  // Variable to store the HTTP request
  String header;

  // Auxiliar variables to manage HTML display
  int new_sheet = 0;
  int start_record = 0;
  int choose_file = 0;

  // variable to get tempo value
  int index_tempo;
  String char_tempo;
  int tempo;
  float time_duration;           // duration of a time calculate with the tempo set by the client in the app in milliseconds
  String time_measure;

  // Current time
  unsigned long currentTime = millis();
  // Previous time
  unsigned long previousTime = 0; 
  // Define timeout time in milliseconds (example: 2000ms = 2s)
  const long timeoutTime = 2000;


  bool beginning; // used to check if we are at the beginning of a measure because the display is different
  int cnt_tamp;
/**
   * @brief Create a wifi server
   * @param char* id: network name
   *        char* pw: password of network
   * @return none
   */
  void Open_Wifi_Server(char* id, char* pw);

  /**
   * @brief Connect to a WiFi network
   * @param none
   * @return none
   */
  void Connect_To_Wifi_Network(void);

  /**
   * @brief Begin the web server and print IP
   * @param none
   * @return none
   */
  void Start_Wifi_Server(void);

 /**
   * @brief Manage the html display
   * @param none
   * @return none
   */
  void Html_Display(void);

 /**
   * @brief Get tempo value and store it in "int tempo"
   * @param none
   * @return none
   */
  void Set_Tempo(void);
   
 /**
   * @brief Update new_sheet/start_recording/choose_file values according to the URL
   * @param none
   * @return none
   */
  void Manage_URL(void);



  public:


  App();
  
   /**
   * @brief Init a web server
   * @param none
   * @return none
   */
  void Init_Server(void);

  /**
   * @brief Wait and connect a client to the web server
   * @param none
   * @return none
   */
  void Start_Client_Connection(void);


  /**
   * @brief Close the client connection
   * @param none
   * @return none
   */
  void Close_Client_Connection(void);

 
/**
   * @brief Get client data and manage html display
   * @param none
   * @return none
   */
  void Manage_App(void);

  int Get_Tempo(void);

  float Get_Time_Duration(void);
  


  };

  #endif
