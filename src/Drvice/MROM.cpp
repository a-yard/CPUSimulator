#include "../../Include/MROM.hpp"


MROM::MROM(char* ImgFile){
    this->BlockDeviceBASE = MROM_BASE;
    this->BlockDeviceSIZE = MROM_SIZE;
    this->PMem = (uint8_t*)malloc(this->BlockDeviceSIZE);
   
    this->load_img(ImgFile);
    
}

void MROM::DrviceWrite(uint32_t addr, int len, uint32_t data){
    cout<<"MRON Can't Write"<<endl;
    assert(0);
}
