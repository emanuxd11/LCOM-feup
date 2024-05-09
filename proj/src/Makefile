# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/drivers
.PATH: ${.CURDIR}/models
.PATH: ${.CURDIR}/viewer

# source code files to be compiled
SRCS = timer.c utils.c gpu.c keyboard.c Game.c gameView.c main.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_ -O2

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
