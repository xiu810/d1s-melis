/*
********************************************************************************
*                                USB Hid Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld. 
*                        All Right Reserved 
*
* FileName		:  usbMouse.h
*
* Author		:  Javen
*
* Date			:  2010.06.02
*
* Description	:  USB Mouse
*
* Others		:  NULL
*
* History:
*		<time> 		<version >		<author>	 	<desc>
*	   2010.06.02	   1.0			 Javen			build this file 
*
********************************************************************************
*/
#ifndef  __USBMOUSE_H__
#define  __USBMOUSE_H__
#include "mod_usbhost.h"
#include "drivers/sys_device.h"

#ifndef DATA_TYPE_X___hdle
#define DATA_TYPE_X___hdle
typedef unsigned int        __hdle;
#endif
#define	 USB_OS_HANDLE	__hdle		//epos��handle

#define  USB_HID_MOUSE_DATA_LEN		64    	/* ������ݵ���󳤶� 	*/
#define  USB_HID_MOUSE_DITHER_AREA	127  	/* ���ȥ������Χ 		*/

/* mouse report */
#define  USB_HID_MOUSE_REPORT_BUTTON_LEFT_BIT	0	/* ������ */
#define  USB_HID_MOUSE_REPORT_BUTTON_RIGHT_BIT	1	/* ����Ҽ� */
#define  USB_HID_MOUSE_REPORT_BUTTON_MIDDLE_BIT	2	/* ����м����м�������²����İ��� */
#define  USB_HID_MOUSE_REPORT_BUTTON_SIDE_BIT	3
#define  USB_HID_MOUSE_REPORT_BUTTON_EXTRA_BIT	4

#if	 0
#define DMSG_MOUSE_TEST   hal_log_info 
#else
#define DMSG_MOUSE_TEST(...) 
#endif


/* �����ȡ�������ݵĶ��� */
typedef struct _usbMouseDataDef{
	usbHidEvnetExcursion_t Button;	/* button 	*/
	usbHidEvnetExcursion_t X;		/* X 		*/
	usbHidEvnetExcursion_t Y;		/* Y 		*/
	usbHidEvnetExcursion_t Wheel;	/* Wheel 	*/
}usbMouseDataDef_t;

#define  USB_HID_DEV_MAGIC    0x5a13d099
typedef struct _usbMouse{
	unsigned int Magic;	             	/* ��ʾ�豸�Ƿ�Ϸ�					*/
	
	HidDev_t *HidDev;
	unsigned int DevNo;					/* ���豸��							*/
    unsigned char  ClassName[32];			/* �豸����, ��"disk" 				*/
    unsigned char  DevName[32];				/* ���豸��, ��"SCSI_DISK_000"		*/

    /* Disk information */
	unsigned int used;                     /* ���豸���� 					*/
	__dev_devop_t MouseOp;			/* �豸�������� 					*/

    /* Disk manager */
	USB_OS_HANDLE MouseParaHdle;	/* openʱ�ľ��						*/
	USB_OS_HANDLE MouseRegHdle;		/* regʱ�ľ�� 						*/

    unsigned char Vendor[256];
	unsigned char Product[256];
    unsigned char Serial[32];

    void *MouseThdId;						/* ��������¼��̵߳�ID 			*/
	hal_sem_t MouseThreadSemi;
	hal_sem_t notify_complete;	/* ͬ��thread����/ɾ�� 				*/

	HidRequest_t HidReq;					/* hid�������� 						*/
	unsigned char Data[USB_HID_MOUSE_DATA_LEN];		/* ������귵�ص����� 				*/
	usbMouseDataDef_t DataDef;				/* ������ݵĶ��� 					*/
	unsigned int StopWork;							/* ���ֹͣ��������closeʱ���� 		*/

	/* test */
	unsigned int USBMouseTestFlag;					/* ���Ա�־ */
	USBHMouseTest_t *USBHMouseTest;	

	USBHMouseEvent_t MouseEvent;	  		/* ��ǰ����app������¼� */
	USBHMouse_CallBack CallBack;

	void *Extern;							/* ��չ�ṹ����MouseDriftControl_t */
}usbMouse_t;

#endif   //__USBMOUSE_H__
