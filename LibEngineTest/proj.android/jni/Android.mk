LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

#
MY_CPP_LIST := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/framework/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/test/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/test/LabelTest/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/test/pattern/component/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/test/SpriteTest/*.cpp)


LOCAL_SRC_FILES := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)
#

#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                  ../../Classes/AppDelegate.cpp \
#                   ../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
