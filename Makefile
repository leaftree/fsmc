

#================================================================
#   Copyright (C) 2018 Liu YunFeng. All rights reserved.
#   
#   文件名称：Makefile
#   创 建 者：Liu YunFeng
#   创建日期：2018年03月10日
#   描    述：
#
#================================================================

CC = gcc
CFLAG = -g -O3 -Wall

OBJECT = main.o log.o util.o driver_loader.o config_loader.o

THIRD_LIBS = -L/usr/lib -ldbug

all:fsmc

fsmc:$(OBJECT)
	$(CC) $(OBJECT) $(CFLAG) $(THIRD_LIBS) -o $@ -ldl

.PHONY:clean
clean:
	rm -f $(OBJECT) fsmc
