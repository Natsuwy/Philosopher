CC = cc

FLAG = -Wall -Werror -Wextra -g3

SUPFLAG = -pthread

INCLUDE = -I .

NAME = philo

SOURCE = main.c \
utils.c \
monitor.c \
setup.c \
forks.c \
status.c \
error_handler.c

OBJ = $(SOURCE:%.c=obj/%.o)

DEP = $(OBJ:.o=.d)

OBJPATH = obj

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
#	ar -rcs $(NAME) $(OBJ)

-include $(DEP)

$(OBJPATH)/%.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(FLAG) -c -MMD -MP $< -o $@ $(INCLUDE) $(SUPFLAG)

clean :
	rm -r $(OBJPATH)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : re fclean clean all