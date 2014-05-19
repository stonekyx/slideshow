ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = main

main_SOURCES = main.cpp playctl.h playctl.cpp util.h util.cpp

main_LDADD = -ldl $(SDL2_LIBS)
AM_CPPFLAGS = $(SDL2_CFLAGS)

inst_plugins_ldflags = -module -shared -avoid-version

pkglib_LTLIBRARIES = instruction.la

instruction_la_SOURCES = instruction.cpp instruction.h
instruction_la_LDFLAGS = $(inst_plugins_ldflags)

pkglib_LTLIBRARIES += inst_plugins/slide.la

inst_plugins_slide_la_SOURCES = slide.cpp slide.h
inst_plugins_slide_la_LDFLAGS = $(inst_plugins_ldflags)

pkglib_LTLIBRARIES += inst_plugins/endslide.la

inst_plugins_endslide_la_SOURCES = endslide.cpp endslide.h
inst_plugins_endslide_la_LDFLAGS = $(inst_plugins_ldflags)

pkglib_LTLIBRARIES += inst_plugins/rectangle.la

inst_plugins_rectangle_la_SOURCES = rectangle.cpp rectangle.h
inst_plugins_rectangle_la_LDFLAGS = $(inst_plugins_ldflags)

pkglib_LTLIBRARIES += inst_plugins/image.la

inst_plugins_image_la_SOURCES = image.cpp image.h
inst_plugins_image_la_LDFLAGS = $(inst_plugins_ldflags)
inst_plugins_image_la_CXXFLAGS = $(SDL2_image_CFLAGS)
inst_plugins_image_la_LIBADD = $(SDL2_image_LIBS)

pkglib_LTLIBRARIES += inst_plugins/text.la

inst_plugins_text_la_SOURCES = text.cpp text.h
inst_plugins_text_la_LDFLAGS = $(inst_plugins_ldflags)

pkglib_LTLIBRARIES += inst_plugins/gcontextchange.la

inst_plugins_gcontextchange_la_SOURCES = gcontextchange.cpp gcontextchange.h
inst_plugins_gcontextchange_la_LDFLAGS = $(inst_plugins_ldflags)

pkglib_LTLIBRARIES += inst_plugins/scriptfile.la

inst_plugins_scriptfile_la_SOURCES = scriptfile.cpp scriptfile.h
inst_plugins_scriptfile_la_LDFLAGS = $(inst_plugins_ldflags)
inst_plugins_scriptfile_la_LIBADD = -ldl

clean-local:
	-find . -type l -name '*.so' -exec rm -vi {} \;

all-local:
	-find . -type f -path '*.libs/*' -name '*.so' -execdir ln -svr {} .. \;
