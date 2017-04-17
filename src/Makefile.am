AUTOMAKE_OPTIONS = foreign

SUBDIRS = 

bin_PROGRAMS = stab
stab_SOURCES = \
	Config.cc \
	Server.cc \
	Main.cc 


stab_CPPFLAGS = -I$(top_srcdir) \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(SEA_CPPFLAGS) \
		$(AIR_CPPFLAGS)


stab_LDADD = \
	$(SEA_LIBADD) \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(AIR_LIBADD)


stab_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = Config.hh \
		 Log.hh \
		 Server.hh


EXTRA_DIST = env.sh stab.cfg log.cfg

stabdir = $(bindir)
stab_DATA = $(EXTRA_DIST)
