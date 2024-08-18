#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>
#include <Wire.h>

#define CAN0_INT 17                              
MCP_CAN can(2); 

#endif