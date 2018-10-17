# Name of the program.
NAME     := SkyShipperinho

# Sources and objects.
SRCS     := main.cpp ABang.cpp GameObject.cpp PlayerShip.cpp Bullet.cpp EnemyShip.cpp AShips.cpp Spaces.cpp
HDRS     := ABang.hpp GameObject.hpp PlayerShip.hpp Bullet.hpp EnemyShip.hpp AShips.hpp IFlyObj.hpp Spaces.hpp
OBJS     := $(SRCS:.cpp=.o)

# Define all the compiling flags.
CXX      := clang++
CXXFLAGS := -std=c++98 -Wall -Werror -Wextra
LNK      := -lncurses

# Compile and create everything.
all: $(NAME)

# Compile the program with the objects.
$(NAME): $(OBJS) $(HDRS)
	@$(CXX) $(OBJS) -o $@ $(LNK)

# This won't run if the source files don't exist or are not modified.
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# Rule to remove all the object files.
clean:
	@rm -f $(OBJS)
	@echo "Objects removed!"

# Rule to remove everything that has been created by the makefile.
fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) removed!"

# Rule to re-make everything.
re:     fclean all

# Protects you if clean / fclean / all / re already exist in the directory
.PHONY: all clean fclean format re
