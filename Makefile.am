AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_AMFLAGS}

AM_CPPFLAGS = $(OPENCV_CFLAGS)

bin_PROGRAMS = cvflappy

cvflappy_SOURCES = src/cvflappy.cpp
#cvflappy_LDFLAGS = -framework TBB
cvflappy_LDADD = $(OPENCV_LIBS)
