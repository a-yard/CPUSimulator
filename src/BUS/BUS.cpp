#include "../../Include/BUS.hpp"

BUS::BUS( char * img_file,char * dtb_file)
{
    
    this->MemoryObj = new Memory(img_file);
    this->UARTObj = new UART();
    
    this->MROMObj = new MROM(dtb_file);
    this->CLINTObj = new CLINT();
}

Word_t BUS::BUSRead(VAddr_t RAddr, int len)
{
    BUSLEAFNODEREAD(Memory);
    BUSLEAFNODEREAD(UART);
    BUSLEAFNODEREAD(MROM);
    BUSLEAFNODEREAD(CLINT);
    AccessBUSOutOfBound(RAddr);
    
}
void BUS::BUSWirte(VAddr_t WAddr, Word_t WData, int WMask)
{
 
    BUSLEAFNODEWIRTE(Memory);
    BUSLEAFNODEWIRTE(UART);
    BUSLEAFNODEWIRTE(CLINT);
    AccessBUSOutOfBound(WAddr);
}

void BUS::AccessBUSOutOfBound(VAddr_t addr){
    cout<<"AccessBUSOutOfBound: 0x"<<hex<<addr<<endl;
    assert(0);
}