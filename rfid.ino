#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("RFID okuyucu hazır. Kartı okutun...");
}

void loop() {
  // Yeni kart var mı?
  if (!rfid.PICC_IsNewCardPresent()) return;

  // Kart okunabiliyor mu?
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("Kart UID: ");

  // Kart UID'ni yazdır
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }

  Serial.println();

  // Kart türünü yazdır
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.print("Kart Tipi: ");
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Okuma işlemini kapat
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
