/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*
*                                (c) Copyright 2006, Micrium, Weston, FL
*                                          All Rights Reserved
*
*                                           ARM Cortex-M3 Port
*
* File      : OS_CPU.H
* Version   : V2.89
* By        : Jean J. Labrosse
*             Brian Nagel
*
* For       : ARMv7M Cortex-M3
* Mode      : Thumb2
* Toolchain : RealView Development Suite
*             RealView Microcontroller Development Kit (MDK)
*             ARM Developer Suite (ADS)
*             Keil uVision
*********************************************************************************************************
*/

#ifndef  OS_CPU_H
#define  OS_CPU_H


#ifdef   OS_CPU_GLOBALS
#define  OS_CPU_EXT
#else
#define  OS_CPU_EXT  extern
#endif

#ifndef  OS_CPU_EXCEPT_STK_SIZE
#define  OS_CPU_EXCEPT_STK_SIZE    128u          /* 默认异常中断大小                                   */
#endif

/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned int   INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   int   INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */

typedef unsigned int   OS_STK;                   /* Each stack entry is 32-bit wide                    */
typedef unsigned int   OS_CPU_SR;                /* Define size of CPU status register (PSR = 32 bits) */

/*
*********************************************************************************************************
*                                              Cortex-M3
*                                      Critical Section Management
*                                            （临界区管理）
*
* Method #1:  Disable/Enable interrupts using simple instructions.  After critical section, interrupts
*             will be enabled even if they were disabled before entering the critical section.
*             NOT IMPLEMENTED
*
* Method #2:  Disable/Enable interrupts by preserving the state of interrupts.  In other words, if
*             interrupts were disabled before entering the critical section, they will be disabled when
*             leaving the critical section.
*             NOT IMPLEMENTED
*
* Method #3:  Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
*             would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
*             disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
*             disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
*             into the CPU's status register.
*********************************************************************************************************
*/

#define  OS_CRITICAL_METHOD   3u                              /* 临界区模式---选择第3种                */

#if OS_CRITICAL_METHOD == 3u
#define  OS_ENTER_CRITICAL()  {cpu_sr = OS_CPU_SR_Save();}    /* 进入临界区（定义于os_cpu_a.asm中）    */
#define  OS_EXIT_CRITICAL()   {OS_CPU_SR_Restore(cpu_sr);}    /* 退出临界区                            */
#endif

/*
*********************************************************************************************************
*                                        Cortex-M3 Miscellaneous
*                                              M3其它参数
*********************************************************************************************************
*/

#define  OS_STK_GROWTH        1u                  /* 栈的生长方向：从高地址往低地址增长                */

#define  OS_TASK_SW()         OSCtxSw()           /* 任务切换，函数OSCtxSw()定义于os_cpu_a.asm中       */

/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/

OS_CPU_EXT  OS_STK   OS_CPU_ExceptStk[OS_CPU_EXCEPT_STK_SIZE];
OS_CPU_EXT  OS_STK  *OS_CPU_ExceptStkBase;

/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/

#if OS_CRITICAL_METHOD == 3u                      /* See OS_CPU_A.ASM                                  */
OS_CPU_SR  OS_CPU_SR_Save(void);
void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
#endif

void       OSCtxSw(void);
void       OSIntCtxSw(void);
void       OSStartHighRdy(void);

/* 不引用以下函数，将引用STM库提供的相应函数 */
// void       OS_CPU_PendSVHandler(void);

//                                                   /* See OS_CPU_C.C                                    */
// void       OS_CPU_SysTickHandler(void);
// void       OS_CPU_SysTickInit(INT32U  cnts);

#endif
