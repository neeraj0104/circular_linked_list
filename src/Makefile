CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -g # C flags
LDFLAGS = -shared  # linking flags
INCPATH= ../include/
RM = rm -f  # rm command
TARGET_LIB = libcircular_linked_list.so # target lib

SRCS = circular_linked_list.c # source files
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${TARGET_LIB}
	rm -f *.o *.d

$(TARGET_LIB): $(OBJS)
	$(CC) -I$(INCPATH) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) -I$(INCPATH) $(CFLAGS) -MM $< >$@


include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)


