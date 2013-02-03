// Copyright (C) 2011 Oliver Schulz <oliver.schulz@tu-dortmund.de>

// This is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.


#ifndef SIGPX_ZigZagEnc_H
#define SIGPX_ZigZagEnc_H

#include <vector>
#include <stdint.h>


namespace sigpx {


class ZigZagEnc {
public:
	static inline uint8_t enc(int8_t x)    { return ((x << 1) ^ (x >> 7)); }
	static inline uint8_t enc(uint8_t x)   { return ((x << 1) ^ (x >> 7)); }

	static inline int8_t dec(int8_t x)    { return ((x >> 1) ^ -(x & 1)); }
	static inline int8_t dec(uint8_t x)   { return ((x >> 1) ^ -(x & 1)); }

	static inline uint16_t enc(int16_t x)  { return ((x << 1) ^ (x >> 15)); }
	static inline uint16_t enc(uint16_t x) { return ((x << 1) ^ (x >> 15)); }

	static inline int16_t dec(int16_t x)  { return ((x >> 1) ^ -(x & 1)); }
	static inline int16_t dec(uint16_t x) { return ((x >> 1) ^ -(x & 1)); }

	static inline uint32_t enc(int32_t x)  { return ((x << 1) ^ (x >> 31)); }
	static inline uint32_t enc(uint32_t x) { return ((x << 1) ^ (x >> 31)); }

	static inline int32_t dec(int32_t x)  { return ((x >> 1) ^ -(x & 1)); }
	static inline int32_t dec(uint32_t x) { return ((x >> 1) ^ -(x & 1)); }

	static inline uint64_t enc(int64_t x)  { return ((x << 1) ^ (x >> 63)); }
	static inline uint64_t enc(uint64_t x) { return ((x << 1) ^ (x >> 63)); }

	static inline int64_t dec(int64_t x)  { return ((x >> 1) ^ -(x & 1)); }
	static inline int64_t dec(uint64_t x) { return ((x >> 1) ^ -(x & 1)); }
};


} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::ZigZagEnc-;
#endif

#endif // SIGPX_ZigZagEnc_H
