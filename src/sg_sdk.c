#include "http.h"
#include "sg_sdk.h"
#include "comm_dev.h"
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t userId_mutex_lock;
pthread_t pthCommDev;
st_SG_DEV dev;
int userId = -1;
extern char *glist;
extern int flagSnapPicCallBack;
//接口函数定义
/*!
  \brief SDK 初始化
  \param pDevList DEV数组列表
  \param Num  设备数组元素个数
  \return 0：执行成功/ -1：执行失败 获取错误码调用 ::SG_GetLastError           
*/
int SG_Init(st_SG_DEV *pDevList, int Num)
{
    int err;
    char *data = "hytek";
    printf("hytek work ***********************************\n");
    strcpy(dev.szIP, "192.168.1.101");
    strcpy(dev.szName, "hytek");
    strcpy(dev.szUser, "hytek");
    strcpy(dev.szPass, "123456");
    strcpy(dev.szType, "infrared");
    strcpy(dev.szMulticastIP, "192.168.1.101");
    
    dev.nTCPPort       = 6000;
    dev.nUDPPort       = 5000;
    dev.nMulticastPort = 4000;
    dev.nConnectType   = SG_SDK_TCP;
    dev.nDecoderTag    = 100;
    strcpy(dev.szSPSHead, "00 00 00 01");
    dev.nSPSDataType   = 0x67;
    dev.bStatus        = false; 
    pDevList = &dev;
    
    err = pthread_mutex_init(&userId_mutex_lock, NULL);
    if (err != 0) 
    {
        printf("userId_mutex_lock init failed\n");
        return -1;
    }
    err = pthread_create(&pthCommDev, NULL, comm_dev_thread, (void*)data);
    if (err != 0) 
    {
        perror("pthread_create error\n");
        return -1;
    }
    err = http_init();
    if(err != 0)
    {
        perror("http_init error\n");
        return -1;
    }
    return 0;
}

/*!
  \brief SDK 资源释放
  \return 0：执行成功/ -1：执行失败 获取错误码调用 ::SG_GetLastError
  \ SGSDK接口技术规范初始化
*/
int SG_Cleanup()
{
    int err;
    void *ret;
    http_clean();
    pthread_cancel(pthCommDev);
    err = pthread_join(pthCommDev, &ret);
    if (err != 0) 
    {
        perror("pthread_join pthCommDev error\n");
        return -1;
    }
    pthread_mutex_destroy(&userId_mutex_lock);
    return 0;
}

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
int SG_SetMessageCallBack(st_SG_DEV* pDev, SG_MessageCallBack pfCallBack, void* pUser){
    return 0;
}

//-----------------------------------------------------------------------------
//     错误信息
//-----------------------------------------------------------------------------
/*!
  \brief 获取最后的错误码
  \param sErrorMsg 错误消息字符串缓冲
  \param Len 缓冲长度
  \return 0：执行成功/ -1：执行失败

*/
int SG_GetLastError( char* sErrorMsg, int Len){
    return 0;
}

//-----------------------------------------------------------------------------
//     用户登录
//-----------------------------------------------------------------------------
/*!
  \brief 用户登录
  \param pdev ::st_SG_DEV 结构信息
  \return 登录情况：成功则返回实际的登录句柄，否则返回-1  获取错误码调用 ::SG_GetLastError
*/
int SG_Login(st_SG_DEV* pdev)
{
    pthread_mutex_lock(&userId_mutex_lock);
    if(userId != -1)
    {
        pthread_mutex_unlock(&userId_mutex_lock);
        return userId;
    }
    else if(strcmp(pdev->szUser, "hytek") == 0)
    {
        if(strcmp(pdev->szPass, "123456") == 0)
        {
            if(pdev->bStatus == true)
            {
                userId = 1;
                pthread_mutex_unlock(&userId_mutex_lock);
                return userId;
            }
        }
    }
    pthread_mutex_unlock(&userId_mutex_lock);
    return -1;
}

/*!
  \brief 用户注销
  \param UserID 用户登录句柄,DVR的实际登录句柄
  \return 0：执行成功/ -1：执行失败  获取错误码调用 ::SG_GetLastError
*/
int SG_Logout(int UserID)
{
    pthread_mutex_lock(&userId_mutex_lock);
    userId = -1;
    pthread_mutex_unlock(&userId_mutex_lock);
    return 0;
}

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
int SG_SnapPic(int UserID,int Channel,int Type,st_SG_Time stStart, st_SG_Time stStop,int Interval, SG_SnapPicCallBack pfCallBack)
{
    snapPic = pfCallBack;
    flagSnapPicCallBack = 1;
    return 0;
}
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
int SG_RealPlay(int UserID,int Channel,SG_RealDataCallBack pfCallBack,void* pUser){
    return 0;
}

