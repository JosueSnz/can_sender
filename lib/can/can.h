#ifndef CAN_H
#define CAN_H

#include "Arduino.h"
#include <mcp_can.h>
#define CAN0_INT 27 // verificar a pinagem

class CAN : public MCP_CAN
{
  using MCP_CAN::MCP_CAN;
  private:

  public:
    long unsigned int rxId;
    unsigned char len = 0;
    unsigned char rxBuf[8];
    char msgString[128]; 
    void sendFloat(float valor, uint16_t id);
    void sendInt(uint16_t valor, uint16_t id);
    void sendDig(uint8_t valor, uint16_t id);
    void readCan();
    void scanCan();
};

float convertByte(byte *rxBuf);

#endif