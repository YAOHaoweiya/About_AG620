#include "tm1668.h"
/*
    开始传输数据
*/
static void TM1668_Start(void)
{
	GPIOA->odt_bit.odt4=0;
}

/*
    结束传输数据
*/
static void TM1668_End(void)
{
	GPIOA->odt_bit.odt4=1;
}



/*
	地址增加模式写入n个字节数据，从SRAM起始地址开始写
	p：写的数据首地址		nBytes：写入数据个数(<=14)		brightness：显示亮度
 */
void TM1668_WriteBytesAddrIncrease(unsigned char *p, unsigned char nBytes, unsigned char brightness)
{
	unsigned char i = 0;

	TM1668_Start();
	spi1_writ_byte(GRID7_SEG10);				/* 设置显示模式：7位10段 */
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(CMD_DataWriteIncrease);	/* 设置数据命令：地址自增 */
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(ADD_00H);					/* 设置显示地址：起始地址 */
	for (i = 0; i < nBytes; i++)
	{
		spi1_writ_byte(p[i]);
	}
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(brightness);				/* 显示控制命令：亮度调节 */
	TM1668_End();
}

/*
	地址固定模式写入n个字节数据，从SRAM起始地址开始写
	p：写的数据首地址		nBytes：写入数据个数(<=14)		brightness：显示亮度
 */
void TM1668_WriteBytesAddrFixed(unsigned char *p, unsigned char nBytes, unsigned char brightness)
{
	unsigned char i = 0;

	TM1668_Start();
	spi1_writ_byte(GRID7_SEG10);				/* 设置显示模式：7位10段 */
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(CMD_DataWriteFixed);		/* 设置数据命令：地址固定 */
	TM1668_End();

	for (i = 0; i < nBytes; i++)
	{
		TM1668_Start();
		spi1_writ_byte(ADD_00H + i);			/* 设置显示地址：起始地址 */
		spi1_writ_byte(p[i]);
		TM1668_End();
	}

	TM1668_Start();
	spi1_writ_byte(brightness);				/* 显示控制命令：亮度调节 */
	TM1668_End();
}

/*
    初始化，1668内部显示寄存器清零，防止出现乱码，并关闭显示
*/
void TM1668_Init(void)
{
	spi_config();
	
	unsigned char i = 0;

	TM1668_Start();
	spi1_writ_byte(GRID7_SEG10);				/* 设置显示模式：7位10段 */
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(CMD_DataWriteIncrease);	/* 设置数据命令：地址自增 */
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(ADD_00H);					/* 设置显示地址：起始地址 */
	for (i = 0; i < 14; i++)
	{
		spi1_writ_byte(0);
	}
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(DSP_OFF);				    /* 显示控制命令：亮度调节 */
	TM1668_End();
}
