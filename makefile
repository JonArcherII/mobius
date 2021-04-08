SUBDIRS = kernel

.PHONY: all clean $(SUBDIRS)

all:
	@$(foreach c, $(SUBDIRS), $(MAKE) -C $(c) && ) true

clean:
	@$(foreach c, $(SUBDIRS), $(MAKE) -C $(c) clean && ) true