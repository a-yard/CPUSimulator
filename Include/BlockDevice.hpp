#ifndef __BLOCKDEVICE_H__
#define __BLOCKDEVICE_H__
#include "Device.hpp"

class BlockDevice : public Device
{
protected:
    uint8_t *PMem;
    
    uint32_t HostToGuest(uint8_t *haddr);
    uint32_t host_read(void *addr, int len);
    void host_write(void *addr, int len, uint32_t data);
    uint32_t BlockDeviceBASE;
    uint32_t BlockDeviceSIZE;
    virtual void out_of_bound(uint32_t addr);
public:
    uint8_t *GuestToHost(uint32_t paddr);
    void load_img(char* ImgFile);
    long img_size;
    ~BlockDevice();
    virtual uint32_t DrviceRead(uint32_t addr, int len);
    virtual void DrviceWrite(uint32_t addr, int len, uint32_t data);


};

#endif