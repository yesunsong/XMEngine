#ifndef _HN_ConverCode_h__
#define _HN_ConverCode_h__

#include <string>
#include "data/xml/XMLParser.h"

USING_NS_CC;

namespace HN {

class HNConverCode {
public:
    static void parseXML(const char* xml);
    static std::string GB2312ToUtf8(const char *gb2313);
    static std::string Utf8ToGB2312(const char *utf8);
    static std::string getString(const char* key);

    static std::string ForceGB2312ToUtf8(const char *gb2313);
    //static XMLParser* xmlParser;
private:

};
}

#define GBKToUtf8(object) HNConverCode::GB2312ToUtf8(object).c_str()
#define Utf8ToGB(object) HNConverCode::Utf8ToGB2312(object).c_str()
#define GetText(object) HN::HNConverCode::getString(object).c_str()

#define ForceGBKToUtf8(object) HNConverCode::ForceGB2312ToUtf8(object).c_str()

#endif // _HN_ConverCode_h__
