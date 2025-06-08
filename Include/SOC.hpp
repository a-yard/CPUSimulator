#ifndef __SOC_H__
#define __SOC_H__
#include "Memory.hpp"
#include "CPU.hpp"
#include "BUS.hpp"
class SOC{
    public:
    
        CPU * CPUObj;
        BUS * BUSObj;
        WEMUState * WEMUStateObj;
        SOC(WEMUState * InWEMUState,char * img_file,char * dtb_file,ISA * InCPU);
        
};

#endif