#include "../../Include/UART.h"

UART::UART(){
    
    this->BlockDeviceBASE = UART_BASE;
    this->BlockDeviceSIZE = UART_SIZE;
    this->UartReg[5]=0x60;
    this->UartReg[0]=0;
    this->is_eofd=0;
    

}

uint32_t UART::DrviceRead(uint32_t addr, int len) {
    if(len!=1)assert(0);
    if(addr==0x10000005)return 0x60 | IsKBHit();
    else if(addr == 0x10000000 && IsKBHit() ) return ReadKBByte();
    else return 0;
    // return this->UartReg[addr&0x7];
}
void UART::DrviceWrite(uint32_t addr, int len, uint32_t data) {
    if(len!=1)assert(0);
    // printf("%x\n%x\n",data,addr);
    // this->UartReg[addr&0x7]=data&0xff;
    if(addr==UART_BASE){
        printf("%c",data);
        fflush( stdout );
    }
  
}


int UART::ReadKBByte(){
    if( is_eofd ) return 0xffffffff;
	char rxchar = 0;
	int rread = read(fileno(stdin), (char*)&rxchar, 1);

	if( rread > 0 ) // Tricky: getchar can't be used with arrow keys.
		return rxchar;
	else
		return -1;
}
int UART::IsKBHit(){
    if( is_eofd ) return -1;
	int byteswaiting;
	ioctl(0, FIONREAD, &byteswaiting);
	if( !byteswaiting && write( fileno(stdin), 0, 0 ) != 0 ) { is_eofd = 1; return -1; } // Is end-of-file for 
	return ((!!byteswaiting)&0x1);
}