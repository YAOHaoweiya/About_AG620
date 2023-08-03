/**
  **************************************************************************
  * @file     custom_usb_hid.h
  * @brief    自定义usb hid .h 文件
  **************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CUSTOM_USB_HID_H
#define __CUSTOM_USB_HID_H

/* Includes ------------------------------------------------------------------*/
#include "at32f425.h"
#include "at32f425_clock.h"
/*USB驱动文件*/
#include "usb_conf.h"
#include "usb_core.h"
#include "usbd_int.h"
#include "custom_hid_class.h"
#include "custom_hid_desc.h"



void custom_usb_hid_config(void);

#endif /* CUSTOM_USB_HID_H */
