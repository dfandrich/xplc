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

#ifndef __XPLC_ISERVICEHANDLER_H__
#define __XPLC_ISERVICEHANDLER_H__

#include <xplc/IObject.h>

class IServiceHandler: public IObject { UNSTABLE_INTERFACE
public:
  static const UUID IID;
  /*
   * The object returned by IServiceHandler::getObject() is
   * already addRef()'d.
   */
  virtual IObject* getObject(const UUID&) = 0;
};

DEFINE_UUID(IServiceHandler::IID) = {0xe897384f, 0x3ba6, 0x46e3,
                                     {0xad, 0x06, 0x53, 0x76,
                                      0x21, 0xa6, 0x0a, 0x03}};

#endif /* __XPLC_ISERVICEHANDLER_H__ */
