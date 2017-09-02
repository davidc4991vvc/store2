C_OBJS = $(C_OBJS) \
  $O\7zCrc.obj
<<<<<<< HEAD
!IF "$(CPU)" == "IA64" || "$(CPU)" == "MIPS"
=======
!IF "$(CPU)" == "IA64" || "$(CPU)" == "MIPS" || "$(CPU)" == "ARM"
>>>>>>> upstream/master
C_OBJS = $(C_OBJS) \
!ELSE
ASM_OBJS = $(ASM_OBJS) \
!ENDIF
  $O\7zCrcOpt.obj
