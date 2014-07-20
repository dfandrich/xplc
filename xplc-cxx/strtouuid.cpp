/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Pierre Phaneuf
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

#include <stdlib.h>
#include <string.h>
#include <xplc/uuid.h>

const UUID UUID::null = {0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}};

void UUID::fromString(const char* str) {
  char tmp[3];
  char* end;
  bool format1 = false;
  bool ok = false;

  do {
    if(*str == '{') {
      format1 = true;
      ++str;
    }

    data0 = strtoul(str, &end, 16);
    if(end != str + 8)
      break;
    str = end;

    if(*str != '-')
      break;
    ++str;

    data1 = strtoul(str, &end, 16);
    if(end != str + 4)
      break;
    str = end;

    if(*str != '-')
      break;
    ++str;

    data2 = strtoul(str, &end, 16);
    if(end != str + 4)
      break;
    str = end;

    if(*str != '-')
      break;
    ++str;

    tmp[2] = 0;

    strncpy(tmp, str, 2);
    data3[0] = strtoul(tmp, &end, 16);
    if(end != tmp + 2)
      break;
    str += 2;

    strncpy(tmp, str, 2);
    data3[1] = strtoul(tmp, &end, 16);
    if(end != tmp + 2)
      break;
    str += 2;

    if(*str != '-')
      break;
    ++str;

    for(int i = 2; i < 8; ++i) {
      strncpy(tmp, str, 2);
      data3[i] = strtoul(tmp, &end, 16);
      if(end != tmp + 2)
	break;
      str += 2;
    }

    if(format1) {
      if(*str != '}')
	break;
      ++str;
    }

    if(*str != 0)
      break;

    ok = true;
  } while(0);

  if(!ok)
    *this = null;
}

