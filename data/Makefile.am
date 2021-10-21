# vim:set noet ts=4:
#
# im-dict-ja - Japanese word dictionary set for input method.
#
# Copyright (c) 2010-2021 Takao Fujiwara <takao.fujiwara1@gmail.com>
# Copyright (c) 2010-2016 Red Hat, Inc.
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
dictsrc_files = \
	emoji.xml \
	era.txt \
	era.xml \
	oldchar.txt \
	oldchar.xml \
	symbol-utf8.txt \
	symbol.txt \
	symbol.xml \
	$(NULL)
dictsrc_DATA = \
	$(dictsrc_files) \
	emoji.txt \
	$(NULL)

DICT_GEN = $(top_builddir)/src/im-dict-gen
$(DICT_GEN):
	(\
	  cd $(top_builddir)/src; \
	  make; \
	);

anthydictdir = $(datadir)/im-dict/dict/anthy
anthydict_DATA = emoji.t era.t oldchar.t symbol.t
nodist_anthydict_DATA = emoji-each.t emoji-emoji.t

emoji.txt: emoji-each.txt emoji-emoji.txt
	@echo "Generate $@"; \
	$(SED) -e '/^#/d' $(srcdir)/emoji-emoji.txt > emoji-emoji.txt.$$$$; \
	$(SED) -e "/^#@EMOJI_EMOJI@/r emoji-emoji.txt.$$$$" \
	        $(srcdir)/emoji-each.txt > emoji-each.txt.$$$$; \
	$(SED) -e '/^#@EMOJI_EMOJI@/d' emoji-each.txt.$$$$ > emoji.txt; \
	rm emoji-emoji.txt.$$$$ emoji-each.txt.$$$$; \
	$(NULL)

emoji.t: emoji-each.t emoji-emoji.t
	@echo "Generate $@"; \
	$(SED) -e '/^#/d' $(builddir)/emoji-emoji.t > emoji-emoji.t.$$$$; \
	$(SED) -e "/^#@EMOJI_EMOJI@/r emoji-emoji.t.$$$$" \
	        $(builddir)/emoji-each.t > emoji-each.t.$$$$; \
	$(SED) -e '/^#@EMOJI_EMOJI@/d' emoji-each.t.$$$$ > emoji.t; \
	rm emoji-emoji.t.$$$$ emoji-each.t.$$$$; \
	$(NULL)

%.t : %.txt %.xml
	@SRC_TXT=$(srcdir)/$$(echo $@ | sed -e "s|\.t|\.txt|"); \
	 SRC_XML=$(srcdir)/$$(echo $@ | sed -e "s|\.t|\.xml|"); \
	echo $(DICT_GEN) --xml $${SRC_XML} $${SRC_TXT}; \
	$(DICT_GEN) --xml $${SRC_XML} $${SRC_TXT} > $@; \
	$(NULL)

desktopdir = $(datadir)/im-dict/desktop
desktop_in_files = \
	emoji-ibus.desktop.in \
	era-ibus.desktop.in \
	oldchar-ibus.desktop.in \
	symbol-ibus.desktop.in \
	$(NULL)

desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
%.desktop: %.desktop.in
	$(AM_V_GEN)$(MSGFMT) --desktop --template $< -d $(top_srcdir)/po -o $@

CLEANFILES = \
	$(anthydict_DATA) \
	$(desktop_DATA) \
	$(nodist_anthydict_DATA) \
	emoji.txt \
	$(NULL)

EXTRA_DIST = \
	$(desktop_in_files) \
	$(dictsrc_files) \
	emoji-each.txt \
	emoji-each.xml \
	emoji-emoji.txt \
	emoji-emoji.xml \
	CLASS.txt \
	$(NULL)

