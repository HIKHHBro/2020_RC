﻿/**
	|------------------------------ Copyright -----------------------------------|
	|                                                                            |
	|                        (C) Copyright 2019,海康平头哥,                       |
	|           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
	|                            All Rights Reserved                             |
	|                                                                            |
	|           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
	|                    https://github.com/GCUWildwolfteam                      |
	|----------------------------------------------------------------------------|
	|--FileName    : bsp_usart.h                                                
	|--Version     : v1.0                                                            
	|--Author      : 海康平头哥                                                       
	|--Date        : 2019-01-15               
	|--Libsupports : 
	|--Description :1.添加rm和rc常用库文件  baseclass.h和baseclass.c                                                   
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|------------------------------declaration of end----------------------------|
 **/
#ifndef __BSP_USART_H 
#define __BSP_USART_H 
#include "baseclass.h "
typedef struct usartDataStrcut
{
	uint8_t a_frame_len;//一帧的长度
	uint8_t rx_buff_size;//接收校验长度
	uint8_t *rx_buff_data; //接收缓存空间地址
	uint8_t rx_on_off;   //数据接收开关
  uint16_t datalen;//一帧数据长度
	xQueueHandle usart_queue; //队列句柄
}usartDataStrcut;
SYS_Status UsartAndDMAInit(UART_HandleTypeDef *huartx,\
																	uint8_t frame_len,\
																	uint8_t on_off);
void UserUsartCallback(UART_HandleTypeDef *huartx);
SYS_Status NoLenRXforUsart(UART_HandleTypeDef *huartx);
SYS_Status UsartQueueCreate(usartDataStrcut *usartx, uint8_t len,
																	 uint8_t deep);
SYS_Status AllocateUsartxSpace(UART_HandleTypeDef *huartx);
usartDataStrcut *GetUsartAddr(UART_HandleTypeDef *huartx);
uint16_t UserUsartQueueRX(UART_HandleTypeDef *huartx, \
																	 uint8_t* pvBuffer); 
#define A_FRAME_CHECK_LEN 1//一帧接收缓存长度
#define DATA_LEN_BYTE_LEN 2//数据长度
#define DATA_LEN_BYTE_HIGH_8 0//数据长度高八位
#define DATA_LEN_BYTE_LOW_8  1//数据长度低八位
#define HEAD_FRAME_LEN (A_FRAME_CHECK_LEN + DATA_LEN_BYTE_LEN)
#define RX_HEAD_ADDR   2//接收数据的首地址
#define DATA_EMPTY     0//没数据
#define GET_A_FRAME_DATA_LEN(len)   (len + HEAD_FRAME_LEN)//计算接收一帧数据的长度
#define GET_DATA_ADDR(addr)         (addr + RX_HEAD_ADDR)//获取数据接收的真实地址
#endif // __BSP_USART_H

/*----------------------------------file of end-------------------------------*/
