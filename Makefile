
.SILENT: buildenvars clearenvars
.PHONY: toolchain


RELEASE=grafland-0.2d.tar.gz
LIST1=cbin cmath editor grafland.png irc shbin toolchain/Makefile toolchain/README
LIST2=clib docs wm gsh Makefile sysmon LICENSE README README.html .htaccess \
	ottercross/Makefile \
	ottercross/README \
	ottercross/packages \
	ottercross/releaseotters.sh \
	ottercross/PASSING \
	musl-otter-cross/Makefile \
	musl-otter-cross/Makefile

WEBSITE=http://www.csit.parkland.edu/~cgraff1
SSHADDR=cgraff1@shaula.csit.parkland.edu:public_html/



all:

	-$(MAKE) -C cbin 
	-$(MAKE) -C irc
	-$(MAKE) -C gsh
	-$(MAKE) -s -C shbin
	-$(MAKE) -C editor
	-$(MAKE) -C sysmon
	-$(MAKE) -C cmath

clean:

	$(MAKE) -C cbin clean 
	$(MAKE) -C irc clean
	$(MAKE) -C gsh clean
	$(MAKE) -C shbin clean
	$(MAKE) -C editor clean
	$(MAKE) -C sysmon clean
	$(MAKE) -C cmath clean

install:

	-$(MAKE) -C cbin install 
	-$(MAKE) -C irc install
	-$(MAKE) -C gsh install
	-$(MAKE) -C shbin install 
	-$(MAKE) -C editor install
	-$(MAKE) -C sysmon install
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
	

