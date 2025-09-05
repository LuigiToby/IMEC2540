#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo2;

int pinServo2 = 15;   // Pin para el servo 2
int angulo2 = 90;     // Ángulo inicial

void setup() {
  Serial.begin(115200);
  
  servo2.attach(pinServo2, 500, 2400);
  servo2.write(angulo2);

  Serial.println("Control interactivo del servo 2");
  Serial.println("Comandos:");
  Serial.println("  w -> subir servo2 (+1°)");
  Serial.println("  s -> bajar servo2 (-1°)");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();

    if (c == 'w') { angulo2 = min(angulo2 + 1, 180); }
    if (c == 's') { angulo2 = max(angulo2 - 1, 0); }

    servo2.write(angulo2);

    Serial.print("Servo2: ");
    Serial.println(angulo2);
  }
}
