CC = gcc
CFLAGS = -Wall -O2
TARGET = sum-nbo
OBJS = sum-nbo.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) $(OBJS)
