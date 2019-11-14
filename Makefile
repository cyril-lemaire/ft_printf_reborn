#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clemaire <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 16:35:50 by clemaire          #+#    #+#              #
#    Updated: 2019/11/14 17:35:46 by cyrlemai         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME :=			libftprintf.a
PRINTF_NAME :=	libprintf.a
LIBFT_NAME :=	libft.a

CC := 			gcc
CFLAGS =		-Wall -Wextra -Werror
MKDIR_P :=		mkdir -p
RM_F :=			rm -f
TOUCH :=		touch
ECHO :=			echo
AR_RCS :=		ar rcs
CP :=			cp

LIBFT_DIR :=		./libft
LIBFT_OBJ_DIR :=	$(LIBFT_DIR)/bin/static

SRC_DIR :=		./src
OBJ_DIR :=		./bin
INCL_DIR :=		./include

SRC_NAMES :=	ft_printf_family	ft_printf_family_2	ft_print			\
				ft_convert			ft_read_conversion	ft_write_conversion	\
				ft_tools_atoi_light	ft_write_uintmax	ft_writers_int		\
				ft_writers_int_2	ft_writers_int_3	ft_writers_chr		\
				ft_writers_others	ft_writers_str		ft_writers_float	\
				t_printer			t_vdprinter			t_vdprinter_2

SRC :=	$(SRC_NAMES:%=$(SRC_DIR)/%.c)	\
		$(LIBFT_SRC:%=$(LIBFT_DIR)/%.c)

OBJ :=	$(SRC_NAMES:%=$(OBJ_DIR)/%.o)

LIBFT_OBJ :=	$(LIBFT_M_SHORT:%=$(LIBFT_OBJ_DIR)/ft_%.o)	\
				$(LIBFT_B_SHORT:%=$(LIBFT_OBJ_DIR)/ft_%_bonus.o)

all: $(NAME)

$(LIBFT_DIR)/%:
	$(MAKE) -C $(LIBFT_DIR) $*

$(OBJ_DIR):
	$(MKDIR_P) $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCL_DIR) -I$(LIBFT_DIR) -c -o $@ $<

$(NAME): $(LIBFT_DIR)/$(LIBFT_NAME) $(OBJ)
	$(CP) $< $@
	$(AR_RCS) $@ $(OBJ)

debug: CFLAGS += -g
debug: all

alt: $(OBJ) $(LIBFT_OBJ)
	$(AR_RCS) $(NAME) $?

alt2: $(LIBFT_DIR)/$(LIBFT_NAME) $(PRINTF_NAME)
	libtool --mode=link cc -static -o $(NAME) $^

alt3: $(LIBFT_DIR)/$(LIBFT_NAME) $(PRINTF_NAME)
	ar -rcT $(NAME) $^

alt4: $(LIBFT_DIR)/$(LBIFT_NAME) $(OBJ)
	$(CP) $< $(NAME)
	$(AR_RCS) $(NAME) $(OBJ)

$(PRINTF_NAME): $(OBJ)
	$(AR_RCS) $@ $?

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	@$(ECHO) "@$(RM_F) [OBJ FILES]"
	@$(RM_F) $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM_F) $(NAME)

re: fclean all

obj: $(OBJ)

.PHONY: all clean fclean re obj alt alt2 alt3
