NAME = Rubik
SRC = *.cpp
OBJ = $(SRC:.cpp=.o)
FRAMEWORKS = -framework OpenGl -w
BREW_INC = -I ~/.brew/include
GLFW_LINK = -L ~/.brew/lib -lglfw

RED = "\033[1;38;2;225;20;20m"
ORANGE = "\033[1;38;2;255;120;10m"
YELLO = "\033[1;38;2;255;200;0m"
GREEN = "\033[1;38;2;0;170;101m"
LG = "\033[1;38;2;167;244;66m"
BLUE = "\033[1;38;2;50;150;250m"
PURPLE = "\033[1;38;2;150;75;255m"
WHITE = "\033[1;38;2;255;250;232m"

all: $(NAME)

$(NAME): $(SRC)
	@echo $(YELLO)Making $(NAME)
	@g++ -std=c++11 $(SRC) -o $(NAME) $(FRAMEWORKS) $(BREW_INC) $(GLFW_LINK)
	@echo $(GREEN)Done!

clean:
	@echo $(YELLO)Cleaning o files
	@/bin/rm -f $(OBJ)

fclean: clean
	@echo $(YELLO)Removing excutable
	@rm -f $(NAME)

re:	fclean all
