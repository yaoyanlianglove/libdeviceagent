#ifndef SGSDK__H
#define SGSDK__H
//////////////////////////////////////////////
//变量与结构定义
#define SG_DEV_TYPE_UNKNOWN          0xFF

///通道数
#define SG_CHANNEL_NUM               16

/// 设备IP地址长度 
#define SG_IP_LEN                   32
/// ipv6地址长度
#define SG_IPV6_LEN                 100
/// 设备默认字符串长度 
#define SG_DEFAULT_LEN              64
/// 日志信息字符串长度 
#define SG_LOG_LEN                  512
/// 文件名长度 
#define SG_FILENAME_LEN             128
// 码标长度
#define SG_DECODE_TAG_LEN           4
// DVR硬盘数
#define SG_DVR_DISK_NUM             16
// OSD长度
#define SG_MAX_OSDLEN               44

///通信方式-TCP
#define SG_SDK_TCP                  0

#define SG_SDK_UDP                  1

#define SG_SDK_MULTI                2

#define SG_SDK_RTP                  3

///最大通道数
#define SG_SDK_MAX_CHANNEL          16

///光圈关停止
#define SG_SDK_IRIS_CLOSE_OFF                 0x0101    
///光圈关 
#define SG_SDK_IRIS_CLOSE_ON                  0x0102    
///光圈开 
#define SG_SDK_IRIS_OPEN_OFF                  0x0103    
///光圈开停止 
#define SG_SDK_IRIS_OPEN_ON                   0x0104    

///近聚焦停止 
#define SG_SDK_FOCUS_NEAR_OFF                 0x0201    
///近聚焦 
#define SG_SDK_FOCUS_NEAR_ON                  0x0202    
///远聚焦停止 遥控
#define SG_SDK_FOCUS_FAR_OFF                  0x0203    
///远聚焦
#define SG_SDK_FOCUS_FAR_ON                   0x0204    

///缩小停止
#define SG_SDK_ZOOM_IN_OFF                    0x0301    
///缩小
#define SG_SDK_ZOOM_IN_ON                     0x0302    
///放大停止
#define SG_SDK_ZOOM_OUT_OFF                   0x0303    
///放大
#define SG_SDK_ZOOM_OUT_ON                    0x0304    

///向上停止
#define SG_SDK_UP_OFF                         0x0401    
///向上
#define SG_SDK_UP_ON                          0x0402    
///向下停止
#define SG_SDK_DOWN_OFF                       0x0403    
///向下 
#define SG_SDK_DOWN_ON                        0x0404    
///右转停止
#define SG_SDK_RIGHT_OFF                      0x0501    
///右转 
#define SG_SDK_RIGHT_ON                       0x0502    
///左转停止 
#define SG_SDK_LEFT_OFF                       0x0503    
///左转 
#define SG_SDK_LEFT_ON                        0x0504    

///预置位保存
#define SG_SDK_PRESET_SAVE                    0x0601    
///预置位调用 
#define SG_SDK_PRESET_GOTO                    0x0602    
///预置位删除 
#define SG_SDK_PRESET_CLEAR                   0x0603    

///左上方向运动停止 
#define SG_SDK_UP_LEFT_OFF                    0x0701    
///左上方向运动 
#define SG_SDK_UP_LEFT_ON                     0x0702    
///左下方向运动停止 
#define SG_SDK_DOWN_LEFT_OFF                  0x0703    
///左下方向运动 控
#define SG_SDK_DOWN_LEFT_ON                   0x0704    
///右上方向运动停止 
#define SG_SDK_UP_RIGHT_OFF                   0x0801    
///右上方向运动 
#define SG_SDK_UP_RIGHT_ON                    0x0802    
///右下方向运动停止
#define SG_SDK_DOWN_RIGHT_OFF                 0x0803    
///右下方向运动 
#define SG_SDK_DOWN_RIGHT_ON                  0x0804    
///停止当前动作 
#define SG_SDK_CURRENT_STOP                   0x0901    

