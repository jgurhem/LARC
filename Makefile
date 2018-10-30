build:
	$(MAKE) -C utils
	$(MAKE) -C check

clean:
	$(MAKE) -C utils clean
	$(MAKE) -C check clean

