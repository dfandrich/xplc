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

#ifndef __XPLC_IGENERICFACTORY_H__
#define __XPLC_IGENERICFACTORY_H__

#include <xplc/IFactory.h>

/**
 * Used to configure the generic factory component.
 */
class IGenericFactory: public IFactory {
  UNSTABLE_INTERFACE
public:
  /**
   * Set the factory function to use.
   */
  virtual void setFactory(IObject*(*)()) = 0;
};

DEFINE_IID(IGenericFactory, {0x11e2d782, 0x065a, 0x47f8,
  {0xb4, 0xb3, 0x8e, 0xb4, 0x24, 0x62, 0xc9, 0xff}});

#endif /* __XPLC_IGENERICFACTORY_H__ */
