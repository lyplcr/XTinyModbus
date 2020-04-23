/********************************************************************************
* @File name: MD_RTU_Serial.h
* @Author: zspace
* @Version: 1.0
* @Date: 2020-4-10
* @Description: Modbus RTU �������ģ��
********************************************************************************/

#ifndef _MDM_RTU_SERIAL_H__
#define _MDM_RTU_SERIAL_H__

/*********************************ͷ�ļ�����************************************/
#include "MD_RTU_Type.h"
/*********************************����******************************************/

/*********************************��������************************************/
/*Ӳ����ʼ�����������ڴ˳�ʼ������*/
void MDMInitSerial(void* obj,uint32 baud,uint8 dataBits,uint8 stopBit,uint8 parity);
/*bsp���жϽ��յ����������*/
void MDMSerialRecvByte(uint8 byte);
/*��ʱ���е��øú���*/
void MDMTimeHandler100US(void);
/*********************************����******************************************/

#endif