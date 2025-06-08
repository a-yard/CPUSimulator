#ifndef __COMMON_H__
#define __COMMON_H__
#include <bits/stdint-uintn.h>
#include <stdlib.h>
#include <cassert>
#include <cstring>
#include <stdio.h>
#include "auto.h"
#include <iostream>
#include <sys/time.h>
#include <vector>
#include <stdlib.h>
#include "macro.h"
typedef uint32_t VAddr_t;
typedef uint32_t Word_t;

#define ANSI_FG_BLACK   "\33[1;30m"
#define ANSI_FG_RED     "\33[1;31m"
#define ANSI_FG_GREEN   "\33[1;32m"
#define ANSI_FG_YELLOW  "\33[1;33m"
#define ANSI_FG_BLUE    "\33[1;34m"
#define ANSI_FG_MAGENTA "\33[1;35m"
#define ANSI_FG_CYAN    "\33[1;36m"
#define ANSI_FG_WHITE   "\33[1;37m"
#define ANSI_BG_BLACK   "\33[1;40m"
#define ANSI_BG_RED     "\33[1;41m"
#define ANSI_BG_GREEN   "\33[1;42m"
#define ANSI_BG_YELLOW  "\33[1;43m"
#define ANSI_BG_BLUE    "\33[1;44m"
#define ANSI_BG_MAGENTA "\33[1;35m"
#define ANSI_BG_CYAN    "\33[1;46m"
#define ANSI_BG_WHITE   "\33[1;47m"
#define ANSI_NONE       "\33[0m"
#define ANSI_FMT(str, fmt) fmt str ANSI_NONE

using namespace std;
typedef struct {
    Word_t gpr[32];
    VAddr_t pc;
    Word_t mepc;  //存放触发异常的PC
    Word_t mstatus; //存放处理器的状态
    Word_t mcause;  //存放触发异常的原因
    Word_t mtvec;   //存放异常入口地址
  } riscv32CPUstate;
  typedef riscv32CPUstate Ref_CPU_state;
  typedef riscv32CPUstate Dut_CPU_state;
// #define RESET_VECTOR 0x80000000
#endif