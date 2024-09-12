/*
 Esse codigo faz parte do inicio da aprendizagem sobre rede can
 O receptor recebe um pacote de dados e o exibe no monitor serial
 Utilizaremos um esp32 para o recebimento e um arduino uno para o envio
*/

#include "main.h"

void setup() {
  Serial.begin(115200);
  Wire.begin();
  // Inicializa o BMP085
  bmp085Calibration();
  if (can.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN Inicializado...");
  } else {
    Serial.println("Erro ao iniciar o CAN...");
  }
  pinMode(CAN0_INT, INPUT_PULLUP);
  pinMode(POT, INPUT);
  can.setMode(MCP_NORMAL);

}

void loop() {
  // Chama a rotina que calcula a temperatura
  // Esta rotina DEVE ser executada primeiro
  float temperature = bmp085GetTemperature(bmp085ReadUT());
  // Chama a rotina que calcula a pressao
  float pressure = bmp085GetPressure(bmp085ReadUP());
  // Chama a rotina que calcula atmosfera
  float atm = pressure / 101325;
  // Chama a rotina que calcula a altitude
  float altitude = calcAltitude(pressure);

  Serial.println();
  Serial.print("Temperatura: ");
  // Mostra a temperatura com 2 casas decimais
  Serial.print(temperature, 2);
  Serial.println(" C");
  Serial.print("Pressao: ");
  Serial.print(pressure, 0);
  Serial.println(" Pa");
  Serial.print("Atmosfera padrao : ");
  // Mostra o valor com 4 casas decimais
  Serial.println(atm, 4); //display 4 decimal places
  Serial.print("Altitude: ");
  // Mostra o valor com 2 casas decimais
  Serial.print(altitude, 2);
  Serial.println(" M");

  /* ADICIONE AQUI O CODIGO PARA ENVIAR OS DADOS PELA REDE CAN
     AMOSTRA DOS DADOS A SEREM ENVIADOS:
     TEMPERATURA: 24.90 
     PRESSAO: 101325
     ATMOSFERA: 0.98
     ALTITUDE: 840.74
  */
  potValue = analogRead(POT);
  Serial.print("Potenciometro: ");
  Serial.println(potValue);
  Serial.println();

  can.sendFloat(temperature, 0x01);
  can.sendFloat(pressure, 0x02);
  can.sendFloat(atm, 0x03);
  can.sendFloat(altitude, 0x04);
  can.sendInt(potValue, 0x05);

  delay(500);
}