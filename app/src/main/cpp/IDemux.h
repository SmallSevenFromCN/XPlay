//
// Created by Administrator on 2019/2/24 0024.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H

#include "XData.h"

//解封装接口
class IDemux {
public:
    //打开文件，或者流媒体  rmtp http rtsp
    virtual bool Open(const char *url) = 0;

    //读取一帧数据，数据由调用者清理
    virtual XData Read() = 0;


};


#endif //XPLAY_IDEMUX_H
