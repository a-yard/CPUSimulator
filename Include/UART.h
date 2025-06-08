#ifndef __MyUART_H__
#define __MyUART_H__

#include "CharacterDevice.hpp"
// 
#include <unistd.h>     // 必需：read(), fileno()
#include <sys/ioctl.h>  // 可选：ioctl()（如果代码中用到）
class UART : public CharacterDevice{
    private:
        uint8_t UartReg[8];
        int is_eofd;
        int ReadKBByte();
        int IsKBHit();
        
    
    public:
        UART();
        virtual uint32_t DrviceRead(uint32_t addr, int len) ;
        virtual void DrviceWrite(uint32_t addr, int len, uint32_t data) ;
        

};

#endif