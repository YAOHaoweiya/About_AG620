#include "AG620_Show.h"



#include "delay.h"
#include "string.h"
#include "stdlib.h"

static const u8 TM1668_10X7_CODE[11]={0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};//数字0-9 和灭
static const u8 USAGE_RATE[6]={0,0X01,0X03,0x07,0x0F,0x1F};//利用率 灯


static u8 led_data[14];

static u8 NOW_CRATE=0;//利用率 值
static u8 NOW_Mode=STAND;
static u8 CH=0;//数字百位
static u8 CT=0;//数字十位
static u8 CO=0;//数字个位
static u8 Alarm_flag=0;
static u16 stand_count=5000;

#define ALARM_DELAY 600 //报警倒计时300ms*2
static u16 d_count=ALARM_DELAY;

/******************************************************************************
      函数说明：数据清空
      入口数据：无
      返回值：  无
******************************************************************************/
static void data_clear(void)
{
	u8 i;
	//清空
	for(i=0;i<14;i++)
		led_data[i]=0x00;
}
/******************************************************************************
      函数说明：所有灯全灭
      入口数据：无
      返回值：  无
******************************************************************************/
static void all_led_off(void)
{
	data_clear();
	TM1668_WriteBytesAddrIncrease(led_data,14,DSP_14_16);	//显示一次修改
}
/******************************************************************************
      函数说明：所有灯全亮
      入口数据：无
      返回值：  无
******************************************************************************/
static void all_led_on(void)
{
	u8 i;
	//清空
	for(i=0;i<14;i++)
		led_data[i]=0xFF;
	TM1668_WriteBytesAddrIncrease(led_data,14,DSP_14_16);	//显示一次修改
}
/******************************************************************************
      函数说明：数码管数显初始化函数
      入口数据：无
      返回值：  无
******************************************************************************/
void ag620_show_init(void)
{
	TM1668_Init();

}


/******************************************************************************
      函数说明：数字显示
      入口数据：无
      返回值：  无
******************************************************************************/
static void number(u8 HUNDRED,u8 TEN,u8 ONE)
{
	//百位
	//if(HUNDRED>0)
		//led_data[4]=TM1668_10X7_CODE[HUNDRED];
	//十位
	//if(HUNDRED>0|TEN>0)
	if(TEN>0)
		led_data[0]=TM1668_10X7_CODE[TEN];
	//个位
		led_data[2]=TM1668_10X7_CODE[ONE];
}
/*********************************************************************************************************
      函数说明：数据映射函数
      入口数据：receive_mode 模式；receive_CH 百位；receive_CH 十位；receive_CH 个位；Alarm 报警标志
      返回值：  无
*********************************************************************************************************/
void num_map(u8 receice_mode,u8 receive_CH,u8 receive_CT,u8 receive_CO,u8 Alarm)
{
	NOW_Mode=receice_mode;
	CH=receive_CH;
	CT=receive_CT;
	CO=receive_CO;
	Alarm_flag=Alarm;
	stand_count=5000;
}

/*********************************************************************************************************
      函数说明：显示处理函数
      入口数据：无
      返回值：  无
*********************************************************************************************************/
void AG620_show(void)
{
	data_clear();
	switch(NOW_Mode)
	{
		case ALL_MODE:
			all_led_on();	
			d_count=ALARM_DELAY;
		return;
		
		case STAND:
			all_led_off();
			d_count=ALARM_DELAY;		
		return;
		
		case TEMP_C:
					led_data[4]=0x01;
			/*温度模式下报警处理*/		
		if(Alarm_flag)
		{
				if(d_count>(ALARM_DELAY/2))
				{
					data_clear();
					led_data[4]=0x01;
					number(CH,CT,CO);
					TM1668_WriteBytesAddrIncrease(led_data,14,DSP_14_16);	//显示一次修改
					
				}
				else 
				{
					all_led_off();
				}
				
				delay_ms(1);
				d_count--;
				if(d_count==0)
						d_count=ALARM_DELAY;	
				return;
				
		}				
			break;
		
		case Pw:
				led_data[4]=0x04;
			/*功率模式下报警处理*/
		if(Alarm_flag)
		{
				if(d_count>(ALARM_DELAY/2))
				{
					data_clear();
					led_data[4]=0x05;
					number(CH,CT,CO);
					TM1668_WriteBytesAddrIncrease(led_data,14,DSP_14_16);	//显示一次修改
					
				}
				else 
				{
					data_clear();
					led_data[4]=0x04;
					number(CH,CT,CO);
					TM1668_WriteBytesAddrIncrease(led_data,14,DSP_14_16);	//显示一次修改
				}
				
				delay_ms(1);
				d_count--;
				if(d_count==0)
						d_count=ALARM_DELAY;	
				return;
				
		}				
			
			break;
		
		default:
			
			break;	
	}
	

	number(CH,CT,CO);//数字显示函数
	TM1668_WriteBytesAddrIncrease(led_data,14,DSP_14_16);	
	
}

void stand_read(void)
{
	
	stand_count--;
	delay_ms(1);
	if(stand_count==0)
	{
		stand_count=5000;
		NOW_Mode=STAND;
	}
	
}

void mydelay(unsigned int ms)
	
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
	{
		for(j=0;j<1000;j++)
		{
			__NOP();
		}
		
	}
}
