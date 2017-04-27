# Makefile

PROG = memtest
SRCS = memtest.c memlib.c
OBJS = $(SRCS:%.c=%.o)
DEPS = $(SRCS:%.c=%.d)

CC = gcc
CFLAGS = -Wall -O2 -MMD -MP

.PHONY: clean

# サフィックスルール適用対象の拡張子の定義
.SUFFIXES: .c .o

# サフィックスルール
.c.o:
	$(CC) $(CFLAGS) -c $<

# プライマリターゲット
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# ファイル削除用ターゲット
clean:
	$(RM) $(PROG) $(OBJS) $(DEPS)

-include $(DEPS)
