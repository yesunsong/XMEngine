#ifndef _APPLICATION_MACRO_H_
#define _APPLICATION_MACRO_H_

#include "cocos2d.h"

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

#endif // !_APPLICATION_MACRO_H_