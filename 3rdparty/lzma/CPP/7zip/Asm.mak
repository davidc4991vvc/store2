<<<<<<< HEAD
=======
!IFDEF ASM_OBJS
>>>>>>> upstream/master
!IF "$(CPU)" == "ARM"
$(ASM_OBJS): ../../../../Asm/Arm/$(*B).asm
	$(COMPL_ASM)
!ELSEIF "$(CPU)" != "IA64" && "$(CPU)" != "MIPS"
$(ASM_OBJS): ../../../../Asm/x86/$(*B).asm
	$(COMPL_ASM)
!ENDIF
<<<<<<< HEAD
=======
!ENDIF
>>>>>>> upstream/master
