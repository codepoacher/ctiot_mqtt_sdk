中国电信终端SDK为物联网领域的开发人员推出，其目的是帮助开发者快速方便搭建终端与中国电信物联网使能平台的双向通信。
现有SDK版本是以标准 MQTT 协议对接中国电信物联网使能平台。
MQTT Linux SDK目录说明：
+-- demo        		: 简要样例程序目录
+-- doc                		: SDK使用文档
+-- READM.md   		: 快速开始说明
+-- mqtt_sdk_sample       	: 完整例程目录, 演示SDK的使用
|   +-- ctiot_client     	: 演示如何使用SDK API的全流程样例
+-- src
    +-- ctiot_client   		: 终端SDK的接口文件目录, 提供所有接口API
    +-- MQTTClient 		: 通信模块, 实现MQTT协议处理
    +-- MQTTPacket		: 通信模块, 实现MQTT协议处理
    +-- platform      		: 硬件平台抽象层, 存放不同嵌入式设备的抽象层接口实现

