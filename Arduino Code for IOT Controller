//Written by Wen//
//ALL RIGHT RESERVED//

// Library Declearation
#include <WiFi.h>
#include <WebServer.h>

// Wifi Configuration
const char* ssid = "Password Bukan 12345678";
const char* password = "12345678";

// Motor Power Levels
const int hybernating = 0;
const int zone_1 = 100;
const int zone_2 = 200;
const int zone_3 = 255;

// Pin Assignments
const int PUSH_SWITCH = 34;
const int READY_LED = 25;
const int NOT_READY_LED = 26;
const int ADJUST_MOTOR_SPEED_M1 = 13;
const int ADJUST_MOTOR_SPEED_M2 = 21;
const int SUPPLY_MOTOR_POWER_M1 = 22;
const int SUPPLY_MOTOR_POWER_M2 = 12;
const int SUPPLY_MOTOR_LEFT_WHEEL_M3A = 17;
const int SUPPLY_MOTOR_LEFT_WHEEL_M3B = 18;
const int SUPPLY_MOTOR_RIGHT_WHEEL_M4A = 15;
const int SUPPLY_MOTOR_RIGHT_WHEEL_M4B = 16;

WebServer server(80);

// Shooter State
bool shooter_state = false;

// Serve the HTML control interface
        server.send(200, "text/html", R"rawliteral(
            <!DOCTYPE html>
            <html lang="en">
      <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Robot Controller</title>
        <style>
            body {
                font-family: Arial, sans-serif;
                text-align: center;
                background-color: #d63384; /* Denser pink background */
                color: white;
                margin: 0;
                padding: 0;
            }

            h1, h2 {
                margin: 20px 0;
            }

            button {
                font-size: 20px;
                padding: 15px 25px;
                margin: 10px;
                cursor: pointer;
                border: none;
                border-radius: 8px;
                background-color: #ffb6c1; /* Light pink buttons */
                color: #333;
                transition: transform 0.2s, background-color 0.3s;
                width: 100%; /* Buttons span the full width */
                max-width: 300px; /* Optional: cap the width for larger screens */
            }

            button:hover {
                transform: scale(1.05);
                background-color: #ff94b0; /* Slightly darker pink on hover */
            }

            .movement-container {
                display: grid;
                grid-template-areas:
                    ". up ."
                    "left stop right"
                    ". down .";
                gap: 10px;
                justify-content: center;
                align-items: center;
            }

            .movement-container button {
                width: 70px; /* Consistent button size */
                height: 70px;
            }

            .up { grid-area: up; }
            .down { grid-area: down; }
            .left { grid-area: left; }
            .right { grid-area: right; }
            .stop { grid-area: stop; }

            .shooter-container {
                display: flex;
                flex-direction: column;
                align-items: center;
                gap: 15px; /* Spacing between rows */
            }

            .section {
                margin: 30px 0;
                padding: 20px;
                border-radius: 10px;
                background-color: rgba(255, 255, 255, 0.1);
            }
        </style>
        <script>
            function sendCommand(command) {
                fetch(`/command?input=${command}`)
                    .then(response => response.text())
                    .then(data => console.log(data))
                    .catch(error => console.error('Error:', error));
            }
        </script>
    </head>
    <body>
        <h1>Robot Controller</h1>
        <div class="section">
            <h2>Movement Control</h2>
            <div class="movement-container">
                <button class="up" onclick="sendCommand('move_forward')">⬆️</button>
                <button class="left" onclick="sendCommand('turn_left')">⬅️</button>
                <button class="stop" onclick="sendCommand('stop')">O</button>
                <button class="right" onclick="sendCommand('turn_right')">➡️</button>
                <button class="down" onclick="sendCommand('move_backward')">⬇️</button>
            </div>
        </div>
        <div class="section">
            <h2>Shooter Control</h2>
            <div class="shooter-container">
                <button onclick="sendCommand('shooter_zone1')">Shooter Power 1</button>
                <button onclick="sendCommand('shooter_zone2')">Shooter Power 2</button>
                <button onclick="sendCommand('shooter_zone3')">Shooter Power 3</button>
                <button onclick="sendCommand('shooter_off')">😴</button>
            </div>
        </div>
    </body>
    </html>
        )rawliteral");
        void handleRoot() {

}

