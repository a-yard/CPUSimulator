#ifndef __FLASH_H__
#define __FLASH_H__
#include "common.hpp"
#include "BlockDevice.hpp"
class Flash : public BlockDevice
{
public:
    Flash();

    Flash(char* ImgFile);

};
#endif