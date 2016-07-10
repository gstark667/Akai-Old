CC=gcc
CCFLAGS=-g
LDFLAGS=-lpthread

O=objects

OBJS= \
    $(O)/client.o \
    $(O)/main.o

all: $(O)/server

clean:
	rm -rf $(O)

$(O)/server: $(OBJS) $(O)
	$(CC) $(CCFLAGS) $(LDFLAGS) $(OBJS) -o $(O)/server

$(O)/%.o: %.c $(O)
	$(CC) $(CCFLAGS) -c $< -o $@

$(O):
	mkdir $(O)
