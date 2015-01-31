//to compile use: gcc -std=c99 -m64 -Os -I/usr/include/lua5.2 babbler.c /usr/lib/x86_64-linux-gnu/liblua5.2.so -lm -o babbler
//to run use: ./babbler short.txt 3 100
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <filename> <n-grams> <length>\n", argv[0]);
        exit(-1);
	}
	const char *filename = argv[1];
	const char *n = argv[2];
	const char *outlength = argv[3];
	
    // get the size of the file
    struct stat info;
    int status = stat(filename, &info);
    if (status < 0) {
        perror("stat error");
        exit(-1);
    }
    // get a buffer of appropriate size
    int size = (int) info.st_size;
    char *buffer = malloc(size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }
    // open the file
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open error");
        exit(-1);
    }
    // read the entire file
    char *ptr = buffer;
    int left = size;
    while (left > 0) {
        int chunk = read(fd, ptr, left);
        if (chunk < 0) {
            perror("read error");
            exit(-1);
        } else if (chunk == 0) {
            fprintf(stderr, "ran out of data\n");
            exit(-1);
        }
        left -= chunk;
        ptr += chunk;
    }
    // close file
    status = close(fd);
    if (status < 0) {
        perror("close error");
        exit(-1);
    }
	/////////////////start my C/////////////////
	int i=0;
	char *strpart;
	char *str[size+1];
	char *fullstr[size+1];
	char *outstr[size+1];
	for(i=0;i<size;i++)
	{
		str[i]=NULL;
		fullstr[i]=NULL;
		outstr[i]=NULL;
	}
	for(i=0;buffer[i];i++)
	{
		buffer[i]=tolower(buffer[i]);
	}
	strcpy(str, buffer);
	strpart=strtok(str, "`~!@#$%^&*()_+-=;:,./<>?[]{}\"\'");
	while(strpart!=NULL)
	{
		strcat(fullstr,strpart);
		strpart=strtok(NULL, "`~!@#$%^&*()_+-=;:,./<>?[]{}\"\'");
		//printf(strpart);

	}
	/////////////////end my C/////////////////
	
    /////////////////start my lua/////////////////
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    
    if (luaL_dofile(L, "babbler.lua")) {
        printf("Error in dofile\n");
    }
    lua_getglobal(L, "babble");
    lua_pushstring(L, fullstr);
    lua_pushstring(L, n);
    lua_pushstring(L, outlength);
    lua_pcall(L, 3, 0, 0);
    lua_close(L); 
    /////////////////end my lua/////////////////
	free(buffer);
	return 0;
}
