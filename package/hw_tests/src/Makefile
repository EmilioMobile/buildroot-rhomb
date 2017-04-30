SUBDIRS = gpio

all:
	for d in $(SUBDIRS); do \
		$(MAKE) -C $$d LINUX_DIR=$(LINUX_DIR) all; \
	done

install:
	dst=$(DESTDIR)/opt/rhomb/hw_tests; \
	mkdir -p $$dst; \
	for d in $(SUBDIRS); do \
		$(MAKE) -C $$d DESTDIR=$$dst install; \
	done
