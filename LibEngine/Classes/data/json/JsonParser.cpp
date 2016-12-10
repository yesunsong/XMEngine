//#include "stdafx.h"
#include "JsonParser.h"
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;

namespace XM {
static rapidjson::Document doc;

JsonParser::JsonParser() {
}

JsonParser::~JsonParser() {
}

JsonParser* JsonParser::parseWithFile(const char *filename, ParseFlag flag) {
    std::string json = FileUtils::getInstance()->getStringFromFile(filename);
    if (flag==ParseFlag::DefaultFlags) {
        doc.Parse<rapidjson::kParseDefaultFlags>(json.c_str());
    } else if (flag == ParseFlag::InsituFlag) {
        doc.Parse<rapidjson::kParseInsituFlag>(json.c_str());
    }
    if (doc.HasParseError()) {
        return nullptr;
    }

    if (!doc.IsObject()) {
        return nullptr;
    }

    JsonParser* parser = new JsonParser();
    return parser;
}

JsonParser* JsonParser::parseWithString(const char *content) {
    return nullptr;
}

bool JsonParser::GetBool(const char* key) {
    if (doc.HasMember(key)) {
        return doc[key].GetBool();
    }
    return false;
}

double JsonParser::GetDouble(const char* key) {
    if (doc.HasMember(key)) {
        return doc[key].GetDouble();
    }
    return 0.0F;
}

int JsonParser::GetInt(const char* key) {
    if (doc.HasMember(key)) {
        return doc[key].GetInt();
    }
    return 0;
}

int64_t JsonParser::GetInt64(const char* key) {
    if (doc.HasMember(key)) {
        return doc[key].GetInt64();
    }
    return 0;
}

unsigned JsonParser::GetUint(const char* key) {
    if (doc.HasMember(key)) {
        return doc[key].GetUint();
    }
    return 0;
}

uint64_t JsonParser::GetUint64(const char* key) {
    if (doc.HasMember(key)) {
        return doc[key].GetUint64();
    }
    return 0;
}

const char* JsonParser::GetString(const char* key) {
    if (doc.HasMember(key)) {
        return doc[key].GetString();
    }
    return "";
}

int JsonParser::GetStringLength(const char* key) {
    if (doc.HasMember(key)) {
        return doc[key].GetStringLength();
    }
    return 0;
}

}
