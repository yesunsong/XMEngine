LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

#$(call import-add-path,$(LOCAL_PATH)/../../LibHNNet)
#$(call import-add-path,$(LOCAL_PATH)/../../LibHNUI)
#$(call import-add-path,$(LOCAL_PATH)/../../LibHNMarket)
#$(call import-add-path,$(LOCAL_PATH)/../../LibHNOpen)

LOCAL_MODULE := lib_engine_static

LOCAL_MODULE_FILENAME := libEngine

#
MY_CPP_LIST := $(wildcard $(LOCAL_PATH)/../LibEngine/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/audio/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/data/json/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/data/xml/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/encryption/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/globel/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/math/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/network/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/pattern/command/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/pattern/mvc/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/pattern/state/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/pattern/physics/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/pattern/platform/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/pattern/render/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/pattern/test/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/ui/base/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/ui/extensions/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../LibEngine/utils/*.cpp)

LOCAL_SRC_FILES := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)
#
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../HNLobby \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../HNLobby/Shop \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../HNLobby/PersionalCenter \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../HNLobby/GameMenu \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../HNLobby/ChildLayer \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../game/BJL/Classes/GameMessage \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../game/DZPoker/Classes/GameMessage \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../game/GoldenToad/Classes/GameMessage \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../game/Landlord/Classes/GameMessage \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../game/NN/Classes/GameMessage \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../game/Stud/Classes/GameMessage \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../game/ThirteenZhang/Classes/GameMessage \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../game/TTNN/Classes/GameMessage

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.. \
                           $(LOCAL_PATH)/../../../../cocos2d \
                           $(LOCAL_PATH)/../../../../cocos2d/cocos \


LOCAL_EXPORT_LDLIBS := -llog \
                        -lz \
                        -landroid
                        
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,.)
