CC = cc

FLAG = -Wall -Werror -Wextra -g3

SUPFLAG = -pthread

INCLUDE = -I .

NAME = Philosopher

SOURCE = main.c \
utils_1.c \
error_handler.c

OBJ = $(SOURCE:%.c=obj/%.o)

OBJPATH = obj

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
#	ar -rcs $(NAME) $(OBJ)

$(OBJPATH)/%.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(FLAG) -c $< -o $@ $(INCLUDE) $(SUPFLAG)

clean :
	rm -r $(OBJPATH)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : re fclean clean all