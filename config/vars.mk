# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000, Pierre Phaneuf
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
# $Id: vars.mk,v 1.9 2000/12/22 20:57:42 pphaneuf Exp $

DISTCLEAN+=config/config.mk
REALCLEAN+=config/depends.mk

# the 'S' option to 'ar' seems to cause problem on Solaris?
#ARFLAGS=rcS
ARFLAGS=rc

RANLIB=ranlib

