#ifndef _HN_NetMessageHall_H_
#define _HN_NetMessageHall_H_

#include "HNBaseType.h"
#include "tmp/HNComStruct.h"

//////////////////////////////////////////////////////////////////////////
///常量定义
#define		MAX_PEOPLE				180				//最大游戏人数 百家乐
#define		MAX_SEND_SIZE			2044			//最大消息包
#define		MAX_TALK_LEN			500				//最大聊天数据长度
#define		NORMAL_TALK_LEN			200				//普通聊天数据长度

//////////////////////////////////////////////////////////////////////////
//游戏通讯指令宏定义

//////////////////////////////////////////////////////////////////////////
// 客户端到服务端心跳指令
#define		MDM_CONNECT			1
#define		ASS_NET_TEST_1		1
#define		ASS_NET_TEST_2		2

//////////////////////////////////////////////////////////////////////////

// 大厅主标识
#define		MDM_GP_CONNECT					1			// 连接消息类型
#define		MDM_GP_LOGONUSERS	 			119			// 统计登录人数
#define		ASS_GP_LOGONUSERS_COUNT			1
//////////////////////////////////////////////////////////////////////////
// 快速登录主ID和，辅助ID标志
#define		MDM_GP_REGISTER			       99			// 快速登录
#define		MDM_GP_IMEI						   139		// 2016 9 21 快速登录 wzx 
#define		ASS_GP_REGISTER					0			//
#define		ERR_REGISTER_ERROR				0			// 注册失败
#define		ERR_REGISTER_SUCCESS			1			// 注册成功
#define		ERR_REGISTER_NAME_EXIST			2			// 用户名存在

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

// 支付通知主ID和，辅助ID标志
#define		MDM_GP_NOTIFY_PAY				88			//
#define		ASS_GP_NOTIFY_PAY				1			//

//////////////////////////////////////////////////////////////////////////

//游戏主标识
#define		MDM_GM_GAME_FRAME				150			//框架消息
#define		MDM_GM_MESSAGE					151			//信息消息


//大厅辅助处理消息标志
#define		ASS_GP_NET_TEST					1			//网络测试
#define		ASS_GP_CONNECT_SUCCESS 			3			//连接成功

//////////////////////////////////////////////////////////////////////////
//大厅登陆
#define		MDM_GP_LOGON					100
#define		ASS_GP_LOGON_BY_NAME			1			//通过用户名字登陆
#define		ASS_GP_LOGON_BY_ACC				2			//通过用户ACC 登陆
#define		ASS_GP_LOGON_BY_MOBILE			3			//通过用户手机登陆
#define		ASS_GP_LOGON_REG				4			//用户注册
#define		ASS_GP_LOGON_SUCCESS			5			//登陆成功
#define		ASS_GP_LOGON_ERROR				6			//登陆失败
#define		ASS_GP_LOGON_ALLO_PART			7			//异地登陆
#define		ASS_GP_LOGON_LOCK_VALID			8			//锁机验证
#define		ASS_GP_LOGON_BY_SOFTWARE        10
#define		ASS_GP_LOGON_MOBILE_VALID		11			//手机验证

#define		ASS_GP_IMEI									1			//2016 9 21 WZx本机登录

