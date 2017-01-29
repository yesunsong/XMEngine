#ifndef _APPLICATION_MACRO_H_
#define _APPLICATION_MACRO_H_

#include <string>
#include <sstream>
#include "cocos2d.h"
USING_NS_CC;

//应用的宏定义
//Android平台
#define ANDROID_PLATFROM       1;
//IOS正版
#define IOS_PLATFORM           2;
//IOS企业级应用
#define IOS_PLATFORM_IN_HOUSE  3;
//win平台
#define WINDOWS_PLATFORM	   4;

#define WIN_SIZE			Director::getInstance()->getWinSize()
#define VISIBLE_SIZE 		Director::getInstance()->getVisibleSize()
#define VISIBLE_ORIGIN		Director::getInstance()->getVisibleOrigin()


#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
template<typename T>
std::string to_string(const T& value) {
    std::ostringstream os;
    os << value;
    return os.str();
}
#endif

#endif // !_APPLICATION_MACRO_H_