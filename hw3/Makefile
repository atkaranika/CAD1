
.RECIPEPREFIX = >
CC=gcc
hw3:hw3.o lib.o
>$(CC) -g lib.o hw3.o  -o hw3 -I/usr/include/tcl -lreadline -ltcl8.6
lib.o:lib.c
>$(CC) -g lib.c -c -o lib.o  -I/usr/include/tcl -ltcl8.6
hw3.o:hw3.c
>$(CC) -c -g hw3.c -c -o hw3.o  -I/usr/include/tcl -lreadline -ltcl8.6

