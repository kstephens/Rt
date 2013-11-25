SUBDIRS = Raster ri Rt

all clean :
	set -xe ;\
	for d in $(SUBDIRS) ;\
	do \
	  $(MAKE) -C $$d $@ ;\
	done
