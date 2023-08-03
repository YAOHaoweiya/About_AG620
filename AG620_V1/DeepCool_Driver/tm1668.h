/**
  **************************************************************************
  * @file     tm1668.h
  * @brief   	tm1668驱动.h文件
  **************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TM1668_H
#define __TM1668_H

#include "spi.h"


/*******************************************************************************
                                显示模式命令设置
*******************************************************************************/
#define GRID4_SEG13 0x00    /* 4位13段 */
#define GRID5_SEG12 0x01    /* 5位12段 */
#define GRID6_SEG11 0x02    /* 6位11段 */
#define GRID7_SEG10 0x03    /* 7位10段 */

/*******************************************************************************
                                数据命令设置
*******************************************************************************/
#define CMD_DataWriteIncrease   0x40    /* 地址自增写数据 */
#define CMD_DataWriteFixed      0x44    /* 固定地址写数据 */


/*******************************************************************************
                                显示控制命令设置
*******************************************************************************/
#define DSP_01_16   0x88    /* 设置脉冲宽度为1/16  */
#define DSP_02_16   0x89    /* 设置脉冲宽度为2/16  */
#define DSP_04_16   0x8A    /* 设置脉冲宽度为4/16  */
#define DSP_10_16   0x8B    /* 设置脉冲宽度为10/16 */
#define DSP_11_16   0x8C    /* 设置脉冲宽度为11/16 */
#define DSP_12_16   0x8D    /* 设置脉冲宽度为12/16 */
#define DSP_13_16   0x8E    /* 设置脉冲宽度为13/16 */
#define DSP_14_16   0x8F    /* 设置脉冲宽度为14/16 8F*/
#define DSP_OFF     0x80    /* 显示关 */

/*******************************************************************************
                                地址命令设置
*******************************************************************************/
#define ADD_00H     0xC0    /* 显示地址: GRID1     */
#define ADD_01H     0xC1    /* 显示地址: GRID1     */
#define ADD_02H     0xC2    /* 显示地址: GRID2     */
#define ADD_03H     0xC3    /* 显示地址: GRID2     */
#define ADD_04H     0xC4    /* 显示地址: GRID3     */
#define ADD_05H     0xC5    /* 显示地址: GRID3     */
#define ADD_06H     0xC6    /* 显示地址: GRID4     */
#define ADD_07H     0xC7    /* 显示地址: GRID4     */
#define ADD_08H     0xC8    /* 显示地址: GRID5     */
#define ADD_09H     0xC9    /* 显示地址: GRID5     */
#define ADD_0AH     0xCA    /* 显示地址: GRID6     */
#define ADD_0BH     0xCB    /* 显示地址: GRID6     */
#define ADD_0CH     0xCC    /* 显示地址: GRID7     */
#define ADD_0DH     0xCD    /* 显示地址: GRID7     */


void TM1668_WriteBytesAddrIncrease(unsigned char *p, unsigned char nBytes, unsigned char brightness);
void TM1668_WriteBytesAddrFixed(unsigned char *p, unsigned char nBytes, unsigned char brightness);
void TM1668_Init(void);


#endif /* __TM1668_H */
