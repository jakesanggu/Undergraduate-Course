.SUFFIXES: .c .o
CC = gcc
CFLAGS = -g

OBJS = main.o find_min.o common_divisor.o common_multiple.o
SRCS = $(OBJS:.o=.c)
HEADERS = my_numeric.h

TARGET = Part3.out

all : $(TARGET)


$(TARGET) :	$(OBJS) $(HEADERS)
	$(CC) -o $@	$^

.PHONY: clean

clean :
	rm -f	$(OBJS)	$(TARGET)



