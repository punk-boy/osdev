/*
***********************************************************
*                      UCOS186C.C
*               80186/80188 Specific Code
*                  SMALL MEMORY MODEL
***********************************************************
*                     INCLUDE FILES
***********************************************************
*/
#include "INCLUDES.H"
#pragma  inline

/*extern UBYTE    OSMapTbl[];
extern UBYTE    OSUnMapTbl[];*/


//OS_TCB OSTaskQueue[OS_ALL_TASK+1];
extern unsigned int OSTaskQueue[OS_ALL_TASK+1];
//OS_TCB OSBlocQueue[OS_ALL_TASK+1];
extern unsigned int OSBlocQueue[OS_ALL_TASK+1];

extern unsigned int OSTQhead;
extern unsigned int OSTQtail;

extern unsigned int OSBQhead;
extern unsigned int OSBQtail;

/*
***********************************************************
*                    CREATE A TASK
***********************************************************
*/

UBYTE OSTaskCreate(void (far *task)(void *dptr), void  *data, void  *pstk, UBYTE  p)
{
    OS_TCB *ptr;
    UWORD  *stk;


    //if (OSTCBPrioTbl[p] == (OS_TCB *)0) {                       /* Avoid creating task if already exist */
    if(OSTCBPrioTbl[p] == (OS_TCB *)0){
        ptr              = OSTCBGetFree();
        ptr->OSTCBPrio   = (UBYTE)p;
        ptr->OSTCBStat   = OS_STAT_RDY;
        ptr->OSTCBDly    = 0;

        stk              = (UWORD *)pstk;                       /* 80186/80188 Small Model              */
        *--stk           = (UWORD)FP_OFF(data);
        *--stk           = (UWORD)FP_SEG(task);
        *--stk           = (UWORD)FP_OFF(task);
        *--stk           = (UWORD)0x0200;                       /* PSW = Int. En.                       */
        *--stk           = (UWORD)FP_SEG(task);
        *--stk           = (UWORD)FP_OFF(task);
        *--stk           = (UWORD)0x0000;                       /* AX = 0                               */
        *--stk           = (UWORD)0x0000;                       /* CX = 0                               */
        *--stk           = (UWORD)0x0000;                       /* DX = 0                               */
        *--stk           = (UWORD)0x0000;                       /* BX = 0                               */
        *--stk           = (UWORD)0x0000;                       /* SP = 0                               */
        *--stk           = (UWORD)0x0000;                       /* BP = 0                               */
        *--stk           = (UWORD)0x0000;                       /* SI = 0                               */
        *--stk           = (UWORD)0x0000;                       /* DI = 0                               */
        *--stk           = (UWORD)0x0000;                       /* ES = 0                               */
        ptr->OSTCBStkPtr = (void *)stk;                         /* Load SP in TCB                       */
        OSTCBPrioTbl[p]  = ptr;
        OS_ENTER_CRITICAL();
        ptr->OSTCBNext        = OSTCBList;
        ptr->OSTCBPrev        = (OS_TCB *)0;
        if (OSTCBList != (OS_TCB *)0) {                         /* Rev. A, This line was missing        */
            OSTCBList->OSTCBPrev = ptr;
        }

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // TODO: judge the queue is full, so that we can enqueue
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        if(p != 63)
        {
            OSTQtail = (OSTQtail+1) % OS_ALL_TASK;
            OSTaskQueue[OSTQtail] = p;
            printf("in OSCreate : OSTQtail = %d, p = %d\n", OSTQtail, p);
        }
        else
        {
            printf("Idle process is created !\n");
        }
        


        /*OSTCBList             = ptr;
        OSRdyGrp             |= OSMapTbl[p >> 3];
        OSRdyTbl[p >> 3]     |= OSMapTbl[p & 0x07];*/
        OS_EXIT_CRITICAL();
        /*if (OSRunning) {
            OSSched();
        }*/
        return (OS_NO_ERR);
    } else {
        return (OS_PRIO_EXIST);
    }
}
