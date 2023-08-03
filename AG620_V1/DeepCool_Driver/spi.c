#include "spi.h"

/*SPI1引脚定义
* PA4---CS
* PA5---SCK
* PA6---MISO
* PA7---MOSI
*/

/******************************************************************************
      函数说明：spi GPIO初始化配置函数
      入口数据：无
      返回值：  无
******************************************************************************/
static void spi_gpio_config(void)
{
	gpio_init_type gpio_initstructure;//定义gpio结构体
	
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);//使能gpio时钟
  gpio_default_para_init(&gpio_initstructure);//gpio结构体设置默认值
	
	/* spi1 sck pin */
  gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;//推挽输出模式  
  gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;//较大电流推动/吸入能力
  gpio_initstructure.gpio_pull           = GPIO_PULL_NONE;  //gpio无上下拉
  gpio_initstructure.gpio_mode           = GPIO_MODE_MUX; //gpio复用模式
  gpio_initstructure.gpio_pins = GPIO_PINS_5;//PA5
  gpio_init(GPIOA, &gpio_initstructure);//赋值
  
  /* spi1 mosi pin */
  gpio_initstructure.gpio_pull           = GPIO_PULL_NONE;  
  gpio_initstructure.gpio_mode           = GPIO_MODE_MUX; 
  gpio_initstructure.gpio_pins = GPIO_PINS_7;//PA7 
  gpio_init(GPIOA, &gpio_initstructure);
  /*CS配置*/
  gpio_initstructure.gpio_pull           = GPIO_PULL_UP;//上拉模式 
  gpio_initstructure.gpio_mode           = GPIO_MODE_OUTPUT; //输出模式
  gpio_initstructure.gpio_pins = GPIO_PINS_4;//PA4
  gpio_init(GPIOA, &gpio_initstructure);
	
	GPIOA->odt_bit.odt4=1;
}

/******************************************************************************
      函数说明：spi1初始化配置函数
      入口数据：无
      返回值：  无
******************************************************************************/
void spi_config(void)
{
	spi_gpio_config();
	
  spi_init_type spi_init_struct;//定义spi结构体
  crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE);//使能spi时钟
	
  spi_default_para_init(&spi_init_struct);//默认spi配置
	
  spi_init_struct.transmission_mode = SPI_TRANSMIT_HALF_DUPLEX_TX;//单线双向只发模式
  spi_init_struct.master_slave_mode =SPI_MODE_MASTER;//主机模式
  spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_128;//128 分频
  spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_LSB;//先发送高位
  spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;//一帧包含 8bit 数据
  spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;//空闲时，时钟输出高电平
  spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;//第一个时钟沿进行数据采样
  spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;//硬件 CS 模式
  spi_init(SPI1, &spi_init_struct);
  spi_enable(SPI1, TRUE);//使能SPI
}

/******************************************************************************
      函数说明：spi数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void spi1_writ_byte(uint8_t dat)
{
    spi_i2s_data_transmit(SPI1,dat);
    /*REST表示非空*/
    while(spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == RESET); //如果非空,则一直等待
    /*RSET表示空闲*/
    while(spi_i2s_flag_get(SPI1, SPI_I2S_BF_FLAG) == TRUE);//如果忙碌,则一直等待
}
