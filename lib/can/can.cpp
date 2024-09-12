#include "can.h"

void CAN::sendInt(uint16_t valor,uint16_t id)
{
  uint8_t hb= highByte(valor);
  uint8_t lb= lowByte(valor);

  byte data[8] = {hb, lb};
  byte sndStat = this->sendMsgBuf(id, 0, 2, data);
  Serial.println(sndStat);
}

void CAN::sendFloat(float valor,uint16_t id)
{
  byte data[4];
  memcpy(data, (unsigned char*) (&valor), 4);

  byte sndStat = this->sendMsgBuf(id, 0, 4, data);
  Serial.println(sndStat);
}

void CAN::sendDig(uint8_t valor,uint16_t id)
{
  byte data[8] = {valor};
  byte sndStat = this->sendMsgBuf(id, 0, 1, data);
  Serial.println(sndStat);
}

float convertByte(byte *rxBuf)
{
  float valor;
  memcpy(&valor, rxBuf, sizeof(valor));
  return valor;
}

void CAN::readCan(){
  this->readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
}

void CAN::scanCan(){
  if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
    sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
  else
    sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);

  Serial.print(msgString);

  if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
    sprintf(msgString, " REMOTE REQUEST FRAME");
    Serial.print(msgString);
  } else {
    for(byte i = 0; i<len; i++){
      sprintf(msgString, " 0x%.2X", rxBuf[i]);
      Serial.print(msgString);
    }
  }
  Serial.println();
}  