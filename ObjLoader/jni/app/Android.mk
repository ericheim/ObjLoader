LOCAL_PATH:= $(call my-dir)


include $(CLEAR_VARS)

LOCAL_MODULE    := libapp
LOCAL_MODULE_FILENAME:= libapp 
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../
LOCAL_CFLAGS    := -Werror -Wall -O4
LOCAL_SRC_FILES := app.cpp 
LOCAL_LDLIBS    := -lGLESv1_CM -ldl -llog -lz 
LOCAL_STATIC_LIBRARIES := libobj libzip libpng


include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_STATIC_LIBRARY)
