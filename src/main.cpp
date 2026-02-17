#include <Arduino.h>
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <SPIFFS.h>
#include <WebServer.h>

#include "config.h"
#include "motor_control.h"
#include "servo_control.h"

WebServer server(80);

WebSocketsServer webSocket(81);

unsigned long lastCmdTime = 0;

bool e_stop = false;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    if (type == WStype_CONNECTED) {
        Serial.printf("Client %u connected\n", num);
        lastCmdTime = millis();
    }

    if (type == WStype_DISCONNECTED) {
        Serial.printf("Client %u disconnected\n", num);
        stopAllMotors();
    }


    if (type != WStype_TEXT) return;
    
    payload[length] = '\0';
    char* msg = (char*)payload;

    if (msg[0] == 'D') {
        if (e_stop) return;

        float joyX, joyY;
        sscanf(msg, "D,%f,%f", &joyX, &joyY);
        joyX = constrain(joyX, -1.0, 1.0);
        joyY = constrain(joyY, -1.0, 1.0);
    
        drive(joyX, joyY);
        lastCmdTime = millis();
    } 
    else if (msg[0] == 'S') {
        int id, angle;
        sscanf(msg, "S,%d,%d", &id, &angle);
        setServoAngle(id, angle);
        lastCmdTime = millis();
    }
    else if (msg[0] == 'E') {
        int state;
        sscanf(msg, "E,%d", &state);
        
        e_stop = state;
        
        if (state) {
            stopAllMotors();
            servoStop();
        } else {
            servoInit();
        }
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    motorInit();
    servoInit();

    Serial.println("Starting WiFi AP...");
    WiFi.mode(WIFI_AP);
    delay(100);
    WiFi.softAP(WIFI_SSID, WIFI_PASS, 1);

    Serial.print("Robot IP: ");
    Serial.println(WiFi.softAPIP());

    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }

    Serial.println("SPIFFS contents:");
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while (file) {
        Serial.println(file.name());
        file = root.openNextFile();
    }

    server.on("/", HTTP_GET, []() {
        Serial.println("HTTP GET /");

        File file = SPIFFS.open("/index.html", "r");
        if (!file) {
            Serial.println("Failed to open index.html");
            server.send(500, "text/plain", "index.html missing");
            return;
        }

        server.streamFile(file, "text/html");
        file.close();
    });

    server.on("/index.css", HTTP_GET, []() {
        File file = SPIFFS.open("/index.css", "r");
        if (!file) {
            server.send(500, "text/plain", "index.css missing");
            return;
        }
        server.streamFile(file, "text/css");
        file.close();
    });

    server.on("/index.js", HTTP_GET, []() {
        File file = SPIFFS.open("/index.js", "r");
        if (!file) {
            server.send(500, "text/plain", "index.js missing");
            return;
        }
        server.streamFile(file, "application/javascript");
        file.close();
    });


    server.begin();
    Serial.println("HTTP server started");

    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    Serial.println("WebSocket Started.");
}

void loop() {
    server.handleClient();
    webSocket.loop();

    if (!e_stop && millis() - lastCmdTime > CMD_TIMEOUT) {
        stopAllMotors();
    }
}