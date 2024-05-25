# Compiler and flags
CC = g++
CFLAGS = -Wall -std=c++20

# Source files
SRCS = main.cpp parser.cpp load_file.cpp variable_defination.cpp cin_cout_expression_parse.cpp array_defination.cpp print_variables.cpp print_arrays.cpp if_condition.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
HDRS = parser.h compound_assignment_operator.h

# Executable name
TARGET = interpreter

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
