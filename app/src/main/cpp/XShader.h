//
// Created by Administrator on 2019/2/26 0026.
//

#ifndef XPLAY_XSHADER_H
#define XPLAY_XSHADER_H

#include <mutex>

enum XShaderType{
    XSHADER_YUV420P = 0,   //Y 4   u 1     v 1      软解码
    XSHADER_NV12 = 25,     //Y4    uv1              手机
    XSHADER_NV21 = 26      //Y4    vu1
};

class XShader {
public:
    virtual bool Init(XShaderType type = XSHADER_YUV420P);
    virtual void Close();
    //获取材质并映射到内存
    virtual void GetTexture(unsigned int index,int width,int height, unsigned char *buf,bool isa= false);
    virtual void Draw();
protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] ={0};
    std::mutex mux;
};


#endif //XPLAY_XSHADER_H
