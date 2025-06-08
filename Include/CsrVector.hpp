#ifndef __CSR_T_H__
#define __CSR_T_H__
#include "common.hpp"
enum PrivilegedLevelenum{
    PrivilegedLevelU=0,
    PrivilegedLevelS,
    PrivilegedLevelH,
    PrivilegedLevelM,
    
};

enum RWPermissionenum{
    RWPermissionRW=0,
    RWPermissionRO=3
    
};

class CSR_T
{
    public:
        Word_t CsrNumber;
        string CsrName;
        Word_t Reg;
        Word_t PrivilegedLevel;
        Word_t RWPermission;
        
       
} ;

#define mstatusAddr 0x300
#define mtvecAddr 0x305
#define mipAddr 0x344
#define mieAddr 0x304
#define mepcAddr 0x341
#define mcauseAddr 0x342
#define mtvalAddr 0x343
#define cycleAddr 0xC00
#define cyclehAddr 0xc80

#define ADDCSR(csrname,csrn,inRWPermission,inPrivilegedLevel,inInitValue) \
    CSR_T CSR_T__##csrn; \
    CSR_T__##csrn.CsrNumber = csrn; \
    CSR_T__##csrn.CsrName = csrname; \
    CSR_T__##csrn.Reg = inInitValue; \
    CSR_T__##csrn.PrivilegedLevel = inPrivilegedLevel ;\
    CSR_T__##csrn.RWPermission = inRWPermission ;\
    csrvector.push_back(CSR_T__##csrn);
    // Word_t cycle;   //cycle 计数器记录自处理器启动以来的时钟周期数  0xc00
	// Word_t cycleh;  //0xc80

	// Word_t time;   //timerl 是一个 32 位的寄存器，用于存储定时器（通常是系统时钟或定时中断机制）的低 32 位值  0xC01
	// Word_t timeh; //timeh 存储的是定时器 time 寄存器的高 32 位  0xC81

class CsrVector{
    // private:
        
    public:
        vector<CSR_T> csrvector;
        
        // CSR_T & operator[](int index) {
        //     for(int i=1;i<this->csrvector.size();i++){
        //         if(index==csrvector[i].CsrNumber)return csrvector[i];
        //     }
        //     return csrvector[0];
        // }
        // Word_t ReadCsr(Word_t CsrId){
        //     for(int i=1;i<this->csrvector.size();i++){
        //         if(CsrId==csrvector[i].CsrNumber)return csrvector[i].Reg;
        //     }
        // }

        CsrVector (){
            ADDCSR("NULL",4096,0,0,0);
            ADDCSR("misa",0x301,RWPermissionRW,PrivilegedLevelM,0x40401101);//
            ADDCSR("mvendorid",0xF11,RWPermissionRO,PrivilegedLevelM,0xff0ff0ff);  //表示非商业实现
            ADDCSR("marchid",0xF12,RWPermissionRO,PrivilegedLevelM,0);  //商业体系结构id
            ADDCSR("mimpid",0xF13,RWPermissionRO,PrivilegedLevelM,0); //处理器实现版本
            ADDCSR("mhartid",0xF14,RWPermissionRO,PrivilegedLevelM,0); //运行代码的硬件线程的整数 ID

            ADDCSR("mstatus",0x300,RWPermissionRW,PrivilegedLevelM,0x1800); //机器状态寄存器      
            ADDCSR("mstatush",0x310,RWPermissionRW,PrivilegedLevelM,0); //机器状态寄存器      
            ADDCSR("mtvec",0x305,RWPermissionRW,PrivilegedLevelM,0); //机器陷阱向量基地址寄存器      
            ADDCSR("mip",0x344,RWPermissionRW,PrivilegedLevelM,0); //机器中断挂起。
            ADDCSR("mie",0x304,RWPermissionRW,PrivilegedLevelM,0); //机器中断使能寄存器    
            ADDCSR("mscratch",0x340,RWPermissionRW,PrivilegedLevelM,0); //机器陷阱处理程序的暂存器
            ADDCSR("mepc",0x341,RWPermissionRW,PrivilegedLevelM,0); //机器异常程序计数器
            ADDCSR("mcause",0x342,RWPermissionRW,PrivilegedLevelM,0); //机器成因寄存器
            ADDCSR("mtval",0x343,RWPermissionRW,PrivilegedLevelM,0); //机器错误地址或指令
            ADDCSR("cycle",0xC00,RWPermissionRO,PrivilegedLevelU,0); //RDCYCLE 指令的时钟周期计数器低32位
            ADDCSR("cycleh",0xC80,RWPermissionRO,PrivilegedLevelU,0); //RDCYCLE 指令的时钟周期计数器高32位

            ADDCSR("pmpaddr0",0x3b0,RWPermissionRW,PrivilegedLevelM,0); 
            ADDCSR("pmpcfg0",0x3a0,RWPermissionRW,PrivilegedLevelM,0); 

            //riscv-test
            ADDCSR("satp",0x180 ,RWPermissionRW,PrivilegedLevelS,0); //监管级地址转换和保护。
            ADDCSR("medeleg",0x302 ,RWPermissionRW,PrivilegedLevelM,0); //机器异常代理寄存器。
            ADDCSR("mideleg",0x303 ,RWPermissionRW,PrivilegedLevelM,0); //机器异常代理寄存器。

            //系统调试预留
            ADDCSR("debug",0x744 ,RWPermissionRW,PrivilegedLevelU,0); 
            ADDCSR("debug1",0x7a0 ,RWPermissionRW,PrivilegedLevelU,0); 
            ADDCSR("debug2",0x7a1 ,RWPermissionRW,PrivilegedLevelU,0); 
            ADDCSR("debug3",0x7a2 ,RWPermissionRW,PrivilegedLevelU,0); 
            ADDCSR("debug4",0x7a3 ,RWPermissionRW,PrivilegedLevelU,0); 
            ADDCSR("debug5",0x7a4 ,RWPermissionRW,PrivilegedLevelU,0); 
            ADDCSR("debug6",0x7a5 ,RWPermissionRW,PrivilegedLevelU,0); 
   
            

        }
        void DisplayCsr(){
            for(int i =0;i<this->csrvector.size();i++){
                printf("%s = %x\n",csrvector[i].CsrName.c_str(),csrvector[i].Reg);
            }
        }
};
#endif