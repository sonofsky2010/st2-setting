/*******************************************************
 CVTouchSDK4L - the Mac OS X library for
                communication with CVTouch devices.

 2012/08/15 Mac OS X Version 1.0

 Copyright (C) 2012-2022 Wigou Lau <liuweigao@cvte.cn>
 All rights reserved

 the SDK interface for CVTouchSDK4Mac
********************************************************/

#ifndef _CVTOUCHTYPE_H_
#define _CVTOUCHTYPE_H_

/** 这里定义一些和应用有关的宏和数据结构 **/

#define USE_OLD_TSERIES

/*///////////////
// Definitions
///////////////*/
#define DEVICEDATA_LEN			64
#define DEVICESN_LEN			16

#define MAX_DEVICE				64
#define MAX_POINT_NUM			32

#define HID_KEY_LEN             56

#define FEATURE_REPORT_CONTROL
#define USE_POLL_HOTPLUG

#ifdef WIN32		/* specific Windows parts */
#include <windows.h>

typedef int int32;
typedef short int int16;
typedef char int8;
typedef unsigned int int32u;
typedef unsigned short int int16u;
typedef unsigned char int8u;

#elif __linux__		/* specific Linux parts */
typedef int int32;
typedef short int int16;
typedef char int8;
typedef unsigned int int32u;
typedef unsigned short int int16u;
typedef unsigned char int8u;
typedef int WORD;
typedef unsigned char BYTE;
typedef char*   LPSTR;
#elif __APPLE__		/* specific Mac OS parts */
typedef int int32;
typedef short int int16;
typedef char int8;
typedef unsigned int int32u;
typedef unsigned short int int16u;
typedef unsigned char int8u;
typedef int WORD;
typedef unsigned char BYTE;
typedef char*   LPSTR;
#else
    #error: unknown OS
#endif

#ifndef CVT_NULL
#define CVT_NULL	NULL
#endif

#ifndef CVT_FALSE
#define CVT_FALSE	0
#endif

#ifndef CVT_TRUE
#define CVT_TRUE	1
#endif

#ifndef CVT_PNP_ARRIVAL
#define	CVT_PNP_ARRIVAL	1
#endif

#ifndef CVT_PNP_REMOVAL
#define	CVT_PNP_REMOVAL	2
#endif

/**触摸状态*/
typedef enum _TouchStatus
{
        NONE,
        TOUCH_DOWN,
        TOUCH_MOVE,
        TOUCH_UP,
        TOUCH_RIGHT_DOWN,
        TOUCH_RIGHT_MOVE,
        TOUCH_RIGHT_UP,
        TOUCH_MIDDLE_DOWN,
        TOUCH_MIDDLE_MOVE,
        TOUCH_MIDDLE_UP,
}TouchStatus;

/** 回调函数返回触摸数据结构体 **/
typedef struct _PointData
{
    /** 点id号 **/
        WORD c;
        /** 触摸状态 **/
        TouchStatus ts;
        /** 触摸原始状态 **/
        WORD s;
        /** X 坐标 **/
        int32 x;
        /** Y 坐标 **/
        int32 y;

        union
        {
                /** (OI TOUCH) 左Sensor触摸宽度 **/
                WORD lw;
                /** (IR TOUCH) X轴触摸宽度**/
                WORD xw;
        };

        union
        {
                /** (OI TOUCH) 右Sensor触摸宽度 **/
                WORD rw;
                /** (IR TOUCH) Y轴触摸宽度**/
                WORD yw;
        };

        /** 设备序号 0 ~ MAX_DEVICE **/
        WORD devNo;
}PointData;

/* Define Success/Error codes. */
typedef enum _CVTStatusCode
{
        CVT_SUCCESS							= 1,
        CVT_FAILED							= -1,
        CVT_ERR_DEVICE_NOT_OPEN				= -2,
        CVT_ERR_INVALID_HANDLE_VALUE		= -3,
        CVT_ERR_INPUT_PARAMETER_ERROR		= -4,
        CVT_ERR_NULL_VALUE					= -5,
        CVT_ERR_TIME_OUT					= -6,
        CVT_ERR_SHARING_VIOLATION			= -7,
        CVT_ERR_MORE_THAN_MAXIMUM			= -8,
        CVT_ERR_NOT_IN_RANGE				= -9,
        CVT_ERR_NOT_ENOUGH_MEMORY			= -10,
        CVT_ERR_NOT_REG_APP					= -11,
        CVT_ERR_NOT_FIND_APP				= -12,
        CVT_ERR_NOT_FIND_DEVICE				= -13,
        CVT_ERR_NOT_SUPPORT_DEVICE			= -14,
        CVT_ERR_SEND_CMD_FAILED				= -15,
        CVT_ERR_RETURN_CMD					= -16
}CVTStatusCode;

typedef enum _CVTPortType
{
        HidPortDevice = 0x01,
        ComPortDevice
}CVTPortType;

typedef enum _CVTDeviceType
{
        IRTouchDevice = 0x01,
        OITouchDevice,
        UtilDevice
}CVTDeviceType;

typedef enum _CVTDataType
{
        OrgDatas = 0x01,
        CmdDatas,
        CoorDatas,
        TuioDatas
}CVTDataType;

typedef struct _LOGICAL_PROPERTY
{
        int XLogicalMin;
        int YLogicalMin;
        int XLogicalMax;
        int YLogicalMax;
}LOGICAL_PROPERTY, *PLOGICAL_PROPERTY;

/** 成像设备状态结构体 **/
typedef struct _OIDevStatus
{
        /** Devoce Mode **/
        int8u bDeviceMode;
        /** USB Format **/
        int8u bUsbFormat;
        /** Device Run Mode **/
        int8u bDeviceRunMode;
        /** TUIO Mode **/
        int8u bForceTUIObit;
        /** TUIO Transmit Mode **/
        int8u bForceTransbit;
        /** Status of OI Touch **/
        int8u bStatus;
}OIDevStatus;

