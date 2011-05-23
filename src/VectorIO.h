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
// You should have received a copy of the GNU General Public License
//
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.


#ifndef SIGPX_VECTORIO_H
#define SIGPX_VECTORIO_H

#include <iostream>
#include <vector>
#include <cassert>
#include <stdint.h>

#include "Math.h"


namespace sigpx {


class VectorIO {
public:
	template<typename tp_Type> static std::ostream& printT(std::ostream &os, const std::vector<tp_Type> &v);

	template<typename tp_Type> static void stuffT(std::vector<tp_Type> &stuffed, std::vector<int32_t> &sizes, const std::vector<tp_Type> &v);

	template<typename tp_Type> static void unstuffT(const std::vector<tp_Type> &stuffed, const std::vector<int32_t> &sizes, int i, std::vector<tp_Type> &v);

	template<typename tp_Type, typename tp_Type2> static void zzEncT(std::vector<tp_Type> &enc, const std::vector<tp_Type2> &v);
	template<typename tp_Type, typename tp_Type2> static void zzDecT(const std::vector<tp_Type> &enc, std::vector<tp_Type2> &v);

	static std::ostream& print(std::ostream &os, const std::vector<int8_t> &v);
	static std::ostream& print(std::ostream &os, const std::vector<uint8_t> &v);
	static void stuff(std::vector<uint8_t> &stuffed, std::vector<int32_t> &sizes, const std::vector<uint8_t> &v);
	static void unstuff(const std::vector<uint8_t> &stuffed, const std::vector<int32_t> &sizes, int i, std::vector<uint8_t> &v);
	static void zzEnc(std::vector<uint8_t> &enc, const std::vector<int8_t> &v);
	static void zzDec(const std::vector<uint8_t> &enc, std::vector<int8_t> &v);

	static std::ostream& print(std::ostream &os, const std::vector<int16_t> &v);
	static std::ostream& print(std::ostream &os, const std::vector<uint16_t> &v);
	static void stuff(std::vector<int16_t> &stuffed, std::vector<int32_t> &sizes, const std::vector<int16_t> &v);
	static void unstuff(const std::vector<int16_t> &stuffed, const std::vector<int32_t> &sizes, int i, std::vector<int16_t> &v);
	static void zzEnc(std::vector<uint16_t> &enc, const std::vector<int16_t> &v);
	static void zzDec(const std::vector<uint16_t> &enc, std::vector<int16_t> &v);

	static std::ostream& print(std::ostream &os, const std::vector<int32_t> &v);
	static std::ostream& print(std::ostream &os, const std::vector<uint32_t> &v);
	static void stuff(std::vector<int32_t> &stuffed, std::vector<int32_t> &sizes, const std::vector<int32_t> &v);
	static void unstuff(const std::vector<int32_t> &stuffed, const std::vector<int32_t> &sizes, int i, std::vector<int32_t> &v);
	static void zzEnc(std::vector<uint32_t> &enc, const std::vector<int32_t> &v);
	static void zzDec(const std::vector<uint32_t> &enc, std::vector<int32_t> &v);
};


template<typename tp_Type> std::ostream& VectorIO::printT(std::ostream &os, const std::vector<tp_Type> &v) {
	using namespace std;
	cout << "(";
	for (int i=0; i<v.size(); ++i) cout << ((i > 0) ? ", " : "") << v[i];
	cout << ")";
	return cout;
}


template<typename tp_Type> void VectorIO::stuffT(std::vector<tp_Type> &stuffed, std::vector<int32_t> &sizes, const std::vector<tp_Type> &v) {
	int offset = stuffed.size();
	size_t requiredSize = offset + v.size();
	if (stuffed.capacity() < requiredSize)
		stuffed.reserve(std::max(stuffed.capacity() * 2, requiredSize));
	stuffed.resize(requiredSize);
	for (int i = 0; i < v.size(); ++i) stuffed[offset + i] = v[i];
	if (sizes.capacity() < sizes.size() + 1) sizes.reserve(std::max(sizes.capacity() * 2, sizes.size() + 1));
	sizes.push_back(v.size());
}


template<typename tp_Type> void VectorIO::unstuffT(const std::vector<tp_Type> &stuffed, const std::vector<int32_t> &sizes, int i, std::vector<tp_Type> &v) {
	assert (i < sizes.size());
	int offset = 0; for (int j = 0; j < i; ++j) offset += sizes[j];
	v.resize(sizes[i]);
	for (int j = 0; j < v.size(); ++j) v[j] = stuffed[offset + j];
}


template<typename tp_Type, typename tp_Type2> void VectorIO::zzEncT(std::vector<tp_Type> &enc, const std::vector<tp_Type2> &v) {
	if (enc.size() != v.size()) {
		if (enc.size() > v.size()) enc.reserve(enc.size());
		enc.resize(v.size());
	}
	for (int i=0; i<v.size(); ++i) enc[i] = Math::zzEnc(v[i]);
}


template<typename tp_Type, typename tp_Type2> void VectorIO::zzDecT(const std::vector<tp_Type> &enc, std::vector<tp_Type2> &v) {
	if (v.size() != enc.size()) {
		if (v.size() > enc.size()) v.reserve(v.size());
		v.resize(enc.size());
	}
	for (int i=0; i<enc.size(); ++i) v[i] = Math::zzDec(enc[i]);
}



} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::VectorIO-;
#endif

#endif // SIGPX_VECTORIO_H
