### Definitions ###
EXE=knight
LIBAPI=api
LIBCON=console
LIBMAP=map
FWDIR=/Library/Frameworks

### Options ###
OPTC_API=
OPTC_CON=
OPTC_MAP=-I${FWDIR}/SDL2.framework/Headers -I${FWDIR}/SDL_ttf.framework/Headers
OPTL_MAP=-F${FWDIR} -framework SDL -L/System/Library/Frameworks -framework Cocoa -framework SDL_ttf
OPTC_REST=${OPTC_MAP}
OPTL_REST=${OPTL_MAP}

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

CON01=console
CON02=print

MAP01=window

SRC01=main

OBJ_API=${OBJDIR_API}/${API01}.o ${OBJDIR_API}/${API02}.o ${OBJDIR_API}/${API03}.o ${OBJDIR_API}/${API04}.o ${OBJDIR_API}/${API05}.o
OBJ_CON=${OBJDIR_CON}/${CON01}.o ${OBJDIR_CON}/${CON02}.o
OBJ_MAP=${OBJDIR_MAP}/${MAP01}.o ${OBJDIR_MAP}/SDLMain.o
OBJ_REST=${OBJDIR}/${SRC01}.o

LIBA_API=${LIBDIR}/lib${LIBAPI}.a
LIBA_CON=${LIBDIR}/lib${LIBCON}.a
LIBA_MAP=${LIBDIR}/lib${LIBMAP}.a

LIBSA=${LIBA_API} ${LIBA_CON} ${LIBA_MAP}

### Rules ###
${BINDIR}/${EXE}: ${LIBSA} ${OBJ_REST}
	${CC} -L${LIBDIR} -l${LIBAPI} -l${LIBCON} -l${LIBMAP} ${OBJ_REST} -o ${BINDIR}/${EXE} ${OPTL_REST}

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

${OBJDIR_MAP}/SDLMain.o: ${SRCDIR_MAP}/SDLMain.m
	${CC} ${OPTC_MAP} -c -o ${OBJDIR_MAP}/SDLMain.o ${SRCDIR_MAP}/SDLMain.m

${OBJDIR_MAP}/%.o: ${SRCDIR_MAP}/%.c
	${CC} ${OPTC_MAP} -c -o $@ $<

${OBJDIR}/%.o: ${SRCDIR}/%.c
	${CC} ${OPTC_REST} -c -o $@ $<

#libs: ${LIBA_API}

api: ${LIBA_API}

console: ${LIBA_CON}

map: ${LIBA_MAP}

clean:
	rm -f ${BINDIR}/${EXE} ${LIBDIR}/*.a ${OBJDIR_API}/*.o ${OBJDIR_CON}/*.o ${OBJDIR_MAP}/*.o ${OBJDIR}/*.o
