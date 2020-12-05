#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//#include <ESP_SSD1306.h>    // Modification of Adafruit_SSD1306 for ESP8266 compatibility
#include <Adafruit_GFX.h>   // Needs a little change in original Adafruit library (See README.txt file)
#include <SPI.h>            // For SPI comm (needed for not getting compile error)
#include <Wire.h>
#include <FastLED.h>

//The setup function is called once at startup of the sketch

const char *ssid = "Neuland_Guest";
const char *password = "";

const int led = 2;

const String htmlOK = "HTTP/1.1 200 OK";
const String htmlContentType = "Content-Type: text/html";
const String htmlBegin = "<!DOCTYPE HTML><html>";
const String htmlLinks = "<head><link rel='stylesheet' href='http://progs.draeger-it.blog/wemosd1/d1.css'/><link rel='shortcut icon' href='http://progs.draeger-it.blog/wemosd1/favicon.ico' /></head><body>";
const String htmlEnd = "</body></html>";
const String htmlBreakLine = "</br>";




#define NUM_LEDS 8
#define DATA_PIN 13
CRGB leds[NUM_LEDS];

//ESP8266WebServer server(80);
WiFiServer server(80);

int mode=0; // animation mode


/**
 * Die Funktion gibt den HTML Kopf auf dem Client aus.
 * Dieses wird für jeden Respond verwendet.
 **/
void printHtmlHeader(WiFiClient client){
  client.println(htmlOK);
  client.println(htmlContentType);
  client.println("");
  client.println(htmlBegin);
  client.println(htmlLinks);
}


/*void handleRoot() {
	digitalWrite(led, 1);
	server.send(200, "text/plain", "Hello from esp8266!");
	digitalWrite(led, 0);
}

void handleNotFound() {
	digitalWrite(led, 1);
	String message = "File Not Foundn";
	message += "URI: ";
	message += server.uri();
	message += "nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "nArguments: ";
	message += server.args();
	message += "n";
	for (uint8_t i = 0; i < server.args(); i++) {
		message += " " + server.argName(i) + ": " + server.arg(i) + "n";
	}
	server.send(404, "text/plain", message);
	digitalWrite(led, 0);
}*/

void setup() {
// Add your initialization code here
	pinMode(led, OUTPUT);
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	Serial.begin(115200);
	WiFi.begin(ssid, password);
	Serial.println("");

// Wait for connection
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	if (MDNS.begin("esp8266")) {
		Serial.println("MDNS responder started");
	}

//	server.on("/", handleRoot);

//	server.on("/inline", []() {
//		server.send(200, "text/plain", "this works as well");
//	});

//	server.onNotFound(handleNotFound);

	server.begin();
	Serial.println("HTTP server started");

}

// The loop function is called in an endless loop
void loop() {
//Add your repeated code here
	//server.handleClient();

	 //Prüfen ob sich ein Client verbunden hat, wenn nicht die Loop "verlassen"
	  WiFiClient client = server.available();
	  if (!client) {
	    return;
	  }

	  // Wenn sich ein Client verbunden hat solange warten bis Daten gesendet werden.
	  Serial.println("Neuer Client verbunden.");
	  while(!client.available()){
	    delay(1);
	  }

	  //Lesen der Anfrage vom Client
	  String request = client.readStringUntil('\r');
	  Serial.println(request);
	  client.flush();
	  //Wenn in der Anfrage die Zeichenkette "/toggle" vorkommt dann...
	  if (request.indexOf("/toggle") != -1) {
	    if(mode == 1){
	      mode = 0;
	    } else {
	        mode = 1;
	    }
	    Serial.print("Modus: ");
	    Serial.println(mode);
	  }
	 //Gibt den Html Header auf der Antwort aus.
	 printHtmlHeader(client);

	  //Ab hier wird die Webseite zusammengesetzt.
	  client.println("<div class='mainWrapper'>");
	  client.print("Die LED ist : ");

	  String value = "-undefined-";

	  //Die Adresse für die Bilder
	  const String imgStartUrl = "http://progs.draeger-it.blog/wemosd1/";
	  String imgUrl = imgStartUrl + "light_on.png";

	  if(mode == 0) {

	  } else {
	    imgUrl = imgStartUrl + "light_off.png";
	  }
	  client.print(value);

	  client.println(htmlBreakLine);
	  client.println(htmlBreakLine);

	  client.println("<img src='"+imgUrl+"' widht='64' height='64'/>");
	  client.println(htmlBreakLine);

	  client.print("<div class='headline'>Klicke <a href=\"/toggle\">hier</a> um die LED ");
	  client.print(value=="AN"?"aus":"an");
	  client.print(" zuschalten.</div>");
	  client.println("");
	  client.println("</div>");
	  client.println(htmlEnd);

	  delay(1); //1ms. Pause
	  led_run();

}
