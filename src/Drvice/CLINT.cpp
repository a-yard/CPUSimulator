#include "../../Include/CLINT.h"

CLINT::CLINT(){
    this->BlockDeviceBASE = CLINT_BASE;
    this->BlockDeviceSIZE = CLINT_SIZE;
    this->mtimecmpH=0;
    this->mtimecmpL=0x10000;
    this->mtimeH=0;
    this->mtimeL=0;
    this->msip=0;
}

uint32_t CLINT::DrviceRead(uint32_t addr, int len) {
    uint32_t ReadData=-1;
    switch (addr)
    {
    case 0X200BFF8:
        ReadData=this->mtimeL;
        break;
    case 0X200BFFC:
        ReadData=this->mtimeH;
        break;
    case 0X2004000:
        ReadData=this->mtimecmpL;
        break;
    case 0X2004004:
        ReadData=this->mtimecmpH;
        break;
    case 0x2000000:
        ReadData=this->msip;
        break;
    default:
        assert(0);
        break;
    }

    return ReadData;
}
void CLINT::DrviceWrite(uint32_t addr, int len, uint32_t data) {
    switch (addr)
    {
    case 0X200BFF8:
        this->mtimeL=data;
        return;
    case 0X200BFFC:
        this->mtimeH=data;
        return;
    case 0X2004000:
        this->mtimecmpL=data;
        return;
    case 0X2004004:
        this->mtimecmpH=data;
        return;
    case 0x2000000:
        
        this->msip = data;
        return;
    default:
        cout<<"access CLINT :"<<hex<<addr<<" error"<<endl;
        assert(0);
        break;
    }
}

void CLINT::UpDataState(){
    struct timeval tv;
	gettimeofday( &tv, 0 );
  
    uint64_t WemuTime =((uint64_t)(tv.tv_sec)) * 1000000LL ;//tv.tv_usec + 
    // 提取高 32 位和低 32 位
    this->mtimeH = (uint32_t)(WemuTime >> 32); // 右移 32 位取高 32 位
    this->mtimeL  = (uint32_t)(WemuTime & 0xFFFFFFFF); // 掩码取低 32 位
    uint64_t mtime = ((uint64_t)this->mtimeH)<<32;//+this->mtimeL;
    mtime += this->mtimeL;
    uint64_t mtimecmp = ((uint64_t)this->mtimecmpH)<<32;//+this->mtimecmpL;
    mtimecmp += this->mtimecmpL;
    // printf("%lx  %lx  %x\n",mtime,mtimecmp,msip);
    if(	mtime >= mtimecmp){
        this->msip=1;
    }
}