// Handle incoming commands
void handleCommand() {
    String input = server.arg("input");
    if (input == "move_forward") {
        digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3A, LOW);
        digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3B, HIGH);
        digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, LOW);
        digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, HIGH);
    } else if (input == "move_backward") {
        digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3A, HIGH);
        digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3B, LOW);
        digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, HIGH);
        digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, LOW);
    } else if (input == "turn_left") {
        digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3A, HIGH);
        digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3B, LOW);
        digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, LOW);
        digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, HIGH);
    } else if (input == "turn_right") {
        digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3A, LOW);
        digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3B, HIGH);
        digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, HIGH);
        digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, LOW);
    } else if (input == "stop") {
        digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3A, LOW);
        digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3B, LOW);
        digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, LOW);
        digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, LOW);
    } else if (input.startsWith("shooter_")) {
        if (input == "shooter_zone1") {
            digitalWrite(READY_LED,HIGH);   
            digitalWrite(SUPPLY_MOTOR_POWER_M1,LOW); 
            digitalWrite(SUPPLY_MOTOR_POWER_M2,LOW);         
            analogWrite(ADJUST_MOTOR_SPEED_M1, zone_1);
            analogWrite(ADJUST_MOTOR_SPEED_M2, zone_1);
        } else if (input == "shooter_zone2") {
            digitalWrite(READY_LED,HIGH);
            digitalWrite(SUPPLY_MOTOR_POWER_M1,LOW); 
            digitalWrite(SUPPLY_MOTOR_POWER_M2,LOW);
            analogWrite(ADJUST_MOTOR_SPEED_M1, zone_2);
            analogWrite(ADJUST_MOTOR_SPEED_M2, zone_2);
        } else if (input == "shooter_zone3") {
            digitalWrite(READY_LED,HIGH);
            digitalWrite(SUPPLY_MOTOR_POWER_M1,LOW); 
            digitalWrite(SUPPLY_MOTOR_POWER_M2,LOW);
            analogWrite(ADJUST_MOTOR_SPEED_M1, zone_3);
            analogWrite(ADJUST_MOTOR_SPEED_M2, zone_3);
        } else if (input == "shooter_off") {
            digitalWrite(READY_LED,LOW);
            digitalWrite(SUPPLY_MOTOR_POWER_M2,HIGH);
            digitalWrite(SUPPLY_MOTOR_POWER_M1,HIGH); 
            analogWrite(ADJUST_MOTOR_SPEED_M1, hybernating);
            analogWrite(ADJUST_MOTOR_SPEED_M2, hybernating);
        }
    }
    server.send(200, "text/plain", "Command executed.");
}

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);

    // Pin configurations
    pinMode(PUSH_SWITCH, INPUT);
    pinMode(READY_LED, OUTPUT);
    pinMode(NOT_READY_LED, OUTPUT);
    pinMode(ADJUST_MOTOR_SPEED_M1, OUTPUT);
    pinMode(ADJUST_MOTOR_SPEED_M2, OUTPUT);
    pinMode(SUPPLY_MOTOR_POWER_M1, OUTPUT);
    pinMode(SUPPLY_MOTOR_POWER_M2, OUTPUT);
    pinMode(SUPPLY_MOTOR_LEFT_WHEEL_M3A, OUTPUT);
    pinMode(SUPPLY_MOTOR_LEFT_WHEEL_M3B, OUTPUT);
    pinMode(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, OUTPUT);
    pinMode(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, OUTPUT);

    server.on("/", handleRoot);
    server.on("/command", handleCommand);
    server.begin();
    Serial.println("Server started");
}

void loop() {
    digitalWrite(NOT_READY_LED,HIGH);
    server.handleClient();
}
