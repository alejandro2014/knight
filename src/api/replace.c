#include "replace.h"

void setPendingFillIfNeeded(int x, int y, int tolerance, int deltaMax) {
    int currentHeight = getHeight(terrain_height, x, y);

    if(isHeightInsideLimits(tolerance, currentHeight, deltaMax) && !isFilled(x, y)) {
        setPendingFill(x, y);
    }
}

void replaceVerticalLine(int x, int yIni, int yFin) {
    int y;

    for(y = yIni; y <= yFin; y++) {
		curent_height = getHeight(terrain_height, x, y);

		if(isHeightInsideLimits(tolerance_mode, curent_height, color_2) && !isFilled(x, y)) {
            replacePoint(terrain_height, x, y);
            setFilled(x, y);

			//now, scan for the up and down neighbours
			if(x > 0) setPendingFillIfNeeded(x-1, y, tolerance_mode, color_2);
            if(x < WIDTH-1) setPendingFillIfNeeded(x+1, y, tolerance_mode, color_2);
        }
		else break;
	}
}

void replaceVerticalLineIfNeeded(int x, int y, int tolerance_mode, int deltaMax) {
    int curent_height = getHeight(terrain_height, x - WIDTH, y);

    if(isHeightInsideLimits(tolerance_mode, curent_height, deltaMax) && !isFilled(x - WIDTH, y)) {
        replace_ver_line(x, y);
    }
}

void replaceHorizontalLine(int xIni, int xFin, int y) {
    int x;

    for(x = xIni; x < xFin; x++) {
        curent_height = getHeight(terrain_height, x, y);

        if(isHeightInsideLimits(tolerance_mode, curent_height, color_2) && !isFilled(x y)) {
            replacePoint(terrain_height, x, y);
            setFilled(x, y);

            //now, scan for the up and down neighbours
            if(y>0) replaceVerticalLineIfNeeded(x - WIDTH, y, tolerance_mode, color_2);
            if(y < HEIGHT-1) replaceVerticalLineIfNeeded(x + WIDTH, y, tolerance_mode, color_2);
        }
        else break;
    }
}

//Replaces two lines, upwards and downwards
void replace_ver_line(int orig_x, int orig_y) {
    replaceVerticalLine(orig_x, 0, orig_y);
    replaceVerticalLine(orig_x, orig_y + 1, HEIGHT - 1);
}

//Scans left and right
void replace_line(short orig_x, short orig_y) {
    replaceLine(0, orig_x, orig_y);
    replaceLine(orig_x + 1, WIDTH - 1, orig_y);
}

int isHeightInsideLimits(int condition, int height, int deltaMax) {
    int maximum = currentHeight;
    int minimum = currentHeight;

    switch(condition) {
        case greater_or_leaser:
            maximum += deltaMax;
            minimum -= deltaMax;
            break;
        case greater: maximum += deltaMax; break;
        case leaser: minimum -= deltaMax; break;
    }

    return (currentHeight >= minimum && currentHeight <= maximum) ? 1 : 0;
}

//the fill tool
void pre_change_area() {
    int i,x,y;
    int map_size=WIDTH*HEIGHT;
    char * some_temp_buffer;
    bool no_pending_found=0;

    if (!get_cur_x_y())return;

    //try to see if the desired filling mode is pattern fill, and if we have a current pattern.
    if(tolerance_replace_mode_2==replace_mode_pattern && !current_pattern.object_mem) {
        sprintf(error_msg_1,"Pattern filling mode, but there is no pattern!");
        sprintf(error_msg_2,"Righ click on the Magic Wand tool, and select a pattern!");
		view_error_menu=1;
		return;
	}

    change_cursor(cursor_wait);

    color_2 = *(terrain_height + cur_y * WIDTH + cur_x);	//get the deepth
    some_temp_buffer=temp_buffer;
    for (i = 0; i <map_size; i++)
        *(some_temp_buffer++)=not_filled;//clear the temp buffer

    replace_line((short)cur_x,(short)cur_y);
	while(1) {
		no_pending_found=0;
		some_temp_buffer=temp_buffer;
		for(i=0;i<map_size;i++) {
		    if(*(some_temp_buffer++)==pending_fill) {
				no_pending_found=1;
				y=i/WIDTH;
				x=i-y*WIDTH;
				replace_line((short)x,(short)y);
			}
        }

		if(!no_pending_found) break;
	}

	some_temp_buffer=temp_buffer;
	for (i = 0; i <map_size; i++)*(some_temp_buffer++)=not_filled;//clear the temp buffer
	change_cursor(last_cursor);
}
