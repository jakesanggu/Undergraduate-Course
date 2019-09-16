.SUFFIXES : .c .o
CC = gcc
CFLAGS = -g

OBJS = main.o printarr.o func1.o
TARGET = Part1.out


all : $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

.PHONY : clean

clean:
	rm -f $(OBJS) $(TARGET)