///雨刷开 
#define SG_SDK_WIPER_ON                       0x0A01    
///雨刷关 
#define SG_SDK_WIPER_OFF                      0x0A02    
///灯亮 
#define SG_SDK_LIGHT_ON                       0x0B01    
///灯灭 
#define SG_SDK_LIGHT_OFF                      0x0B02    
///加热开 
#define SG_SDK_HEATER_ON                      0x0C01    
///加热关 
#define SG_SDK_HEATER_OFF                     0x0C02    
///红外开
#define SG_SDK_INFRARED_ON                    0x0D01    
///红外关 
#define SG_SDK_INFRARED_OFF                   0x0D02    

///轨迹巡航开始 
#define SG_SDK_TRACK_CRUISE_ON                0x0F01    
///轨迹巡航停止 
#define SG_SDK_TRACK_CRUISE_OFF               0x0F02    
///预置位巡航开始 
#define SG_SDK_PRESET_CRUISE_ON               0x1001    
///预置位巡航停止 
#define SG_SDK_PRESET_CRUISE_OFF              0x1002    

/// SDK 不支持方法和参数宏定义
#define SG_SDK_UNSUPPORT                    0xFF

typedef int bool;
#define true 1
#define false 0

//Dev前端系统信息
typedef struct _st_SG_DEV{
  char    szIP[SG_IP_LEN];                  //Dev IP
  char    szName[SG_DEFAULT_LEN];           //Dev名称
  char    szUser[SG_DEFAULT_LEN];           //Dev 用户名
  char    szPass[SG_DEFAULT_LEN];     //Dev 密码
  char    szType[SG_DEFAULT_LEN];           //Dev 类型
  char    szMulticastIP[SG_IP_LEN];         //Dev 多播IP
  int     nTCPPort;                         //TCP 端口
  int     nUDPPort;                         //UDP 端口
  int     nMulticastPort;                   //Multicast 端口
  int     nConnectType;               //通信方式
        int     nDecoderTag; 
  char    szSPSHead[SG_DEFAULT_LEN];        //SPS头部标记
  int     nSPSDataType;                     //SPS需要接收的数据头类型关
  bool    bStatus;                          //设备状态,true:可用,false:不可用
//    _st_SG_DEV()
//  {
////    memset(szID,0,SG_DEVICE_CODE_LEN);
//        memset(szIP,0,SG_IP_LEN);
//        memset(szName,0,SG_DEFAULT_LEN);
//        memset(szUser,0,SG_DEFAULT_LEN);
//        memset(szPass,0,SG_DEFAULT_LEN);
//        memset(szType,0,SG_DEFAULT_LEN);
//            nDecoderTag = 0;
    
//        memset(szMulticastIP,0,SG_IP_LEN);
//        memset(szSPSHead,0,SG_DEFAULT_LEN);
//    }
}st_SG_DEV;

//时间结构定义
typedef struct _st_SG_Time{
  unsigned int    Year;      //年
  unsigned char   Month;   //年
  unsigned char   Day;       //日
  unsigned char   Hour;      //时
  unsigned char   Minute;    //分
  unsigned char   Second;  //秒
  unsigned int    MiSecond;  //毫秒
}st_SG_Time;


///时间结构定义
typedef struct _st_SG_VideoFile{
  char         Name[SG_FILENAME_LEN];               //文件名
  st_SG_Time   stStartTime;                  //录像开始时间
  st_SG_Time   stStopTime;                   //录像结束时间
  int          Len;                          //录像长度
  int          Type;                           //文件类型 
}st_SG_VideoFile;


//告警信息 
typedef struct _st_SG_Alarm_Info{
  unsigned char  MmotionDection[SG_CHANNEL_NUM];    //动态侦测报警
  unsigned char  VideoLost[SG_CHANNEL_NUM];         //信号丢失报警
  unsigned char  VideoCover[SG_CHANNEL_NUM];        //视频遮挡告警
  unsigned char  DiskNumber[SG_DVR_DISK_NUM];       //发生报警的磁盘
  st_SG_Time    stAlarmTime;                    //告警发生的时间
//  _st_SG_Alarm_Info()
//  {
//    memset(MmotionDection,0,SG_CHANNEL_NUM);
//    memset(VideoLost,0,SG_CHANNEL_NUM);
//    memset(VideoCover,0,SG_CHANNEL_NUM);
//    memset(DiskNumber,0,SG_CHANNEL_NUM);
//  }
}st_Alarm_Info;


