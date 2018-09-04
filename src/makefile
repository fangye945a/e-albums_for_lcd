NAME=../bin/main
CC=arm-linux-gcc
INCLUDE :=-I../include
LIBS :=-L../lib -ljpeg -lm
OBJ=$(patsubst %.c,%.o,$(wildcard *.c))

$(NAME):$(OBJ)
	$(CC) -o $@ $^ $(LIBS) 
%.o:%.c
	$(CC) -c $^ -o  $@ 	$(INCLUDE)
clean:
	rm $(OBJ)
