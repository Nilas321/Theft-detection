#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Manivannan";
const char* password = "sarath11";

WebServer server(80);

bool motion = false;

void handleRoot() {
  String html = "<html><head><meta http-equiv='refresh' content='1'></head><body>";
  html += "<h1>PIR Sensor Status</h1>";
  html += motion ? "<p><b>Motion Detected!</b></p>" : "<p>No motion detected</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}


#define PIR_PIN 13
#define LED_PIN 2

void setup() {
  pinMode(PIR_PIN,INPUT);
  pinMode(LED_PIN,OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}
  // put your setup code here, to run once:

void loop() {
  server.handleClient();
  int motioncheck = digitalRead(PIR_PIN);
  motion = (motioncheck == HIGH);
  if (motion){
    digitalWrite(LED_PIN,HIGH);
    //Serial.println("Motion Detected");
  }
  else{
    digitalWrite(LED_PIN,LOW);
    //Serial.println("No Motion Detected");
  }
  delay(100);
  // put your main code here, to run repeatedly:

}