//视频参数结构
typedef struct _st_SG_VideoParam
{
  //视频分辨率定义
  int Resolution;
  //支持的视频分辨率
  //int SupportResolution;
  //图像质量 0/1/2/3:差/普通/较好/好
  int Quality;
  //码率 单位: k/s
  int Bitrate;
  //帧率 单位: 帧/s
  int FrameRate;
  //关键帧间隔
  int IFrame;
  //压缩方式
  int Codec;
  //支持的压缩方式
  //int SupportCodec;
  //变码流/定码流 : 0/1
  int BitrateType;
//  _st_SG_VideoParam()
//  {
//    Resolution = 0;
//    Quality = 0;
//    Bitrate = 0;
//    FrameRate = 0;
//    IFrame = 0;
//    Codec = 0;
//    BitrateType = 0;
//  }
}st_SG_VideoParam;

///日志信息结构定义
typedef struct _st_SG_LogInfo{
  ///日志类型
  int         Type;
  ///时间
  st_SG_Time  stTime;
  ///信息
  char        Log[SG_LOG_LEN];
  ///设备信息
  char        Device[SG_DEFAULT_LEN];

//  _st_SG_LogInfo()
//  {
//    Type = 0;
//    ::memset(&stTime, 0x00, sizeof(stTime));
//    Log = "";
//    ::memset(Device, 0x00, SG_DEFAULT_LEN);
//    bPrint = true;
//  }
}st_SG_LogInfo;

typedef struct _st_SG_Rect
{

  int xOffset;
  int yOffset;
  int Width;
  int Height;
//  _st_SG_Rect()
//  {
//    xOffset = 0;
//    yOffset = 0;
//    Width = 0;
//    Height = 0;
//  }
}st_SG_Rect;

typedef struct _st_SG_VideoOsdInfo
{
  int Show;
  st_SG_Rect rcRelativePos;
  char Text[SG_MAX_OSDLEN];
}st_SG_VideoOsdInfo;


typedef struct _st_SG_NetCFG
{
  char IP[SG_IP_LEN];
  char MaskIP[SG_IP_LEN];
  char GateIP[SG_IP_LEN];
//  _st_SG_NetCFG()
//  {
//    memset(IP,0,SG_IP_LEN);
//    memset(MaskIP,0,SG_IP_LEN);
//    memset(GateIP,0,SG_IP_LEN);
//  }
}st_SG_NetCFG;

typedef struct _st_SG_RecordTime
{
  st_SG_Time  timeBegin;
  st_SG_Time  timeEnd;
}st_SG_RecordTime;

typedef struct _st_SG_RecordPlan
{
  int Weekday;
  st_SG_RecordTime *pStruRecordTime;
  int RecordTimeElem;
//  _st_SG_RecordPlan()
//  {
//    Weekday = -1;
//    pStruRecordTime = NULL;
//    RecordTimeElem = -1;
//  }
}st_SG_RecordPlan;

///////////////////////////////////////////////////////////////////
//回调函数
///实时视频数据捕获回调函数  
typedef void(*SG_RealDataCallBack)(int RealPlayHandle, int DataType, char *Buffer, int BufSize, void *pUser);

///回放视频数据捕获回调函数 
typedef void(*SG_PlayDataCallBack)(int PlayBackHandle, int DataType, char *Buffer, int BufSize, void *pUser);

/// 接收设备报警消息  
typedef void(*SG_MessageCallBack)(int Type, char *pAlarm, int Len, void* pUser, void *pAlarmInfo);

/// 接收登陆，重连等异常消息 
typedef void(*SG_ExceptionCallBack)(int Type, int UserID, int Handle, void *pUser);

/// 抓图回调
typedef void(*SG_SnapPicCallBack)(int UserID, int DataType, char* FileName, int FileSize, void *pUser);


