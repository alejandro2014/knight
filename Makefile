### Definitions ###
EXE=knight
LIBAPI=api
LIBCON=console
LIBMAP=map

### Options ###
OPTC_API=-g
OPTC_CON=-I/usr/local/include -g
OPTC_MAP=-I/usr/local/include -g
OPTC_REST=-I/usr/local/include -g

OPTL=-L/usr/local/lib -lSDL2 -lSDL2_ttf

### Directories ###
BINDIR=./bin
LIBDIR=./lib
OBJDIR=./obj
SRCDIR=./src

OBJDIR_API=${OBJDIR}/${LIBAPI}
OBJDIR_CON=${OBJDIR}/${LIBCON}
OBJDIR_MAP=${OBJDIR}/${LIBMAP}

SRCDIR_API=${SRCDIR}/${LIBAPI}
SRCDIR_CON=${SRCDIR}/${LIBCON}
SRCDIR_MAP=${SRCDIR}/${LIBMAP}

### Names of the files ###
API01=api
API02=hme_lowlevel
API03=generate_terrain
API04=flood
API05=replace

CON01=console_draw
CON02=console_lang
CON03=console_load
CON04=console_print
CON05=console_write

MAP01=map_draw
MAP02=events

SRC01=main
SRC02=draw
SRC03=hme_load
SRC04=font

OBJ_API=${OBJDIR_API}/${API01}.o ${OBJDIR_API}/${API02}.o ${OBJDIR_API}/${API03}.o ${OBJDIR_API}/${API04}.o ${OBJDIR_API}/${API05}.o
OBJ_CON=${OBJDIR_CON}/${CON01}.o ${OBJDIR_CON}/${CON02}.o ${OBJDIR_CON}/${CON03}.o ${OBJDIR_CON}/${CON04}.o ${OBJDIR_CON}/${CON05}.o
OBJ_MAP=${OBJDIR_MAP}/${MAP01}.o ${OBJDIR_MAP}/${MAP02}.o
OBJ_REST=${OBJDIR}/${SRC01}.o ${OBJDIR}/${SRC02}.o ${OBJDIR}/${SRC03}.o ${OBJDIR}/${SRC04}.o

LIBA_API=${LIBDIR}/lib${LIBAPI}.a
LIBA_CON=${LIBDIR}/lib${LIBCON}.a
LIBA_MAP=${LIBDIR}/lib${LIBMAP}.a

LIBSA=${LIBA_API} ${LIBA_CON} ${LIBA_MAP}

### Rules ###
${BINDIR}/${EXE}: ${LIBSA} ${OBJ_REST}
	${CC} -L${LIBDIR} -l${LIBAPI} -l${LIBCON} -l${LIBMAP} ${OBJ_REST} -o ${BINDIR}/${EXE} ${OPTL}

${LIBA_API}: ${OBJ_API}
	ar rcs ${LIBA_API} ${OBJ_API}

${LIBA_CON}: ${OBJ_CON}
	ar rcs ${LIBA_CON} ${OBJ_CON}

${LIBA_MAP}: ${OBJ_MAP}
	ar rcs ${LIBA_MAP} ${OBJ_MAP}

${OBJDIR_API}/%.o: ${SRCDIR_API}/%.c
	${CC} ${OPTC_API} -c -o $@ $<

${OBJDIR_CON}/%.o: ${SRCDIR_CON}/%.c
	${CC} ${OPTC_CON} -c -o $@ $<

${OBJDIR_MAP}/%.o: ${SRCDIR_MAP}/%.c
	${CC} ${OPTC_MAP} -c -o $@ $<

${OBJDIR}/%.o: ${SRCDIR}/%.c
	${CC} ${OPTC_REST} -c -o $@ $<

api: ${LIBA_API}

console: ${LIBA_CON}

map: ${LIBA_MAP}

clean:
	rm -f ${BINDIR}/${EXE} ${LIBDIR}/*.a ${OBJDIR_API}/*.o ${OBJDIR_CON}/*.o ${OBJDIR_MAP}/*.o ${OBJDIR}/*.o
