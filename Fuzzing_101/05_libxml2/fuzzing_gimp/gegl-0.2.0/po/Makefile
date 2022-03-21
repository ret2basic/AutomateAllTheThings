# Makefile for program source directory in GNU NLS utilities package.
# Copyright (C) 1995, 1996, 1997 by Ulrich Drepper <drepper@gnu.ai.mit.edu>
#
# This file file be copied and used freely without restrictions.  It can
# be used in projects which are not available under the GNU Public License
# but which still want to provide support for the GNU gettext functionality.
# Please note that the actual code is *not* freely available.
#
# - Modified by Owen Taylor <otaylor@redhat.com> to use GETTEXT_PACKAGE
#   instead of PACKAGE and to look for po2tbl in ./ not in intl/
#
# - Modified by jacob berkman <jacob@ximian.com> to install
#   Makefile.in.in and po2tbl.sed.in for use with glib-gettextize
#
# - Modified by Rodney Dawes <dobey@novell.com> for use with intltool
#
# We have the following line for use by intltoolize:
# INTLTOOL_MAKEFILE

GETTEXT_PACKAGE = gegl-0.2
XGETTEXT_KEYWORDS=--keyword=_ --keyword=N_ --keyword=Q_:1g --keyword=C_:1c,2 --keyword=NC_:1c,2

PACKAGE = gegl
VERSION = 0.2.0

SHELL = /bin/sh

srcdir = .
top_srcdir = ..
top_builddir = ..


prefix = /home/ret2basic/AutomateAllTheThings/Fuzzing_101/05_libxml2/Fuzzing_gimp/gimp-2.8.16/install
exec_prefix = ${prefix}
datadir = ${datarootdir}
datarootdir = ${prefix}/share
libdir = ${exec_prefix}/lib
DATADIRNAME = share
itlocaledir = $(prefix)/$(DATADIRNAME)/locale
subdir = po
install_sh = ${SHELL} /home/ret2basic/AutomateAllTheThings/Fuzzing_101/05_libxml2/fuzzing_gimp/gegl-0.2.0/install-sh
# Automake >= 1.8 provides /usr/bin/mkdir -p.
# Until it can be supposed, use the safe fallback:
mkdir_p = $(install_sh) -d

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644

GMSGFMT = /usr/bin/msgfmt
MSGFMT = /usr/bin/msgfmt
XGETTEXT = /usr/bin/xgettext
INTLTOOL_UPDATE = /usr/bin/intltool-update
INTLTOOL_EXTRACT = /usr/bin/intltool-extract
MSGMERGE = INTLTOOL_EXTRACT=$(INTLTOOL_EXTRACT) srcdir=$(srcdir) $(INTLTOOL_UPDATE) --gettext-package $(GETTEXT_PACKAGE) --dist
GENPOT   = INTLTOOL_EXTRACT=$(INTLTOOL_EXTRACT) srcdir=$(srcdir) $(INTLTOOL_UPDATE) --gettext-package $(GETTEXT_PACKAGE) --pot

ALL_LINGUAS = 

PO_LINGUAS=$(shell if test -r $(srcdir)/LINGUAS; then grep -v "^\#" $(srcdir)/LINGUAS; fi)

USER_LINGUAS=$(shell if test -n "$(LINGUAS)"; then LLINGUAS="$(LINGUAS)"; ALINGUAS="$(ALL_LINGUAS)"; for lang in $$LLINGUAS; do if test -n "`grep ^$$lang$$ $(srcdir)/LINGUAS`" -o -n "`echo $$ALINGUAS|grep ' ?$$lang ?'`"; then printf "$$lang "; fi; done; fi)

USE_LINGUAS=$(shell if test -n "$(USER_LINGUAS)"; then LLINGUAS="$(USER_LINGUAS)"; else if test -n "$(PO_LINGUAS)"; then LLINGUAS="$(PO_LINGUAS)"; else LLINGUAS="$(ALL_LINGUAS)"; fi; fi; for lang in $$LLINGUAS; do printf "$$lang "; done)

POFILES=$(shell LINGUAS="$(USE_LINGUAS)"; for lang in $$LINGUAS; do printf "$$lang.po "; done)

