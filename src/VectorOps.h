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


#ifndef SIGPX_VECTOROPS_H
#define SIGPX_VECTOROPS_H

#include <iostream>
#include <vector>
#include <cassert>
#include <stdint.h>

#include <TGraph.h>

#include "filters.h"


namespace sigpx {


class VectorOps {
public:
	template<typename tp_Type> static std::ostream& printT(std::ostream &os, const std::vector<tp_Type> &v);

	template<typename tp_Type> static void stuffT(std::vector<tp_Type> &stuffed, std::vector<int32_t> &sizes, const std::vector<tp_Type> &v);

	template<typename tp_Type> static void unstuffT(const std::vector<tp_Type> &stuffed, const std::vector<int32_t> &sizes, size_t i, std::vector<tp_Type> &v);

	template<typename tp_Type, typename tp_Type2> inline static void copyT(const std::vector<tp_Type> &src, std::vector<tp_Type2> &trg) {
		trg.resize(src.size());
		for (size_t i = 0; i < src.size(); ++i) trg[i] = src[i];
	}

	static std::ostream& print(std::ostream &os, const std::vector<int8_t> &v);
	static std::ostream& print(std::ostream &os, const std::vector<uint8_t> &v);
	static std::ostream& print(std::ostream &os, const std::vector<int16_t> &v);
	static std::ostream& print(std::ostream &os, const std::vector<uint16_t> &v);
	static std::ostream& print(std::ostream &os, const std::vector<int32_t> &v);
	static std::ostream& print(std::ostream &os, const std::vector<uint32_t> &v);
	static std::ostream& print(std::ostream &os, const std::vector<float> &v);
	static std::ostream& print(std::ostream &os, const std::vector<double> &v);
	
	inline static int8_t* buffer(std::vector<int8_t> &v) { return &(v[0]); }
	inline static const int8_t* buffer(const std::vector<int8_t> &v) { return &(v[0]); }
	inline static uint8_t* buffer(std::vector<uint8_t> &v) { return &(v[0]); }
	inline static const uint8_t* buffer(const std::vector<uint8_t> &v) { return &(v[0]); }
	inline static int16_t* buffer(std::vector<int16_t> &v) { return &(v[0]); }
	inline static const int16_t* buffer(const std::vector<int16_t> &v) { return &(v[0]); }
	inline static uint16_t* buffer(std::vector<uint16_t> &v) { return &(v[0]); }
	inline static const uint16_t* buffer(const std::vector<uint16_t> &v) { return &(v[0]); }
	inline static int32_t* buffer(std::vector<int32_t> &v) { return &(v[0]); }
	inline static const int32_t* buffer(const std::vector<int32_t> &v) { return &(v[0]); }
	inline static uint32_t* buffer(std::vector<uint32_t> &v) { return &(v[0]); }
	inline static const uint32_t* buffer(const std::vector<uint32_t> &v) { return &(v[0]); }
	inline static float* buffer(std::vector<float> &v) { return &(v[0]); }
	inline static const float* buffer(const std::vector<float> &v) { return &(v[0]); }
	inline static double* buffer(std::vector<double> &v) { return &(v[0]); }
	inline static const double* buffer(const std::vector<double> &v) { return &(v[0]); }

	static void stuff(std::vector<char> &stuffed, std::vector<int32_t> &sizes, const std::vector<char> &v);
	static void stuff(std::vector<int16_t> &stuffed, std::vector<int32_t> &sizes, const std::vector<int16_t> &v);
	static void stuff(std::vector<int32_t> &stuffed, std::vector<int32_t> &sizes, const std::vector<int32_t> &v);

	static void unstuff(const std::vector<char> &stuffed, const std::vector<int32_t> &sizes, size_t i, std::vector<char> &v);
	static void unstuff(const std::vector<int16_t> &stuffed, const std::vector<int32_t> &sizes, size_t i, std::vector<int16_t> &v);
	static void unstuff(const std::vector<int32_t> &stuffed, const std::vector<int32_t> &sizes, size_t i, std::vector<int32_t> &v);

	inline static void copy(const std::vector<int8_t> &src, std::vector<int8_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<int8_t> &src, std::vector<uint8_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<uint8_t> &src, std::vector<int8_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<int16_t> &src, std::vector<int16_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<int16_t> &src, std::vector<uint16_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<int16_t> &src, std::vector<int32_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<int16_t> &src, std::vector<float> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<int16_t> &src, std::vector<double> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<uint16_t> &src, std::vector<int16_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<int32_t> &src, std::vector<int32_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<int32_t> &src, std::vector<uint32_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<int32_t> &src, std::vector<int16_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<int32_t> &src, std::vector<float> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<int32_t> &src, std::vector<double> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<uint32_t> &src, std::vector<int32_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<float> &src, std::vector<float> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<float> &src, std::vector<double> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<float> &src, std::vector<int16_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<float> &src, std::vector<int32_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<double> &src, std::vector<double> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<double> &src, std::vector<float> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<double> &src, std::vector<int16_t> &trg) { copyT(src, trg); }
	inline static void copy(const std::vector<double> &src, std::vector<int32_t> &trg) { copyT(src, trg); }

