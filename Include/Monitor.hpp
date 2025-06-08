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
    char *img_file;
    char *elf_file;
    char *diff_so_file;
    char * dtb_file;
    char * Kernal_file;
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