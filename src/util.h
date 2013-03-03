// Copyright (C) 2011 Oliver Schulz <oliver.schulz@tu-dortmund.de>

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.


#ifndef SIGPX_UTIL_H
#define SIGPX_UTIL_H

#include <stdexcept>

#include "ZigZagEnc.h"


namespace sigpx {


class Util {
public:
	inline static ssize_t mirrorIndex(ssize_t i)
		{ return sigpx::ZigZagEnc::enc(i) >> 1; }
	inline static ssize_t indexExtMirror(size_t n, ssize_t i)
		{ return n - 1 - mirrorIndex(mirrorIndex(i) % (2*n) - n);	}
};


} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::Util-;
#endif


#endif // SIGPX_UTIL_H
