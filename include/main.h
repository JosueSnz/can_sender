#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>
#include <Wire.h>
#include "can.h"
#include "gy80.h"

CAN can(10); // verificar a pinagem

#define POT A0   
int potValue = 0;                     

#endif