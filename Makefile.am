ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = main

main_SOURCES = main.cpp

main_LDADD = -ldl

inst_plugins_ldflags = -module -shared -avoid-version

pkglib_LTLIBRARIES = inst_plugins/rectangle.la

inst_plugins_rectangle_la_SOURCES = rectangle.cpp
inst_plugins_rectangle_la_LDFLAGS = $(inst_plugins_ldflags)

pkglib_LTLIBRARIES += inst_plugins/image.la

inst_plugins_image_la_SOURCES = image.cpp
inst_plugins_image_la_LDFLAGS = $(inst_plugins_ldflags)

pkglib_LTLIBRARIES += inst_plugins/text.la

inst_plugins_text_la_SOURCES = text.cpp
inst_plugins_text_la_LDFLAGS = $(inst_plugins_ldflags)

pkglib_LTLIBRARIES += inst_plugins/gcontextchange.la

inst_plugins_gcontextchange_la_SOURCES = gcontextchange.cpp
inst_plugins_gcontextchange_la_LDFLAGS = $(inst_plugins_ldflags)

pkglib_LTLIBRARIES += scriptfile.la

scriptfile_la_SOURCES = scriptfile.cpp instruction.cpp slide.cpp
scriptfile_la_LDFLAGS = -module -shared -avoid-version

clean-local:
	-find . -type l -name '*.so' -exec rm -vi {} \;

all-local:
	-find . -type f -path '*.libs/*' -name '*.so' -execdir ln -svr {} .. \;
