# Linux Car Stereo Makefile

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
INCLUDES = -Iinclude
LIBS = -lpthread

# Directories
SRCDIR = src
OBJDIR = obj
INCLUDEDIR = include

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = car_stereo

# Default target
all: $(TARGET)

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build target
$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "✅ Car Stereo built successfully!"

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Install target (copy to /usr/local/bin)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/
	sudo chmod +x /usr/local/bin/$(TARGET)
	@echo "✅ Car Stereo installed to /usr/local/bin/"

# Uninstall target
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "❌ Car Stereo uninstalled"

# Clean build files
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "🧹 Cleaned build files"

# Development build with debug symbols
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)
	@echo "🐛 Debug build complete"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Check for memory leaks (requires valgrind)
memcheck: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Create distribution package
dist: clean
	tar -czf car_stereo_v1.0.tar.gz . --exclude='.git*'
	@echo "📦 Distribution package created: car_stereo_v1.0.tar.gz"

# Show help
help:
	@echo "Linux Car Stereo Build System"
	@echo "=============================="
	@echo "Targets:"
	@echo "  all      - Build the car stereo application"
	@echo "  install  - Install to /usr/local/bin/"
	@echo "  uninstall- Remove from /usr/local/bin/"
	@echo "  clean    - Remove build files"
	@echo "  debug    - Build with debug symbols"
	@echo "  run      - Build and run the application"
	@echo "  memcheck - Run with valgrind memory checker"
	@echo "  dist     - Create distribution package"
	@echo "  help     - Show this help message"

# System requirements check
syscheck:
	@echo "Checking system requirements..."
	@which gcc >/dev/null || echo "❌ gcc not found"
	@which make >/dev/null || echo "❌ make not found"
	@echo "✅ System check complete"

.PHONY: all install uninstall clean debug run memcheck dist help syscheck
