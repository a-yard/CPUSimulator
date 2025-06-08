#ifndef __CLINT_H__
#define __CLINT_H__
#include "CharacterDevice.hpp"
class CLINT:public CharacterDevice{
    private:
        Word_t mtimeL;
        Word_t mtimeH;
        Word_t mtimecmpL;
        Word_t mtimecmpH;
        Word_t msip;
       

    public:
        CLINT();
        virtual uint32_t DrviceRead(uint32_t addr, int len) ;
        virtual void DrviceWrite(uint32_t addr, int len, uint32_t data) ;
        void UpDataState();
};
#endif