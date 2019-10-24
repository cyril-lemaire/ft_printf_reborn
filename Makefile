#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clemaire <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 16:35:50 by clemaire          #+#    #+#              #
#    Updated: 2019/10/24 14:20:57 by cyrlemai         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME :=			libftprintf.a

CC := 			gcc
CFLAGS :=		-Wall -Wextra -Werror
MKDIR_P :=		mkdir -p
RM_F :=			rm -f
TOUCH :=		touch
ECHO :=			echo
AR_RCS :=		ar rcs

LIBFT_DIR :=		./libft
LIBFT_OBJ_DIR :=	$(LIBFT_DIR)/bin/static

SRC_DIR :=		./src
OBJ_DIR :=		./bin
INCL_DIR :=		./include

LIBFT_M_SHORT :=	memset		bzero		memcpy		memccpy		memmove	\
					memchr		memcmp		strlen		strlcpy		strlcat	\
					strchr		strrchr		strnstr		strncmp		atoi	\
					isalpha		isdigit		isalnum		isascii		isprint	\
					toupper		tolower		calloc		strdup		substr	\
					strjoin		strtrim		split		itoa		strmapi	\
					putchar_fd	putstr_fd	putendl_fd	putnbr_fd

LIBFT_B_SHORT :=	strcat		strcmp		strcpy		strnlen		strncat	\
					strncpy		strstr		memalloc	memdel		strnew	\
					strdel		strclr		striter		striteri	strmap	\
					strequ		strnequ		putchar		putstr		putendl	\
					putnbr		lstnew		lstdelone	lstclear	lstadd_front\
					lstsize		lstlast		lstiter		lstmap		isspace	\
					mod			abs			lstadd_back	lstdelnext	lstgetindex	\
					lstdelindex	min			max			realloc		stracat	\
					stradd		wclen		wcslen		wctomb

SRC_NAMES :=	ft_printf_family	ft_printf_family_2	ft_print			\
				ft_convert			ft_read_conversion	ft_write_conversion	\
				ft_tools_atoi_light	ft_tools_imaxabs	ft_tools_write_uimax\
				ft_writers_int		ft_writers_int_2	ft_writers_chr		\
				ft_writers_other	ft_writers_str							\
				t_printer			t_vdprinter			t_vdprinter_2

SRC :=	$(SRC_NAMES:%=$(SRC_DIR)/%.c)	\
		$(LIBFT_SRC:%=$(LIBFT_DIR)/%.c)

OBJ :=	$(SRC_NAMES:%=$(OBJ_DIR)/%.o)

LIBFT_OBJ :=	$(LIBFT_M_SHORT:%=$(LIBFT_OBJ_DIR)/ft_%.o)	\
				$(LIBFT_B_SHORT:%=$(LIBFT_OBJ_DIR)/ft_%_bonus.o)

TEST_NAME :=	printf_tester
TEST_FILES :=	main.c

all: $(NAME)

$(LIBFT_DIR)/%:
	$(MAKE) -C $(LIBFT_DIR) $*

$(OBJ_DIR):
	$(MKDIR_P) $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCL_DIR) -I$(LIBFT_DIR) -c -o $@ $<

$(NAME): $(LIBFT_OBJ) $(OBJ)
	$(AR_RCS) $@ $?

$(NAME)_alt: $(OBJ_DIR) $(OBJ)
	$(AR_RCS) $@ $(?:$<=)

$(NAME)_alt2: $(LIBFT_DIR)/$(LIBFT_NAME) $(PRINTF_NAME)
	libtool --mode=link cc -static -o $@ $^

$(NAME)_alt3: $(LIBFT_DIR)/$(LIBFT_NAME) $(PRINTF_NAME)
	ar -rcT $@ $^

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

test: $(TEST_NAME)
	./$<

$(TEST_NAME): $(TEST_FILES) $(NAME)
	$(CC) -Weverything -fsanitize=address -I$(INCL_DIR) -I$(LIBFT_DIR) -L. -lftprintf -o $@ $(filter %.c,$^)

obj: $(OBJ)

.PHONY: all clean fclean re obj test
