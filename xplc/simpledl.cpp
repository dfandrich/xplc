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

#ifdef __LINUX__
#include <dlfcn.h>
#endif
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>
#endif

#include <xplc/utils.h>
#include "simpledl.h"

IObject* SimpleDynamicLoader::create() {
  return new GenericComponent<SimpleDynamicLoader>;
}

IObject* SimpleDynamicLoader::getInterface(const UUID& aUuid) {
  if(aUuid.equals(IObject::IID)) {
    addRef();
    return static_cast<IObject*>(this);
  }

  if(aUuid.equals(IFactory::IID)) {
    addRef();
    return static_cast<IFactory*>(this);
  }

  if(aUuid.equals(ISimpleDynamicLoader::IID)) {
    addRef();
    return static_cast<ISimpleDynamicLoader*>(this);
  }

  return 0;
}

IObject* SimpleDynamicLoader::createObject() {
  IObject* obj;

  obj = factory();

  if(obj)
    obj->addRef();

  return obj;
}

const char* SimpleDynamicLoader::loadModule(const char* filename) {
#ifdef __GCC__
  const char* err;

  /* clear out dl error */
  (void)dlerror();

  if(dlh)
    dlclose(dlh);

  err = dlerror();
  if(err)
    return err;

  /*
   * FIXME: should we open with RTLD_LAZY instead? RTLD_NOW is safer,
   * but if it is too costly, maybe we should just verify that
   * libraries are complete during development?
   */
  dlh = dlopen(filename, RTLD_NOW);
  if(!dlh) {
    err = dlerror();
    return err;
  }

  /*
   * FIXME: What is the proper C++ cast to use here? reinterpret_cast
   * with GCC gives a warning that "ISO C++ forbids casting between
   * pointer-to-function and pointer-to-object".
   */
  factory = (IObject*(*)())(dlsym(dlh, "XPLC_SimpleModule"));
  err = dlerror();
  if(err)
    return err;

  return 0;
#endif
#ifdef WIN32
	/*
	 * TODO: unload previous DLL?
	 */

	// buffer for possible error message
	static char msg[256];

	/*
	 * Load the DLL. This will do a typical DLL search: application dir, current dir,
	 * windows/system, windows, path.
	 */
	HINSTANCE hInstance = LoadLibraryEx(filename, 0, 0);
	if(!hInstance) {
		if(FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, msg, sizeof(msg), 0))
			return msg;
		else
			return "Something went wrong loading a module and error handling failed. Blame Windows.";
	}

	/*
	 * Get entry point.
	 */
	FARPROC proc = GetProcAddress(hInstance, "XPLC_SimpleModule");
	if(!proc) {
		if(FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, msg, sizeof(msg), 0))
			return msg;
		else
			return "Something went wrong finding the exported symbol and error handling failed. Blame Windows.";
	}

	/*
	 * All done!
	 */
	factory = (IObject*(*)())proc;
	return 0;
#endif
}
