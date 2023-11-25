NAME := philo

SRC_DIR := cfiles
OBJ_DIR	:= obj

SRCS := \
	cfiles/philo.c		\
	cfiles/philo_init.c \
	cfiles/philo_state_n_time.c \
	cfiles/philo_threads.c \
	cfiles/philo_utils.c \

SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC := cc

CFLAGS := -g -pthread -Wall -Wextra -Werror
CPPFLAGS := -I include

RM := rm -f
MAKEFLAGS += --no-print-directory
DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
	$(info $(NAME) compiled)

$(OBJ_DIR)/%.o: %.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re
.SILENT: