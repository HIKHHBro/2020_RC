/**
	|------------------------------ Copyright -----------------------------------|
	|                                                                            |
	|                       (C) Copyright 2019,海康平头哥,                        |
	|          1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China       |
	|                            All Rights Reserved                             |
	|                                                                            |
	|          By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)          |
	|                     https://github.com/GCUWildwolfteam                     |
	|----------------------------------------------------------------------------|
	|--FileName    : sys_task.c                                                
	|--Version     : v2.0                                                            
	|--Author      : 海康平头哥                                                       
	|--Date        : 2019-01-15               
	|--Libsupports : 
	|--Description :                                                       
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|------------------------------declaration of end----------------------------|
 **/
#include "sys_task.h"
/* ----------------- 任务句柄 -------------------- */
	osThreadId startSysInitTaskHandle; 
	osThreadId startParseTaskHandle;
	osThreadId startGimbalTaskHandle;
	osThreadId startTxTaskHandle;//发送任务
/* ----------------- 任务钩子函数 -------------------- */
	void StartSysInitTask(void const *argument);
	void StartParseTask(void const *argument);
	void StartGimbalTask(void const *argument);
	void StartTxTask(void const *argument);
/* ----------------- 任务信号量 -------------------- */
//static uint8_t parse_task_status = 0;//数据解析任务工作状态标志
uint8_t enble_s = 0;
/**
	* @Data    2019-01-16 18:30
	* @brief   系统初始化
	* @param   void
	* @retval  void
	*/
	void SysInitCreate(void)
	{
		/* -------- 系统初始化任务创建 --------- */
		osThreadDef(sysInitTask, StartSysInitTask, osPriorityRealtime, 0, SYS_INIT_HEAP_SIZE);
		startSysInitTaskHandle = osThreadCreate(osThread(sysInitTask), NULL);
    /* -------- 帧率软定时创建 --------- */
#if defined (_FPS_)
    	FpsUserTimeInit();
#endif
	}
/**
	* @Data    2019-01-16 18:27
	* @brief   系统初始化钩子函数
	* @param   argument: Not used 
	* @retval  void
	*/
	void StartSysInitTask(void const * argument)
	{
    for(;;)
    {
			/* -------- 数据分析任务 --------- */
      osThreadDef(parseTask, StartParseTask, osPriorityHigh, 0, PARSE_HEAP_SIZE);
      startParseTaskHandle = osThreadCreate(osThread(parseTask), NULL);	
			/* ------ 云台任务 ------- */
			osThreadDef(gimbalTask, StartGimbalTask, osPriorityNormal, 0, GIMBAL_HEAP_SIZE);
      startGimbalTaskHandle = osThreadCreate(osThread(gimbalTask), NULL);
      osDelay(10);
      ProgressBarLed(LED_GPIO, 500);
      enble_s =1;
      vTaskResume(startParseTaskHandle);
      vTaskResume(startGimbalTaskHandle);
			/* -------- 删除系统任务 --------- */
			vTaskDelete(startSysInitTaskHandle);
    }
	}
	/**
	* @Data    2019-01-16 18:27
	* @brief   解析任务
	* @param   argument: Not used
	* @retval  void
	*/
	void StartParseTask(void const *argument)
	{
    ParseInit();
		for(;;)
		{
				ParseData();
				osDelay(2);
		}
	}
/**
	* @Data    2019-09-10 19:19
	* @brief   云台任务钩子函数
	* @param   argument: Not used
	* @retval  void
	*/
	void StartGimbalTask(void const *argument)
	{
    const dbusStruct* pRc_t;
    pRc_t = GetRcStructAddr();//遥控数据
    GimbalInit(pRc_t);
		for (;;)
		{  
			GimbalCtrl();
      osDelay(GIMBAL_PERIOD);
		}
	}
/**
	* @Data    2019-03-20 20:01
	* @brief   用户数据发送任务
	* @param   void
	* @retval  void
	*/
void StartTxTask(void const *argument){
	const dbusStruct* pRc_t;
	pRc_t = GetRcStructAddr();
	UserTxInit(pRc_t);
	for (;;)
	{ 
		UserTxControl();
			osDelay(4);
	}
}
/*----------------------------------file of end-------------------------------*/
  
