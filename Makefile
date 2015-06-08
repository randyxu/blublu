# author: randyxw@gmail.com
TARGET = server

CC = gcc
CFLAGS = -g -Wall -Werror
LINKFLAGS =

INCLUDES = 
SRCDIR = src
LIBS =
OBJDIR = objs

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst %.c, $(OBJDIR)/%.o, $(SOURCES))


$(TARGET) : build $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LINKFLAGS) $(LIBS)

$(OBJECTS) : $(OBJDIR)/%.o:%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

build : 
	@mkdir -p $(OBJDIR)/$(SRCDIR)




.PHONY:clean

clean:
	rm -rf $(OBJDIR)
	rm -f $(TARGET)

