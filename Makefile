obj-m := hello.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	gcc -o insert insert.c

install:
	cp hello.ko $(DESTDIR)
	cp insert $(DESTDIR)

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	rm -f insert
