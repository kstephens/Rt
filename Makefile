SUBDIRS = Raster ri Rt

all clean clean-tests :
	@set -xe ;\
	for d in $(SUBDIRS) ;\
	do \
	  $(MAKE) -C $$d $@ ;\
	done

$(SUBDIRS:%=%-all) :
	$(MAKE) -C $(@:%-all=%) all

$(SUBDIRS:%=%-clean) :
	$(MAKE) -C $(@:%-clean=%) clean

test: test-anim

test-anim: Rt/t/test-anim.gif

cores=8
Rt/t/test-*.ppm : Rt/t/rttest.t
	cd Rt && t/rttest.t $(cores)

Rt/t/test-anim.gif : Rt/t/test-*.ppm
	for f in Rt/t/test-*.ppm ;\
	do \
	  pnmquant 256 $$f | pamtogif > $$f.gif ;\
	done
	gifsicle --colors 256 --color-method median-cut --dither --loopcount=forever --delay=25 -O3 Rt/t/test-*.ppm.gif > Rt/t/test-anim.gif

