src = main.c
cflags = -I../common -I$(LINUX_DIR)/arch/arm/include
libs =
target = gpio_test

all:$(target)

$(target):
	$(CC) $(CFLAGS) $(cflags) $(libs) $(src) -o $(target)

install:
	cp $(target) $(DESTDIR)
