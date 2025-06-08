#ifndef __CHARACTERDEVICE_H__
#define __CHARACTERDEVICE_H__
#include "Device.hpp"

class CharacterDevice : public Device
{
protected:
    uint32_t BlockDeviceBASE;
    uint32_t BlockDeviceSIZE;
    virtual void out_of_bound(uint32_t addr);

public:
    virtual uint32_t DrviceRead(uint32_t addr, int len) = 0;
    virtual void DrviceWrite(uint32_t addr, int len, uint32_t data) = 0;
};
#endif