/// 错误代码
#define		ERR_GP_ERROR_UNKNOW				0		    //未知错误
#define		ERR_GP_LOGON_SUCCESS			1		    //登陆成功
#define		ERR_GP_USER_NO_FIND				2		    //登陆名字错误
#define		ERR_GP_USER_PASS_ERROR			3		    //用户密码错误
#define		ERR_GP_USER_VALIDATA			4		    //用户帐号禁用
#define		ERR_GP_USER_IP_LIMITED			5		    //登陆 IP 禁止
#define		ERR_GP_USER_EXIST				6		    //用户已经存在
#define		ERR_GP_PASS_LIMITED				7		    //密码禁止效验
#define		ERR_GP_IP_NO_ORDER				8		    //不是指定地址 
#define		ERR_GP_LIST_PART				9		    //部分游戏列表
#define		ERR_GP_LIST_FINISH				10		    //全部游戏列表
#define		ERR_GP_USER_LOGON				11		    //此帐号已经登录
#define		ERR_GP_USERNICK_EXIST			12		    //此昵称已经存在
#define		ERR_GP_USER_BAD					13		    //未法字符
#define		ERR_GP_IP_FULL					14		    //IP已满
#define		ERR_GP_LOCK_SUCCESS				15		    //锁定机器成功	
#define		ERR_GP_ACCOUNT_HAS_LOCK			16		    //机器已经处于锁定状态	
#define		ERR_GP_UNLOCK_SUCCESS			17		    //解除锁定成功 
#define		ERR_GP_NO_LOCK					18		    //机器根本就没有锁定，所以解锁失败 
#define		ERR_GP_CODE_DISMATCH			19		    //机器码不匹配，解锁失败。
#define		ERR_GP_ACCOUNT_LOCKED			20		    //本账号锁定了某台机器，登录失败
#define		ERR_GP_MATHINE_LOCKED			21
#define		ERR_GP_USER_BaiMingDan			34			//客户端给了的提示是服务器正在维护中

// 第三方认证返回的错误码
#define		ERR_GP_USER_NOT_EXIST           30			// 用户不存在
#define		ERR_GP_USER_OVERDATE            31			// 用户已过期

#define		EXP_GP_ALLO_PARTY				50			//本账号异地登陆

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

#define		MDM_GP_LIST						101			// 游戏列表

///通信辅助标识
#define		ASS_GP_LIST_KIND				1			//获取游戏类型列表
#define		ASS_GP_LIST_NAME				2			//获取游戏名字列表
#define		ASS_GP_LIST_ROOM				3			//获取游戏房间列表
#define		ASS_GP_LIST_COUNT				4			//获取游戏人数列表
#define		ASS_GP_ROOM_LIST_PEOCOUNT		5			//获取游戏人数列表
#define		ASS_GP_ROOM_PASSWORD			6			//发送房间密码,试图进入密码房间时发送此消息
#define		ASS_GP_GET_SELLGAMELIST			7			//获取游戏销售列表

//////////////////////////////////////////////////////////////////////////
//添加用户资料管理通讯协议
#define		MDM_GP_USERINFO	 				115
#define		ASS_GP_USERINFO_UPDATE_BASE		1		//用户更新基本信息
#define		ASS_GP_USERINFO_UPDATE_DETAIL	2		//用户更新详细信息
#define		ASS_GP_USERINFO_UPDATE_PWD		3		//用户修改密码
#define		ASS_GP_USERINFO_ACCEPT			5		//服务端已接受
#define		ASS_GP_USERINFO_NOTACCEPT		6		//服务端未能接受
#define		ASS_GP_USERINFO_NOTACCEPT_BADWORD 8		//服务端未能接受（敏感词汇）
#define		ASS_GP_USERINFO_NICKNAMEID		10		//根据玩家昵称找ID或ID找昵称
//////////////////////////////////////////////////////////////////////////

//2016 7 21 更换用户头像字段
#define MDM_GP_SET_LOGO						113
#define ASS_GP_SET_LOGO						1


/////////////////////////////////////////////////////////////////////////
//用户设置头像 2016 7 21
struct MSG_GP_S_SET_LOGO {
    INT       iUserID;
    UINT     iLogoID;
};

struct MSG_GP_R_SetLogo {
    UINT	dwCommanResult;			//请求的结果
};

//////////////////////////////////////////////////////////////////////////
///	网络通信数据包定义

// 连接成功消息
typedef struct tagMSG_S_ConnectSuccess {
    BYTE							bMaxVer;									//最新版本号码
    BYTE							bLessVer;									//最低版本号码
    BYTE							bReserve[2];								//保留字段
    LLONG							i64CheckCode;						//加密后的校验码，由客户端解密在包头中返回
} GNUC_PACKED MSG_S_ConnectSuccess;