//////////////////////////////////////////////////////////////////////////
//接口函数定义
/*!
  \brief SDK 初始化
  \param pDevList DEV数组列表
  \param Num  设备数组元素个数
  \return 0：执行成功/ -1：执行失败 获取错误码调用 ::SG_GetLastError           
*/
int SG_Init(st_SG_DEV *pDevList, int Num);

/*!
  \brief SDK 资源释放
  \return 0：执行成功/ -1：执行失败 获取错误码调用 ::SG_GetLastError
  \ SGSDK接口技术规范初始化
*/
int SG_Cleanup();

//-----------------------------------------------------------------------------
//     异常消息回调
//-----------------------------------------------------------------------------
/*!
  \brief 设置SDK消息回调函数
  \param pDev ::st_SG_DEV 结构指针
  \param pfCallBack ::SG_MessageCallBack 回调函数
  \param pUser 用户数据
  \return 0：执行成功/ -1：执行失败  获取错误码调用 ::SG_GetLastError
*/
int SG_SetMessageCallBack(st_SG_DEV* pDev, SG_MessageCallBack pfCallBack, void* pUser);

//-----------------------------------------------------------------------------
//     错误信息
//-----------------------------------------------------------------------------
/*!
  \brief 获取最后的错误码
  \param sErrorMsg 错误消息字符串缓冲
  \param Len 缓冲长度
  \return 0：执行成功/ -1：执行失败

*/
int SG_GetLastError( char* sErrorMsg, int Len);

//-----------------------------------------------------------------------------
//     用户登录
//-----------------------------------------------------------------------------
/*!
  \brief 用户登录
  \param pdev ::st_SG_DEV 结构信息
  \return 登录情况：成功则返回实际的登录句柄，否则返回-1  获取错误码调用 ::SG_GetLastError
*/
int SG_Login(st_SG_DEV* pdev);

/*!
  \brief 用户注销
  \param UserID 用户登录句柄,DVR的实际登录句柄
  \return 0：执行成功/ -1：执行失败  获取错误码调用 ::SG_GetLastError
*/
int SG_Logout(int UserID);

/*!
 \brief 设置抓图
  \param UserID 登录句柄
  \param Channel 通道号
  \param Type , 抓图类型，0：单次推送，1：周期上送
  \param stStart , 抓图开始时间
  \param stStop , 抓图结束时间
  \param Interval, 抓图间隔 为0时取消上送
  \param pfCallBack , 抓图回调通知函数
  \return 成功返回0 ,失败返回-1  获取错误码调用 ::SG_GetLastError

*/
int SG_SnapPic(int UserID,int Channel,int Type,st_SG_Time stStart, st_SG_Time stStop,int Interval, SG_SnapPicCallBack pfCallBack);
//-----------------------------------------------------------------------------
//     视频相关
//-----------------------------------------------------------------------------


/*!
 \brief 实时视频预览
  \param UserID 登录句柄
  \param Channel 通道号
  \param pfCallBack,实时视频数据捕获回调函数
  \param pUser,用户保留数据
   \return 实时播放成功返回播放句柄,失败返回-1  获取错误码调用 ::SG_GetLastError

*/
int SG_RealPlay(int UserID,int Channel,SG_RealDataCallBack pfCallBack,void* pUser);

/*!
  \brief 停止视频播放
  \param PlayHandle 实际的视频播放句柄,
  \return 0：执行成功/ -1：执行失败  获取错误码调用 ::SG_GetLastError

*/
int SG_StopRealPlay(int PlayHandle);



