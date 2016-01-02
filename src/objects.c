#include "objects.h"

void pre_load_object() {
	SDL_Event event;
	if(!current_object.object_mem) {
		load_object=1;//tell the file open save function to load an object, not a terrain
		DoFileOpenSave (0);
    	while (SDL_PollEvent (&event));	//clears all the events
	}
}

void function_object(int object_mode) {
    switch(object_mode) {
        case put_object:
            *(start_display_pointer+j)=cur_height/4;
            break;

        case add_object:
            cur_height+=*(terrain_height+k*WIDTH+l);
            if(cur_height>255)cur_height=255;
            *(start_display_pointer+j)=cur_height/4;
            break;

        case sub_object:
            cur_height=*(terrain_height+k*WIDTH+l)-cur_height;
            if(cur_height<0)*(start_display_pointer+j)=black;
            else *(start_display_pointer+j)=cur_height/4;
            break;
    }
}

void function_object_zoom(int object_mode, int *height) {
    int cur_height = *height;

    switch(object_mode) {
        case put_object:
            cur_height /= 4;
            break;

        case add_object:
            cur_height += getHeight(terrain_height, l, k);
            if(cur_height>255) cur_height = 255;
            cur_height/=4;
            break;

        case sub_object:
            cur_height = getHeight(terrain_height, l, k) - cur_height;
            if(cur_height<0) cur_height = 0;
            else cur_height/=4;
            break;
    }

    *height = cur_height;
}

void draw_object_on_screen(SDL_Surface * this_screen) {
    int my_pitch;
    int object_x_start,object_y_start;
    int object_x_end,object_y_end;
    int object_x_screen_start,object_y_screen_start;
    int object_x_screen_end,object_y_screen_end;
    int object_x_terrain_start,object_y_terrain_start;
    int object_x_terrain_end,object_y_terrain_end;

    int x,y,i,j,k,l;

    int cur_height;
    Uint8 * start_display_pointer;
    Uint8 * start_object_pointer;

    Uint8 *screen_buffer;
    screen_buffer = (Uint8 *) this_screen->pixels;
    my_pitch = this_screen->pitch;

    //first, check to see if we really have the object
    //if we don't have it, it means that the user tried to load an invalid file
    //or he pressed the cancel button.
    if(!current_object.object_mem) {
        int i;
    	current_object.object_mem=0;
    	//change the tool to the draw tool
    	current_tool=t_place;
    	for(i=0;i<no_of_main_tool_bar_icons;i++)
            main_tool_bar[i].icon_active = 0;

    	main_tool_bar[0].icon_active = 1;
    	change_cursor_show(cursor_put);
    	return;
    }

    //ok, first, get the object screen x/y, according to the zoom level (if any)
    object_x_screen_start=x_mouse_pos-(current_object.object_x_len/2*terrain_ratio);
    object_y_screen_start=y_mouse_pos-(current_object.object_y_len/2*terrain_ratio);
    object_x_screen_end=x_mouse_pos+(current_object.object_x_len/2*terrain_ratio);
    object_y_screen_end=y_mouse_pos+(current_object.object_y_len/2*terrain_ratio);
    //now, find out which part of the object we display (if it is outside of the screen)
    //the start part
    if(object_x_screen_start>0)object_x_start=0;
    else object_x_start=(object_x_screen_start*-1)/terrain_ratio;
    if(object_y_screen_start>0)object_y_start=0;
    else object_y_start=(object_y_screen_start*-1)/terrain_ratio;
    //end part
    if(object_x_screen_end<window_width)object_x_end=current_object.object_x_len;
    else object_x_end=current_object.object_x_len-((object_x_screen_end-window_width)/terrain_ratio);
    if(object_y_screen_end<window_height)object_y_end=current_object.object_y_len;
    else object_y_end=current_object.object_y_len-((object_y_screen_end-window_height)/terrain_ratio);
    //do some final adjustments
    if(object_x_screen_start<0)object_x_screen_start=0;
    if(object_y_screen_start<0)object_y_screen_start=0;

    //now, do get the terrain coordinates.
    object_x_terrain_start=((x_mouse_pos-x_screen_offset)-(current_object.object_x_len/2*terrain_ratio))/ terrain_ratio + xoffset;
    object_y_terrain_start=((y_mouse_pos-y_screen_offset)-(current_object.object_y_len/2*terrain_ratio))/ terrain_ratio + yoffset;
    object_x_terrain_end=((x_mouse_pos-x_screen_offset)+(current_object.object_x_len/2*terrain_ratio))/ terrain_ratio + xoffset;
    object_y_terrain_end=((y_mouse_pos-y_screen_offset)+(current_object.object_y_len/2*terrain_ratio))/ terrain_ratio + yoffset;

    if(terrain_ratio==1) {
        i=0;
	    k=object_y_terrain_start+object_y_start;
	    for(y=object_y_start;y<object_y_end;y++) {
			start_object_pointer=current_object.object_mem+y*current_object.object_x_len;
			start_display_pointer=screen_buffer+(object_y_screen_start+i)*my_pitch;
			j=object_x_screen_start;
			l=object_x_terrain_start+object_x_start;

			for(x=object_x_start;x<object_x_end;x++) {
			    cur_height=*(start_object_pointer+x);
			    if(cur_height && l>=0 && l<WIDTH && k>=0 && k<HEIGHT) {
                    function_object(object_mode);
			    }

			    j++;
			    l++;
		    }

			i++;
			k++;
        }
    } else {//the terain is zoomed in, use other routines, for better optimization
        int screen_size=window_height*my_pitch;
	    int screen_offset_int_pointer;

        i=0;
        k=object_y_terrain_start+object_y_start;

        for(y=object_y_start;y<object_y_end;y++) {
            start_object_pointer=current_object.object_mem+y*current_object.object_x_len;
            start_display_pointer=screen_buffer+(object_y_screen_start+i*terrain_ratio)*my_pitch;
            screen_offset_int_pointer=(object_y_screen_start+i*terrain_ratio)*my_pitch;
            j=object_x_screen_start;
            l=object_x_terrain_start+object_x_start;

            for(x=object_x_start;x<object_x_end;x++) {
                cur_height=*(start_object_pointer+x);

                if(cur_height && l>=0 && l<WIDTH && k>=0 && k<HEIGHT) {
                    int m,n,another_displacement;

                    function_object_zoom(object_mode, &cur_height);

                    for(m=0;m<terrain_ratio;m++)
                        for(n=0;n<terrain_ratio;n++) {
                            another_displacement=m*my_pitch+n;
                            if(screen_offset_int_pointer+j+another_displacement < screen_size)
                                *(start_display_pointer+j+another_displacement) = cur_height;
                        }
                    }

                    j+=terrain_ratio;
                    l++;
              }
              i++;
              k++;
          }
    }
}

void do_load_object(char * FileName, terrain_object *this_current_object) {
    int i = 0;
    int file_header[25];
    FILE *f = NULL;

    //get the file name, if it is a pattern
	if(load_object==2) {
        sprintf(pattern_file_name, FileName);
	}

    if(getFileExtension(FileName) == "bmp") {
        load_bmp_object(FileName,this_current_object);
    } else {
	    sprintf(error_msg_1,"Invalid file format!");
	    sprintf(error_msg_2,"Please use only bmp or hmp extensions!");
	    view_error_menu=1;
    }
}

void getFileExtension() {
    if((*(FileName+i)=='B' || *(FileName+i)=='b') && (*(FileName+i+1)=='M' || *(FileName+i+1)=='m') && (*(FileName+i+2)=='P' || *(FileName+i+2)=='p')) {
        return "bmp";
    }
}
