CC = gcc
CFLAGS = -c -Wall
LDLIBS = -lncursesw
CFILES = *.c
OBJS = $(CFILES:%.c=%.o)
OBJROOT = ./obj
LOG = ./log/*
SAVEDATA = ./data/save_data.dat
PROGRAM = block_out

$(PROGRAM) : $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJROOT)/$(OBJS) $(LDLIBS)

.SUFFIXES: .c .o
.c.o :
	$(CC) $(CFLAGS) $^
	@mv *.o $(OBJROOT)

.PHONY: all clean init rev_init
all : $(PROGRAM)

clean :
	@$(RM) $(PROGRAM) $(OBJROOT)/$(OBJS) $(OBJS)

#gitにコミットする場合にpushする前に実行(gitでも「./obj/* ./log/* ./data/save_data.dat ./*.exe ./*.o」の.gitignoreを設定すること)
init :
	@$(RM) $(PROGRAM) $(OBJROOT)/$(OBJS) $(OBJS) $(LOG) $(SAVEDATA)