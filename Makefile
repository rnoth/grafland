
.SILENT: buildenvars clearenvars
.PHONY: toolchain


RELEASE=grafland-0.2g.tar.gz
WEBSITE=http://www.csit.parkland.edu/~cgraff1




all:

	-$(MAKE) -C bin 
	-$(MAKE) -C irc
	-$(MAKE) -C gsh
	-$(MAKE) -s -C shbin
	-$(MAKE) -C editor
	-$(MAKE) -C sysmon
	-$(MAKE) -C math

clean:

	$(MAKE) -C bin clean 
	$(MAKE) -C irc clean
	$(MAKE) -C gsh clean
	$(MAKE) -C shbin clean
	$(MAKE) -C editor clean
	$(MAKE) -C sysmon clean
	$(MAKE) -C math clean

install:

	-$(MAKE) -C bin install 
	-$(MAKE) -C irc install
	-$(MAKE) -C gsh install
	-$(MAKE) -C shbin install 
	-$(MAKE) -C editor install
	-$(MAKE) -C sysmon install
	-$(MAKE) -C math install
	# Install toolchain last if it exists
	-$(MAKE) -C toolchain install

toolchain:

	$(MAKE) -C toolchain

toolchainclean:

	$(MAKE) -C toolchain clean 

buildenvars:

	$(MAKE) -s -C toolchain buildenvars

clearenvars:

	$(MAKE) -s -C toolchain clearenvars

release:

	#tar -cf $(RELEASE) $(LIST1) $(LIST2)

	-echo "$(WEBSITE)/$(RELEASE)" >> README
	-echo >> README
	-echo "  <A HREF=\"$(WEBSITE)/$(RELEASE)\">$(WEBSITE)/$(RELEASE)</A>" >> README.html
	-echo "  <br>" >> README.html
	

	-git add *
	-git commit -m $(RELEASE)
	-git push origin master
	

