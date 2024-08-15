//
// Created by LiuLingJian on 24-8-14.
//

#include "FlowDrive.h"
#include "main.h"
#include "tim.h"
#include "usart.h"

uint16_t ccr1_cnt = 0;
uint16_t ccr2_cnt = 0;
uint16_t Period_cnt = 0;
uint16_t Period_cnt1 = 0;
uint16_t Period_cnt2 = 0;
uint16_t ic_flag = 0;
uint16_t end_flag = 0;

float frequency = 0;
float flow = 0;

void FreAndFlowCalcu(void) {

  HAL_Delay(100);
  if (end_flag) {
    frequency =1000000 / (float)(Period_cnt2 * 65536 + ccr2_cnt + 1); // 计算频率
    printf("\r\nfrequency= %.2f Hz", frequency);
    flow = (frequency+2) / 2.6; // 流量计算
    printf("\r\nflow= %.2f L/Min", flow);
    end_flag = 0;
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM3) {
    Period_cnt++;
  }
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
  if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
    if (end_flag == 0) {
      switch (ic_flag) {
      case 0: {
        __HAL_TIM_SET_COUNTER(&htim3, 0);
        ccr1_cnt = 0;
        ccr2_cnt = 0;
        Period_cnt = 0;
        Period_cnt1 = 0;
        Period_cnt2 = 0;
        __HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1,
                                      TIM_INPUTCHANNELPOLARITY_FALLING);
        ic_flag = 1;
        break;
      }
      case 1: {
        ccr1_cnt = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);
        Period_cnt1 = Period_cnt;
        __HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1,
                                      TIM_INPUTCHANNELPOLARITY_RISING);
        ic_flag = 2;
        break;
      }
      case 2: {
        ccr2_cnt = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);
        Period_cnt2 = Period_cnt;
        ic_flag = 0;
        end_flag = 1;
        break;
      }
      default:
        break;
      }
    }
  }
}