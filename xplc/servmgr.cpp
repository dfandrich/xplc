/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000, Pierre Phaneuf
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include <stdlib.h>
#include "servmgr.h"

IObject* ServiceManager::getInterface(const UUID& uuid) {
  do {
    if(uuid.equals(IObject::IID))
      break;

    if(uuid.equals(IServiceManager::IID))
      break;

    return NULL;
  } while(0);

  addRef();
  return this;
}

void ServiceManager::registerUuid(const UUID& aUuid, IObject* aObj) {
  ObjectNode* node;

  node = registered;
  while(node) {
    if(node->uuid.equals(aUuid))
      break;

    node = node->next;
  }

  if(node)
    return;

  node = new ObjectNode;
  node->next = registered;
  node->uuid = aUuid;
  node->obj = aObj;
  node->obj->addRef();
  registered = node;
}

void ServiceManager::unregisterUuid(const UUID& aUuid) {
}

IObject* ServiceManager::getObjectByUuid(const UUID& aUuid) {
  ObjectNode* node;

  node = registered;
  while(node) {
    if(node->uuid.equals(aUuid))
      break;

    node = node->next;
  }

  if(node) {
    node->obj->addRef();
    return node->obj;
  } else
    return NULL;
}

void ServiceManager::shutdown() {
  ObjectNode* node;
  ObjectNode* ptr;

  node = registered;
  while(node) {
    node->obj->release();
    ptr = node;
    node = node->next;
    delete ptr;
  }
  registered = NULL;
}

