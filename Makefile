### Definitions ###
EXE=knight
LIBAPI=api
LIBCON=console
LIBMAP=map
LIBWID=widgets

### Options ###
OPTC_API=-g
OPTC_CON=-I/usr/local/include -g
OPTC_MAP=-I/usr/local/include -g
OPTC_WID=-I/usr/local/include -g
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
OBJDIR_WID=${OBJDIR}/${LIBWID}

SRCDIR_API=${SRCDIR}/${LIBAPI}
SRCDIR_CON=${SRCDIR}/${LIBCON}
SRCDIR_MAP=${SRCDIR}/${LIBMAP}
SRCDIR_WID=${SRCDIR}/${LIBWID}

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

MAP01=draw
MAP02=draw_terrain
MAP03=events
MAP04=font

WID01=menu_bar

SRC01=main

OBJ_API=${OBJDIR_API}/${API01}.o ${OBJDIR_API}/${API02}.o ${OBJDIR_API}/${API03}.o ${OBJDIR_API}/${API04}.o ${OBJDIR_API}/${API05}.o
OBJ_CON=${OBJDIR_CON}/${CON01}.o ${OBJDIR_CON}/${CON02}.o ${OBJDIR_CON}/${CON03}.o ${OBJDIR_CON}/${CON04}.o ${OBJDIR_CON}/${CON05}.o
OBJ_MAP=${OBJDIR_MAP}/${MAP01}.o ${OBJDIR_MAP}/${MAP02}.o ${OBJDIR_MAP}/${MAP03}.o ${OBJDIR_MAP}/${MAP04}.o
OBJ_WID=${OBJDIR_WID}/${WID01}.o
OBJ_REST=${OBJDIR}/${SRC01}.o

LIBA_API=${LIBDIR}/lib${LIBAPI}.a
LIBA_CON=${LIBDIR}/lib${LIBCON}.a
LIBA_MAP=${LIBDIR}/lib${LIBMAP}.a
LIBA_WID=${LIBDIR}/lib${LIBWID}.a

LIBSA=${LIBA_API} ${LIBA_CON} ${LIBA_MAP} ${LIBA_WID}

### Rules ###
${BINDIR}/${EXE}: ${LIBSA} ${OBJ_REST}
	${CC} -L${LIBDIR} -l${LIBAPI} -l${LIBCON} -l${LIBMAP} -l${LIBWID} ${OBJ_REST} -o ${BINDIR}/${EXE} ${OPTL}

${LIBA_API}: ${OBJ_API}
	ar rcs ${LIBA_API} ${OBJ_API}

${LIBA_CON}: ${OBJ_CON}
	ar rcs ${LIBA_CON} ${OBJ_CON}

${LIBA_MAP}: ${OBJ_MAP}
	ar rcs ${LIBA_MAP} ${OBJ_MAP}

${LIBA_WID}: ${OBJ_WID}
	ar rcs ${LIBA_WID} ${OBJ_WID}

${OBJDIR_API}/%.o: ${SRCDIR_API}/%.c
	${CC} ${OPTC_API} -c -o $@ $<

${OBJDIR_CON}/%.o: ${SRCDIR_CON}/%.c
	${CC} ${OPTC_CON} -c -o $@ $<

${OBJDIR_MAP}/%.o: ${SRCDIR_MAP}/%.c
	${CC} ${OPTC_MAP} -c -o $@ $<

${OBJDIR_WID}/%.o: ${SRCDIR_WID}/%.c
	${CC} ${OPTC_WID} -c -o $@ $<

${OBJDIR}/%.o: ${SRCDIR}/%.c
	${CC} ${OPTC_REST} -c -o $@ $<

api: ${LIBA_API}

console: ${LIBA_CON}

map: ${LIBA_MAP}

widgets: ${LIBA_WID}

clean:
	rm -f ${BINDIR}/${EXE} ${LIBDIR}/*.a ${OBJDIR_API}/*.o ${OBJDIR_CON}/*.o ${OBJDIR_MAP}/*.o ${OBJDIR_WID}/*.o  ${OBJDIR}/*.o