/*!
  \brief 录像文件检索,返回的文件结构中也包含了文件类型
  \param UserID 登录句柄
  \param Channel 通道号
  \param stStart ::st_SG_Time 结构表示的开始时间
  \param stStop ::st_SG_Time 结构表示的结束时间
  \param pstFiles ::st_SG_VideoFile 结构体数组指针，由调用者负责申请空间，用于
                 存放查询结果
  \param Count 申请的结构空间个数，查询结果最多存放个数
  \return 小于0 表示出现查询错误，请调用 ::SG_GetLastError 查询错误码；
                返回0表示没有查询到；其他值为查询结果个数
*/
int SG_FindVideoFiles(int UserID,int Channel,st_SG_Time stStart,st_SG_Time stStop,st_SG_VideoFile* pstFiles,int Count,int FileType);
/*!
  \brief 录像回放
  \param UserID 登录句柄
  \param Channel 通道号
  \param FileName 录像文件名
  \param hWnd 窗口播放句柄
  \return 小于0 表示出现错误，请调用 ::SG_GetLastError 查询错误码；
          其他值表示回放句柄，供 ::SG_PlayBackPause (播放控制) 和 
          ::SG_StopPlayBack 使用
*/
int SG_PlayBack(int UserID, int Channel, char* pFileName, void* hWnd);

/*!
  \brief 录像根据起始时间回放，为应用端多路同时播放提供同步数据
  \param UserID 登录句柄
  \param Channel 通道号
  \param stStart ::st_SG_Time 结构表示的开始时间
  \param stStop ::st_SG_Time 结构表示的结束时间
  \return 小于0 表示出现错误，请调用 ::SG_GetLastError 查询错误码；
          其他值表示回放句柄，供 ::SG_PlayBackPause (播放控制) 和 
          ::SG_StopPlayBack 使用
*/
int SG_PlayBackByTime(int UserID, int Channel, st_SG_Time stStart, st_SG_Time stStop);

/*!
  \brief 停止录像回放
  \param UserID 登录句柄
  \param PlayBackHandle 回放句柄, 是 ::SG_PlayBack 返回的结果
  \return 0：成功 -1：失败
*/
int SG_StopPlayBack(int UserID, int PlayBackHandle);

/*!
  \brief 录像回放控制-暂停，DVR数组的下标值
  \param PlayBackHandle 视频回放句柄
  \return 0：成功 -1：失败
*/
int SG_PlayBackPause(int UserID, int PlayBackHandle);

/*!
  \brief 录像回放控制-播放
  \param UserID 登录句柄
  \param PlayBackHandle 视频回放句柄
  \return 0：成功 -1：失败
*/
int SG_PlayBackPlay(int UserID, int PlayBackHandle);
/*!
  \brief 录像回放控制-恢复
  \param iUserID 登录句柄
  \param iPlayBackHandle 视频回放句柄
  \return 0：成功 -1：失败
*/
int SG_PlayBackResume(int UserID, int PlayBackHandle);

/*!
  \brief 录像回放控制-从指定位置开始播放
  \param UserID 登录句柄
  \param PlayBackHandle 视频回放句柄
  \param Offset 播放起始秒数
  \param Total  总时间长度
  \return 0：成功 -1：失败
*/
int SG_PlayBackSeek(int UserID, int PlayBackHandle, int Offset, int Total, int size);

/*!
  \brief 录像回放控制-快放
  \param UserID 登录句柄
  \param PlayBackHandle 视频回放句柄
  \return 0：成功 -1：失败
*/
int SG_PlayBackFast(int UserID, int PlayBackHandle);

/*!
  \brief 录像回放控制-慢放
  \param UserID 登录句柄
  \param PlayBackHandle 视频回放句柄
  \return 0：成功 -1：失败
*/
int SG_PlayBackSlow(int UserID, int PlayBackHandle);

/*!
  \brief 录像回放控制-正常速度放
  \param UserID 登录句柄
  \param PlayBackHandle 视频回放句柄
  \return 0：成功 -1：失败
*/
int SG_PlayBackNormal(int UserID, int PlayBackHandle);

/*!
  \brief 云镜控制
  \param UserID 登录句柄
  \param Channel 通道号
  \param Cmd 命令参数
  \param Para1 方向控制指令（上、下、左、右、左上、左下、右上、右下等）代表
         方向运动速度，取值范围为[1，9]，1 为最低速度，9 为最高速度；
  \param Para2 方向控制指令（上、下、左、右、左上、左下、右上、右下等）代表
         纵向运动速度，取值范围为[1，9]，1 为最低速度，9 为最高速度；
  \param Para3 保留；
  \return 0：成功 -1：失败
*/
int SG_PTZControl(int UserID, int Channel, int Cmd,int Para1, int Para2, int Para3);

