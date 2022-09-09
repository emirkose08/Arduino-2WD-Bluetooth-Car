// TELEFON ÜZERİNDEN BLUETOOTH ARACILIĞIYLA KONTROL EDİLEBİLEN 2WD ARABA PROJEMİN KODLARI -Emir Köse

//Motor Sürücü Bağlantılarımız
const int motorA1  = 5;  // L298N'in IN3 Girişi
const int motorA2  = 9;  // L298N'in IN1 Girişi
const int motorB1  = 6; // L298N'in IN2 Girişi
const int motorB2  = 10;  // L298N'in IN4 Girişi

// Değişken Tanımlama
 
char state; //Bluetooth Modülünden Gelecek Olan Sinyal Üzerinden Daha Sonra İşlem Yapacağımız İçin Onu Bir Değişkene Atıyoruz
int vSpeed = 255;   // Standart Hız, 0-255 arası bir değer alabilir

void setup() {
  // Motor Pinlerimizi Çıktı Olarak Belirleyelim
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  // 9600 baud hızında bir seri port açalım
  Serial.begin(9600);
}

void loop() {
  Serial.print(state);
  Serial.print(" ");
  Serial.println(vSpeed);

  /*Bluetooth Bağlantısı Koptuğunda Veya Kesildiğinde Arabayı Durdur. */
    
  if (digitalRead(state) == LOW) {
    state = 'S';
  }

  //Seri Haberleşme "1" Değerindeyse Bluetooth Üzerinden Gelen Veriyi Başta Tanımladığımız "state" Değişkenine Kaydet
  if (Serial.available() > 0) {
    state = Serial.read();
  }

  /* Uygulamadan Ayarlanabilen 4 Hız Seviyesi.(Değerler 0-255 Arasında Olmalı)*/
  if (state == '0') {
    vSpeed = 0;
  }
  else if (state == '1') {
    vSpeed = 100;
  }
  else if (state == '2') {
    vSpeed = 180;
  }
  else if (state == '3') {
    vSpeed = 200;
  }
  else if (state == '4') {
    vSpeed = 255;
  }

  //Gelen veri 'F' ise araba ileri gider.
  if (state == 'F') {
    analogWrite(motorA1, vSpeed); analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 0);      analogWrite(motorB2, 0);
  }
  //Gelen veri 'G' ise araba ileri sol(çapraz) gider.
  else if (state == 'G') {
    analogWrite(motorA1, 200 ); analogWrite(motorA2, 100);
    analogWrite(motorB1, 0);    analogWrite(motorB2, 0);
  }
  //Gelen veri 'I' ise araba ileri sağ(çapraz) gider.
  else if (state == 'I') {
    analogWrite(motorA1, 100); analogWrite(motorA2, 200);
    analogWrite(motorB1, 0);      analogWrite(motorB2, 0);
  }
  //Gelen veri 'B' ise araba geri gider.
  else if (state == 'B') {
    analogWrite(motorA1, 0);   analogWrite(motorA2, 0);
    analogWrite(motorB1, vSpeed);   analogWrite(motorB2, vSpeed);
  }
  //Gelen veri 'H' ise araba geri sol(çapraz) gider
  else if (state == 'H') {
    analogWrite(motorA1, 0);   analogWrite(motorA2, 0);
    analogWrite(motorB1, 100); analogWrite(motorB2, 200);
  }
  //Gelen veri 'J' ise araba geri sağ(çapraz) gider
  else if (state == 'J') {
    analogWrite(motorA1, 0);   analogWrite(motorA2, 0);
    analogWrite(motorB1, 200);   analogWrite(motorB2, 100);
  }
  //Gelen veri 'L' ise araba sola gider.
  else if (state == 'L') {
    analogWrite(motorA1, 200);   analogWrite(motorA2, 100);
    analogWrite(motorB1, 0); analogWrite(motorB2, 0);
  }
  //Gelen veri 'R' ise araba sağa gider
  else if (state == 'R') {
    analogWrite(motorA1, 100);   analogWrite(motorA2, 200);
    analogWrite(motorB1, 0);   analogWrite(motorB2, 0);
  }

  //Gelen veri 'S' ise arabayı durdur.
  else if (state == 'S') {
    analogWrite(motorA1, 0);  analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
  }
}
