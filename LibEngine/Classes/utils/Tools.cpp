//#include "stdafx.h"
#include "Tools.h"
#include "math.h"
#include <regex>
#include "HNBaseType.h"

namespace HN {

#define LSCANF(X) scanf("%I64d", &X)

bool Tools::verifyEmailAddress(const std::string &email) {
    std::regex pattern(
        "([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
    return std::regex_match(email, pattern);
}

bool Tools::verifyPhone(const std::string &phone) {
    return true;
}

bool Tools::verifyChinese(const std::string &word) {
    std::regex pattern("^[\u4e00-\u9fa5]+$");
    return std::regex_match(word, pattern);
}

bool Tools::verifyNumber(const std::string &word) {
    std::regex pattern("^[0-9]*$");
    return std::regex_match(word, pattern);
}

bool Tools::verifyNumberAndEnglish(const std::string &word) {
    std::regex pattern("^[A-Za-z0-9]+$");
    return std::regex_match(word, pattern);
}

std::string Tools::base64urlencode(const std::string &str) {
    std::string encode = str;
    std::string::size_type pos(0);
    while ((pos = encode.find("+")) != std::string::npos) {
        encode.replace(pos, 1, "%2B");
    }
    pos = 0;
    while ((pos = encode.find("/")) != std::string::npos) {
        encode.replace(pos, 1, "%2F");
    }
    return encode;
}

std::string Tools::addComma(LLONG value) {
    char buffer[64] = {0};
    sprintf(buffer, "%lld", value);
    char xin[100] = {0}; // 逗号分隔
    sprintf(xin, "%lld", value);

    int len = strlen(buffer);
    if (len > 4) { //超过四位数
        int wei = len % 4 > 0 ? len % 4 : 4;
        int j = 0;
        int idx = 0;
        for (int i = 0; i < len; i++) {
            if (wei == 0) { // 4的倍数
                if (idx++ == 3) {
                    xin[j++] = ',';
                    idx = 0;
                }
            } else { //非4的倍数
                if (idx++ == wei) {
                    xin[j++] = ',';
                    idx = 0;
                    wei = 3;
                }
            }
            xin[j++] = buffer[i];
        }
    }
    return std::string(xin);
}

std::string Tools::convertNumberOnlySignificantDigits(LLONG number) {
    char buffer[128] = {0};

    //不用格式化直接返回字符串
    sprintf(buffer, "%lld", number);
    return std::string(buffer);

    //如果为4位数字
    if (number <= 9999) {
        sprintf(buffer, "%lld", number);
    }
    // 5位数字
    else if (number > 9999 && number <= 99999) {
        sprintf(buffer, "%0.3f 万", number * 1.0f / 10000.0f);
    }
    // 6位数字
    else if (number > 99999 && number <= 999999) {
        sprintf(buffer, "%0.2f 万", number * 1.0f / 10000.0f);
    }
    // 7位数字
    else if (number > 999999 && number <= 9999999) {
        sprintf(buffer, "%0.1f 万", number * 1.0f / 10000.0f);
    }
    // 8位数字
    else if (number > 9999999 && number <= 99999999) {
        sprintf(buffer, "%d 万", number / 10000);
    }
    // 9位数字
    else if (number > 99999999 && number <= 999999999) {
        sprintf(buffer, "%0.3f 亿", number * 1.0f / 100000000.0f);
    }
    // 10位数字
    else if (number > 999999999 && number <= 9999999999) {
        sprintf(buffer, "%0.2f 亿", number * 1.0f / 100000000.0f);
    }
    // 11位数字
    else if (number > 9999999999 && number <= 99999999999) {
        sprintf(buffer, "%0.1f 亿", number * 1.0f / 100000000.0f);
    }
    // 12位数字及以上
    else if (number > 99999999999) {
        sprintf(buffer, "%lld 亿", number / 100000000);
    }
    return std::string(buffer);
}

std::string Tools::fourSeparateMoney(LLONG money) {
    char buffer[100] = {0};
    sprintf(buffer, "%lld", money);
    char xin[100] = {0}; // 逗号分隔
    {
        if (strlen(buffer) > 4) {
            int wei = strlen(buffer) % 4 > 0 ? strlen(buffer) % 4 : 4;
            int j = 0;
            int idx = 0;
            for (int i = 0; i < strlen(buffer); i++) {
                if (wei == 0) {
                    if (idx++ == 3) {
                        xin[j++] = ',';
                        idx = 0;
                    }
                } else {
                    if (idx++ == wei) {
                        xin[j++] = ',';
                        idx = 0;
                        wei = 3;
                    }
                }
                xin[j++] = buffer[i];
            }
            return xin;
        } else {
            return buffer;
        }
    }
}

std::string Tools::numberToChinese(LLONG money) {
    char *sNum[] = {"零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"};
    char *sBit[] = {"", "拾", "佰", "仟"};
    char *sTep[] = {"", "万", "亿", "万", "亿", "万", "亿"};
    char *blank = " ";
    char input[100];
    char output[500];
    LLONG m, n, i, j, isZero = 0;

    memset(output, 0, 500);
    j = money;
    n = (LLONG)log10((LLONG)j) + 1;
    for (i = 0; i < n; i++, j = j / 10)
        input[i] = (char)(j % 10);
    for (i = n - 1; i >= 0; i--) {
        j = input[i];
        if (j == 0)
            isZero = 1;
        else if (j > 0 && isZero == 1) { // N 个零完事了
            strcat(output, sNum[0]);
            isZero = 0;
        }
        if (j > 0) {
            strcat(output, sNum[j]);
            strcat(output, sBit[(i) % 4]);
        }
        if (i % 4 == 0) {
            int m = i + 4;
            if (m > n) {
                m = n;
            }
            bool bAllZero = true;
            for (int k = i; k < m; k++) {
                if (input[k] > 0) {
                    bAllZero = false;
                }
            }

            if (!bAllZero) {
                strcat(output, sTep[i / 4]);
                isZero = 0;
            }
        }
    }
    if (strlen(output) == 0)
        strcat(output, sNum[0]);
    return std::string(output);
}

Image *Tools::getImageData(const char *filename, Size &size) {
    Image *image = new Image();
    image->initWithImageFile(filename);
    size.width = image->getWidth();
    size.height = image->getHeight();
    return image;
}

//是否含有特殊字符 标点符号
bool Tools::isSpecialCharacter(const char *s) {
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] >= 0 && s[i] < 48)
            return false;
        if (s[i] >= 58 && s[i] <= 64)
            return false;
        if (s[i] >= 91 && s[i] <= 96)
            return false;
        if (s[i] >= 123 && s[i] <= 127)
            return false;
    }
    return true;
}

Color4B Tools::getPixelColor(unsigned char *data, const Vec2 &pos, Size size) {
    unsigned int x = pos.x, y = pos.y, width = size.width, height = size.height;
    Color4B c = {0, 0, 0, 0};
    unsigned int *pixel = (unsigned int *)data;
    pixel = pixel + ((height - y - 1) * width + x);
    c.r = *pixel & 0xff;
    c.g = (*pixel >> 8) & 0xff;
    c.b = (*pixel >> 16) & 0xff;
    c.a = (*pixel >> 24) & 0xff; //这个值  就是透明度
    log("r:%d,g:%d,b:%d,a:%d", c.r, c.g, c.b, c.a);
    return c;
}

}
