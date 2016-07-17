CC=g++
CCFLAGS=-g
LDFLAGS=-lpthread

O=objects

OBJS= \
    $(O)/user.o \
    $(O)/server.o \
    $(O)/channel.o \
    $(O)/main.o

all: $(O)/server

clean:
	rm -rf $(O)

$(O)/server: $(OBJS) $(O)
	$(CC) $(CCFLAGS) $(LDFLAGS) $(OBJS) -o $(O)/server

$(O)/%.o: %.cpp $(O)
	$(CC) $(CCFLAGS) -c $< -o $@

$(O):
	mkdir $(O)
