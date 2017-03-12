EXE=knight

OPTC=-I/usr/local/include -g
OPTL=-L/usr/local/lib -lSDL2 -lSDL2_ttf

BINDIR=./bin
LIBDIR=./lib
OBJDIR=./obj
SRCDIR=./src

SRCDIR_API=${SRCDIR}/api
SRCDIR_CON=${SRCDIR}/console
SRCDIR_MAP=${SRCDIR}/map
SRCDIR_WID=${SRCDIR}/widgets

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

WID01=menu_bar
WID02=actions
WID03=menus
WID04=widgets
WID05=load_widgets_fake

SRC01=main
SRC02=draw
SRC03=hme_load
SRC04=font

OBJDIR_API=${OBJDIR}/api
OBJDIR_CON=${OBJDIR}/console
OBJDIR_MAP=${OBJDIR}/map
OBJDIR_WID=${OBJDIR}/widgets

OBJ_API=${OBJDIR_API}/${API01}.o ${OBJDIR_API}/${API02}.o ${OBJDIR_API}/${API03}.o ${OBJDIR_API}/${API04}.o ${OBJDIR_API}/${API05}.o
OBJ_CON=${OBJDIR_CON}/${CON01}.o ${OBJDIR_CON}/${CON02}.o ${OBJDIR_CON}/${CON03}.o ${OBJDIR_CON}/${CON04}.o ${OBJDIR_CON}/${CON05}.o
OBJ_MAP=${OBJDIR_MAP}/${MAP01}.o ${OBJDIR_MAP}/${MAP02}.o
OBJ_WID=${OBJDIR_WID}/${WID01}.o ${OBJDIR_WID}/${WID02}.o ${OBJDIR_WID}/${WID03}.o ${OBJDIR_WID}/${WID04}.o ${OBJDIR_WID}/${WID05}.o
OBJ_REST=${OBJDIR}/${SRC01}.o ${OBJDIR}/${SRC02}.o ${OBJDIR}/${SRC03}.o ${OBJDIR}/${SRC04}.o
OBJ=${OBJ_API} ${OBJ_CON} ${OBJ_MAP} ${OBJ_WID} ${OBJ_REST}

### Rules ###
${BINDIR}/${EXE}: ${OBJ}
	gcc ${OBJ} -o ${BINDIR}/${EXE} ${OPTL}

${OBJDIR_API}/%.o: ${SRCDIR_API}/%.c
	gcc -c ${OPTC} -o $@ $<

${OBJDIR_CON}/%.o: ${SRCDIR_CON}/%.c
	gcc -c ${OPTC} -o $@ $<

${OBJDIR_MAP}/%.o: ${SRCDIR_MAP}/%.c
	gcc -c ${OPTC} -o $@ $<

${OBJDIR_WID}/%.o: ${SRCDIR_WID}/%.c
	gcc -c ${OPTC} -o $@ $<

${OBJDIR}/%.o: ${SRCDIR}/%.c
	gcc -c ${OPTC} -o $@ $<

clean:
	rm -f ${BINDIR}/${EXE} ${OBJDIR}/*.o ${OBJDIR_API}/*.o ${OBJDIR_CON}/*.o ${OBJDIR_MAP}/*.o ${OBJDIR_WID}/*.o
