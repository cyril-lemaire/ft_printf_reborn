#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clemaire <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 16:35:50 by clemaire          #+#    #+#              #
#    Updated: 2019/11/15 13:14:32 by cyrlemai         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME :=			libft.a

CC := 			gcc
CFLAGS :=		-Wall -Wextra -Werror

SRC_DIR :=		./src
STATIC_DIR :=	./bin/static
INCL_DIR :=		.

MANDATORY_SHORT :=	memset		bzero		memcpy		memccpy		memmove		\
	memchr		memcmp		strlen		strlcpy		strlcat		\
	strchr		strrchr		strnstr		strncmp		atoi		\
	isalpha		isdigit		isalnum		isascii		isprint		\
	toupper		tolower		calloc		strdup		substr		\
	strjoin		strtrim		split		itoa		strmapi		\
	putchar_fd	putstr_fd	putendl_fd	putnbr_fd

BONUS_SHORT :=		strcat			strcmp			strcpy			\
	strnlen			strncat			strnew			strmap			\
	strncpy			strstr			memalloc		memdel			\
	strdel			strclr			striter			striteri		\
	strequ			strnequ			putchar			putstr			\
	putendl			lstadd_front	isspace			stracat			\
	putnbr			lstnew			lstdelone		lstclear		\
	lstsize			lstlast			lstiter			lstmap			\
	mod				abs				lstadd_back		lstdelnext		\
	lstgetindex		intpow			isupper			islower			\
	lstdelindex		min				max				realloc			\
	stradd			wclen			wcslen			wctomb

MANDATORY_NAMES := 	$(addprefix ft_, $(MANDATORY_SHORT))
BONUS_NAMES :=		$(BONUS_SHORT:%=ft_%_bonus)

MANDATORY_SRC :=	$(MANDATORY_NAMES:%=$(SRC_DIR)/%.c)
BONUS_SRC :=		$(BONUS_NAMES:%=$(SRC_DIR)/%.c)

STATIC_OBJ =		$(MANDATORY_NAMES:%=$(STATIC_DIR)/%.o)

STATIC_BONUS_OBJ :=	$(BONUS_NAMES:%=$(STATIC_DIR)/%.o)

all: $(NAME)

a: $(NAME)

bonus: $(NAME)

$(NAME): $(STATIC_OBJ) $(STATIC_BONUS_OBJ)
	ar rcs $@ $?

$(STATIC_DIR):
	mkdir -p $@

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.c | $(STATIC_DIR)
	$(CC) -c $(CFLAGS) -I$(INCL_DIR) -o $@ $<

clean:
	@echo '@rm -f [STATIC OBJECTS]'
	@rm -f $(STATIC_OBJ) $(STATIC_BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

reclean: re
	$(MAKE) clean

.PHONY: all a clean fclean re reclean bonus
