#ifndef _XMLPARSER_H
#define _XMLPARSER_H

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

/************************************************************************/
/* 使用SAX解析xml                                                                     */
/************************************************************************/
namespace HN {
class XMLParser : public Ref, public SAXDelegator {
public:
    XMLParser();
    virtual ~XMLParser();

    static XMLParser* parseWithFile(const char *xmlFileName);
    static XMLParser* parseWithString(const char *content);
    string getString(const char *key);

    //对应xml标签开始,如：<string name="app_name">
    virtual void startElement(void *ctx, const char *name, const char **atts);
    //对应xml标签结束,如：</string>
    virtual void endElement(void *ctx, const char *name);
    //对应xml标签文本
    virtual void textHandler(void *ctx, const char *s, int len);

private:
    ValueMap m_Map;
    string m_key;
    string startXMLElement;
    string endXMLElement;

private:
    //从本地xml文件读取
    bool initWithFile(const char *xmlFileName);
    //从字符中读取，可用于读取网络中的xml数据
    bool initWithString(const char *content);
};

}
#endif // _XMLPARSER_H