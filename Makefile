obj-m := debugfs_preempt_count.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
		$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

insmod:
		insmod debugfs_preempt_count.ko

rmmod:
		rmmod debugfs_preempt_count.ko

reload:
		-make rmmod
		make insmod
