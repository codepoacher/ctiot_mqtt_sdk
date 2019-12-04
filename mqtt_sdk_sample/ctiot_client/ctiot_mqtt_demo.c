#include "ctiot_mqtt_client.h"
#include "ctiot_log.h"
#include "MQTTClient.h"
#include "ctiot_os.h"

#include "ctiot_device_info.h"

#ifndef array_size
#define array_size(a) (sizeof(a)/sizeof(*(a)))
#endif

mqtt_client_s *g_phandle = NULL;

#include <string.h>



#ifdef NEED_DN_DATA
CTIOT_CB_FUNC ctiotCbFunc;
#endif

void ctiot_mqtt_demo_entry(void)
{
    int count = 0;
login:
    count = 0;
    mqtt_param_s ctiot_params;
    mqtt_device_info_s device_info;

    ctiot_params.server_ip = DEVICE_TCPADDRESS;
    ctiot_params.server_port = DEVICE_TCPPORT;

    ctiot_params.info.security_type = MQTT_SECURITY_TYPE_NONE;


	#ifdef NEED_DN_DATA
    if(CTIOT_OK != ctiot_mqtt_init(&ctiot_params, &ctiotCbFunc, &g_phandle))
	#else
	if (CTIOT_OK != ctiot_mqtt_init(&ctiot_params, NULL, &g_phandle))
	#endif
    {
        return;
    }

    device_info.codec_mode = MQTT_CODEC_MODE_JSON;
    device_info.connection_type = MQTT_STATIC_CONNECT;
    device_info.password = DEVICE_TOKEN;
    device_info.u.s_info.deviceid = DEVICE_ID;

	CTIOT_LOG(LOG_INFO, "deviceID: %s , password: %s ",device_info.u.s_info.deviceid,device_info.password);
    (void)ctiot_mqtt_login(&device_info, g_phandle);

    CTIOT_MSG_STATUS ret = CTIOT_SUCCESS;
    while(count < 1)
    {
        count ++;
        OS_SLEEP(1000);
        ret = ctiot_handleMessagr(g_phandle);
        if( ret == CTIOT_SUCCESS)
        {
            char * payload = NULL;
			DATA_REPORT_SIGNAL_REPORT para1 = { 0 };
			CTIOT_MSG_STATUS ret = ctiot_mqtt_encode_data_report_signal_report(&para1,&payload);
			CTIOT_LOG(LOG_INFO, "ctiot_mqtt_encode_data_report_signal_report result:%d",ret);
			if(ret != CTIOT_SUCCESS)
			{
				continue;
			}
			ret = ctiot_mqtt_msg_publish("signal_report", 0, payload);
			//OS_PUT_MEM(payload);
 			CTIOT_LOG(LOG_INFO, "ctiot_mqtt_msg_publish result : %d", ret);


            char * payload2 = NULL;
			DATA_REPORT_DATA_REPORT para2 = { 0 };
			CTIOT_MSG_STATUS ret2 = ctiot_mqtt_encode_data_report_data_report(&para2, &payload2);
			CTIOT_LOG(LOG_INFO, "ctiot_mqtt_encode_data_report_data_report result:%d",ret2);
			if(ret2 != CTIOT_SUCCESS)
			{
				continue;
			}
			ret2 = ctiot_mqtt_msg_publish("data_report", 0, payload2);
			//OS_PUT_MEM(payload);
 			CTIOT_LOG(LOG_INFO, "ctiot_mqtt_msg_publish result : %d", ret2);
        }
    }

    ctiot_mqtt_logout(g_phandle);

    OS_SLEEP(5000);
    goto login;
    return ;
}

