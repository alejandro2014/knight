EXE=heightmap

BINDIR=./bin
OBJDIR=./obj
SRCDIR=./src

CC=gcc
#ifeq ($(CC),cc)
	#OPTC=-g -I/usr/include/SDL
	#OPTC=-g -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
	#OPTL=-L/usr/lib64 -lSDL -L/usr/lib -lSDL_ttf
	OPTC=-I/usr/include/SDL2 -D_REENTRANT
	OPTL=-L/usr/lib/x86_64-linux-gnu -L/usr/local/lib -lSDL2 -lSDL2_ttf -lm
#else
#	OPTC=-g -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -ferror-limit=200 #-Werror
#	OPTL=-L/Library/Frameworks -L/System/Library/Frameworks -framework SDL -framework Cocoa -framework SDL_ttf
#endif

SRC01=actions
SRC02=cursors
SRC03=display_terrain
SRC04=draw_stuff
SRC05=events
SRC06=font
SRC07=generate_terrain
SRC08=global
SRC09=global_tools
SRC10=init
SRC11=actions_core
SRC12=load_save
SRC13=main
SRC14=menus
SRC15=objects
SRC16=settings
SRC17=tools
SRC18=load_widgets

OBJ_LINUX=${OBJDIR}/${SRC01}.o ${OBJDIR}/${SRC02}.o ${OBJDIR}/${SRC03}.o ${OBJDIR}/${SRC04}.o ${OBJDIR}/${SRC05}.o ${OBJDIR}/${SRC06}.o ${OBJDIR}/${SRC07}.o ${OBJDIR}/${SRC08}.o ${OBJDIR}/${SRC09}.o ${OBJDIR}/${SRC10}.o ${OBJDIR}/${SRC11}.o ${OBJDIR}/${SRC12}.o ${OBJDIR}/${SRC13}.o ${OBJDIR}/${SRC14}.o ${OBJDIR}/${SRC15}.o ${OBJDIR}/${SRC16}.o ${OBJDIR}/${SRC17}.o ${OBJDIR}/${SRC18}.o
OBJ_MAC=${OBJ_LINUX} ${OBJDIR}/SDLMain.o

#ifeq ($(CC), cc)
	OBJ=${OBJ_LINUX}
#else
#	OBJ=${OBJ_MAC}
#endif

${BINDIR}/${EXE}: ${OBJ}
	${CC} ${OBJ} -o ${BINDIR}/${EXE} ${OPTL}

${OBJDIR}/%.o: ${SRCDIR}/%.c
	${CC} ${OPTC} -c -o $@ $<

${OBJDIR}/SDLMain.o: ${SRCDIR}/SDLMain.m
	${CC} ${OPTC} -c ${SRCDIR}/SDLMain.m -o ${OBJDIR}/SDLMain.o

clean:
	rm -f ${OBJDIR}/*.o ${BINDIR}/${EXE}
