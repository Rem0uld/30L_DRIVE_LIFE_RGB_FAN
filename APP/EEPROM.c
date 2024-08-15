//
// Created by LiuLingJian on 24-8-13.
//

#include "EEPROM.h"
#include "i2c.h"

#include <stdio.h>
#define AT24XX_WRITE 0xA0 // 写地址
#define AT24XX_READ 0xA1  // 读地址
#define BuffSize 64        // 缓冲区
unsigned char AppVer[] = {"Test Write"};
unsigned char ReadBuff[16];

void AT24CWrite() {
  int i = 0;
  for (i;i<sizeof(AppVer)+1;i++)
    HAL_I2C_Mem_Write(&hi2c1,AT24XX_WRITE,i,I2C_MEMADD_SIZE_8BIT,AppVer,sizeof(AppVer),1000);
    HAL_Delay(20);
}
void AT24CRead() {
HAL_I2C_Mem_Read(&hi2c1,AT24XX_READ,0,I2C_MEMADD_SIZE_8BIT,ReadBuff,sizeof(ReadBuff),1000);

}