// 用户登陆（帐号）结构
typedef struct tagMSG_GP_S_LogonByNameStruct {
    UINT								uRoomVer;						//大厅版本
    CHAR								szName[64];						//登陆名字
    CHAR								TML_SN[128];
    CHAR								szMD5Pass[52];					//登陆密码
    CHAR								szMathineCode[64];				//本机机器码 锁定机器
    CHAR                                szCPUID[24];					//CPU的ID
    CHAR                                szHardID[24];					//硬盘的ID
    CHAR								szIDcardNo[64];					//证件号
    CHAR								szMobileVCode[8];				//手机验证码
    BYTE								byCheckEx;						//检查扩展
    INT									gsqPs;
    INT									iUserID;						//用户ID登录，如果ID>0用ID登录
    char								szImei[64];						///Imei	2016-9-13 linshilong
    char								szNetType[64];					///网络类型 2016-9-13 linshilong
    char								szUDID[64];						///客户端唯一标识 2016-11-2 linshilong
#if (HN_TAREGET_PLATFORM == HN_TARGET_PHONE_ONLY)
    UINT								uNameID;
#endif
} GNUC_PACKED MSG_GP_S_LogonByNameStruct;

// 大厅登录返回结果
typedef struct tagMSG_GP_R_LogonResult {
    INT									dwUserID;							//用户 ID
    INT									dwGamePower;						//游戏权限
    INT									dwMasterPower;						//管理权限
    INT									dwMobile;							//手机号码
    INT									dwAccID;							//Acc 号码
    UINT								dwLastLogonIP;						//上次登陆 IP
    UINT								dwNowLogonIP;						//现在登陆 IP
    UINT								bLogoID;							//用户头像
    bool								bBoy;								//性别
    CHAR								szName[61];							//用户登录名
    CHAR								TML_SN[128];						//数字签名
    CHAR								szMD5Pass[50];						//用户密码
    CHAR								nickName[32];						//用户昵称
    LLONG								i64Money;							//用户金币
    LLONG								i64Bank;							//用户财富
    INT									dwFascination;						//魅力
    //LLONG                               iLotteries;                         //奖券

    //新用户资料
    CHAR								szSignDescr[128];					//个性签名
    CHAR								szRealName[20];						//真实姓名
    CHAR								szIDCardNo[36];						//证件号
    CHAR								szMobileNo[50];						//移动电话
    CHAR								szQQNum[20];						//QQ号码
    CHAR								szAdrNation[50];					//玩家的国藉
    CHAR								szAdrProvince[50];					//玩家所在的省份
    CHAR								szAdrCity[50];						//玩家所在的城市
    CHAR								szZipCode[10];						//邮政编码
    CHAR								szEmail[50];						//电子邮件
    CHAR								szAddress[128];						//联系地址
    CHAR								szSchooling[20];					//文化程度
    CHAR								szHomePage[128];					//个人主页
    CHAR								szTelNo[20];						//固定电话
    CHAR								szMSNID[50];						//MSN帐号

    INT									dwTimeIsMoney;						///上次登陆时长所换取的金币
    INT									iVipTime;							///
    INT									iDoublePointTime;					///双倍积分时间
    INT									iProtectTime;						///护身符时间，保留
    bool								bLoginBulletin;						///是否有登录公告
    INT									iLockMathine;						///当前帐号是否锁定了某台机器，1为锁定，0为未锁定
    INT									iBindMobile;						///当前帐号是否绑定手机号码，1为绑定，0为未绑定
    INT									iAddFriendType;						///是否允许任何人加为好友
} GNUC_PACKED MSG_GP_R_LogonResult;

typedef MSG_GP_R_LogonResult MSG_GP_UserInfo;

// 登陆服务器登陆信息
typedef struct tagDL_GP_RoomListPeoCountStruct {
    UINT							uID;				//房间ID
    UINT							uOnLineCount;		//在线人数
    INT								uVirtualUser;		//扩展机器人人数
} GNUC_PACKED DL_GP_RoomListPeoCountStruct;

//////////////////////////////////////////////////////////////////////////
// 统计登录人数
typedef struct tagONLINEUSERSCOUNT {
    UINT							uiLogonPeopCount;	//登录人数
} GNUC_PACKED ONLINEUSERSCOUNT;

