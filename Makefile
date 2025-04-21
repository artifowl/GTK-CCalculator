# Variables
CC = gcc
CFLAGS = `pkg-config --cflags gtk4` -Wall -g
LDFLAGS = `pkg-config --libs gtk4`
SRC = calculator_gui.c calculator_logic.c
OBJ = $(SRC:.c=.o)
EXEC = calculator

# Default Rules
all: $(EXEC)

# Compile exe
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Clean object files and executable
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and executable
clean:
	rm -f $(OBJ) $(EXEC)
# Rule to clean everything
fclean: clean

# Recompile from scratch
re: fclean all
