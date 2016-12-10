#ifndef _HNBaseCommand_H__
#define _HNBaseCommand_H__

#include "HNBaseType.h"
#include <string>

#define		HN_TARGET_PHONE_ONLY    0x01  //手游独立平台，和PC、网页数据不互通
#define		HN_TARGET_MIX_PLATFORM  0x02  //混合平台，和PC、网页数据互通

//登录服务器地址
static std::string PLATFORM_SERVER_ADDRESS;
// 服务器地址（更新）
static std::string WEB_SERVER_URL;
// API接口地址（公告、支付）
static std::string API_SERVER_URL;
//版本更新
static std::string UPDATE_URL;
//支付宝回调地址
static std::string alipayNotifyURL;
//不同地区支付类型
static std::string PAY_TYPE;
static std::string APP_ID;
static std::string APP_SHARE_KEY;

static bool FOR_APP_STORE;
//是否是授信版本
static bool EXTEND_VERSION;

enum HN_Game_Type {
    eSingleGame = 0, // single game.
    eMixGame    = 1, // mix game.
};

// 此处为密钥由客户自己管理，设置在整数范围
LLONG getSecrectKey();

// 平台的端口
INT getPlatformServerPort();

// 获取游戏类型
HN_Game_Type getGameType();

// 平台的登录ID地址
void setPlatformServerAddress(std::string url);
std::string getPlatformServerAddress();
std::string getPlatformServerHost();

// 获取API接口地址
void setAPIServerUrl(std::string url);
std::string getAPIServerUrl();

// 获取域名Url
void setWebServerUrl(std::string url);
std::string getWebServerUrl();

void setUpdateURL(std::string url);
std::string getUpdateURL();

//支付宝回调地址
void setAlipayNotifyURL(std::string url);
std::string getAlipayNotifyURL();

//不同地区IAP参数配置
void setPayType(std::string type);
std::string getPayType();

void setAppId(std::string appId);
std::string getAppId();

void setAppShareKey(std::string key);
std::string getAppShareKey();

//是否是App Store上架版本
void setForAppStore(bool isAppStore);
bool getForAppStore();

//是否是授信版本，true为授信版本，false为App Store上架版本
void setExtendVersion(bool extendVersion);
bool getExtendVersion();

// 目标平台类型
#define		HN_TAREGET_PLATFORM HN_TARGET_MIX_PLATFORM

#endif	//_HNBaseCommand_H__
