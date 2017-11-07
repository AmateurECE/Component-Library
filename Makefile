################################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    The Makefile for the source in this repository.
#
# CREATED:	    11/07/2017
#
# LAST EDITED:	    11/07/2017
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

################################################################################
