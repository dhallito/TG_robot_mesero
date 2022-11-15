#include "lector_rfid.h"

MFRC522 rfid(SS_PIN, RST_PIN);

void iniciar_rfid(){
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522
}

bool get_new_id(){
    if (rfid.PICC_IsNewCardPresent()){
      return true;
    }else{
      return false;
    }
//  if (rfid.PICC_IsNewCardPresent()) {
//    if (rfid.PICC_ReadCardSerial()) {
//      String new_tag_id; 
//      for (int i = 0; i < rfid.uid.size; i++) {
//          new_tag_id = new_tag_id + String(rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX);
//      }
//      rfid.PICC_HaltA();
//      rfid.PCD_StopCrypto1();
//      return new_tag_id;
//    }
//  }else{
//    return "";
//  }
}
