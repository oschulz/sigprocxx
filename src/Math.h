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


#ifndef SIGPX_MATH_H
#define SIGPX_MATH_H

#include <stdint.h>


namespace sigpx {


class Math {
public:
	void run();

	static inline uint8_t zzEnc(int8_t x) { return ((x << 1) ^ (x >> 7)); }

	static inline int8_t zzDec(uint8_t x) { return ((x >> 1) ^ -(x & 1)); }

	static inline uint16_t zzEnc(int16_t x) { return ((x << 1) ^ (x >> 15)); }

	static inline int16_t zzDec(uint16_t x) { return ((x >> 1) ^ -(x & 1)); }

	static inline uint32_t zzEnc(int32_t x) { return ((x << 1) ^ (x >> 31)); }

	static inline int32_t zzDec(uint32_t x) { return ((x >> 1) ^ -(x & 1)); }

	static inline uint64_t zzEnc(int64_t x) { return ((x << 1) ^ (x >> 63)); }

	static inline int64_t zzDec(uint64_t x) { return ((x >> 1) ^ -(x & 1)); }
};


} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::Math-;
#endif

#endif // SIGPX_MATH_H
