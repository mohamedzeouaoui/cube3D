NAME            =   libft.a

CC              =   cc
CFLAGS          =   -Wall -Werror -Wextra -I. -MMD -MP 
LDFLAGS         =   

BUILD_DIR       =   build
SRC_DIR         =   .

SRC             =   $(shell find -type f -name '*.c')
OBJ             =   $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP             =   $(OBJ:.o=.d)

RM              =   rm -rf
AR				=	ar -rcs

all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

-include $(DEP)

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