DISTFILES = Makefile.in.in POTFILES.in $(POFILES)
EXTRA_DISTFILES = POTFILES.skip Makevars LINGUAS

POTFILES = \
	../gegl/gegl-init.c \
	../gegl/module/geglmodule.c \
	../operations/common/bilateral-filter.c \
	../operations/common/box-blur.c \
	../operations/common/brightness-contrast.c \
	../operations/common/buffer-sink.c \
	../operations/common/buffer-source.c \
	../operations/common/c2g.c \
	../operations/common/checkerboard.c \
	../operations/common/color-temperature.c \
	../operations/common/color-to-alpha.c \
	../operations/common/color.c \
	../operations/common/contrast-curve.c \
	../operations/common/difference-of-gaussians.c \
	../operations/common/display.c \
	../operations/common/dropshadow.c \
	../operations/common/edge-laplace.c \
	../operations/common/edge-sobel.c \
	../operations/common/exp-combine.c \
	../operations/common/fattal02.c \
	../operations/common/fractal-explorer.c \
	../operations/common/gaussian-blur.c \
	../operations/common/gegl-buffer-load-op.c \
	../operations/common/gegl-buffer-save-op.c \
	../operations/common/grey.c \
	../operations/common/grid.c \
	../operations/common/introspect.c \
	../operations/common/invert.c \
	../operations/common/layer.c \
	../operations/common/lens-distortion.c \
	../operations/common/levels.c \
	../operations/common/load.c \
	../operations/common/magick-load.c \
	../operations/common/mantiuk06.c \
	../operations/common/map-absolute.c \
	../operations/common/map-relative.c \
	../operations/common/matting-global.c \
	../operations/common/mblur.c \
	../operations/common/mirrors.c \
	../operations/common/mono-mixer.c \
	../operations/common/motion-blur.c \
	../operations/common/noise-reduction.c \
	../operations/common/noise.c \
	../operations/common/opacity.c \
	../operations/common/open-buffer.c \
	../operations/common/over.c \
	../operations/common/pixelize.c \
	../operations/common/polar-coordinates.c \
	../operations/common/posterize.c \
	../operations/common/raw-load.c \
	../operations/common/rectangle.c \
	../operations/common/reinhard05.c \
	../operations/common/remap.c \
	../operations/common/ripple.c \
	../operations/common/save.c \
	../operations/common/snn-mean.c \
	../operations/common/stress.c \
	../operations/common/stretch-contrast.c \
	../operations/common/svg-huerotate.c \
	../operations/common/svg-luminancetoalpha.c \
	../operations/common/svg-matrix.c \
	../operations/common/svg-saturate.c \
	../operations/common/threshold.c \
	../operations/common/unsharp-mask.c \
	../operations/common/value-invert.c \
	../operations/common/vignette.c \
	../operations/common/waves.c \
	../operations/common/weighted-blend.c \
	../operations/common/write-buffer.c \
	../operations/core/clone.c \
	../operations/core/convert-format.c \
	../operations/core/crop.c \
	../operations/core/nop.c \
	../operations/external/ff-load.c \
	../operations/external/jp2-load.c \
	../operations/external/jpg-load.c \
	../operations/external/jpg-save.c \
	../operations/external/matting-levin.c \
	../operations/external/path.c \
	../operations/external/pixbuf.c \
	../operations/external/png-load.c \
	../operations/external/png-save.c \
	../operations/external/ppm-load.c \
	../operations/external/ppm-save.c \
	../operations/external/rgbe-load.c \
	../operations/external/rgbe-save.c \
	../operations/external/save-pixbuf.c \
	../operations/external/sdl-display.c \
	../operations/external/svg-load.c \
	../operations/external/text.c \
	../operations/external/v4l.c \
	../operations/external/vector-fill.c \
	../operations/external/vector-stroke.c \
	../operations/generated/add.c \
	../operations/generated/clear.c \
	../operations/generated/color-burn.c \
	../operations/generated/color-dodge.c \
	../operations/generated/darken.c \
	../operations/generated/difference.c \
	../operations/generated/divide.c \
	../operations/generated/dst-atop.c \
	../operations/generated/dst-in.c \
	../operations/generated/dst-out.c \
	../operations/generated/dst-over.c \
	../operations/generated/dst.c \
	../operations/generated/exclusion.c \
	../operations/generated/gamma.c \
	../operations/generated/hard-light.c \
	../operations/generated/lighten.c \
	../operations/generated/multiply.c \
	../operations/generated/overlay.c \
	../operations/generated/plus.c \
	../operations/generated/screen.c \
	../operations/generated/soft-light.c \
	../operations/generated/src-atop.c \
	../operations/generated/src-in.c \
	../operations/generated/src-out.c \
	../operations/generated/src-over.c \
	../operations/generated/src.c \
	../operations/generated/subtract.c \
	../operations/generated/svg-multiply.c \
	../operations/generated/xor.c \
	../operations/transform/reflect.c \
	../operations/transform/rotate.c \
	../operations/transform/scale.c \
	../operations/transform/shear.c \
	../operations/transform/transform-core.c \
	../operations/transform/transform.c \
	../operations/transform/translate.c \
	../operations/workshop/box-max.c \
	../operations/workshop/box-min.c \
	../operations/workshop/box-percentile.c \
	../operations/workshop/buffer-cache.c \
	../operations/workshop/color-reduction.c \
	../operations/workshop/color-rotate.c \
	../operations/workshop/convolution-matrix.c \
	../operations/workshop/cubism.c \
	../operations/workshop/deinterlace.c \
	../operations/workshop/demosaic-bimedian.c \
	../operations/workshop/demosaic-simple.c \
	../operations/workshop/disc-percentile.c \
	../operations/workshop/ditto.c \
	../operations/workshop/emboss.c \
	../operations/workshop/external/ff-save.c \
	../operations/workshop/external/gluas.c \
	../operations/workshop/external/lens-correct.c \
	../operations/workshop/external/line-profile.c \
	../operations/workshop/fractal-trace.c \
	../operations/workshop/generated/average.c \
	../operations/workshop/generated/blend-reflect.c \
	../operations/workshop/generated/negation.c \
	../operations/workshop/generated/soft-burn.c \
	../operations/workshop/generated/soft-dodge.c \
	../operations/workshop/generated/subtractive.c \
	../operations/workshop/hstack.c \
	../operations/workshop/kuwahara.c \
	../operations/workshop/linear-gradient.c \
	../operations/workshop/mandelbrot.c \
	../operations/workshop/max-rgb.c \
	../operations/workshop/noise-spread.c \
	../operations/workshop/plasma.c \
	../operations/workshop/radial-gradient.c \
	../operations/workshop/rawbayer-load.c \
	../operations/workshop/red-eye-removal.c \
	../operations/workshop/snn-percentile.c \
	../operations/workshop/warp.c \
	../operations/workshop/whirl-pinch.c

