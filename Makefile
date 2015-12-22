EXE=knight

BINDIR=./bin
LIBDIR=./lib
OBJDIR=./obj
SRCDIR=./src

OPTC_API=-I${SRCDIR}
API01=api
API02=hme_lowlevel
API03=generate_terrain
OBJDIR_API=${OBJDIR}/api
OBJ_API=${OBJDIR_API}/${API01}.o ${OBJDIR_API}/${API02}.o ${OBJDIR_API}/${API03}.o

#SRC01=widgets
#SRC02=load_widgets_fake
#SRC03=helper
#SRC04=main
#SRC05=console

#OBJ_LINUX=${OBJDIR}/${SRC01}.o ${OBJDIR}/${SRC02}.o ${OBJDIR}/${SRC03}.o ${OBJDIR}/${SRC04}.o ${OBJDIR}/${SRC05}.o
#OBJ=${OBJ_LINUX}

#${BINDIR}/${EXE}: ${OBJ}
#	${CC} ${OBJ} -o ${BINDIR}/${EXE} ${OPTL}

#${OBJDIR}/%.o: ${SRCDIR}/%.c
#	${CC} ${OPTC} -c -o $@ $<

api: ${OBJ_API}
	ar rcs ${LIBDIR}/api.a ${OBJ_API}

${OBJDIR_API}/%.o: ${SRCDIR}/api/%.c
	${CC} ${OPTC_API} -c -o $@ $<

clean:
	rm -f ${BINDIR}/${EXE} ${LIBDIR}/*.a ${OBJDIR_API}/*.o
