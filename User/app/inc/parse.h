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
	|--FileName    : parse.h                                                
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
#ifndef __PARSE_H 
#define __PARSE_H  
 #include "pc_data.h" 
 #include "hmi_usart.h" 
 #include "DJI_dbus.h" 
 #include "pc_data.h" 
 #include "gimbal.h"  
 void ParseInit(void);
 void ParseData(void);
 	const dbusStruct* GetRcStructAddr(void);
	uint32_t GetRcStatus(void);
	uint32_t GetPcDataStatus(void);
  const pcDataStruct* GetPcDataStructAddr(void);
#endif	// __PARSE_H
/*-----------------------------------file of end------------------------------*/