CATALOGS=$(shell LINGUAS="$(USE_LINGUAS)"; for lang in $$LINGUAS; do printf "$$lang.gmo "; done)

.SUFFIXES:
.SUFFIXES: .po .pox .gmo .mo .msg .cat

.po.pox:
	$(MAKE) $(GETTEXT_PACKAGE).pot
	$(MSGMERGE) $< $(GETTEXT_PACKAGE).pot -o $*.pox

.po.mo:
	$(MSGFMT) -o $@ $<

.po.gmo:
	file=`echo $* | sed 's,.*/,,'`.gmo \
	  && rm -f $$file && $(GMSGFMT) -o $$file $<

.po.cat:
	sed -f ../intl/po2msg.sed < $< > $*.msg \
	  && rm -f $@ && gencat $@ $*.msg


all: all-yes

all-yes: $(CATALOGS)
all-no:

$(GETTEXT_PACKAGE).pot: $(POTFILES)
	$(GENPOT)

install: install-data
install-data: install-data-yes
install-data-no: all
install-data-yes: all
	$(mkdir_p) $(DESTDIR)$(itlocaledir)
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  dir=$(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $$dir; \
	  if test -r $$lang.gmo; then \
	    $(INSTALL_DATA) $$lang.gmo $$dir/$(GETTEXT_PACKAGE).mo; \
	    echo "installing $$lang.gmo as $$dir/$(GETTEXT_PACKAGE).mo"; \
	  else \
	    $(INSTALL_DATA) $(srcdir)/$$lang.gmo $$dir/$(GETTEXT_PACKAGE).mo; \
	    echo "installing $(srcdir)/$$lang.gmo as" \
		 "$$dir/$(GETTEXT_PACKAGE).mo"; \
	  fi; \
	  if test -r $$lang.gmo.m; then \
	    $(INSTALL_DATA) $$lang.gmo.m $$dir/$(GETTEXT_PACKAGE).mo.m; \
	    echo "installing $$lang.gmo.m as $$dir/$(GETTEXT_PACKAGE).mo.m"; \
	  else \
	    if test -r $(srcdir)/$$lang.gmo.m ; then \
	      $(INSTALL_DATA) $(srcdir)/$$lang.gmo.m \
		$$dir/$(GETTEXT_PACKAGE).mo.m; \
	      echo "installing $(srcdir)/$$lang.gmo.m as" \
		   "$$dir/$(GETTEXT_PACKAGE).mo.m"; \
	    else \
	      true; \
	    fi; \
	  fi; \
	done

# Empty stubs to satisfy archaic automake needs
dvi info tags TAGS ID:

# Define this as empty until I found a useful application.
install-exec installcheck:

uninstall:
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  rm -f $(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES/$(GETTEXT_PACKAGE).mo; \
	  rm -f $(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES/$(GETTEXT_PACKAGE).mo.m; \
	done

check: all $(GETTEXT_PACKAGE).pot
	rm -f missing notexist
	srcdir=$(srcdir) $(INTLTOOL_UPDATE) -m
	if [ -r missing -o -r notexist ]; then \
	  exit 1; \
	fi

mostlyclean:
	rm -f *.pox $(GETTEXT_PACKAGE).pot *.old.po cat-id-tbl.tmp
	rm -f .intltool-merge-cache

clean: mostlyclean

distclean: clean
	rm -f Makefile Makefile.in POTFILES stamp-it
	rm -f *.mo *.msg *.cat *.cat.m *.gmo

maintainer-clean: distclean
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	rm -f Makefile.in.in

distdir = ../$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir: $(DISTFILES)
	dists="$(DISTFILES)"; \
	extra_dists="$(EXTRA_DISTFILES)"; \
	for file in $$extra_dists; do \
	  test -f $(srcdir)/$$file && dists="$$dists $(srcdir)/$$file"; \
	done; \
	for file in $$dists; do \
	  test -f $$file || file="$(srcdir)/$$file"; \
	  ln $$file $(distdir) 2> /dev/null \
	    || cp -p $$file $(distdir); \
	done

update-po: Makefile
	$(MAKE) $(GETTEXT_PACKAGE).pot
	tmpdir=`pwd`; \
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  echo "$$lang:"; \
	  result="`$(MSGMERGE) -o $$tmpdir/$$lang.new.po $$lang`"; \
	  if $$result; then \
	    if cmp $(srcdir)/$$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	      rm -f $$tmpdir/$$lang.new.po; \
            else \
	      if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	        :; \
	      else \
	        echo "msgmerge for $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	        rm -f $$tmpdir/$$lang.new.po; \
	        exit 1; \
	      fi; \
	    fi; \
	  else \
	    echo "msgmerge for $$lang.gmo failed!"; \
	    rm -f $$tmpdir/$$lang.new.po; \
	  fi; \
	done

Makefile POTFILES: stamp-it
	@if test ! -f $@; then \
	  rm -f stamp-it; \
	  $(MAKE) stamp-it; \
	fi

stamp-it: Makefile.in.in $(top_builddir)/config.status POTFILES.in
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/Makefile.in CONFIG_HEADERS= CONFIG_LINKS= \
	       $(SHELL) ./config.status

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:

update:
	echo "[encoding: UTF-8]" > POTFILES.in
	echo "" >> POTFILES.in
	(cd ..; git grep "_(\"" | grep -v Binary | sed s/:.\*// | uniq >> po/POTFILES.in)
