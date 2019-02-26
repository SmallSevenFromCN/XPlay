//
// Created by Administrator on 2019/2/26 0026.
//

#ifndef XPLAY_IAUDIOPLAY_H
#define XPLAY_IAUDIOPLAY_H


#include <list>
#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay: public IObserver {
public:
    //缓冲满后堵塞
    virtual void Update(XData data);
    //获取缓冲数据，如果没有则堵塞
    virtual XData GetData();
    virtual bool StartPlay(XParameter out) = 0;

    //最大缓冲
    int maxFrame = 100;

protected:
    std::list<XData>frames;
    std::mutex framesMutex;
};


#endif //XPLAY_IAUDIOPLAY_H
