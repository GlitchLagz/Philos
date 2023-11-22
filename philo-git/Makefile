NAME = philo
X86 = arch -x86_64
SRC = cfiles/*.c
CMP = $(X86) gcc -Wall -Werror -Wextra $(SRC) -o $(NAME) -g -fsanitize=address
all : $(NAME)
	@echo "Successful Make"
$(NAME):
	$(CMP)
clean:
	rm $(NAME)
fclean: clean
	rm -rf $(NAME)
re: fclean all
