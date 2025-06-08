#ifndef __MROM_H__
#define __MROM_H__
#include "BlockDevice.hpp"
class MROM:public BlockDevice{
    public:
        MROM(char* ImgFile);
        void DrviceWrite(uint32_t addr, int len, uint32_t data);
};
#endif