#ifndef __BUS_H__
#define __BUS_H__

#include "Memory.hpp"
#include "WEMUState.hpp"
#include "UART.h"
#include "MROM.hpp"
#include "CLINT.h"

#define BUSLEAFNODEREAD(DeviceName) \
{ \
uint32_t DeviceNameAddrHead = DeviceName ## _BASE; \
uint32_t DeviceNameAddrTail = DeviceNameAddrHead+ DeviceName ## _SIZE; \
if(RAddr>=DeviceNameAddrHead&&RAddr<=DeviceNameAddrTail){\
            return this-> DeviceName ## Obj->DrviceRead(RAddr, len); \
    } \
}

#define BUSLEAFNODEWIRTE(DeviceName) \
{ \
uint32_t DeviceNameAddrHead = DeviceName ## _BASE; \
uint32_t DeviceNameAddrTail = DeviceNameAddrHead+ DeviceName ## _SIZE; \
if(WAddr>=DeviceNameAddrHead&&WAddr<=DeviceNameAddrTail){\
        this->DeviceName ## Obj->DrviceWrite(WAddr,  WMask,WData); \
        return;\
    } \
}


class BUS{
    private:
        
        WEMUState * WEMUStateObj;
        
        void AccessBUSOutOfBound(VAddr_t addr);

    public:
        UART *UARTObj ;
        Memory * MemoryObj;
        MROM * MROMObj;
        CLINT * CLINTObj;
        Word_t BUSRead(VAddr_t RAddr,int len);
        void BUSWirte(VAddr_t WAddr,Word_t WData,int WMask);
        BUS (char * img_file,char * dtb_file);
};
#endif