LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

FILE_LIST := hellocpp/main.cpp 
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/OC/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/OC/Android/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/crash/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/crash/Android/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/metro/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/demo/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ui/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ui/media/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ui/login/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ui/widget/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ui/income/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ui/publish/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ui/model/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ui/grab/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ui/chat/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ui/manage/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/tools/*.cpp)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
	
LOCAL_C_INCLUDES := $(shell find $(LOCAL_PATH)/../../Classes -type d)

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
