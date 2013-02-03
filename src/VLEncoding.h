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


#ifndef SIGPX_VLENCODING_H
#define SIGPX_VLENCODING_H

#include <vector>
#include <stdexcept>
#include <cassert>
#include <stdint.h>

#include "ZigZagEnc.h"


namespace sigpx {


class VLEncoding {
public:
	template<typename tp_Type> static void encSigned(std::vector<char> &enc, const std::vector<tp_Type> &v);
	template<typename tp_Type> static void encUnsigned(std::vector<char> &enc, const std::vector<tp_Type> &v);
	
	template<typename tp_Type> static void decSigned(const std::vector<char> &enc, std::vector<tp_Type> &v);
	template<typename tp_Type> static void decUnsigned(const std::vector<char> &enc, std::vector<tp_Type> &v);
	
	static void enc(std::vector<char> &enc, const std::vector<int16_t> &v);
	static void enc(std::vector<char> &enc, const std::vector<int32_t> &v);
	static void enc(std::vector<char> &enc, const std::vector<int64_t> &v);

	static void enc(std::vector<char> &enc, const std::vector<uint16_t> &v);
	static void enc(std::vector<char> &enc, const std::vector<uint32_t> &v);
	static void enc(std::vector<char> &enc, const std::vector<uint64_t> &v);

	static void dec(const std::vector<char> &enc, std::vector<int16_t> &v);
	static void dec(const std::vector<char> &enc, std::vector<int32_t> &v);
	static void dec(const std::vector<char> &enc, std::vector<int64_t> &v);

	static void dec(const std::vector<char> &enc, std::vector<uint16_t> &v);
	static void dec(const std::vector<char> &enc, std::vector<uint32_t> &v);
	static void dec(const std::vector<char> &enc, std::vector<uint64_t> &v);
};


template<typename tp_Type> void VLEncoding::encSigned(std::vector<char> &enc, const std::vector<tp_Type> &v) {
	enc.clear();
	for (size_t i = 0; i < v.size(); ++i) {
		tp_Type rest = ZigZagEnc::enc(v[i]);
		assert(rest >= 0);
		do {
			tp_Type newRest = rest >> 7;
			char b = (newRest == 0) ? (rest & 0x7F) : ((rest & 0x7F) | 0x80);
			if (enc.size() == enc.capacity()) enc.reserve(std::min(2 * enc.size(), size_t(1)));
			enc.push_back(b);
			rest = newRest;
		} while (rest > 0);
	}
}


template<typename tp_Type> void VLEncoding::encUnsigned(std::vector<char> &enc, const std::vector<tp_Type> &v) {
	enc.clear();
	for (size_t i = 0; i < v.size(); ++i) {
		tp_Type rest = v[i];
		assert(rest >= 0);
		do {
			tp_Type newRest = rest >> 7;
			char b = (newRest == 0) ? (rest & 0x7F) : ((rest & 0x7F) | 0x80);
			if (enc.size() == enc.capacity()) enc.reserve(std::min(2 * enc.size(), size_t(1)));
			enc.push_back(b);
			rest = newRest;
		} while (rest > 0);
	}
}

template<typename tp_Type> void VLEncoding::decSigned(const std::vector<char> &enc, std::vector<tp_Type> &v) {
	v.clear();
	int maxPos = 8 * sizeof(tp_Type);
	tp_Type x = 0; int pos = 0;
	for (size_t i = 0; i < enc.size(); ++i) {
		if (pos >= maxPos) throw std::runtime_error("Overflow during decoding of variable-length encoded number.");
		char b = enc[i];
		x = x | ((b & 0x7f) << pos);
		if ((b & 0x80) == 0) {
			if (v.size() == v.capacity()) v.reserve(std::min(2 * v.size(), size_t(1)));
			v.push_back(ZigZagEnc::dec(x));
			x = 0; pos = 0;
		}
		else pos += 7;
	}
}


template<typename tp_Type> void VLEncoding::decUnsigned(const std::vector<char> &enc, std::vector<tp_Type> &v) {
	v.clear();
	int maxPos = 8 * sizeof(tp_Type);
	tp_Type x = 0; int pos = 0;
	for (size_t i = 0; i < enc.size(); ++i) {
		if (pos >= maxPos) throw std::runtime_error("Overflow during decoding of variable-length encoded number.");
		char b = enc[i++];
		x = x | ((b & 0x7f) << pos);
		if ((b & 0x80) == 0) {
			if (v.size() == v.capacity()) v.reserve(std::min(2 * v.size(), size_t(1)));
			v.push_back(x);
			x = 0; pos = 0;
		}
		else pos += 7;
	}
}


} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::VLEncoding-;
#endif

#endif // SIGPX_VLENCODING_H
