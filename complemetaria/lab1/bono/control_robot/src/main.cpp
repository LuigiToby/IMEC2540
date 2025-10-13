#include <Arduino.h>
#include <ESP32Servo.h>
#include <math.h>

// --------- Configuración de servos ----------
Servo servo1;  // Base
Servo servo2;  // Tijera

int pinServo1 = 13;
int pinServo2 = 15;

// --------- Parámetros del robot ----------
float L_min = 20.0;   // Longitud mínima (cm)
float L_max = 28.0;   // Longitud máxima (cm)
float servo2_min = 0;   // Ángulo mínimo servo 2
float servo2_max = 45;  // Ángulo máximo servo 2

// --------- Trayectoria infinito ----------
float A = 6.0;  // Escala en x
float B = 4.0;  // Escala en y
float x_offset = 18.0;  // Traslación en x
float y_offset = 8.0;   // Traslación en y

int N = 200;        // Número de puntos
int delay_ms = 50;  // Retardo entre puntos

// --------- Funciones auxiliares ----------
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void moverEfector(float x, float y) {
  // Coordenadas polares
  float r = sqrt(x * x + y * y);
  float theta = atan2(y, x) * 180.0 / PI;

  // Saturar al rango permitido
  r = constrain(r, L_min, L_max);
  theta = constrain(theta, 0, 120);

  // Conversión a servos
  float angulo1 = map(theta, 0, 120, 0, 180);
  float angulo2 = map(r, L_min, L_max, servo2_min, servo2_max);

  servo1.write(angulo1);
  servo2.write(angulo2);

  Serial.print("x: "); Serial.print(x);
  Serial.print(" y: "); Serial.print(y);
  Serial.print(" | Servo1: "); Serial.print(angulo1);
  Serial.print(" Servo2: "); Serial.println(angulo2);
}

// --------- Setup ----------
void setup() {
  Serial.begin(115200);

  servo1.attach(pinServo1, 500, 2400);
  servo2.attach(pinServo2, 500, 2400);

  Serial.println("Iniciando trazo de trayectoria en forma de infinito...");
}

// --------- Loop ----------
void loop() {
  for (int i = 0; i < N; i++) {
    float t = 2 * PI * i / N;

    float x = A * sin(t) + x_offset;
    float y = B * sin(t) * cos(t) + y_offset;

    moverEfector(x, y);
    delay(delay_ms);
  }
}
