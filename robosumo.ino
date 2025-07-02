#include <Dabble.h>

SoftwareSerial BTserial(11, 12); // RX→12, TX→11

// Пины моторов
#define LEFT_MOTOR_DIR 3
#define LEFT_MOTOR_PWM 5
#define RIGHT_MOTOR_DIR 6
#define RIGHT_MOTOR_PWM 9

void setup() {
  // Настройка пинов моторов
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  
  // Настройка связи
  Serial.begin(9600);
  BTserial.begin(9600);
  Dabble.begin(BTserial);
  
  Serial.println("Робот готов к управлению");
}

void setMotors(int leftSpeed, int rightSpeed) {
  // Левый мотор
  digitalWrite(LEFT_MOTOR_DIR, leftSpeed >= 0);
  analogWrite(LEFT_MOTOR_PWM, abs(leftSpeed));
  
  // Правый мотор
  digitalWrite(RIGHT_MOTOR_DIR, rightSpeed >= 0);
  analogWrite(RIGHT_MOTOR_PWM, abs(rightSpeed));
  
  Serial.print("Моторы: Л=");
  Serial.print(leftSpeed);
  Serial.print(" П=");
  Serial.println(rightSpeed);
}

void loop() {
  Dabble.processInput(); // Обработка команд
  
  if (GamePad.isUpPressed()) {
    setMotors(150, 150); // Вперёд
  }
  else if (GamePad.isDownPressed()) {
    setMotors(-150, -150);// Назад
  }
  else if (GamePad.isLeftPressed()) {
    setMotors(-100, 100); // Влево
  }
  else if (GamePad.isRightPressed()) {
    setMotors(100, -100); // Вправо
  }
  else if (millis() % 1000 == 0) {
    setMotors(0, 0); // Автостоп
  }
  
  delay(100);
}