/*!
  \brief 预置点操作（转到、设置和删除）
  \param UserID 登录句柄
  \param Channel 通道号 
  \param Cmd 预置点命令参数
  \param Para1 预置位相关指令代表预置位编号，取值范围为[1，300]；
  \param Para2 保留；
  \param Para3 保留；
  \return 0：成功 -1：失败
*/
int SG_PTZPreset(int UserID, int Channel, int Cmd,int Para1, int Para2, int Para3);


/*!
  \brief 巡航操作
  \param UserID 登录句柄, ::SG_Login 返回值
  \param Channel 通道号
  \param Cmd 巡航命令参数 
  \param Para1 巡航路径；
  \param Para2 保留；
  \param Para3 保留；
  \return 0：成功 -1：失败
*/
int SG_PTZCruise(int UserID, int Channel, int Cmd, int Para1, int Para2, int Para3);


/// 设置实时视频数据捕获回调函数
int SG_SetRealDataCallBack(SG_RealDataCallBack pfCallBack, void* pUser);

/// 设置回放数据捕获回调函数
int SG_SetPlayDataCallBack(int UserID, int PlayBackHandle, SG_PlayDataCallBack pfCallBack, void* pUser);

/// 设置实时视频数据捕获回调函数
int SG_SetSnapPicCallBack(SG_SnapPicCallBack pfCallBack, void* pUser);

/*!
  \brief 设备状态
  \param UserID 登录句柄
  \return 设备正常，返回0,设备故障返回-1
*/
int SG_DevState(int UserID);

/*!
  \brief 重启设备
  \param UserID , 登录句柄
  \return 0表示成功，-1表示失败
*/
int SG_RebootDev(int UserID);

/*!
  \brief 获取设备网络参数
  \param UserID , 登录句柄
  \param pDev ::st_SG_DEV 结构指针
  \return 0表示成功，-1表示失败
*/
int SG_GetDevIP(int UserID,st_SG_DEV* stDev);

/*!
  \brief 设置设备网络参数
  \param UserID , 登录句柄
  \param pDev ::st_SG_DEV 结构体
  \return 0表示成功，-1表示失败
*/
int SG_SetDevIP(int UserID,st_SG_DEV stDev);


/*!
  \brief 设置设备的IP
  \param UserID , 登录句柄，
  \param stTime ,时间信息
  \return 0表示成功，-1表示失败
*/
int SG_SetDevTime(int UserID,st_SG_Time stTime);

/*!
\brief 设置视频图像的显示参数
\param UserID 登录句柄
\param Bright 图像亮度 范围(0-255)
\param Contrast 对比度 范围(0-255)
\param Saturation 饱和度 范围(0-255)
\param Hue 色度 范围(0-255)
\return 0：成功 -1：失败
*/
int SG_SetImageSetting (int UserID,int Channel, int Bright,int Contrast,int Saturation, int Hue);

/*!
\brief 获取视频图像的显示参数
\param UserID 登录句柄
\param Bright 图像亮度 范围(0-255)
\param Contrast 对比度 范围(0-255)
\param Saturation 饱和度 范围(0-255)
\param Hue 色度 范围(0-255)
\return 0：成功 -1：失败
*/
int SG_GetImageSetting(int UserID,int Channel, int *Bright,int *Contrast,int *Saturation, int *Hue);


/*!
\brief 设置视频参数
\param UserID 登录句柄
\param Channel 通道号
\param pParam 视频参数结构
\return 0：成功 -1e：失败
*/
int SG_SetVideoParam (int UserID,int Channel,st_SG_VideoParam* pParam);


/*!
\brief 获取视频参数
\param UserID 登录句柄
\param Channel 通道号
\param pParam 视频参数结构
\return 0：成功 -1：失败
*/
int SG_GetVideoParam (int UserID,int Channel,st_SG_VideoParam* pParam);

