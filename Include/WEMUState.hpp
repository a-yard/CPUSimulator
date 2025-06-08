#ifndef __WEMUState_H__
#define __WEMUState_H__
#include "common.hpp"
enum
{
    WEMU_RUNNING,
    WEMU_STOP,
    WEMU_END,
    WEMU_ABORT,
    WEMU_QUIT
};
class WEMUState
{
public:
    int state;
    VAddr_t halt_pc;
    uint32_t halt_ret;
};
#endif