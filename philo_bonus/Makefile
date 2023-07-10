# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/08 16:31:21 by ylyoussf          #+#    #+#              #
#    Updated: 2023/07/10 15:52:29 by ylyoussf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

OBJSFOLDER = objs/

SRCS_PARSER = ft_atoi.c \
			  ft_itoa.c \
			  ft_memcpy.c \
			  ft_strdup.c \
			  ft_strlen.c \
			  ft_strjoin.c \
			  ft_memcmp.c \
			  ft_isdigit.c \
			  parser.c

SRCS_DEBUG = debug.c

SRCS_TIME = time_utils.c

SRCS_PHILO_ROUTINE = philo_routine.c

SRCS_PHILO_UTILS = philo_utils.c \
				   philo_utils_2.c

OBJS_FILES = $(SRCS_PARSER:.c=.o) \
			 $(SRCS_DEBUG:.c=.o) \
			 $(SRCS_TIME:.c=.o) \
			 $(SRCS_PHILO_UTILS:.c=.o) \
			 $(SRCS_PHILO_ROUTINE:.c=.o) \
			 main.o

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))

GLOBAL_HEADERS = include/structs.h Makefile

all: objs $(NAME)

$(OBJSFOLDER):
	@mkdir objs

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

$(OBJSFOLDER)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/parser/libft/%.c include/parser.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/parser/%.c include/parser.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/debug/%.c include/debug.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/time_utils/%.c include/time_utils.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/philo_utils/%.c include/philo_utils.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/philo_routine/%.c include/philo_routine.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJS)

.PHONY: all clean fclean re
