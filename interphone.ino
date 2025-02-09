#include<ESP8266WiFi.h>

const char* ssid = //your choice ssid;    

const char* password = //your choice of password;   

int BUZZER = 4;   

WiFiServer server(80);

void setup()
{

  Serial.begin("your serial");

 pinMode(BUZZER, OUTPUT); 

  digitalWrite(BUZZER, LOW);
  
  
  

   Serial.print("Connecting to the Newtork");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)

  {

    delay(500);

    Serial.print(".");

  }

  Serial.println("WiFi connected"); 

  server.begin();  

  Serial.println("Server started");

 

  Serial.print("IP Address of network: "); 

  Serial.println(WiFi.localIP());

  Serial.print("Copy and paste the following URL: https://"); 

  Serial.print(WiFi.localIP());

  Serial.println("/");

}

 

void loop()

{

  WiFiClient client = server.available();

  if (!client)

  {

    return;

  }

  Serial.println("Waiting for new client");

  while(!client.available())

  {

    delay(1);

  }

 

  String request = client.readStringUntil('\r');

  Serial.println("Request");
  Serial.println(request);

  client.flush();

//  Serial.println(request.indexOf("/LED=ON"));

  int value3=LOW;

  
 if(request.indexOf("BUZZER=ON") != -1)

  {

    digitalWrite(BUZZER, HIGH); // Turn LED ON

    Serial.println(request.indexOf("BUZZER=ON"));

    value3 = HIGH;

  }

  if(request.indexOf("BUZZER=OFF") != -1)

  {

    digitalWrite(BUZZER, LOW); // Turn LED OFF

    Serial.println(request.indexOf("/BUZZER=OFF"));

    value3 = LOW;
  }
//*------------------HTML Page Code---------------------*//

 

  client.println("HTTP/1.1 200 OK"); //

  client.println("Content-Type: text/html");

  client.println("");

  client.println("<!DOCTYPE HTML>");

  client.println("<html>");

 

  
   client.print(" CONTROL BUZZER: ");

 

  if(value3 == HIGH)

  {

    client.print("ON");

  }

  else

  {

    client.print("OFF");

  }

  client.println("<br><br>");

  client.println("<a href=\"/BUZZER=ON\"\"><button>ON</button></a>");
  client.println("<a href=\"/BUZZER=OFF\"\"><button>OFF</button></a><br />");
   
   
   client.println("</html>");

 

  delay(1);

  Serial.println("Client disonnected");

  Serial.println("");

}
