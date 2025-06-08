#include "../../Include/CharacterDevice.hpp"

void CharacterDevice::out_of_bound(uint32_t addr){
    if((addr>this->BlockDeviceBASE&&addr>=this->BlockDeviceBASE<this->BlockDeviceSIZE+this->BlockDeviceBASE)){
        cout << "access CharacterDevice out of bound: 0x" << hex << addr << endl;
        assert(0);
    }
}