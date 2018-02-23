include ../Makefile.inc

GEN_EXE = t_fork \
	  fork_file_sharing \
	  fork_whos_on_first \
	  fork_sig_sync \
	  multi_wait \
	  child_status \
	  make_zombie \
	  t_execve \
	  t_envargs

LINUX_EXE = large_file

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${LPLIB}		# True as a rough approximation
