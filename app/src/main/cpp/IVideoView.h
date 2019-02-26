//
// Created by Administrator on 2019/2/26 0026.
//

#ifndef XPLAY_IVIDEOVIEW_H
#define XPLAY_IVIDEOVIEW_H


#include "XData.h"
#include "IObserver.h"

class IVideoView :public IObserver{
public:
    virtual void SetRender(void *win) =0;
    virtual void Render(XData data) = 0;
    virtual void Update(XData data);
};


#endif //XPLAY_IVIDEOVIEW_H
