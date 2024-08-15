//
// Created by LiuLingJian on 24-8-12.
//

#include "SmartFan.h"
#include "adc.h"
#include "gpio.h"
#include "main.h"
#include "math.h"
#include <stdio.h>

uint16_t AdcValue[7] = {0}; // 所有ADC值数组
const float Rp = 10.0;      // 25℃NTC阻值，单位k
const float T2 = (273.15 + 25.0);
const float Bx = 3950.0; // B值
const float Ka = 273.15; // k值

void FanDrive(uint8_t FANS, uint8_t State) {
  switch (FANS) {
  case 1:
    if (State == 1) {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    } else {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
    }
  case 2:
    if (State == 1) {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
    } else {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
    }
  default:
    break;
  }
}

void SmartFan() {
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)AdcValue,
                    sizeof(AdcValue)); // 开启ADC DMA，将数据存储进数组
  float Rntc1, Rntc2, Rntc3, Rntc4 = 0.0;
  float Temp1, Temp2, Temp3, Temp4 = 0.0;

  Rntc1 = 11.0 / (4096.0 / AdcValue[2] - 1); // 计算Rntc阻值
  Rntc2 = 11.0 / (4096.0 / AdcValue[1] - 1); // 计算Rntc阻值
  Rntc3 = 11.0 / (4096.0 / AdcValue[3] - 1); // 计算Rntc阻值
  Rntc4 = 11.0 / (4096.0 / AdcValue[4] - 1); // 计算Rntc阻值

  Temp1 = 1.0 / (log(Rntc1 / Rp) / Bx + 1 / T2) - Ka; // 计算温度值(B值法)
  printf("Temp1 = %.2f C\r\n", Temp1);
  Temp2 = 1.0 / (log(Rntc2 / Rp) / Bx + 1 / T2) - Ka; // 计算温度值(B值法)
  printf("Temp2 = %.2f C\r\n", Temp2);
  Temp3 = 1.0 / (log(Rntc3 / Rp) / Bx + 1 / T2) - Ka; // 计算温度值(B值法)
  printf("Temp3 = %.2f C\r\n", Temp3);
  Temp4 = 1.0 / (log(Rntc4 / Rp) / Bx + 1 / T2) - Ka; // 计算温度值(B值法)
  printf("Temp4 = %.2f C\r\n", Temp4);
  HAL_ADC_Stop_DMA(&hadc1); // 关闭ADC DMA

  if (Temp1 && Temp2 >= 45.0) {
    FanDrive(1, 1);
  } else {
    FanDrive(1, 0);
  }
  if (Temp3 && Temp4 >= 45.0 ) {
    FanDrive(2,1);
  }else {
    FanDrive(2,0);
  }
}
