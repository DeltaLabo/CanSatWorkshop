#include <WiFi.h>
#include <WebServer.h>

#include "pins.h"
#include "Servo.h"

static const char* AP_SSID = "PDM";

Servo PDMServo;
WebServer server(80);

int currentServoAngle = 0;

void setServoAngle(int angle) {
    currentServoAngle = angle;
    PDMServo.write(angle);
}

void sendRoot() {
    String page =
        "<!doctype html>"
        "<html><head>"
        "<meta name='viewport' content='width=device-width, initial-scale=1'>"
        "<title>PDM Servo</title>"
        "</head><body>"
        "<h1>PDM Servo</h1>"
        "<p>Current position: ";
    page += String(currentServoAngle);
    page +=
        " deg</p>"
        "<p>Allowed positions:</p>"
        "<p>"
        "<a href='/0'><button>0 deg</button></a> "
        "<a href='/90'><button>90 deg</button></a> "
        "<a href='/180'><button>180 deg</button></a>"
        "</p>"
        "</body></html>";
    server.send(200, "text/html", page);
}

void sendServoSet(int angle) {
    setServoAngle(angle);
    server.sendHeader("Location", "/");
    server.send(303);
}

void setup() {
    Serial.begin(115200);

    PDMServo.attach(PDM_Servo_Pin);
    setServoAngle(0);

    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID);

    server.on("/", HTTP_GET, sendRoot);
    server.on("/0", HTTP_GET, []() { sendServoSet(0); });
    server.on("/90", HTTP_GET, []() { sendServoSet(90); });
    server.on("/180", HTTP_GET, []() { sendServoSet(180); });
    server.onNotFound([]() {
        server.send(404, "text/plain", "Only /0, /90, and /180 are allowed");
    });
    server.begin();

    Serial.print("PDM servo AP started. Connect to ");
    Serial.print(AP_SSID);
    Serial.print(" and open http://");
    Serial.println(WiFi.softAPIP());
}

void loop() {
    server.handleClient();
}
