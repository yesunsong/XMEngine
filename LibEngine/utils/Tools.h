#ifndef __Tools_h__
#define __Tools_h__

#include "HNBaseType.h"
#include "cocos2d.h"
#include <string>
USING_NS_CC;

namespace HN {
class Tools {
public:
    static bool verifyEmailAddress(const std::string &email);
    static bool verifyPhone(const std::string &phone);
    static bool verifyChinese(const std::string &word);
    static bool verifyNumber(const std::string &word);
    static bool verifyNumberAndEnglish(const std::string &word);
    static std::string fourSeparateMoney(LLONG money);
    static std::string base64urlencode(const std::string &str);
    static std::string numberToChinese(LLONG money);
    static bool isSpecialCharacter(const char *s);
    //增加逗号
    static std::string addComma(LLONG value);
    /************************************************************************/
    /* 数字转换成带单位的字符串，保留4位有效数字  by HBC                    */
    /************************************************************************/
    static std::string convertNumberOnlySignificantDigits(LLONG number);

    static Image *getImageData(const char *filename, Size &size);
    static Color4B getPixelColor(unsigned char *data, const Vec2 &pos, Size size);
};
}


#endif // __Tools_h__