/*!
  \brief 停止视频播放
  \param PlayHandle 实际的视频播放句柄,
  \return 0：执行成功/ -1：执行失败  获取错误码调用 ::SG_GetLastError

*/
int SG_StopRealPlay(int PlayHandle){
    return 0;
}



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
int SG_FindVideoFiles(int UserID,int Channel,st_SG_Time stStart,st_SG_Time stStop,st_SG_VideoFile* pstFiles,int Count,int FileType){
    return 0;
}
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
int SG_PlayBack(int UserID, int Channel, char* pFileName, void* hWnd){
    return 0;
}

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
int SG_PlayBackByTime(int UserID, int Channel, st_SG_Time stStart, st_SG_Time stStop){
    return 0;
}

/*!
  \brief 停止录像回放
  \param UserID 登录句柄
  \param PlayBackHandle 回放句柄, 是 ::SG_PlayBack 返回的结果
  \return 0：成功 -1：失败
*/
int SG_StopPlayBack(int UserID, int PlayBackHandle){
    return 0;
}

/*!
  \brief 录像回放控制-暂停，DVR数组的下标值
  \param PlayBackHandle 视频回放句柄
  \return 0：成功 -1：失败
*/
int SG_PlayBackPause(int UserID, int PlayBackHandle){
    return 0;
}

/*!
  \brief 录像回放控制-播放
  \param UserID 登录句柄
  \param PlayBackHandle 视频回放句柄
  \return 0：成功 -1：失败
*/
int SG_PlayBackPlay(int UserID, int PlayBackHandle){
    return 0;
}
/*!
  \brief 录像回放控制-恢复
  \param iUserID 登录句柄
  \param iPlayBackHandle 视频回放句柄
  \return 0：成功 -1：失败
*/
int SG_PlayBackResume(int UserID, int PlayBackHandle){
    return 0;
}

/*!
  \brief 录像回放控制-从指定位置开始播放
  \param UserID 登录句柄
  \param PlayBackHandle 视频回放句柄
  \param Offset 播放起始秒数
  \param Total  总时间长度
  \return 0：成功 -1：失败
*/
int SG_PlayBackSeek(int UserID, int PlayBackHandle, int Offset, int Total, int size){
    return 0;
}

/*!
  \brief 录像回放控制-快放
  \param UserID 登录句柄
  \param PlayBackHandle 视频回放句柄
  \return 0：成功 -1：失败
*/
int SG_PlayBackFast(int UserID, int PlayBackHandle){
    return 0;
}

/*!
  \brief 录像回放控制-慢放
  \param UserID 登录句柄
  \param PlayBackHandle 视频回放句柄
  \return 0：成功 -1：失败
*/
int SG_PlayBackSlow(int UserID, int PlayBackHandle){
    return 0;
}

/*!
  \brief 录像回放控制-正常速度放
  \param UserID 登录句柄
  \param PlayBackHandle 视频回放句柄
  \return 0：成功 -1：失败
*/
int SG_PlayBackNormal(int UserID, int PlayBackHandle){
    return 0;
}

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
int SG_PTZControl(int UserID, int Channel, int Cmd,int Para1, int Para2, int Para3){
    return 0;
}

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
int SG_PTZPreset(int UserID, int Channel, int Cmd,int Para1, int Para2, int Para3){
    return 0;
}


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
int SG_PTZCruise(int UserID, int Channel, int Cmd, int Para1, int Para2, int Para3){
    return 0;
}


/// 设置实时视频数据捕获回调函数
int SG_SetRealDataCallBack(SG_RealDataCallBack pfCallBack, void* pUser){
    return 0;
}

/// 设置回放数据捕获回调函数
int SG_SetPlayDataCallBack(int UserID, int PlayBackHandle, SG_PlayDataCallBack pfCallBack, void* pUser){
    return 0;
}

/// 设置实时视频数据捕获回调函数
int SG_SetSnapPicCallBack(SG_SnapPicCallBack pfCallBack, void* pUser)
{
    snapPic = pfCallBack;
    flagSnapPicCallBack = 1;
    return 0;
}

/*!
  \brief 设备状态
  \param UserID 登录句柄
  \return 设备正常，返回0,设备故障返回-1
*/
int SG_DevState(int UserID)
{
    if(dev.bStatus == true)
        return 0;
    else
        return -1;
}

/*!
  \brief 重启设备
  \param UserID , 登录句柄
  \return 0表示成功，-1表示失败
*/
int SG_RebootDev(int UserID){
    return 0;
}

/*!
  \brief 获取设备网络参数
  \param UserID , 登录句柄
  \param pDev ::st_SG_DEV 结构指针
  \return 0表示成功，-1表示失败
*/
int SG_GetDevIP(int UserID,st_SG_DEV* stDev){
    return 0;
}

/*!
  \brief 设置设备网络参数
  \param UserID , 登录句柄
  \param pDev ::st_SG_DEV 结构体
  \return 0表示成功，-1表示失败
*/
int SG_SetDevIP(int UserID,st_SG_DEV stDev){
    return 0;
}


/*!
  \brief 设置设备的IP
  \param UserID , 登录句柄，
  \param stTime ,时间信息
  \return 0表示成功，-1表示失败
*/
int SG_SetDevTime(int UserID,st_SG_Time stTime){
    return 0;
}

