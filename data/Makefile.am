# vim:set noet ts=4:
#
# im-dict-ja - Japanese word dictionary set for input method.
#
# Copyright (c) 2010-2014 Takao Fujiwara <takao.fujiwara1@gmail.com>
# Copyright (c) 2010-2014 Red Hat, Inc.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
# USA

dictsrcdir = $(datadir)/im-dict/src
dictsrc_DATA = \
	emoji.txt \
	emoji.xml \
	era.txt \
	era.xml \
	oldchar.txt \
	oldchar.xml \
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
anthydict_DATA = emoji.t era.t oldchar.t symbol.t
%.t : %.txt %.xml
	@SRC_TXT=$$(echo $@ | sed -e "s|\.t|\.txt|"); \
	 SRC_XML=$$(echo $@ | sed -e "s|\.t|\.xml|"); \
	echo $(DICT_GEN) --xml $${SRC_XML} $${SRC_TXT}; \
	$(DICT_GEN) --xml $${SRC_XML} $${SRC_TXT} > $@

clean-dict: $(anthydict_DATA)
	rm -f $(anthydict_DATA)

desktopdir = $(datadir)/im-dict/desktop
desktop_in_files = \
	emoji-ibus.desktop.in \
	era-ibus.desktop.in \
	oldchar-ibus.desktop.in \
	symbol-ibus.desktop.in \
	$(NULL)

desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = \
	CLASS.txt \
	$(NULL)