//////////////////////////////////////////////////////////////////////////
// 获取游戏房间数据包
typedef struct tagMSG_GP_SR_GetRoomStruct {
    UINT								uKindID;		//类型 ID
    UINT								uNameID;		//名字 ID
} GNUC_PACKED MSG_GP_SR_GetRoomStruct;

//////////////////////////////////////////////////////////////////////////
// 玩家列表操作
typedef struct tagMSG_GP_User_Opt_Struct {
    INT									dwTargetID;		//操作对像
    INT									dwUserID;		//操作id
    UINT								uType;			//操作类型
} GNUC_PACKED MSG_GP_User_Opt_Struct;

//////////////////////////////////////////////////////////////////////////
// 获取游戏房间数据包
typedef struct tagMSG_GP_SR_OnLineStruct {
    UINT								uKindID;		//类型 ID
    UINT								uNameID;		//名字 ID
    UINT								uOnLineCount;	//在线人数
} GNUC_PACKED MSG_GP_SR_OnLineStruct;

//////////////////////////////////////////////////////////////////////////
// 游戏信息
typedef struct tagMSG_GM_S_ClientInfo {
    BYTE								bEnableWatch;	//允许旁观
} GNUC_PACKED MSG_GM_S_ClientInfo;

//////////////////////////////////////////////////////////////////////////
// 用户注册信息
typedef struct tagMSG_GP_SR_Register {
    BYTE								byFromPhone;	// 0-从PC注册,1-从移动注册
    BYTE								byFastRegister;	// 0-快速注册，1-普通注册
    BYTE									gender;				//2016 7 14 性别
#if (HN_TAREGET_PLATFORM == HN_TARGET_PHONE_ONLY)
    UINT								uNameID;
#endif
    CHAR								szHardID[64];	// 硬件ID
    CHAR								szName[64];		// 用户名
    CHAR								szPswd[64];		// 密码
    CHAR								szNickName[64];// 昵称
    UINT								LogonTimes;		// 登陆次数
    char								szIP[64];		///IP	2016-9-13 linshilong
    char								szImei[64];		///Imei	2016-9-13 linshilong
    char								szNetType[64];	///网络类型 2016-9-13 linshilong
    char								szUDID[64];		///客户端唯一标识 2016-11-2 linshilong
} GNUC_PACKED MSG_GP_S_Register;

//////////////////////////////////////////////////////////////////////////

// 购买商品信息
typedef struct taMSG_GP_CS_NOTIFY_IOSPayResult {
    UINT								userID;								// 用户ID
    UINT								productPrice;						// 商品价格
#if (HN_TAREGET_PLATFORM == HN_TARGET_PHONE_ONLY)
    UINT	                            uNameID;
#endif
    LLONG								llMoney;							// 购买的金币
    CHAR								productSerialNumber[128];			// 商品ID
} GNUC_PACKED MSG_GP_CS_NOTIFY_IOSPayResult;

//////////////////////////////////////////////////////////////////////////
// 用户修改密码
typedef struct MSG_GP_S_ChPassword {
    UINT dwUserID;			//用户ID
    CHAR szHardID[24];		//硬盘ID
    CHAR szMD5OldPass[80];  //用户老密码
    CHAR szMD5NewPass[80];  //用户新密码
    MSG_GP_S_ChPassword() {
        ::memset(this, 0x0, sizeof(MSG_GP_S_ChPassword));
    }
} GNUC_PACKED MSG_GP_S_ChPassword;

//////////////////////////////////////////////////////////////////////////
//手机短信验证码获取
#define		MDM_GP_SMS				117
#define		ASS_GP_SMS_VCODE		1
typedef struct MSG_GP_SmsVCode {
    char szName[61];		//用户名
    char szMobileNo[50];	//手机号码
    char szVCode[36];		//产生的验证码，使用MD5加密
    /*
     * 短信验证码类型
     * 0为登陆验证
     * 1为锁机验证
     * 2为解锁机验证
     * 3为修改手机验证
     * 4为绑定手机验证
     * 5为解除绑定手机验证
     */
    UINT nType;				//短信验证码类型

} GNUC_PACKED MSG_GP_SmsVCode;;

