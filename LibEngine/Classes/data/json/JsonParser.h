#ifndef _JSON_PARSER_H_
#define  _JSON_PARSER_H_

#include "cocos2d.h"
USING_NS_CC;

namespace XM {

//自定义解析标签，这样子才具有更大的扩展性
enum ParseFlag {
    DefaultFlags = 0,		//!< Default parse flags. Non-destructive parsing. Text strings are decoded into allocated buffer.
    InsituFlag = 1			//!< In-situ(destructive) parsing.
};

class JsonParser {
public:
    JsonParser();
    ~JsonParser();

public:
    static JsonParser* parseWithFile(const char *filename, ParseFlag flag = ParseFlag::DefaultFlags);
    static JsonParser* parseWithString(const char *content);

    bool GetBool(const char* key);
    double GetDouble(const char* key);
    int GetInt(const char* key);
    int64_t GetInt64(const char* key);
    unsigned GetUint(const char* key);
    uint64_t GetUint64(const char* key);
    const char* GetString(const char* key);
    int GetStringLength(const char* key);

private:

};
}

#endif //  _JSON_PARSER_H_