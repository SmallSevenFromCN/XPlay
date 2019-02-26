//
// Created by Administrator on 2019/2/26 0026.
//

#ifndef XPLAY_SLAUDIOPLAY_H
#define XPLAY_SLAUDIOPLAY_H


#include "IAudioPlay.h"

class SLAudioPlay: public IAudioPlay {
public:
    virtual bool StartPlay(XParameter out);
    void PlayCall(void *bufq);

    SLAudioPlay();
    virtual ~SLAudioPlay();
protected:
    unsigned char *buf =0;
};


#endif //XPLAY_SLAUDIOPLAY_H