//////////////////////////////////////////////////////////////////////////
///绑定手机号码

#define		MDM_GP_BIND_MOBILE	112
#define		ASS_GP_BIND_MOBILE	1

typedef struct MSG_GP_S_BindMobile {
    UINT								dwUserID;				//用户ID
    UINT								dwCommanType;			//命令请求类型,1表示要求绑定，0表示要求解除绑定
    char								szMobileNo[50];			//手机号码
} GNUC_PACKED MSG_GP_S_BindMobile;

///绑定/解除绑定手机返回数据包
typedef struct MSG_GP_R_BindMobile {
    UINT	dwUserID;
    UINT	dwCommanType;				//请求命令类型（0请求解除绑定手机结果，1请求绑定手机结果）
    UINT	dwCommanResult;				//请求的结果
} GNUC_PACKED MSG_GP_R_BindMobile;

//2016 7 4 wzx
#define MDM_GP_USER_MONEY			110								//在游戏中进行银行操作 单向发包 ID

//////////////////////////////////////////////////////////////////////////
///通信主标识
#define	MDM_GP_MESSAGE					103								///系统消息
///通信辅助标识
#define ASS_GP_NEWS_SYSMSG				1								///新闻和系统消息
//#define ASS_GP_DUDU						2							///小喇叭
#define ASS_GP_TALK_MSG					3								//聊天消息
///聊天结构
struct MSG_GR_RS_NormalTalk {
    UINT								crColor;							///字体颜色
    WORD								iLength;							///信息长度
    INT									dwSendID;							///用户 ID
    INT									dwTargetID;							///目标 ID
    INT									nDefaultIndex;						///=0，输入的内容，>0，选择的内容
    CHAR								szMessage[MAX_TALK_LEN+1];			///聊天内容
} GNUC_PACKED;

//////////////////////////////////////////////////////////////////////////
// 道具获取以及兑换消息。

#define		MDM_GP_PROP							140
#define		ASS_PROP_BUY_NEW					0x0b
#define		ASS_PROP_GETUSERPROP				0x01
#define		DTK_GP_PROP_BUY_ERROR				10
#define		DTK_GP_PROP_BUY_NOMONEY				20
#define		DTK_GP_PROP_BUY_SUCCEED				80		//购买成功
#define		DTK_GP_PROP_BUYANDUSE_SUCCEED		81		//即买即用成功

typedef struct _TAG_PROP_BUY {
    INT		dwUserID;					//购买者ID
    INT		nPropID;					//道具ID
    INT		iPropPayMoney;				//总共的金币
    INT		nPropBuyCount;				//道具数量
    /*
     * 这个字段意思是即买即用（1）还是买了等待被用（0），如果像等下管理员换成话费的应该填0，否则不会存在用户道具表里面
     */
    bool	bUse;						//手游特别注意

    _TAG_PROP_BUY() {
        memset(this, 0x0, sizeof(_TAG_PROP_BUY));
        bUse = false;
    }
} GNUC_PACKED _TAG_PROP_BUY;

typedef struct MSG_PROP_C_GETSAVED {
    INT		dwUserID;						//用户ID
} GNUC_PACKED MSG_PROP_C_GETSAVED;


// 服务端发送的数据。
// 从服务器上取得的个人道具，每一个道具一条消息。
typedef struct MSG_PROP_S_GETPROP {
    INT			dwUserID;						//用户ID号
    INT			nPropID;						//道具ID号
    INT			nHoldCount;						//拥有道具的数量
    CHAR		szPropName[50];					//道具名称
    INT			attribAction;					//操作属性
    INT			attribValue;					//取值属性
    INT			dwCost;							//当前该笔交易花了多少钱，服务器须提供此数据
    INT			iPrice;							//道具价格
    INT			iVipPrice;						//VIP道具价格
} GNUC_PACKED MSG_PROP_S_GETPROP, _TAG_USERPROP;


//主ID=140，辅助ID=21
#define		MDM_GP_NET_PROP_BUY_LOG		140
#define		ASS_GP_NET_PROP_BUY_LOG		21

