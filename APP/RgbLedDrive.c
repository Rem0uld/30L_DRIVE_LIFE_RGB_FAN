//
// Created by LiuLingJian on 24-8-12.
//

#include "RgbLedDrive.h"
#include "gpio.h"
#include "main.h"
enum Colors;
enum State;

void ShowLedColor(int Colors, int State) {
  HAL_GPIO_WritePin(GPIOA, RED_Pin | GREEN_Pin | BLUE_Pin, GPIO_PIN_SET);
  switch (Colors) {
  case RED:
    if (State == ON)
      HAL_GPIO_WritePin(GPIOA, RED_Pin, GPIO_PIN_RESET);
    else
      HAL_GPIO_WritePin(GPIOA, RED_Pin, GPIO_PIN_SET);
    break;
  case GREEN:
    if (State == ON)
      HAL_GPIO_WritePin(GPIOA, GREEN_Pin, GPIO_PIN_RESET);
    else
      HAL_GPIO_WritePin(GPIOA, GREEN_Pin, GPIO_PIN_SET);
    break;
  case BLUE:
    if (State == ON)
      HAL_GPIO_WritePin(GPIOA, BLUE_Pin, GPIO_PIN_RESET);
    else
      HAL_GPIO_WritePin(GPIOA, BLUE_Pin, GPIO_PIN_SET);
    break;
  case ALL:
    if (State == ON)
      HAL_GPIO_WritePin(GPIOA, RED_Pin | GREEN_Pin | BLUE_Pin, GPIO_PIN_RESET);
    else
      HAL_GPIO_WritePin(GPIOA, RED_Pin | GREEN_Pin | BLUE_Pin, GPIO_PIN_SET);
    break;
  default:
    break;
  }
}