typedef struct _IRWidthData
{
        int16u uXWidth;
        int16u uYWidth;
}IRWidthData;

/** 数据包结构体 **/
typedef struct _CVTDeviceData
{
        /** 数据类型,0表示原始字节数据，1表示坐标数据,2 **/
        int16u m_nDataType;
        /** 是否要求回复 **/
        int8u m_bReply;
        /** 表示此类数据包还有多少个，0表示无限多个，1表示只有一个，2表示有2个数据包（发送完当前坐标之后下一个自动减一）//可以不需要 **/
        int16u m_nDataCount;
        /** 设备序号,用于判断是那个设备传来的数据,对于设备上传的数据该值表示设备序号，对于应用下发数据，该值表示应用序号 **/
        int16u m_nDeviceNo;
        /** 数据内容 **/
        int8u m_cData[DEVICEDATA_LEN];
}CVTDeviceData;

/** 设备属性结构 **/
typedef struct _CVTDeviceInfo
{
        /** 设备类型 **/
        CVTDeviceType m_nDeviceType;
        /** 接口类型 **/
        CVTPortType m_nPortType;
        /** 产品ID，固件特性 **/
        int16u m_nPID;
        /** 厂商ID，固件特性 **/
        int16u m_nVID;
        /** 固件版本，固件特性 **/
        int16u m_nPVN;
        /** 设备校验码 **/
        int32u m_nCheckSUM;
        /** SVN编码 **/
        int16u m_nSVNNUM;
        /** 产品生产日期 **/
        int16u m_nDate;
        /** 产品生产地 **/
        int16u m_nAddr;
        /** 产品批号 **/
        int16u m_nPNO;
        /** 生产厂商ID **/
        int16u m_nFID;
        /** 产品序列号 **/
        int8u m_nSN[16];
        /** 设备名称编号 **/
        int16u m_nDeviceNameIndex;
        /** 设备序号 0 ~ MAX_DEVICE，用于和CCVTDevice类配对,创建成功后由CCVTDevice类填写 **/
        int16u m_nDeviceNo;
        /** 设备支持最大点数 **/
        int16u m_nMaxPointNum;
        /** 逻辑属性 **/
        LOGICAL_PROPERTY m_nLogicalProp;

#ifdef WIN32
        /** 设备名 **/
        char m_sDevName[MAX_PATH];
        /** 设备名，供低版本使用，HidD_SetFeature/HidD_GetFeature **/
        char m_sDevFeatureName[MAX_PATH];
        /** 设备名，命令通道名 **/
        char m_sCmdDevName[MAX_PATH];
        /** 设备名，数据通道名 **/
        char m_sDataDevName[MAX_PATH];
        /** 设备名，Digitizers Touch Screen名 **/
        char m_sTouchDevName[MAX_PATH];
        /** Report ID **/
        int8 m_nReportID;
#elif __linux__
        /** 设备名 **/
        char m_sDevName[260];
        /** 设备路径 **/
        char m_sPath[260];
#elif __APPLE__
	/** 设备名 **/
	char m_sDevName[260];
	/** 设备路径 **/
	char m_sPath[260];
#endif

        /** 成像触摸点状态模式 (00 07 07 07 ... 07 04) **/
        bool ptStatusOIMode;
        /** 是否带有宽度数据 **/
        bool ptWidthDataMode;
}CVTDeviceInfo;

struct CVTDevInfoNode
{
    CVTDeviceInfo devInfo;
    CVTDevInfoNode *next;
};

/** the raw data callback function **/
typedef void (*RawDataCallbackObject)(CVTDeviceData *pDeviceData, const void *callbackObject);
/** the multitouch data callback function **/
typedef void (*MultiTouchCallbackObject) (const PointData *pData, const int maxPointNum, const void *callbackObject);
/** the hotplug callback function with device path **/
typedef int (*HotplugCallbackObject) (const LPSTR path, const bool attached, const void *callbackObject);
/** the hotplug callback function with device info **/
typedef int (*HotplugDevInfoCallbackObject) (CVTDeviceInfo *pDevInfo, const bool attached, const void *callbackObject);

/** 应用程序信息 **/
typedef struct _CVTAppInfo
{
        /** 应用程序类型 **/
        int16u m_nAppType;
        /** 客户编码 **/
        int16u m_nClientID;
        /** 客户优先级 **/
        int16u m_nPriority;
        /** 客户功能码 **/
        int16u m_nFunCode;
        /** 应用接口序号 0 ~ MAX_APPINTERFACE ，用于和CCVTAppInterface类配对，创建成功后由CCVTAppInterface类填写 **/
        int16u m_nAppInterfaceNo;
        /** 回调函数指针 **/
        RawDataCallbackObject m_fnRawDataCallbackObject;
        /** 回调函数指针 返回坐标数据 返回主线程this指针 **/
        MultiTouchCallbackObject m_fnMultiTouchCallbackObject;
        /** 回调函数指针 返回USB HID设备热插拔信息 返回主线程this指针 **/
        HotplugCallbackObject m_fnHotplugCallbackObject;
        /** 回调函数指针 返回USB HID设备热插拔信息 返回设备信息应用可直接StartDevice 返回this指针 **/
        HotplugDevInfoCallbackObject m_fnHotplugDevInfoCallbackObject;
        /** 输入主线程this指针 **/
        void *m_pThis;
}CVTAppInfo;

#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#define CVTprintf   printf
#else
#define CVTprintf(arg)
#endif

#endif // _CVTOUCHTYPE_H_