typedef struct NET_PROP_BUY_LOG_RESULT {
    CHAR	szPropName[50];						//道具名称
    BYTE	bPropID;							//道具ID
    UINT	iPorpCount;							//购买数量
    BYTE	bCostType;							//花费的类型（1-金币，2-奖券）
    UINT	iCost;								//花费的数量
    LLONG	llTime;								//购买的时间
} GNUC_PACKED NET_PROP_BUY_LOG_RESULT;


//////////////////////////////////////////////////////////////////////////////////////////
//
// 排行榜消息
//////////////////////////////////////////////////////////////////////////////////////////
#define MDM_GP_PAIHANGBANG					133

struct MSG_GP_PaiHangBang_In {
	INT		count;		//前几名
	INT		type;		// 0:金币总合来排 1: 钱包的来 2: 银行的来 其它值，直接失败 3:魅力
	INT		pageSize;   //每页显示多少条记录
	INT		curPage;	//当前第几页
	INT		reqType;	//请求类型、PC端还是手机端、0是手机1是PC端
} GNUC_PACKED;

struct MSG_GP_MoneyPaiHangBang_Item {
    CHAR							nickName[64];						///用户昵称
    LLONG							i64Money;							///用户金币
} GNUC_PACKED;

struct MSG_GP_MoneyPaiHangBang_Result {
    MSG_GP_MoneyPaiHangBang_Item items[20];
} GNUC_PACKED;

// 2016 7 1 银行进行金币处理服务端给客户发送消息结构wzx
struct MSG_GP_Get_User_WalletMoney_BankMoney {
    LLONG i_Wallet;//.钱包long
    LLONG i_Bank;//银行long

} GNUC_PACKED;

//////////////////////////////////////////////////////////////////////////////////////////
//
// 签到消息
//////////////////////////////////////////////////////////////////////////////////////////
#define MDM_GP_SIGN							134
#define ASS_GP_SIGN_CHECK					1
#define ASS_GP_SIGN_DO						2


//签到
struct MSG_GP_S_SIGN_CHECK_RESULT {
    UINT				dwUserID;
    BYTE				iRs;			//结果: 0:未签到 1-已经签到
    INT					iGetMoney;		//当天签到可获取的金币
    BYTE				byCountDay;		//连续签到天数
} GNUC_PACKED;

struct MSG_GP_S_SIGN_DO_RESULT {
    UINT				dwUserID;
    BYTE				iRs;			//结果: 0-失败 1-签到成功，
    INT					iGetMoney;		//当天签到获取的金币
} GNUC_PACKED;


//////////////////////////////////////////////////////////////////////////////////////////
//
// 在线奖励消息
//////////////////////////////////////////////////////////////////////////////////////////

//在线奖励金币
#define MDM_GP_ONLINE_AWARD					135
#define ASS_GP_ONLINE_AWARD_CHECK			1
#define ASS_GP_ONLINE_AWARD_DO				2

//0失败  1 成功
struct MSG_GP_S_ONLINE_AWARD_CHECK_RESULT {
    UINT	dwUserID;
    UINT	iLeftTime;				//还差多少时间可以领取,0表示可以领取
    UINT	iOnLineTimeMoney;		//能领取的金币
} GNUC_PACKED;
struct MSG_GP_S_ONLINE_AWARD_DO_RESULT {
    UINT	dwUserID;
    UINT    iCurrentGetMoney;		//此次领取的金币
    UINT	iNextTime;				//下次时间
    UINT	iNextMoney;				//下次金币
} GNUC_PACKED;

//#define MDM_GP_NOTIFY_PAY				88
#define ASS_GP_GET_MONEY_BY_PAY_DO 		2
#define ASS_GP_GET_MONEY_BY_PAY_CHECK	3

//0失败  1 成功
//通过支付的钱奖励金币
struct MSG_GP_S_GetMoney_ByPay {
    UINT							dwUserID;
    LLONG							i64TotalMoney;		//累计充了多少钱
    LLONG							i64Money;			//应该得到多少金币奖励
} GNUC_PACKED;

#endif // !_HN_HNNetMessageHall_H_
