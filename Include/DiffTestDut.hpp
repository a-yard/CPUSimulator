#ifndef __DIFFTESTDUT_H_
#define __DIFFTESTDUT_H_
#include <dlfcn.h>
#include "common.hpp"
#include "ISA.hpp"
#include "BUS.hpp"
#include "WEMUState.hpp"


enum
{
    DIFFTEST_TO_DUT,
    DIFFTEST_TO_REF
};



class DiffTestDut
{
private:
    void (*ref_difftest_memcpy)(VAddr_t addr, void *buf, size_t n, bool direction) = NULL;
    void (*ref_difftest_regcpy)(void *dut, bool direction) = NULL;
    void (*ref_difftest_exec)(uint64_t n) = NULL;
    void (*ref_difftest_raise_intr)(uint64_t NO) = NULL;
    WEMUState *WEMUStateObj;
    Dut_CPU_state  Dut_CPU_stateObj;
    BUS * BUSObj;
    class ISA * ISAObj;
    bool is_skip_ref = false;
    int skip_dut_nr_inst = 0;
    void GetLocalCPUState();

public:

DiffTestDut(char* ref_so_file, long img_size, int port, BUS *InBUS, WEMUState *InWEMUState, ISA *InISA);
    void difftest_skip_ref();
    void difftest_skip_dut(int nr_ref, int nr_dut);
    void checkregs(Ref_CPU_state *ref, VAddr_t pc);
    void difftest_step(VAddr_t pc, VAddr_t npc);
    
};
#endif