# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000-2002, Pierre Phaneuf
# Copyright (C) 2002, Net Integration Technologies, Inc.
#
# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU Library General Public License as
# published by the Free Software Foundation; either version 2 of the
# License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.
#
# $Id: vars.mk,v 1.8 2002/06/28 16:51:38 pphaneuf Exp $

TARGETS+=libxplc.a libxplc_s.a libxplc.so.$(VERSION)

CXXDEPS+=$(wildcard xplc/*.cpp)

LIBXPLC_OBJS:=$(patsubst %.cpp,%.o,$(wildcard xplc/*.cpp))

ifeq ("$(call oddeven,$(VERSION_MINOR))", "even")
LIBXPLC_SONAME:=libxplc.so.$(BINARY_VERSION)
else
LIBXPLC_SONAME:=libxplc.so.$(VERSION)-unstable
endif

