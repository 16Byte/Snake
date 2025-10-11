# === Project settings ===
APP = snake
SRC = main.cpp

# === Compiler settings ===
CC = clang++
CFLAGS = -Wall -std=c++17 $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib)

# === Default target ===
all: $(APP)

$(APP): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(APP)

# === Run target ===
run: $(APP)
	./$(APP)

# === Clean target ===
clean:
	rm -f $(APP)
