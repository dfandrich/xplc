/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2003, Pierre Phaneuf
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

#ifndef __XPLC_UUID_H__
#define __XPLC_UUID_H__

/** \file
 *
 * Universally Unique IDentifiers.
 * 
 * A UUID is a sequence of 16 bytes that is unique throughout the
 * universe, and which can uniquely identify anything you might want.
 * It will never have a name conflict with any other UUID.  To come up
 * with a UUID of your own, run the 'uuidgen' program that comes with
 * many Unix and Windows systems.  Although any UUID is guaranteed to
 * be unique, there is a downside: it's almost impossible for a human
 * to read, understand, or remember the contents of a UUID.  For a
 * less unique, human-readable alternative to UUIDs, see IMoniker.
 * 
 * A UUID is what is known as a "strong name". It is like the name of
 * a class in a C++ program, or of a global variable, but the "strong"
 * part refers to how this name, unlike the name of a C++ class, is
 * unique and refers precisely to this one thing. C++ names are "weak
 * names", it is very easy to create two different things with the
 * same name, for example, classes named "String" are very common, and
 * two different "String" classes could not be used in the same
 * program. When making a single program, it is possible to avoid
 * these conflicts, but with a component system, you never know how
 * components will be used together, thus the need for strong names.
 *
 * The UUID is the standard way of looking up and indexing objects in
 * XPLC.  All "well-known" objects you need to look for (such as the
 * standard XPLC moniker and category services, and other objects you
 * create yourself) will have a UUID you can look up using the service
 * manager.  Note that objects referenced by a UUID are necessarily
 * "singletons" - that is, objects of a class that is only
 * instantiated once in any program.  For example, a factory that
 * produces HelloWorld objects would have its own UUID - so you can
 * ask for a HelloWorldFactory and get "the" HelloWorldFactory - but
 * the HelloWorld objects it produces would not be findable by UUID.
 * (If they all had the same UUID, it wouldn't be very Universally
 * Unique, would it?  And if they all had different UUIDs, how would
 * you know which UUID to look for?)
 * 
 * Also: when you retrieve a different interface from an IObject using
 * its getInterface() method, you do so by looking up the UUID of that
 * interface, also known as an IID (which is just a nickname for UUID,
 * they are identical in meaning).  Every interface must have an IID,
 * but the IID is the same for all objects implementing that
 * interface.  However, you can have multiple objects implementing a
 * particular interface, and each of those objects will have its own
 * UUID.
 */

//@{
#ifndef GUID_DEFINED
#define GUID_DEFINED
/**
 * The structure underlying UUIDs. This is similar to the Windows
 * definition, for compatibility reasons.
 */
typedef struct _GUID {
  //@{
  unsigned long Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char Data4[8];
  //@}
} GUID;
#endif

#ifndef UUID_DEFINED
#define UUID_DEFINED
typedef GUID UUID;
#ifndef uuid_t
#define uuid_t UUID
#endif
#endif
//@}

/**
 * Equality operator for UUIDs.
 */
inline bool operator==(const UUID& uuid1, const UUID& uuid2) {
    return
      (&uuid1 == &uuid2) ||
      ((static_cast<const unsigned long*>(&uuid1.Data1)[0] == static_cast<const unsigned long*>(&uuid2.Data1)[0]) &&
       (static_cast<const unsigned long*>(&uuid1.Data1)[1] == static_cast<const unsigned long*>(&uuid2.Data1)[1]) &&
       (static_cast<const unsigned long*>(&uuid1.Data1)[2] == static_cast<const unsigned long*>(&uuid2.Data1)[2]) &&
       (static_cast<const unsigned long*>(&uuid1.Data1)[3] == static_cast<const unsigned long*>(&uuid2.Data1)[3]));
}

/**
 * Inequality operator for UUIDs.
 */
inline bool operator!=(const UUID& uuid1, const UUID& uuid2) {
    return
      (&uuid1 != &uuid2) &&
      ((static_cast<const unsigned long*>(&uuid1.Data1)[0] != static_cast<const unsigned long*>(&uuid2.Data1)[0]) ||
       (static_cast<const unsigned long*>(&uuid1.Data1)[1] != static_cast<const unsigned long*>(&uuid2.Data1)[1]) ||
       (static_cast<const unsigned long*>(&uuid1.Data1)[2] != static_cast<const unsigned long*>(&uuid2.Data1)[2]) ||
       (static_cast<const unsigned long*>(&uuid1.Data1)[3] != static_cast<const unsigned long*>(&uuid2.Data1)[3]));
}

/**
 * Converts a printable C string to a UUID.  The string is of the form
 * "9c318f06-52ec-4a62-b5fb-9279216e8586" (without the quotes), but
 * will also tolerate opening and closing braces before and after.
 * 
 * This is the form produced by the 'uuidgen' program and is used in
 * the Windows registry.
 */
const UUID UuidFromString(const char* str);

/**
 * Fill the given pointer with a printable string representing the
 * given UUID.  The string is of the form
 * "9c318f06-52ec-4a62-b5fb-9279216e8586" (without the quotes).
 * 
 * 'str' should point to at least 39 bytes of available memory.
 * Always returns 'str', which has been null-terminated.
 */
char* UuidToString(const UUID& uuid, char* str);

/// The NULL UUID.  Nothing will ever have this UUID, I promise.
static const UUID UUID_null = {0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}};

/** \struct IID uuid.h xplc/uuid.h
 *
 * An Interface IDentifier.  Every interface (abstract classes derived from
 * IObject) must have a unique IID, so that getInterface() can ask for that
 * interface.
 * 
 * Generate a UUID for your IID using 'uuidgen', then declare your IID
 * using DEFINE_IID(ClassName).  If you need to obtain the UUID corresponding
 * to that interface in the future, call the static function
 * IID<ClassName>::get().
 */
template<class T>
struct IID {
};

/**
 * Used to define the IID of an interface.
 */
#define DEFINE_IID(iface, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11) \
static const UUID iface##_IID = u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11; \
template <> \
struct IID<iface> { \
  static const UUID& get() { \
    return iface##_IID; \
  } \
}

#endif /* __XPLC_UUID_H__ */
