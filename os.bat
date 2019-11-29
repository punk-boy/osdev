@echo "cd Z:\shared\osdev\"
@cd /d Z:\shared\osdev\
@echo "bcc test1.c ucos.c ucos186c.c ucos186a.asm"
@start bcc test1.c ucos.c ucos186c.c ucos186a.asm
@pause
@echo "del test1.obj ucos.obj ucos186a.obj ucos186c.obj"
@del ".\TEST1.OBJ" /F
@del ".\UCOS.OBJ" /F
@del ".\UCOS186A.OBJ" /F
@del ".\UCOS186C.OBJ" /F
@echo "================================"