	template<typename tp_Type> static TGraph* graphT(const std::vector<tp_Type> &x, const std::vector<tp_Type> &y);
	template<typename tp_Type> static TGraph* graphT(const std::vector<tp_Type> &y);

	static TGraph* graph(const std::vector<int16_t> &x, const std::vector<int16_t> &y);
	static TGraph* graph(const std::vector<int32_t> &x, const std::vector<int32_t> &y);
	static TGraph* graph(const std::vector<float> &x, const std::vector<float> &y);
	static TGraph* graph(const std::vector<double> &x, const std::vector<double> &y);

	static TGraph* graph(const std::vector<int16_t> &y);
	static TGraph* graph(const std::vector<int32_t> &y);
	static TGraph* graph(const std::vector<float> &y);
	static TGraph* graph(const std::vector<double> &y);

	static void draw(const std::vector<int16_t> &x, const std::vector<int16_t> &y, Option_t* chopt = "A*") { graph(x, y)->Draw(chopt); }
	static void draw(const std::vector<int32_t> &x, const std::vector<int32_t> &y, Option_t* chopt = "A*") { graph(x, y)->Draw(chopt); }
	static void draw(const std::vector<float> &x, const std::vector<float> &y, Option_t* chopt = "A*") { graph(x, y)->Draw(chopt); }
	static void draw(const std::vector<double> &x, const std::vector<double> &y, Option_t* chopt = "A*") { graph(x, y)->Draw(chopt); }

	static void draw(const std::vector<int16_t> &y, Option_t* chopt = "A*") { graph(y)->Draw(chopt); }
	static void draw(const std::vector<int32_t> &y, Option_t* chopt = "A*") { graph(y)->Draw(chopt); }
	static void draw(const std::vector<float> &y, Option_t* chopt = "A*") { graph(y)->Draw(chopt); }
	static void draw(const std::vector<double> &y, Option_t* chopt = "A*") { graph(y)->Draw(chopt); }
};


template<typename tp_Type> std::ostream& VectorOps::printT(std::ostream &os, const std::vector<tp_Type> &v) {
	using namespace std;
	cout << "(";
	for (size_t i = 0; i < v.size(); ++i) cout << ((i > 0) ? ", " : "") << v[i];
	cout << ")";
	return cout;
}


template<typename tp_Type> void VectorOps::stuffT(std::vector<tp_Type> &stuffed, std::vector<int32_t> &sizes, const std::vector<tp_Type> &v) {
	size_t offset = stuffed.size();
	size_t requiredSize = offset + v.size();
	if (stuffed.capacity() < requiredSize)
		stuffed.reserve(std::max(stuffed.capacity() * 2, requiredSize));
	stuffed.resize(requiredSize);
	for (size_t i = 0; i < v.size(); ++i) stuffed[offset + i] = v[i];
	if (sizes.capacity() < sizes.size() + 1) sizes.reserve(std::max(sizes.capacity() * 2, sizes.size() + 1));
	sizes.push_back(v.size());
}


template<typename tp_Type> void VectorOps::unstuffT(const std::vector<tp_Type> &stuffed, const std::vector<int32_t> &sizes, size_t i, std::vector<tp_Type> &v) {
	assert (i < sizes.size());
	size_t offset = 0; for (size_t j = 0; j < i; ++j) offset += sizes[j];
	v.resize(sizes[i]);
	for (size_t j = 0; j < v.size(); ++j) v[j] = stuffed[offset + j];
}


template<typename tp_Type> TGraph* VectorOps::graphT(const std::vector<tp_Type> &x, const std::vector<tp_Type> &y) {
	assert(x.size() == y.size());
	return new TGraph(x.size(), VectorOps::buffer(x), VectorOps::buffer(y));
}


template<typename tp_Type> TGraph* VectorOps::graphT(const std::vector<tp_Type> &y) {
	std::vector<tp_Type> x; RangeIterator<tp_Type>(0, y.size()).fillTo(x);
	return graphT(x, y);
}


} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::VectorOps-;
#endif

#endif // SIGPX_VECTOROPS_H
