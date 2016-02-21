AM_CFLAGS = @CFLAGS@ -DHIPO_BASEETC='"$(sysconfdir)"' -DPREFIX='"$(prefix)"' \
 -DHIPO_EXEC='"$(libexecdir)"' -DHIPO_VAR='"$(localstatedir)"'
AM_LDFLAGS =
# this lists the binaries to produce, the (non-PHONY, binary) targets in
# # the previous manual Makefile
#
sbin_PROGRAMS = hipoclockd
hipoclockd_SOURCES = config.c hipoclockd.c
hipoclockd_CFLAGS = -I$(top_srcdir)/include $(AM_CFLAGS)
