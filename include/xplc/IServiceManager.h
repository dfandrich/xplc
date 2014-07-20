/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
 * Copyright (C) 2002, Net Integration Technologies, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#ifndef __XPLC_ISERVICEMANAGER_H__
#define __XPLC_ISERVICEMANAGER_H__

#include <xplc/IObject.h>
#include <xplc/IServiceHandler.h>

class IServiceManager: public IServiceHandler {
  UNSTABLE_INTERFACE
public:
  virtual void addHandler(IServiceHandler*) = 0;
  virtual void addFirstHandler(IServiceHandler*) = 0;
  virtual void addLastHandler(IServiceHandler*) = 0;
  virtual void removeHandler(IServiceHandler*) = 0;
};

DEFINE_IID(IServiceManager, {0x22bdabd9, 0xa63a, 0x4b5e,
  {0xb1, 0x61, 0xb6, 0x36, 0x52, 0x27, 0xd7, 0x8e}});

#endif /* __XPLC_ISERVICEMANAGER_H__ */
