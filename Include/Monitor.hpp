#ifndef __MONITOR_H__
#define __MONITOR_H__
#include "common.hpp"
#include "SOC.hpp"
#include "WEMUState.hpp"
#include "sdb.hpp"
#include "ISA.hpp"
#include <getopt.h>

#define no_argument 0
#define required_argument 1
#define optional_argument 2

class Monitor
{
private:
    char *img_file=NULL;
    char *elf_file=NULL;
    char *diff_so_file=NULL;
    char * dtb_file=NULL;
    char * Kernal_file=NULL;
    sdb *sdbObj;
    WEMUState *WEMUStateObj;

public:
    SOC *SOCObj;
    Monitor(int argc, char *argv[],ISA * InCPU);
    ~Monitor();
    int is_exit_status_bad();
    int parse_args(int argc, char *argv[]);
    void welcome();
};

#endif