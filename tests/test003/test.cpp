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

#include "../test.h"
#include <xplc/xplc.h>
#include <xplc/utils.h>
#include "../xplc/statichandler.h"

/*
 * test003
 *
 * Verifies the static service handler;
 */

void test() {
  IStaticServiceHandler* handler;
  TestObject* test;
  IObject* obj;
  ITestInterface *itest;

  handler = StaticServiceHandler::create();
  ASSERT(handler, "could not instantiate static service handler");

  handler->addRef();

  test = new TestObject;
  ASSERT(test, "could not instantiate test object");

  test->addRef();
  VERIFY(test->getRefCount() == 1, "the test object has an incorrect refcount");

  handler->addObject(TestObject::CID, test);
  VERIFY(test->getRefCount() == 2, "static service handler did not addRef the test component");

  obj = handler->getObject(TestObject::CID);
  ASSERT(obj, "could not get test component from static service handler");

  itest = mutateInterface<ITestInterface>(obj);
  ASSERT(itest, "test component does not have the expected interface");

  VERIFY(test->getRefCount() == 3, "the test object has an incorrect refcount");
  itest->setRefCount(10);
  itest->addRef();
  VERIFY(itest->getRefCount() == 11, "test component has unexpected behavior");
  itest->setRefCount(3);

  VERIFY(itest->release() == 2, "test component has incorrect refcount");

  handler->removeObject(TestObject::CID);
  VERIFY(test->getRefCount() == 1, "static service handler did not release the test component");

  obj = handler->getObject(TestObject::CID);
  VERIFY(!obj, "static service handler did not remove the test component");
  if(obj)
    obj->release();

  VERIFY(handler->release() == 0, "static service handler has non-zero refcount after release");

  VERIFY(test->release() == 0, "test object has non-zero refcount after release");
}

