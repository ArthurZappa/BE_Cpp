// Load Wi-Fi library
#include <ESP8266WiFi.h>

class App{
  private : 
  char *ssid;
  char *password;
  WiFiClient client;
  String currentLine = "";// make a String to hold incoming data from the client

  public:

  // Current time
  unsigned long currentTime = millis();
  // Previous time
  unsigned long previousTime = 0; 
  // Define timeout time in milliseconds (example: 2000ms = 2s)
  const long timeoutTime = 2000;


  /**
   * @brief Create a wifi server and set web server port to http
   * @param char* id: network name
   *        char* pw: password of network
   * @return WiFiServer
   */
  WiFiServer Open_Wifi_Server(char* id, char* pw);

  /**
   * @brief Connect to a WiFi network
   * @param none
   * @return none
   */
  void Connect_To_Wifi_Network(void);

  /**
   * @brief Begin the web server and print IP
   * @param WiFiServer server: server created in Open_Wifi_Server
   * @return none
   */
  void Start_Wifi_Server(WiFiServer server);

   /**
   * @brief Init a web server
   * @param none
   * @return none
   */
  void Init_Server(void);

  /**
   * @brief Wait and connect a client to the web server
   * @param WIFiServer server : server to connect the client 
   * @return none
   */
  void Start_Client_Connection(WiFiServer server);


  /**
   * @brief Close the client connection
   * @param none
   * @return none
   */
  void Close_Client_Connection(void);

  /**
   * @brief Manage the html display
   * @param none
   * @return none
   */
  void Html_Display(void);


  void Manage_Gpio(void);

/**
   * @brief Get client data and manage html display
   * @param none
   * @return none
   */
  void Manage_App(void);



  };
