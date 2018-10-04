build:
	$(MAKE) -C utils
	$(MAKE) -C check_results

clean:
	$(MAKE) -C utils clean
	$(MAKE) -C check_results clean

