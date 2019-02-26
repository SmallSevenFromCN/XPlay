//
// Created by Administrator on 2019/2/24 0024.
//

#ifndef XPLAY_XDATA_H
#define XPLAY_XDATA_H


struct XData {
    unsigned  char *data = 0;
    unsigned char *datas[8] ={0};
    int size = 0;
    bool isAudio = false;
    void Drop();
    int width = 0;
    int height = 0;
};


#endif //XPLAY_XDATA_H
