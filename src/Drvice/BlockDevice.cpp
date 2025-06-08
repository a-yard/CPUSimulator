#include "../../Include/BlockDevice.hpp"

uint8_t* BlockDevice::GuestToHost(uint32_t paddr){
    return (uint8_t *)(this->PMem + paddr - BlockDeviceBASE);
}

uint32_t BlockDevice::HostToGuest(uint8_t *haddr){
    return (uint32_t)(haddr - this->PMem + BlockDeviceBASE);
}

uint32_t BlockDevice::host_read(void *addr, int len){
    switch (len)
    {
    case 1:
        return *(uint8_t *)addr;
    case 2:
        return *(uint16_t *)addr;
    case 4:
        return *(uint32_t *)addr;
    default:
        assert(0);
    }
}

void BlockDevice::host_write(void *addr, int len, uint32_t data)
{
    switch (len)
    {
    case 1:
        *(uint8_t *)addr = data;
        return;
    case 2:
        *(uint16_t *)addr = data;
        return;
    case 4:
        *(uint32_t *)addr = data;
        return;
    default:
        printf("len=%d,data=%x\n",len,data);
        assert(0);
    }
}

void BlockDevice::out_of_bound(uint32_t addr){
    if(!(addr>=this->BlockDeviceBASE&&addr<=this->BlockDeviceSIZE+this->BlockDeviceBASE)){
        cout << "access BlockDevice out of bound: 0x" << hex << addr << endl;
        assert(0);
    }
}

void BlockDevice::load_img(char* ImgFile){
    if (ImgFile == NULL) {
        this->img_size= 4096; // built-in image size
        return;
      }
      FILE *fp = fopen(ImgFile, "rb");
    
      fseek(fp, 0, SEEK_END);
      long size = ftell(fp);
      printf("%x\n\n",size);
      fseek(fp, 0, SEEK_SET);
      int ret = fread(GuestToHost(this->BlockDeviceBASE), size, 1, fp);
    
      fclose(fp);
      img_size=size;
      

}
BlockDevice::~BlockDevice(){
    free(this->PMem);
}


uint32_t BlockDevice::DrviceRead(uint32_t addr, int len)
{
   
    out_of_bound(addr);
    return host_read(GuestToHost(addr), len);
}
void BlockDevice::DrviceWrite(uint32_t addr, int len, uint32_t data)
{
     out_of_bound(addr);
    host_write(GuestToHost(addr), len, data);
}