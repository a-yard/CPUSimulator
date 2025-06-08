#include "../../Include/SOC.hpp"

SOC::SOC(WEMUState * InWEMUState,char * img_file,char * dtb_file,ISA * InCPU){
    this->BUSObj = new BUS(img_file,dtb_file);
    this->CPUObj = new CPU(InWEMUState,InCPU);
}