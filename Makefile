
CC = g++
CFLAGS = -Wall -g
INCLUDES = -I./includes

# LDFLAGS = -L./lib  -L../lib
LIBS = -lm

# VPath source files
SRCS = main.cpp camera.cpp cam_hardware.cpp vpathlog.cpp
OBJS = $(SRCS:.cpp=.o)


# our executable file 
MAIN = vpath

.PHONY: depend clean

all:	$(MAIN)

$(MAIN): $(MSG) \
		$(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LDFLAGS) $(LIBS)


.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