/*!
\brief 设置时间的OSD的信息
\param UserID 登录句柄
\param Channel 通道号
\param Pos 时间OSD显示位置
\param Show OSD是否显示，1显示，0不显示
\return 0：成功 -1：失败
*/
int SG_SetVideoTimeOSD (int UserID, int Channel,st_SG_Rect *Pos,int  Show);

/*!
\brief 获取时间的OSD的信息
\param UserID 登录句柄
\param Channel 通道号
\param Pos 时间OSD显示位置
\param Show OSD是否显示，1显示，0不显示
\return 0：成功 -1：失败
*/
int SG_GetVideoTimeOSD (int UserID, int Channel,st_SG_Rect* Pos,int *Show);

/*!
\brief 设置视频通道的OSD 信息
\param UserID 登录句柄
\param Channel DEV对应的通道号
\param pVideoOsdInfo OSD配置信息
\param ElemCount OSD配置个数
\return 0：成功 -1：失败
*/
int SG_SetVideoOSD (int UserID, int Channel,st_SG_VideoOsdInfo *pVideoOsdInfo,int ElemCount);


/*!
\brief 获取视频通道的OSD 信息
\param UserID 登录句柄
\param Channel 通道号
\param pVideoOsdInfo OSD的信息
\param ElemCount OSD配置个数
\return 0：成功 -1：失败
*/
int SG_GetVideoOSD (int UserID, int Channel,st_SG_VideoOsdInfo *pVideoOsdInfo,int* ElemCount);

/*!
\brief 设置通道的录像计划
\param UserID 登录句柄
\param Client 通道号
\param Enable 录像启用标签 1/2:启用/禁用
\param pStruRecordPlan 录像计划
\param StruCount 录像计划个数
\return 0：成功 -1：失败
*/
int SG_SetRecrodSchedule (int UserID, int Channel,int Enable, st_SG_RecordPlan *pStruRecordPlan,int StruCount);

/*!
\brief 获取通道的录像计划
\param UserID 登录句柄
\param Client 通道号
\param Enable 录像启用标签 1/2:启用/禁用
\param pStruRecordPlan 录像计划
\param StruCount 录像计划个数
\return 0：成功 -1：失败
*/
int SG_GetRecrodSchedule (int UserID, int Channel,int *Enable, st_SG_RecordPlan *pStruRecordPlan,int *StruCount);
/*!
\brief 音频接收数据回调
\param VoicePlayHandle 音频句柄
\param EncodeType 音频编码类型 0：AAC 1：G711
\param Buffer 回调视频数据
\param BufSize 回调视频数据大小
\param pUser 用户数据
\return 成功：0 失败：-1 执行失败 获取错误码调用 ::SG_GetLastError  
*/
typedef void(*SG_RecvVoiceDataCallBack)(int VoicePlayHandle, int EncodeType, char *Buffer, int BufSize, void *pUser);
/*!
\brief 开启语音对讲
\param UserID 登录句柄
\param Chanel 通道号
\param pfCallBack 音频接收回调函数
\param pUser 用户数据
\return 失败：-1 其他值表示语音对讲句柄 执行失败 获取错误码调用 ::SG_GetLastError  
*/
int SG_StartVoice(int UserID, int Chanel, SG_RecvVoiceDataCallBack pfCallBack, void* pUser);
/*!
\brief 发送音频数据
\param UserID 登录句柄
\param VoicePlayHandle 音频句柄
\param EncodeType 编码类型 0：AAC 1：G711
\param Buffer 音频数据
\param BufSize 数据大小
\return 成功：0 失败：-1 执行失败 获取错误码调用 ::SG_GetLastError  
*/
int SG_SendVoiceData(int UserID, int VoicePlayHandle,int EncodeType, char *Buffer, int BufSize);

/*!
\brief 关闭语音对讲
\param UserID 登录句柄
\param VoicePlayHandle 通道号
\param 输出参数 无
\return 成功：0 失败：-1 执行失败 获取错误码调用 ::SG_GetLastError  
*/
int SG_StopVoice(int UserID, int Chanel, int VoicePlayHandle);


SG_SnapPicCallBack snapPic;
#endif 
