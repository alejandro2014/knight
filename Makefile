EXE=heightmap

BINDIR=./bin
OBJDIR=./obj
SRCDIR=./src

ifeq ($(CC),gcc)
	OPTC=-g -I/usr/include/SDL #-I/Library/Frameworks/SDL_ttf.framework/Headers #-Werror
	OPTL=#-L/Library/Frameworks -L/System/Library/Frameworks -framework SDL -framework Cocoa -framework SDL_ttf
else
	OPTC=-g -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -ferror-limit=200 #-Werror
	OPTL=-L/Library/Frameworks -L/System/Library/Frameworks -framework SDL -framework Cocoa -framework SDL_ttf
endif

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

OBJ=${OBJDIR}/${SRC01}.o ${OBJDIR}/${SRC02}.o ${OBJDIR}/${SRC03}.o ${OBJDIR}/${SRC04}.o ${OBJDIR}/${SRC05}.o ${OBJDIR}/${SRC06}.o ${OBJDIR}/${SRC07}.o ${OBJDIR}/${SRC08}.o ${OBJDIR}/${SRC09}.o ${OBJDIR}/${SRC10}.o ${OBJDIR}/${SRC11}.o ${OBJDIR}/${SRC12}.o ${OBJDIR}/${SRC13}.o ${OBJDIR}/${SRC14}.o ${OBJDIR}/${SRC15}.o ${OBJDIR}/${SRC16}.o ${OBJDIR}/${SRC17}.o ${OBJDIR}/${SRC18}.o ${OBJDIR}/SDLMain.o

${BINDIR}/${EXE}: ${OBJ}
	${CC} ${OPTL} ${OBJ} -o ${BINDIR}/${EXE}

${OBJDIR}/%.o: ${SRCDIR}/%.c
	${CC} ${OPTC} -c -o $@ $<

${OBJDIR}/SDLMain.o: ${SRCDIR}/SDLMain.m
	${CC} ${OPTC} -c ${SRCDIR}/SDLMain.m -o ${OBJDIR}/SDLMain.o

clean:
	rm -f ${OBJDIR}/*.o ${BINDIR}/${EXE}
