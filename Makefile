EXE=knight

BINDIR=./bin
LIBDIR=./lib
OBJDIR=./obj
SRCDIR=./src

OPTC_API=-ferror-limit=200
API01=api
API02=hme_lowlevel
API03=generate_terrain
API04=flood
API05=replace
#API06=brush
#API07=bmp
#API08=load_save
OBJDIR_API=${OBJDIR}/api
OBJ_API=${OBJDIR_API}/${API01}.o ${OBJDIR_API}/${API02}.o ${OBJDIR_API}/${API03}.o ${OBJDIR_API}/${API04}.o ${OBJDIR_API}/${API05}.o
#${OBJDIR_API}/${API06}.o ${OBJDIR_API}/${API07}.o ${OBJDIR_API}/${API08}.o

OPTC_CON=-ferror-limit=200
CON01=console
CON02=print
OBJDIR_CON=${OBJDIR}/console
OBJ_CON=${OBJDIR_CON}/${CON01}.o ${OBJDIR_CON}/${CON02}.o

OPTC_MAP=-I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -ferror-limit=200 #-Werror
OPTL_MAP=-L/Library/Frameworks -L/System/Library/Frameworks -framework SDL -framework Cocoa -framework SDL_ttf
MAP01=window
OBJDIR_MAP=${OBJDIR}/2d
OBJ_MAP=${OBJDIR_MAP}/${MAP01}.o ${OBJDIR_MAP}/SDLMain.o

OPTC_REST=${OPTC_MAP}
OPTL_REST=
SRC01=main
OBJ_REST=${OBJDIR}/${SRC01}.o

LIB_API=${LIBDIR}/libapi.a
LIB_CON=${LIBDIR}/libconsole.a
LIB_MAP=${LIBDIR}/libmap.a
LIBS=${LIB_API} ${LIB_CON} ${LIB_MAP}

${BINDIR}/${EXE}: ${LIBS} ${OBJ_REST}
	${CC} -L${LIBDIR} -lapi -lconsole -lmap ${OBJ_REST} -o ${BINDIR}/${EXE} ${OPTL_REST}

${LIB_API}: ${OBJ_API}
	ar rcs ${LIB_API} ${OBJ_API}

${LIB_CON}: ${OBJ_CON}
	ar rcs ${LIB_CON} ${OBJ_CON}

${LIB_MAP}: ${OBJ_MAP}
	ar rcs ${LIB_MAP} ${OBJ_MAP}

${OBJDIR_API}/%.o: ${SRCDIR}/api/%.c
	${CC} ${OPTC_API} -c -o $@ $<

${OBJDIR_CON}/%.o: ${SRCDIR}/console/%.c
	${CC} ${OPTC_CON} -c -o $@ $<

${OBJDIR_MAP}/SDLMain.o: ${SRCDIR}/2d/SDLMain.m
	${CC} ${OPTC_MAP} -c -o ${OBJDIR_MAP}/SDLMain.o ${SRCDIR}/2d/SDLMain.m

${OBJDIR_MAP}/%.o: ${SRCDIR}/2d/%.c
	${CC} ${OPTC_MAP} -c -o $@ $<

${OBJDIR}/%.o: ${SRCDIR}/%.c
	${CC} ${OPTC_REST} -c -o $@ $<

libs: ${LIBS}

api: ${LIB_API}

console: ${LIB_CON}

map: ${LIB_MAP}

clean:
	rm -f ${BINDIR}/${EXE} ${LIBDIR}/*.a ${OBJDIR_API}/*.o ${OBJDIR_CON}/*.o ${OBJDIR_MAP}/*.o ${OBJDIR}/*.o
