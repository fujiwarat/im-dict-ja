# vim:set noet ts=4:
#
# im-dict-ja - Japanese word dictionary set for input method.
#
# Copyright (c) 2010 Takao Fujiwara <takao.fujiwara1@gmail.com>
# Copyright (c) 2010 Red Hat, Inc.
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

noinst_DIST = \
	$(NULL)

bin_PROGRAMS = im-dict-gen

im_dict_gen_SOURCES = \
    im-dict-gen.c \
    xml-parse.c \
    xml-parse.h \
    $(NULL)

im_dict_gen_CFLAGS = \
    @GLIB2_CFLAGS@ \
    @LIBXML2_CFLAGS@ \
    $(NULL)

im_dict_gen_LDADD = \
    @GLIB2_LIBS@ \
    @LIBXML2_LIBS@ \
    $(NULL)

