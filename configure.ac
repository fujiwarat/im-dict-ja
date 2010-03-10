# vim:set et ts=4:
#
# im-dict-ja - Japanese word dictionary set for input method
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
#
# if not 1, append datestamp to the version number.
m4_define([im_dict_released], [0])
m4_define([im_dict_major_version], [0])
m4_define([im_dict_minor_version], [1])
m4_define([im_dict_micro_version], [0])
m4_define(im_dict_maybe_datestamp,
    m4_esyscmd([if test x]im_dict_released[ != x1; then date +.%Y%m%d | tr -d '\n\r'; fi]))

m4_define([im_dict_version],
    im_dict_major_version.im_dict_minor_version.im_dict_micro_version[]im_dict_maybe_datestamp)

AC_INIT([im-dict-ja], [im_dict_version], [http://code.google.com/p/ibus/issues/entry],[im-dict-ja])
AM_INIT_AUTOMAKE([1.10])
AC_GNU_SOURCE

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# define PACKAGE_VERSION_* variables
AM_SANITY_CHECK
AM_MAINTAINER_MODE
AM_DISABLE_STATIC
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CXX
AC_ISC_POSIX
AC_HEADER_STDC
AM_PROG_LIBTOOL
IT_PROG_INTLTOOL([0.35.0])

# For dislpay Date
m4_define(im_dict_maybe_datedisplay,
    m4_esyscmd([if test x]im_dict_released[ != x1; then date '+%a %b %d %Y' | tr -d '\n\r'; fi]))
m4_define([im_dict_datedisplay], im_dict_maybe_datedisplay)
DATE_DISPLAY="im_dict_datedisplay"
AC_SUBST(DATE_DISPLAY)

# pkgconfig
AM_PATH_GLIB_2_0
PKG_CHECK_MODULES(GLIB2, [
    glib-2.0 >= 2.8
])

PKG_CHECK_MODULES(LIBXML2, [
    libxml-2.0 >= 2.0
])

# define GETTEXT_* variables
GETTEXT_PACKAGE=im-dict-ja
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [Gettext package])

AM_GLIB_GNU_GETTEXT

# OUTPUT files
AC_CONFIG_FILES([ po/Makefile.in
Makefile
im-dict-ja.spec
data/Makefile
src/Makefile
])

AC_OUTPUT
