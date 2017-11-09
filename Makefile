################################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    The Makefile for the source in this repository.
#
# CREATED:	    11/07/2017
#
# LAST EDITED:	    11/08/2017
###

TOP:=$(PWD)
CC=gcc
CFLAGS=-g -Wall -O0 # TODO: Fix these make flags

SRCS += iec60062.c

OBJS=$(patsubst %.c,%.o,$(SRCS))

.PHONY: force clean

all: force $(OBJS)

$(OBJS): force

force:

clean:
	rm -f $(TOP)/*.o

test: force gnp10-test stdvalue-test

gnp10-test: force
	$(CC) $(CFLAGS) `pkg-config --cflags gsl` \
	`if [ -d /home/etwardy ]; then \
		echo -I/home/etwardy/Documents/gsl-release-2-4/; fi` \
	-o gnp10-test gnp10-test.c \
	`pkg-config --libs gsl` \
	`if [ -d /home/etwardy/ ]; then \
		echo -L /home/etwardy/Documents/gsl-release-2-4/.libs/; fi`

stdvalue-test: force
	$(CC) $(CFLAGS) `pkg-config --cflags gsl` \
	`if [ -d /home/etwardy ]; then \
		echo -I/home/etwardy/Documents/gsl-release-2-4/; fi` \
	-o stdvalue-test stdvalue-test.c \
	`pkg-config --libs gsl` \
	`if [ -d /home/etwardy/ ]; then \
		echo -L /home/etwardy/Documents/gsl-release-2-4/.libs/; fi`

################################################################################
