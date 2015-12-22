EXE=knight

BINDIR=./bin
LIBDIR=./lib
OBJDIR=./obj
SRCDIR=./src

OPTC_API=
API01=api
API02=hme_lowlevel
API03=generate_terrain
OBJDIR_API=${OBJDIR}/api
OBJ_API=${OBJDIR_API}/${API01}.o ${OBJDIR_API}/${API02}.o ${OBJDIR_API}/${API03}.o

OPTC_CON=
CON01=console
OBJDIR_CON=${OBJDIR}/console
OBJ_CON=${OBJDIR_CON}/${CON01}.o

OPTC_REST=
OPTL_REST=
SRC01=main
OBJ_REST=${OBJDIR}/${SRC01}.o

LIB_API=${LIBDIR}/libapi.a
LIB_CON=${LIBDIR}/libconsole.a
LIBS=${LIB_API} ${LIB_CON}

${BINDIR}/${EXE}: ${LIBS} ${OBJ_REST}
	${CC} -L${LIBDIR} -lapi -lconsole ${OBJ_REST} -o ${BINDIR}/${EXE} ${OPTL_REST}

${LIB_API}: ${OBJ_API}
	ar rcs ${LIB_API} ${OBJ_API}

${LIB_CON}: ${OBJ_CON}
	ar rcs ${LIB_CON} ${OBJ_CON}

${OBJDIR_API}/%.o: ${SRCDIR}/api/%.c
	${CC} ${OPTC_API} -c -o $@ $<

${OBJDIR_CON}/%.o: ${SRCDIR}/console/%.c
	${CC} ${OPTC_CON} -c -o $@ $<

${OBJDIR}/%.o: ${SRCDIR}/%.c
	${CC} ${OPTC_REST} -c -o $@ $<

libs: ${LIBS}

api: ${LIB_API}

console: ${LIB_CON}
		
clean:
	rm -f ${BINDIR}/${EXE} ${LIBDIR}/*.a ${OBJDIR_API}/*.o ${OBJDIR_CON}/*.o ${OBJDIR}/*.o
