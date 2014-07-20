/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
 * Copyright (C) 2001, St�phane Lajoie
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

#ifndef __XPLC_UTILS_H__
#define __XPLC_UTILS_H__

#include <stddef.h>
#include <xplc/IFactory.h>

struct UUID_Info {
  const UUID* const iid;
  const ptrdiff_t delta;
};

#define UUID_MAP_BEGIN(component) const UUID_Info GenericComponent<component>::uuids[] = {

#define UUID_MAP_ENTRY(iface) { &iface::IID, reinterpret_cast<ptrdiff_t>(static_cast<iface*>(reinterpret_cast<ThisComponent*>(1))) - 1 },

#define UUID_MAP_ENTRY_2(iface, iface2) { &iface::IID, reinterpret_cast<ptrdiff_t>(static_cast<iface2*>(reinterpret_cast<ThisComponent*>(1))) - 1 },

#define UUID_MAP_END { 0, 0 } };

/*
 * Mix-in template that contains an implementation of methods a basic
 * component will need to implement.
 */
template<class Component>
class GenericComponent: public Component {
private:
  typedef GenericComponent ThisComponent;
  static const UUID_Info uuids[];
  unsigned int refcount;
public:
  GenericComponent(): refcount(0) {
  }
  virtual unsigned int addRef() {
    return ++refcount;
  }
  virtual unsigned int release() {
    if(--refcount)
      return refcount;

    /* protect against re-entering the destructor */
    refcount = 1;

    delete this;

    return 0;
  }
  virtual IObject* getInterface(const UUID& uuid) {
    return XPLC_getInterface_real(this, uuid, uuids);
  }
};

IObject* XPLC_getInterface_real(void* self, const UUID& uuid,
                                const UUID_Info* uuidlist);

/*
 * This templated function is a typesafe way to call the getInterface
 * method of a component and cast it properly. If the component does
 * not support the interface, a NULL pointer will be returned.
 */
template<class Interface>
Interface* get(IObject* aObj) {
  if(!aObj)
    return 0;

  return static_cast<Interface*>(aObj->getInterface(Interface::IID));
}

/*
 * This templated function is very similar to the "get" one, except
 * that it automatically releases the inbound reference, without
 * regard whether the getInterface actually yielded something.
 */
template<class Interface>
Interface* mutate(IObject* aObj) {
  Interface* rv;

  if(!aObj)
    return 0;

  rv = static_cast<Interface*>(aObj->getInterface(Interface::IID));

  aObj->release();

  return rv;
}

/*
 * This templated function is a shorthand to get a factory, create an
 * object a get an interface.
 */
template<class Interface>
Interface* create(const UUID& cid) {
  IServiceManager* servmgr;
  IFactory* factory;
  Interface* rv;

  servmgr = XPLC_getCoreServiceManager();
  if(!servmgr)
    return 0;

  factory = mutate<IFactory>(servmgr->getObject(cid));
  servmgr->release();
  if(!factory)
    return 0;

  rv = mutate<Interface>(factory->createObject());

  factory->release();

  return rv;
}

#endif /* __XPLC_UTILS_H__ */
