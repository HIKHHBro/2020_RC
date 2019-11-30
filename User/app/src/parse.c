/**
	|--------------------------------- Copyright --------------------------------|
	|                                                                            |
	|                      (C) Copyright 2019,海康平头哥,                         |
	|           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
	|                           All Rights Reserved                              |
	|                                                                            |
	|           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
	|                    https://github.com/GCUWildwolfteam                      |
	|----------------------------------------------------------------------------|
	|--FileName    : parse.c                                              
	|--Version     : v1.0                                                          
	|--Author      : 海康平头哥                                                     
	|--Date        : 2019-02-02             
	|--Libsupports : 
	|--Description :                                                     
	|--FunctionList                                                     
	|-------1. ....                                                     
	|          <version>:                                                     
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|-----------------------------declaration of end-----------------------------|
 **/
#include "parse.h" 
/* -------------- 结构体 ----------------- */
 dbusStruct dbus_t; //大疆遥控
 //pcDataStruct pc_t; //openmv数据
 //hmiStrct hmi_t;    //串口屏
/* -------------- 外部链接 ----------------- */
extern osThreadId startParseTaskHandle;
extern UART_HandleTypeDef huart1;//串口1
	/**
	* @Data    2019-02-14 14:36
	* @brief   数据解析任务初始化
	* @param   void
	* @retval  void
	*/
void ParseInit(void)
{
  DJIDbusInit(&dbus_t,&huart1);//大疆遥控初始化
  //PcDataRxInit(&pc_t);         //openmv数据接收初始化
  //HmiUsartInit(&hmi_t);        //串口屏初始化
  /* -------- 挂起等待任务系统初始化 --------- */
	vTaskSuspend(startParseTaskHandle);
}

	/**
	* @Data    2019-02-14 14:36
	* @brief   数据解析
	* @param   void
	* @retval  void
	*/
	void ParseData(void)
	{
    DbusParseData(&dbus_t);//遥控数据解析
    //Pc_ParseData(&pc_t);//openmv数据解析
    //HmiUsartParseData(&hmi_t);
	}
 /*
	* @Data    2019-02-24 11:59
	* @brief   获取遥控构体地址
	* @param   void
	* @retval  void
	*/
	const dbusStruct* GetRcStructAddr(void)
	{
		return &dbus_t;
	}
	/**
	* @Data    2019-03-13 15:30
	* @brief   
	* @param   void
	* @retval  void
	*/
	uint32_t GetRcStatus(void)
	{
		return (dbus_t.status);
	}

  void can_rx(uint32_t id,uint8_t *data)
  {
		GimbalParseDate(id,data);
  }
void can2_rx(uint32_t id,uint8_t *data)
{
      //ChassisParseDate(id,data);
}
/*-----------------------------------file of end------------------------------*/


