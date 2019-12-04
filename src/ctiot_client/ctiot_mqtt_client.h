#ifndef _CTIOT_MQTT_CLIENT_H
#define _CTIOT_MQTT_CLIENT_H

#include <stdbool.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef   signed char  SDK_S8;
typedef unsigned char  SDK_U8;

typedef     short int  SDK_S16;
typedef unsigned short SDK_U16;

typedef   signed int   SDK_S32;
typedef unsigned int   SDK_U32;

typedef unsigned long long SDK_U64;

typedef enum
{
    CTIOT_OK                   = 0,
    CTIOT_ARG_INVALID          = -1,
    CTIOT_BUF_OVERFLOW         = -2,
    CTIOT_MSG_CONGEST          = -3,
    CTIOT_MALLOC_FAILED        = -4,
    CTIOT_RESOURCE_NOT_FOUND   = -5,
    CTIOT_RESOURCE_NOT_ENOUGH  = -6,
    CTIOT_CLIENT_UNREGISTERED  = -7,
    CTIOT_SOCKET_CREATE_FAILED = -8,
    CTIOT_ERR                  = -9,
    CTIOT_YIELD_ERROR          = -10
} CTIOT_STATUS;

#ifndef MQTT_COMMAND_TIMEOUT_MS
#define MQTT_COMMAND_TIMEOUT_MS (10 * 1000)
#endif

#ifndef MQTT_EVENTS_HANDLE_PERIOD_MS
#define MQTT_EVENTS_HANDLE_PERIOD_MS (1*1000)
#endif

#ifndef MQTT_KEEPALIVE_INTERVAL_S
#define MQTT_KEEPALIVE_INTERVAL_S (100)
#endif

#ifndef MQTT_SENDBUF_SIZE
#define MQTT_SENDBUF_SIZE (1024 * 2)
#endif

#ifndef MQTT_READBUF_SIZE
#define MQTT_READBUF_SIZE (1024 * 2)
#endif

/* the unit is milisecond */
#ifndef MQTT_WRITE_FOR_SECRET_TIMEOUT
#define MQTT_WRITE_FOR_SECRET_TIMEOUT (30 * 1000)
#endif

/* MQTT retry connection delay interval. The delay inteval is
(MQTT_CONN_FAILED_BASE_DELAY << MIN(coutinious_fail_count, MQTT_CONN_FAILED_MAX_TIMES)) */
#ifndef MQTT_CONN_FAILED_MAX_TIMES
#define MQTT_CONN_FAILED_MAX_TIMES  6
#endif

/*The unit is millisecond*/
#ifndef MQTT_CONN_FAILED_BASE_DELAY
#define MQTT_CONN_FAILED_BASE_DELAY 1000
#endif

typedef struct mqtt_client_tag_s mqtt_client_s;

typedef enum
{
    MQTT_SECURITY_TYPE_NONE,
    MQTT_SECURITY_TYPE_PSK,
    MQTT_SECURITY_TYPE_CA,
    MQTT_SECURITY_TYPE_MAX
}mqtt_security_type_e;

typedef struct
{
    uint8_t *psk_id;
    uint32_t psk_id_len;
    uint8_t *psk;
    uint32_t psk_len;
}mqtt_security_psk_s;

typedef struct
{
    char *ca_crt;
    uint32_t ca_len;
}mqtt_security_ca_s;

typedef struct
{
    mqtt_security_type_e security_type;
    union
    {
        mqtt_security_psk_s psk;
        mqtt_security_ca_s ca;
    }u;
}mqtt_security_info_s;

typedef struct
{
    char *server_ip;
    char *server_port;
    mqtt_security_info_s info;
}mqtt_param_s;

typedef enum
{
    MQTT_STATIC_CONNECT, //static connection, one device one password mode
    MQTT_DYNAMIC_CONNECT,//dynamic connection, one product type one password mode
    MQTT_MAX_CONNECTION_TYPE
}mqtt_connection_type_e;

typedef struct
{
    char *deviceid;
}mqtt_static_connection_info_s;

typedef enum
{
    MQTT_QOS_MOST_ONCE,  //MQTT QOS 0
    MQTT_QOS_LEAST_ONCE, //MQTT QOS 1
    MQTT_QOS_ONLY_ONCE,  //MQTT QOS 2
    MQTT_QOS_MAX
}mqtt_qos_e;

typedef enum
{
    MQTT_CODEC_MODE_BINARY,
    MQTT_CODEC_MODE_JSON,
    MQTT_MAX_CODEC_MODE
}mqtt_codec_mode_e;

typedef struct
{
    mqtt_connection_type_e connection_type;
    mqtt_codec_mode_e codec_mode;
    char *password;
    union
    {
        mqtt_static_connection_info_s s_info;
    }u;
}mqtt_device_info_s;

