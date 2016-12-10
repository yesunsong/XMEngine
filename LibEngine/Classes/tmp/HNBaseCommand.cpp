#include "HNBaseCommand.h"
#include "HNEngineExport.h"

LLONG getSecrectKey() {
    return 20150611;
}

INT getPlatformServerPort() {
    return 3015;
}

HN_Game_Type getGameType() {
    return HN_Game_Type::eMixGame;
}

void setPlatformServerAddress(std::string url) {
    PLATFORM_SERVER_ADDRESS = url;
}

std::string getPlatformServerAddress() {
    std::string address(PLATFORM_SERVER_ADDRESS);
    //by HBC
    return HN::HNSocket::domainToIP(address.c_str());

    if (HN::HNSocket::isValidIP(address)) {
        return address;
    } else {
        std::vector<std::string> ips = HN::HNSocket::getIpAddress(address.c_str());
        return ips.empty() ? "" : ips.at(0);
    }
}

std::string getPlatformServerHost() {
    std::string host(PLATFORM_SERVER_ADDRESS);
    return host;
}

void setAPIServerUrl(std::string url) {
    API_SERVER_URL = url;
}

std::string getAPIServerUrl() {
    return API_SERVER_URL;
}

void setWebServerUrl(std::string url) {
    WEB_SERVER_URL = url;
}

std::string getWebServerUrl() {
    return WEB_SERVER_URL;
}

std::string getUpdateURL() {
    return UPDATE_URL;
}

void setUpdateURL(std::string url) {
    UPDATE_URL = url;
}

void setAlipayNotifyURL(std::string url) {
    alipayNotifyURL = url;
}
std::string getAlipayNotifyURL() {
    return alipayNotifyURL;
}

std::string getPayType() {
    return PAY_TYPE;
}

void setPayType(std::string type) {
    PAY_TYPE = type;
}

//IAP内购参数相关
void setAppId(std::string appId) {
    APP_ID = appId;
}
std::string getAppId() {
    return APP_ID;
}

void setAppShareKey(std::string key) {
    APP_SHARE_KEY = key;
}
std::string getAppShareKey() {
    return APP_SHARE_KEY;
}

//是否是App Store上架版本
void setForAppStore(bool isAppStore) {
    FOR_APP_STORE = isAppStore;
}
bool getForAppStore() {
    return FOR_APP_STORE;
}

//是否是授信版本
void setExtendVersion(bool extendVersion)
{
    EXTEND_VERSION = extendVersion;
}
bool getExtendVersion()
{
    return EXTEND_VERSION;
}
