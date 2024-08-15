//
// Created by LiuLingJian on 24-8-12.
//

#include "SysAdcValue.h"
#include "adc.h"
#include "main.h"

#include <stdio.h>
uint16_t SystemAdcValue[9] = {0};


void SystemInfo() {
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)SystemAdcValue,sizeof(SystemAdcValue)); // 开启ADC DMA，将数据存储进数组
  float SysInVi = 0.0;
  float SysOutIo = 0.0;
  SysInVi = SystemAdcValue[0]/4096.0*24;
  printf("System Voltage = %.2f V\r\n",SysInVi);
  SysOutIo = SystemAdcValue[8];
  printf("UVC1 Current Output = %.2f mA\r\n",SysOutIo);
  HAL_ADC_Stop_DMA(&hadc1); // 关闭ADC DMA

}