//*************************************************
//
//! @addtogroup 消息状态
//!
//! @{
//
//*************************************************
typedef enum{
    CTIOT_SUCCESS = 0,
    CTIOT_PUBLISH_ERROR,
    CTIOT_PARA_ERROR,
	CTIOT_TYPE_ERROR,
}CTIOT_MSG_STATUS;
//*************************************************
//
//! @}
//
//*************************************************

//*************************************************
//
//! @addtogroup 公共API接口
//!
//! @{
//
//*************************************************
//**************************************************
//
//! @brief ctiot_mqtt登录
//!
//! @param mqtt_device_info_s 设备信息结构体
//! @param mqtt_client_s mqtt_client句柄
//!
//! @retval  int 返回结果码
//!
//**************************************************
CTIOT_MSG_STATUS ctiot_mqtt_msg_publish(char *topic, mqtt_qos_e qos, char* payload);
//**************************************************
//
//! @brief ctiot_mqtt参数初始化
//!
//! @param mqtt_param_s 初始化结构体
//! @param callback_struct 回调函数结构体 
//! @param mqtt_client_s 返回初始化的mqtt_client 
//!
//! @retval  int 返回结果码
//!
//**************************************************
int ctiot_mqtt_init(const mqtt_param_s *params, void *callback_struct, mqtt_client_s **phandle);
//**************************************************
//
//! @brief ctiot_mqtt登录
//!
//! @param mqtt_device_info_s 设备信息结构体
//! @param mqtt_client_s mqtt_client句柄
//!
//! @retval  int 返回结果码
//!
//**************************************************
int ctiot_mqtt_login(const mqtt_device_info_s* device_info, mqtt_client_s* phandle);

//**************************************************
//
//! @brief ctiot_mqtt接受消息
//!
//! @param mqtt_device_info_s 设备信息结构体
//!
//! @retval  int 返回结果码
//!
//**************************************************
CTIOT_STATUS ctiot_handleMessagr(mqtt_client_s* phandle);

//**************************************************
//
//! @brief ctiot_mqtt登出
//!
//! @param mqtt_device_info_s 设备信息结构体
//!
//! @retval  int 返回结果码
//!
//**************************************************
CTIOT_STATUS ctiot_mqtt_logout(mqtt_client_s* phandle);

//**************************************************
//
//! @brief 查看ctiot_mqtt是否连接
//!
//! @param mqtt_device_info_s 设备信息结构体
//!
//! @retval  int 返回结果码
//!
//**************************************************
int ctiot_mqtt_isconnected(mqtt_client_s* phandle);
//*************************************************
//
//! @}
//
//*************************************************


//*************************************************
//
//! @addtogroup service为signal_report的数据结构体
//!
//! @{
//
//*************************************************
typedef struct {
	mqtt_qos_e qos;     //!< QOS等级
	int rsrp;    //!< 
	int sinr;    //!< 
	int pci;    //!< 
	int ecl;    //!< 
	int cell_id;    //!< 
} DATA_REPORT_SIGNAL_REPORT; 
//*************************************************
//
//! @}
//
//*************************************************

//*************************************************
//
//! @addtogroup service为data_report的数据结构体
//!
//! @{
//
//*************************************************
typedef struct {
	mqtt_qos_e qos;     //!< QOS等级
	char* wifi_pwd;    //!< 
	char* wifi_name;    //!< 
} DATA_REPORT_DATA_REPORT; 
//*************************************************
//
//! @}
//
//*************************************************


//*************************************************
//
//! @addtogroup 非公共API接口
//!
//! @{
//
//*************************************************
//**************************************************
//
//! @brief service为signal_report
//!
//! @param DATA_REPORT_SIGNAL_REPORT 参见@ref DATA_REPORT_SIGNAL_REPORT
//!
//! @retval  CTIOT_MSG_STATUS 返回结果码
//!
//**************************************************
CTIOT_MSG_STATUS ctiot_mqtt_encode_data_report_signal_report(DATA_REPORT_SIGNAL_REPORT* para,char** payload);

//**************************************************
//
//! @brief service为data_report
//!
//! @param DATA_REPORT_DATA_REPORT 参见@ref DATA_REPORT_DATA_REPORT
//!
//! @retval  CTIOT_MSG_STATUS 返回结果码
//!
//**************************************************
CTIOT_MSG_STATUS ctiot_mqtt_encode_data_report_data_report(DATA_REPORT_DATA_REPORT* para,char** payload);

//*************************************************
//
//! @}
//
//*************************************************

#ifdef __cplusplus
}
#endif

#endif //_CTIOT_MQTT_CLIENT_H
