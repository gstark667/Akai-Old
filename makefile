CC=g++
CCFLAGS=-I/usr/include/qt -fPIC
LDFLAGS=
LIBS=-lQt5Core -lQt5Gui -lQt5Widgets

OBJDIR=objects

all: $(OBJDIR)/akai

clean:
	rm -rf $(OBJDIR)

$(OBJDIR)/akai: \
    $(OBJDIR)/main.o \
    $(OBJDIR)/mainwindow.o
	$(CC) $(LDFLAGS) $(OBJDIR)/main.o $(OBJDIR)/mainwindow.o -o $(OBJDIR)/akai $(LIBS)

$(OBJDIR)/%.o: %.cpp $(OBJDIR)
	$(CC) $(CCFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)
