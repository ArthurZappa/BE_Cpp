// Load Wi-Fi library
#include <ESP8266WiFi.h>

class App{
  private : 
  char *ssid;
  char *password;
  WiFiServer server;
  WiFiClient client;
  String currentLine = "";// make a String to hold incoming data from the client

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
   * @brief Manage the gpio
   * @param none
   * @return none
   */
  void Manage_Gpio(void);

  public:

  // Current time
  unsigned long currentTime = millis();
  // Previous time
  unsigned long previousTime = 0; 
  // Define timeout time in milliseconds (example: 2000ms = 2s)
  const long timeoutTime = 2000;

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



  };
