SHELL := /bin/bash
CC= gcc
CFLAGS = -g
##TARGET LIST##
################
TARGET1 = part1.out
TARGET2 = part2.out
TARGET3 = part3.out
TARGET4 = part4.out  #문제 2번 파트 1,2,3 종합
OUT_SUFFIX = out
################
OBJS = main.o read_from_shm.o func0.o

TARGET = $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)
.PHONY : clean

all:	$(TARGET)
	@echo "Part1, Part2, Part3 프로그램 설치완료"

$(TARGET1):
	cd $* ; $(MAKE)

$(TARGET2):
	cd $* ; $(MAKE)

$(TARGET3):
	cd $(TARGET2:.$(OUT_SUFFIX)=)/$*; $(MAKE)
$(TARGET4): $(OBJS)
	$(CC) -o $@ $^

clean:
	cd $(TARGET1:.$(OUT_SUFFIX)=); $(MAKE) clean
	cd $(TARGET2:.$(OUT_SUFFIX)=); $(MAKE) clean
	cd $(TARGET2:.$(OUT_SUFFIX)=)/$(TARGET3:.$(OUT_SUFFIX)=); $(MAKE) clean
	rm -rf $(TARGET4) $(OBJS)
