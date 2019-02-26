#include "SSD1306Wire.h"
#include <WiFi.h>
#define B1 25
#define B2 26
#define B3 27
const char* ssid     = "esp32";
const char* password = "esp32_01";
SSD1306Wire  display(0x3c, 21, 22);

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
   delay(10);
 display.init();
   display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        delay(10);
 
        display.drawString(0, 0, "To Start Connect to");
                display.drawString(0, 16, "SSID : esp32");
        display.drawString(0, 32, "Password : esp32_01");
  display.display();
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    display.clear();
      
        display.setFont(ArialMT_Plain_16);
         display.drawString(0, 0, "Connected");
       display.drawString(0, 16, "Navigate to");
              display.drawString(0, 32,WiFi.localIP().toString() );
              
               
  display.display();
  delay(10000);
    server.begin();
    pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(B3, OUTPUT);
  pinMode(5, OUTPUT);
digitalWrite(B1, HIGH); 
digitalWrite(B2, HIGH); 
digitalWrite(B3, HIGH); 
digitalWrite(5, HIGH);

}

 String stateB1="OFF" , stateB2="OFF" , stateB3="OFF";
void loop(){

 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=2\">");
 client.println();
            // the content of the HTTP response follows the header:
            client.print("BULB 01: <button onclick= location.href=\"/A\"> ON </button> <button onclick= location.href=\"/B\"> OFF </button> <br>");
             client.print("BULB 02: <button onclick= location.href=\"/C\"> ON </button> <button onclick= location.href=\"/D\"> OFF </button> <br>");
              client.print("BULB 03: <button onclick= location.href=\"/E\"> ON </button> <button onclick= location.href=\"/F\"> OFF </button> <br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
      ////////////////////////// BULB 01 ///////////////////////////////////        
        if (currentLine.endsWith("GET /A")) {
       digitalWrite(B1, LOW);
       delay(10);
      stateB1="ON";
}        
                       
      if (currentLine.endsWith("GET /B")) {
digitalWrite(B1, HIGH); 
delay(10);    
stateB1="OFF";
        }
        ////////////////////////// BULB 02 ///////////////////////////////////        
        if (currentLine.endsWith("GET /C")) {
       digitalWrite(B2, LOW);
       delay(10);
     stateB2="ON";
}        
                       
      if (currentLine.endsWith("GET /D")) {
digitalWrite(B2, HIGH);
delay(10);     
stateB2="OFF";
        }

        ////////////////////////// BULB 03 ///////////////////////////////////        
        if (currentLine.endsWith("GET /E")) {
       digitalWrite(B3, LOW);
       delay(10);
     stateB3="ON";
}        
                       
      if (currentLine.endsWith("GET /F")) {
digitalWrite(B3, HIGH);
delay(10);     
stateB3="OFF";

      }    
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
   display.clear();
     delay(10);
display.setTextAlignment(TEXT_ALIGN_LEFT);
    
       display.drawString(0, 0, "Home Automation");
       display.drawString(0, 16,"BULB 1 : " + stateB1 );
        display.drawString(0, 32,"BULB 2 : " + stateB2 );
        display.drawString(0, 48,"BULB 3 : " + stateB3 );
        delay(10);
  display.display();
}
