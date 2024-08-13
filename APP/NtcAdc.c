//
// Created by LiuLingJian on 24-8-12.
//

#include "NtcAdc.h"
#include "main.h"
#include "adc.h"
#include "math.h"
uint16_t NtcValue[8]={0};
int8_t Ntc1Adc = 0;
int8_t Ntc2Adc = 0;
int8_t Ntc3Adc = 0;
int8_t Ntc4Adc = 0;


void GetNtcValue() {
    HAL_ADC_Start_DMA(&hadc1,(uint32_t*)NtcValue,8);
    Ntc1Adc = NtcValue[3];
    Ntc2Adc = NtcValue[1];
    Ntc3Adc = NtcValue[4];
    Ntc4Adc = NtcValue[5];

}

