CFLAGS = -Wall -c -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CC = g++

SRC_DIR = src
OUT_DIR = out

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OUT_DIR)/%.o,$(SOURCES))
EXECUTABLE = application

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR) $(EXECUTABLE)
