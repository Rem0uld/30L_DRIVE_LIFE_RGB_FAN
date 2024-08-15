//
// Created by LiuLingJian on 24-8-12.
//

#include "UvcDrive.h"
#include "main.h"
#include "tim.h"
void UvcHighDrive()//UVC全电流输出
{
  HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);//关闭PWM输出
  __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,499);//设置占空比为99%（全电流输出）

  HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_2);//关闭PWM输出
  __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,499);//设置占空比为99%（全电流输出）

  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);//打开PWM输出
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);//打开PWM输出
}

void UvcLowDrive()//UVC低电流输出（抑菌模式）
{
  HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);//关闭PWM输出
  __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,5);//设置占空比为1%（低电流输出）


  HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_2);//关闭PWM输出
  __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,5);//设置占空比为1%（低电流输出）

  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);//打开PWM输出
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);//打开PWM输出
}

void UvcTest() {

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
  /*Configure GPIO pins : PAPin PAPin PAPin PAPin
                           PAPin */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
  /*Configure GPIO pins : PAPin PAPin PAPin PAPin
                           PAPin */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}