CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -g # C flags
INCPATH= ../include/
LIBPATH= ../src/
RM = rm -f  # rm command
APP_NM = test_circular_linked_list
SRCS = test_circular_linked_list.c # source files
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: 
	$(CC) -I$(INCPATH) -L$(LIBPATH) -o $(APP_NM) $(SRCS) -lcircular_linked_list -lpthread

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)



