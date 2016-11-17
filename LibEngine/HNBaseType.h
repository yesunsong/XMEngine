#ifndef __HN_BaseType_H__
#define __HN_BaseType_H__

typedef		char				CHAR;
typedef		unsigned char       BYTE;

typedef		unsigned short      WORD;

typedef		short               SHORT;

typedef		int					INT;
typedef		unsigned int		UINT;

typedef		long long			LLONG;

typedef		double              DOUBLE;
typedef		float               FLOAT;

#define		INVALID_VALUE			UINT(-1)
#define		INVALID_BYTE			BYTE(-1)
#define		INVALID_DESKNO			BYTE(-1)
#define		INVALID_DESKSTATION		BYTE(-1)
#define		INVALID_USER_ID         INT(-1)

#include <cstring>
#include <cassert>

enum emSocketStatus {
    //未知
    SocketStatus_UNKNOW = 0,

    SocketStatus_CONNECT,
    //超时
    SocketStatus_OUTTIME,
    SocketStatus_STCCESS,
    //接收消息
    SocketStatus_RECV,
    //断线
    SocketStatus_DISCONNECT,
    //出错
    SocketStatus_ERROR
};

#endif	//__HN_BaseType_H__
