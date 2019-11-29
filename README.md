# osdev
my os kernel (modifiy from ucos186)
create on 2019.11.29 In LNNU
your can eamil tommao9925@gmail.com or direcetly issues on this page to report bugs or question, I will repeat immediately. :)
## Thanks
Thanks to my OS teacher selfless tutorial, for contact you can email qing_kun@163.com or 13804249076@163.com

## Environment  
+ XP3 sp3
+ borlandc


## v0.01 update
1. remove all unrelated function for easier operation, `OSMapTbl` and `OSUnMapTbl`.
2. add a `OSTaskQueue` and `OSBlocQuue` for process priority control.
3. modifiy the idle process and the 1st process(to print data to display the detail how the os running), remove all other process.

> after all the modify, you can choose any process you want manually, and see the how the two process runnig.

## v0.02 update  
1. repair a bug in OSInit, your can see the source code, I annotate the bug repair.
2. we let the program run 1st process as soon as executed.
3. recover the `OSTimeDly`, `OSSched`, in task 1 (also the 1st process now), call `OSTimeDly`, make itself blocked, then we schedule the system, let the idle process running.

> finished this step, we finished a schedule from a process to another process, so we can call it a simple process switch.




