#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "Dhakad Launde";
const char* password = "98765432";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String LeftWheelState = "off";
String RightWheelState = "off";

int state=2;
String stateStr="UP";
void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Started");
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    //Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        
       // String line = client.readStringUntil('\r');
       // Serial.println(line);
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
            /*
            // turns the LEFT on and off
            if (header.indexOf("GET /?cmd=LEFTON") >= 0) {
              Serial.println("LEFT ON");
              LeftWheelState = "on";             
            } else if (header.indexOf("GET /?cmd=LEFTOFF") >= 0) {
              Serial.println("LEFT off");
              LeftWheelState = "off";      
            } else if (header.indexOf("GET /?cmd=RIGHTON") >= 0) {
              Serial.println("RIGHT on");
              RightWheelState = "on";

            } else if (header.indexOf("GET /?cmd=RIGHTOFF") >= 0) {
              Serial.println("RIGHT off");
              RightWheelState = "off";
            }
            */

            // turns the LEFT on and off
            if (header.indexOf("GET /?cmd=0") >= 0) {
              Serial.println("LEFT");
               stateStr = "LEFT";  
               state =0;         
            } else if (header.indexOf("GET /?cmd=1") >= 0) {
              Serial.println("RIGHT");
              stateStr = "RIGHT"; 
              state=1;
            } else if (header.indexOf("GET /?cmd=2") >= 0) {
              Serial.println("UP");
              stateStr = "UP" ;
              state=2;
            } else if (header.indexOf("GET /?cmd=3") >= 0) {
              Serial.println("DOWN");
              stateStr = "DOWN"; 
              state=3;
            }



            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP8266 Web Server</h1>");
            client.println("<form method=\"get\">"); 
            // Display current state, LEFT  buttons 
            /*
            client.println("<p>Left wheel " + LeftWheelState + "</p>");
            // If the LeftWheelState is off, it displays the ON button       
            if (LeftWheelState=="off") {
              client.println("<p><button name=\"cmd\" class=\"button\" type=\"submit\" value=\"LEFTON\">LEFT ON</button></p>");
            } else {
              client.println("<p><button name=\"cmd\" class=\"button\" type=\"submit\" value=\"LEFTOFF\">LEFT OFF</button></p>");
            } 
               
            // Display current state, and RIGHT buttons
            client.println("<p>Rigth Wheel " + RightWheelState + "</p>");
            // If the RightWheelState is off, it displays the ON button       
            if (RightWheelState=="off") {
              client.println("<p><button name=\"cmd\" class=\"button\" type=\"submit\" value=\"RIGHTON\">RIGHT ON</button></p>");
            } else {
              client.println("<p><button name=\"cmd\" class=\"button\" type=\"submit\" value=\"RIGHTOFF\">RIGHT OFF</button></p>");
            }
           
           client.println("<p>Command:<input type=\"text\" name=\"cmd1\" onkeydown=\"if (event.keyCode == 13) { this.form.submit(); return false; }\"></p>");
            */

            client.println("<p>Wheel " + stateStr + "</p>");

            if(state!=0)
            client.println("<p><button name=\"cmd\" class=\"button\" type=\"submit\" value=\"0\">LEFT-0</button></p>");
            else
            client.println("<p>LEFT-0</p>");
            
            if(state!=1)
            client.println("<p><button name=\"cmd\" class=\"button\" type=\"submit\" value=\"1\">RIGHT-1</button></p>");
            else
            client.println("<p>RIGHT-1</p>");
            if(state!=2)
            client.println("<p><button name=\"cmd\" class=\"button\" type=\"submit\" value=\"2\">UP-2</button></p>");
            else
            client.println("<p>UP-2</p>");
            if(state!=3)
            client.println("<p><button name=\"cmd\" class=\"button\" type=\"submit\" value=\"3\">DOWN-3</button></p>");
            else
            client.println("<p>DOWN-3</p>");
            
            client.println("</form>");
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
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
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    //Serial.println("Client disconnected.");
    Serial.println("");
  }
}
