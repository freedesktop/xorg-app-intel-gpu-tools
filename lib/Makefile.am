IGT_LIB_PATH := $(builddir)
GPU_TOOLS_PATH := $(top_srcdir)

SUBDIRS = . tests

include Makefile.sources

libintel_tools_la_SOURCES = $(lib_source_list)

noinst_LTLIBRARIES = libintel_tools.la
noinst_HEADERS = check-ndebug.h

if HAVE_LIBDRM_VC4
    libintel_tools_la_SOURCES += 	\
        igt_vc4.c			\
        igt_vc4.h
endif

if !HAVE_LIBDRM_INTEL
    libintel_tools_la_SOURCES += 	\
        stubs/drm/intel_bufmgr.c	\
        stubs/drm/intel_bufmgr.h
endif

AM_CPPFLAGS = -I$(top_srcdir)
AM_CFLAGS = \
	    $(CWARNFLAGS) \
	    $(DRM_CFLAGS) \
	    $(PCIACCESS_CFLAGS) \
	    $(LIBUNWIND_CFLAGS) \
	    $(KMOD_CFLAGS) \
	    $(PROCPS_CFLAGS) \
	    $(DEBUG_CFLAGS) \
	    -DIGT_SRCDIR=\""$(abs_top_srcdir)/tests"\" \
	    -DIGT_DATADIR=\""$(pkgdatadir)"\" \
	    -DIGT_LOG_DOMAIN=\""$(subst _,-,$*)"\" \
	    -pthread

AM_CFLAGS += $(CAIRO_CFLAGS)

libintel_tools_la_LIBADD = \
	$(DRM_LIBS) \
	$(PCIACCESS_LIBS) \
	$(PROCPS_LIBS) \
	$(KMOD_LIBS) \
	$(CAIRO_LIBS) \
	$(LIBUDEV_LIBS) \
	$(LIBUNWIND_LIBS) \
	$(TIMER_LIBS) \
	-lm

