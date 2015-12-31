#include "bmp.h"

void save_bmp(char * FileName, char * raw_mem, int x_size, int y_size) {
	/*int i,x,y,x_padding;
	uint8_t * file_mem;
	uint8_t * file_mem_start;
	FILE *f = NULL;
	int file_lenght;
	x_padding=x_size%4;
	if(x_padding)x_padding=4-x_padding;
	file_lenght=1078+(x_size+x_padding)*y_size;
  	f = fopen (FileName, "wb");
  	if(!f) {
			printf("Unable to create file!");
			printf("File already in use, or bad permission!");
			return;
		}
	file_mem = (uint8_t *) calloc ( 20000, sizeof(uint8_t));
	//clear the header...
	for(i=0;i<1078;i++)*(file_mem+i)=0;

	file_mem_start=file_mem;
	*((short *) file_mem)=19778;//BM (the identifier)
	file_mem+=2;
	*((int *) file_mem)=file_lenght;//file lenght
	file_mem+=8;
	*((int *) file_mem)=1078;//offset of data
	file_mem+=4;
	*((int *) file_mem)=40;//bitmap header lenght
	file_mem+=4;
	*((int *) file_mem)=x_size;//bitmap width
	file_mem+=4;
	*((int *) file_mem)=y_size;//bitmap height
	file_mem+=4;
	*((short *) file_mem)=1;//bitmap planes
	file_mem+=2;
	*((short *) file_mem)=8;//bits / pixel
	file_mem+=26;//ok, now we are at the color pallete (BGRA)
	//now, we need gray shades
	for(i=0;i<256;i++) {
			*(file_mem++)=i;//b
			*(file_mem++)=i;//g
			*(file_mem++)=i;//r
			*(file_mem++)=0;//a
		}
	//ok, now, transfer each line from source to destination, in reverse order
	fwrite (file_mem_start, 1078, 1, f);//write the header
	raw_mem+=(y_size-1)*x_size;
	file_mem=file_mem_start;
	for(y=0;y<y_size;y++) {
			for(x=0;x<x_size;x++)*(file_mem++)=*(raw_mem++);
			fwrite (file_mem_start, x_size+x_padding, 1, f);
			raw_mem-=x_size*2;//go at the beginning of the previous line
			file_mem=file_mem_start;
		}



fclose (f);
free(file_mem);*/
}

bool load_bmp(char * FileName) {
	/*int i,x,y,x_padding,x_size,y_size,colors_no,current_color,current_pallete_entry;
	uint8_t *file_mem;
	uint8_t *file_mem_start;
	uint8_t *color_pallete;
	bool is_24b=0;
	FILE *f = fopen (FileName, "rb");
	int file_lenght;

  	if (!f) {
        printf("Unable to open file!");
        printf("File doesn't exist, or bad permission!");
        return false;
	}

  	file_mem = (uint8_t *) calloc ( 20000, sizeof(uint8_t));
  	fread (file_mem, 1, 50, f);//header only

  	//now, check to see if our bmp file is indeed a bmp file, and if it is 8 bits, uncompressed
  	if(*((short *) file_mem)!=19778)//BM (the identifier) {
		free(file_mem);
		fclose (f);
			printf("Unsuported BMP format!");
			printf("BMP files have to be 8 or 24b, uncompressed!");
		return false;
	}
	file_mem+=18;
	x_size=*((int *) file_mem);
	file_mem+=4;
	y_size=*((int *) file_mem);
	file_mem+=6;
	if(*((short *)file_mem)!=8)//8 bit/pixel?
	if(*((short *)file_mem)!=24) {
		free(file_mem);
		fclose (f);
			printf("Unsuported BMP format!");
			printf("BMP files have to be 8 or 24b, uncompressed!");
		return false;
	  }
	  else is_24b=true;
	file_mem+=2;
	if(*((int *)file_mem)!=0)//any compression? {
		free(file_mem);
		fclose (f);
			printf("Unsuported BMP format!");
			printf("BMP files have to be 8 or 24b, uncompressed!");
		return false;
	  }
	  file_mem+=16;

	WIDTH=x_size;
	HEIGHT=y_size;

	  colors_no=*((int *)file_mem);
	  if(!colors_no)colors_no=256;
	  file_mem+=8;//here comes the pallete
	  //if we have a 24 bit bmp, then we don't need the pallete stuff

	  if(is_24b) {
				allocate_mem(WIDTH, HEIGHT);
				if(!terrain_height)return false;
				x_padding=x_size*3%4;
				if(x_padding)x_padding=4-x_padding;

				for(y=y_size-1;y>=0;y--) {
						fread (file_mem, 1, x_size*3+x_padding, f);
						//now, get the luminosity of each pixel
						for(x=0;x<x_size;x++) {
							current_color=*(file_mem+x*3);
							current_color+=*(file_mem+x*3+1);
							current_color+=*(file_mem+x*3+2);
							*(terrain_height+y*x_size+x)=current_color/3;
						}

					}

				free(file_mem);
				fclose (f);
				return true;
	  		}

	  color_pallete=file_mem+4;
	  fread (file_mem, 1, colors_no*4+4, f);//header only
	  file_mem+=colors_no*4;

	x_padding=x_size%4;
	if(x_padding)x_padding=4-x_padding;

	//now, allocate the memory for the new terrain
	allocate_mem(WIDTH, HEIGHT);
	if(!terrain_height)return false;

	for(y=y_size-1;y>=0;y--) {
			fread (terrain_height+y*x_size, 1, x_size-x_padding, f);
			//now, get the luminosity of each pixel
			for(x=0;x<x_size;x++) {
				current_pallete_entry=*(terrain_height+y*x_size+x);
				current_color=*(color_pallete+current_pallete_entry*4);
				current_color+=*(color_pallete+current_pallete_entry*4+1);
				current_color+=*(color_pallete+current_pallete_entry*4+2);
				*(terrain_height+y*x_size+x)=current_color/3;
			}

		}

	free(file_mem);
	fclose (f);*/
	return true;
}
