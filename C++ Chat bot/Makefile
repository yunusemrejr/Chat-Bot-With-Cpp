# ──────────────────────────────────────────────────────────
#  C++ Chat Bot — Build Configuration
#  Originally by Yunus Emre Vurgun (2022) | Enhanced (2026)
# ──────────────────────────────────────────────────────────

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2
TARGET   := chatbot
SRC      := chat.cpp

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: clean $(TARGET)
