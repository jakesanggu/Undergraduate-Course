.SUFFIXES : .c .o
CC = gcc
CFLAGS = -g
TARGET = Part2.out


OBJS = main.o func2.o write_to_shm.o
SRCS = (main:.o = .c)

all:	$(TARGET)


$(TARGET) :	$(OBJS) extra.h
	$(CC) -o $(TARGET) $^

clean :
	rm -f $(OBJS) $(TARGET)


