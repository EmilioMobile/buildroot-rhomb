src = main.c
cflags = -I../common
libs =
target = devmem

all:$(target)

$(target):
	$(CC) $(CFLAGS) $(cflags) $(libs) $(src) -o $(target)

install:
	cp $(target) $(DESTDIR)
