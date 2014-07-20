# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000-2001, Pierre Phaneuf
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
# $Id: rules.mk,v 1.9 2002/05/25 00:11:21 pphaneuf Exp $

.PHONY: tests

tests: $(TESTS)
	@echo "Running tests:"
	@for TEST in $(TESTS); do $$TEST; done; true

include $(wildcard tests/*/rules.mk)

