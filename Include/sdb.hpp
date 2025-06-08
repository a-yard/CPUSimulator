#ifndef __sdb_H__
#define __sdb_H__
#include "common.hpp"

#include <readline/readline.h>
#include <readline/history.h>
#include <iostream>
#include "watchpoint.hpp"
#include "expr.hpp"
#include "CPU.hpp"
#include "Memory.hpp"
#include "WEMUState.hpp"
#define NR_CMD ARRLEN(cmd_table)
static int is_batch_mode = false;
class sdb
{
private:
    struct
    {
        const char *name;
        const char *description;
    } cmd_table[9];
    watchpoint *watchpointObj;
    expr *exprObj;
    BUS *BUSObj;
    CPU * CPUObj;
    
    char *rl_gets();
    int cmd_c(char *args);
    int cmd_q(char *args);
    int cmd_si(char *args);
    int cmd_info(char *args);
    int cmd_x(char *args);
    int cmd_w(char *args);
    int cmd_d(char *args);
    int cmd_p(char *args);
    int cmd_help(char *args);
    int SelectFun(int n,char *args);
    WEMUState * NPC_State;


public:
    sdb(BUS *,CPU * InCPU);
    ~sdb();
    void sdb_mainloop();
    
    void sdb_set_batch_mode();
  
};
#endif