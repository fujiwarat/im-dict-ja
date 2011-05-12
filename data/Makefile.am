# vim:set noet ts=4:
#
# im-dict-ja - Japanese word dictionary set for input method.
#
# Copyright (c) 2010-2011 Takao Fujiwara <takao.fujiwara1@gmail.com>
# Copyright (c) 2010-2011 Red Hat, Inc.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this program; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place, Suite 330,
# Boston, MA  02111-1307  USA

dictsrcdir = $(datadir)/im-dict/src
dictsrc_DATA = \
	symbol-utf8.txt \
	symbol.txt \
	symbol.xml \
	$(NULL)

DICT_GEN = $(top_builddir)/src/im-dict-gen
$(DICT_GEN):
	(\
	  cd $(top_builddir)/src; \
	  make; \
	);

anthydictdir = $(datadir)/im-dict/dict/anthy
anthydict_DATA = symbol.t
%.t : %.txt %.xml
	@SRC_TXT=$$(echo $@ | sed -e "s|\.t|\.txt|"); \
	 SRC_XML=$$(echo $@ | sed -e "s|\.t|\.xml|"); \
	echo $(DICT_GEN) --xml $${SRC_XML} $${SRC_TXT}; \
	$(DICT_GEN) --xml $${SRC_XML} $${SRC_TXT} > $@

clean-dict: $(anthydict_DATA)
	rm -f $(anthydict_DATA)

desktopdir = $(datadir)/im-dict/desktop
desktop_in_files = symbol-ibus.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = \
	CLASS.txt \
	$(NULL)