/*!
\brief 设置视频图像的显示参数
\param UserID 登录句柄
\param Bright 图像亮度 范围(0-255)
\param Contrast 对比度 范围(0-255)
\param Saturation 饱和度 范围(0-255)
\param Hue 色度 范围(0-255)
\return 0：成功 -1：失败
*/
int SG_SetImageSetting (int UserID,int Channel, int Bright,int Contrast,int Saturation, int Hue){
    return 0;
}

/*!
\brief 获取视频图像的显示参数
\param UserID 登录句柄
\param Bright 图像亮度 范围(0-255)
\param Contrast 对比度 范围(0-255)
\param Saturation 饱和度 范围(0-255)
\param Hue 色度 范围(0-255)
\return 0：成功 -1：失败
*/
int SG_GetImageSetting(int UserID,int Channel, int *Bright,int *Contrast,int *Saturation, int *Hue){
    return 0;
}


/*!
\brief 设置视频参数
\param UserID 登录句柄
\param Channel 通道号
\param pParam 视频参数结构
\return 0：成功 -1e：失败
*/
int SG_SetVideoParam (int UserID,int Channel,st_SG_VideoParam* pParam){
    return 0;
}


/*!
\brief 获取视频参数
\param UserID 登录句柄
\param Channel 通道号
\param pParam 视频参数结构
\return 0：成功 -1：失败
*/
int SG_GetVideoParam (int UserID,int Channel,st_SG_VideoParam* pParam){
    return 0;
}

/*!
\brief 设置时间的OSD的信息
\param UserID 登录句柄
\param Channel 通道号
\param Pos 时间OSD显示位置
\param Show OSD是否显示，1显示，0不显示
\return 0：成功 -1：失败
*/
int SG_SetVideoTimeOSD (int UserID, int Channel,st_SG_Rect *Pos,int  Show){
    return 0;
}

/*!
\brief 获取时间的OSD的信息
\param UserID 登录句柄
\param Channel 通道号
\param Pos 时间OSD显示位置
\param Show OSD是否显示，1显示，0不显示
\return 0：成功 -1：失败
*/
int SG_GetVideoTimeOSD (int UserID, int Channel,st_SG_Rect* Pos,int *Show){
    return 0;
}

/*!
\brief 设置视频通道的OSD 信息
\param UserID 登录句柄
\param Channel DEV对应的通道号
\param pVideoOsdInfo OSD配置信息
\param ElemCount OSD配置个数
\return 0：成功 -1：失败
*/
int SG_SetVideoOSD (int UserID, int Channel,st_SG_VideoOsdInfo *pVideoOsdInfo,int ElemCount){
    return 0;
}


/*!
\brief 获取视频通道的OSD 信息
\param UserID 登录句柄
\param Channel 通道号
\param pVideoOsdInfo OSD的信息
\param ElemCount OSD配置个数
\return 0：成功 -1：失败
*/
int SG_GetVideoOSD (int UserID, int Channel,st_SG_VideoOsdInfo *pVideoOsdInfo,int* ElemCount){
    return 0;
}

/*!
\brief 设置通道的录像计划
\param UserID 登录句柄
\param Client 通道号
\param Enable 录像启用标签 1/2:启用/禁用
\param pStruRecordPlan 录像计划
\param StruCount 录像计划个数
\return 0：成功 -1：失败
*/
int SG_SetRecrodSchedule (int UserID, int Channel,int Enable, st_SG_RecordPlan *pStruRecordPlan,int StruCount){
    return 0;
}

/*!
\brief 获取通道的录像计划
\param UserID 登录句柄
\param Client 通道号
\param Enable 录像启用标签 1/2:启用/禁用
\param pStruRecordPlan 录像计划
\param StruCount 录像计划个数
\return 0：成功 -1：失败
*/
int SG_GetRecrodSchedule (int UserID, int Channel,int *Enable, st_SG_RecordPlan *pStruRecordPlan,int *StruCount){
    return 0;
}

/*!
\brief 开启语音对讲
\param UserID 登录句柄
\param Chanel 通道号
\param pfCallBack 音频接收回调函数
\param pUser 用户数据
\return 失败：-1 其他值表示语音对讲句柄 执行失败 获取错误码调用 ::SG_GetLastError  
*/
int SG_StartVoice(int UserID, int Chanel, SG_RecvVoiceDataCallBack pfCallBack, void* pUser){
    return 0;
}
/*!
\brief 发送音频数据
\param UserID 登录句柄
\param VoicePlayHandle 音频句柄
\param EncodeType 编码类型 0：AAC 1：G711
\param Buffer 音频数据
\param BufSize 数据大小
\return 成功：0 失败：-1 执行失败 获取错误码调用 ::SG_GetLastError  
*/
int SG_SendVoiceData(int UserID, int VoicePlayHandle,int EncodeType, char *Buffer, int BufSize){
    return 0;
}

/*!
\brief 关闭语音对讲
\param UserID 登录句柄
\param VoicePlayHandle 通道号
\param 输出参数 无
\return 成功：0 失败：-1 执行失败 获取错误码调用 ::SG_GetLastError  
*/
int SG_StopVoice(int UserID, int Chanel, int VoicePlayHandle){
    return 0;
}
