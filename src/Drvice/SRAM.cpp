#include "../../Include/SRAM.hpp"

SRAM::SRAM(){
    this->BlockDeviceBASE = SRAM_BASE;
    this->BlockDeviceSIZE = SRAM_SIZE;
    this->PMem = (uint8_t*)malloc(this->BlockDeviceSIZE);
}