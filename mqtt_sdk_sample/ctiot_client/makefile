
#
# a Makefile to build sample.c which can be release to customer if they want
#


.PHONY: clean, release, build_linux

CC ?= gcc
#CC = /home/wsg/mpu/openwrt/staging_dir/toolchain-arm_gcc-andromeda/bin/arm-oe-linux-gnueabi-gcc
#CC = /home/wsg/WD100/openwrt/staging_dir/toolchain-mips_gcc-ar71xx/bin/mips-openwrt-linux-uclibc-gcc
#export STAGING_DIR=/home/wsg/WD100/openwrt/staging_dir/toolchain-mips_gcc-ar71xx/bin:$STAGING_DIR
AR ?= ar
OS ?= linux
TLS ?= 0
IMAGE_NAME ?= ctiot_mqtt_client

CCFLAGS = -c -O

INCLUDE_PATH_FLAG = -I../../src/MQTTClient   \
                    -I../../src/MQTTPacket   \
                    -I../../src/platform     \
                    -I../../src/ctiot_client \
					-I./

SOURCE_FILES_C = ../../src/MQTTClient/MQTTLinux.c                  \
				 ../../src/MQTTClient/MQTTClient.c                 \
				 ../../src/MQTTPacket/MQTTConnectClient.c          \
				 ../../src/MQTTPacket/MQTTConnectServer.c          \
				 ../../src/MQTTPacket/MQTTDeserializePublish.c     \
				 ../../src/MQTTPacket/MQTTFormat.c                 \
				 ../../src/MQTTPacket/MQTTPacket.c                 \
				 ../../src/MQTTPacket/MQTTSerializePublish.c       \
				 ../../src/MQTTPacket/MQTTSubscribeClient.c        \
				 ../../src/MQTTPacket/MQTTSubscribeServer.c        \
				 ../../src/MQTTPacket/MQTTUnsubscribeClient.c      \
				 ../../src/MQTTPacket/MQTTUnsubscribeServer.c      \
				 ../../src/platform/ctiot_os.c                     \
				 ../../src/ctiot_client/ctiot_log.c                \
				 ../../src/ctiot_client/cJSON.c                    \
				 ../../src/ctiot_client/ctiot_mqtt_client.c        \
				 ../../src/ctiot_client/ctiot_memory.c             \
				 main.c                                            \
				 ctiot_mqtt_demo.c                                 




ifeq ($(OS),linux)
	BUILD_VARIANT = build_linux
endif

ifeq ($(TLS), 1)
CCFLAGS += -DUSE_MBEDTLS
endif

ifneq ($(TLS), 0)
MBED_DIR := ../../src/Mbedtls/baseLib
MBED_SOURCES := $(wildcard $(MBED_DIR)/*.c)

INCLUDE_PATH_FLAG += -I../../src/Mbedtls/baseLib   \
					 -I../../src/Mbedtls/errorType \
					 -I../../src/Mbedtls/network   \
					 -I../../src/Mbedtls/timer     \

SOURCE_FILES_C +=  $(MBED_SOURCES)
endif

OBJS = $(subst .c,.o,${SOURCE_FILES_C})

CCFLAGS += ${INCLUDE_PATH_FLAG}


build_linux: ${OBJS}
	${CC} -g -o ${IMAGE_NAME}  ${OBJS} -lpthread  -ldl


%.o: %.c
	${CC} ${CCFLAGS} -o $@ $< 


clean:
	-rm -f ${OBJS}
	-rm ${IMAGE_NAME}


