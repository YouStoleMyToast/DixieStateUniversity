include ../../Makefile.top

PROJECT_LIST  := SA_Test Genesis

all install clean spotless:
	for d in $(PROJECT_LIST); do \
		$(MAKE) -f Makefile.$$d $@ ; \
	done

$(PROJECT_LIST):
	$(MAKE) -f Makefile.$@

include ../../Makefile.dep
