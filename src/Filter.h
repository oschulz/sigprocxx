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


#ifndef SIGPX_FILTER_H
#define SIGPX_FILTER_H

#include <functional>
#include <vector>
#include <cstddef>
#include <cassert>
#include <stdint.h>


namespace sigpx {


template<typename From, typename To> class Mapper: public std::unary_function<From, To> {
public:
	virtual To operator()(From x) = 0;

	// src and target may be the same vector if types From and To are equal
	void operator()(const std::vector<From> &src, std::vector<To> &trg);

	std::vector<To> operator()(const std::vector<From> &src);

	virtual ~Mapper() {}
};


template<typename From, typename To> void Mapper<From, To>::operator()(const std::vector<From> &src, std::vector<To> &trg) {
	trg.resize(src.size());
	for (size_t i=0; i<src.size(); ++i) trg[i] = operator()(src[i]);
}


template<typename From, typename To> std::vector<To> Mapper<From, To>::operator()(const std::vector<From> &src)
	{ std::vector<To> trg; operator()(src, trg); return trg; }




template<typename tp_Type> class Filter: public Mapper<tp_Type, tp_Type> {
public:
	virtual tp_Type operator()(tp_Type x) = 0;

	virtual ~Filter() {}
};



template<typename tp_Type> class Iterator {
public:
	virtual bool empty() const { return size() > 0; }
	virtual size_t size() const = 0;

	virtual tp_Type next() = 0;
	
	inline void fillTo(std::vector<tp_Type> &trg, size_t n) {
		assert(n <= size());
		trg.resize(n);
		for (size_t i=0; i<n; ++i) trg[i] = next();
	}

	inline void fillTo(std::vector<tp_Type> &trg) { fillTo(trg, size()); }

	inline std::vector<tp_Type> toVector()
		{ std::vector<tp_Type> trg; fillTo(trg, size()); return trg; }
	
	virtual ~Iterator() {}
};


template<typename tp_Type> class RangeIterator: public Iterator<tp_Type> {
protected:
	const tp_Type until, step;
	size_t pos;
public:
	bool empty() const { return pos >= until; }
	size_t size() const { return (pos < until) ? (until - pos) / step : 0; }

	tp_Type next() { tp_Type result = pos; pos += step; return result; }

	RangeIterator(tp_Type from, tp_Type until, tp_Type step = 1): until(until), step(step), pos(0) {}
};


} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::Mapper<int8_t,  int8_t>-;
#pragma link C++ class sigpx::Mapper<int16_t, int16_t>-;
#pragma link C++ class sigpx::Mapper<int16_t, int32_t>-;
#pragma link C++ class sigpx::Mapper<int16_t, float>-;
#pragma link C++ class sigpx::Mapper<int16_t, double>-;
#pragma link C++ class sigpx::Mapper<int32_t, int32_t>-;
#pragma link C++ class sigpx::Mapper<int32_t, int16_t>-;
#pragma link C++ class sigpx::Mapper<int32_t, float>-;
#pragma link C++ class sigpx::Mapper<int32_t, double>-;
#pragma link C++ class sigpx::Mapper<int64_t, int64_t>-;
#pragma link C++ class sigpx::Mapper<float,   float>-;
#pragma link C++ class sigpx::Mapper<float,   double>-;
#pragma link C++ class sigpx::Mapper<double,  double>-;
#pragma link C++ class sigpx::Mapper<double,  float>-;

#pragma link C++ class sigpx::Filter<int8_t>-;
#pragma link C++ class sigpx::Filter<int16_t>-;
#pragma link C++ class sigpx::Filter<int32_t>-;
#pragma link C++ class sigpx::Filter<int64_t>-;
#pragma link C++ class sigpx::Filter<float>-;
#pragma link C++ class sigpx::Filter<double>-;

#pragma link C++ class sigpx::Iterator<int8_t>-;
#pragma link C++ class sigpx::Iterator<int16_t>-;
#pragma link C++ class sigpx::Iterator<int32_t>-;
#pragma link C++ class sigpx::Iterator<int64_t>-;
#pragma link C++ class sigpx::Iterator<float>-;
#pragma link C++ class sigpx::Iterator<double>-;

#pragma link C++ class sigpx::RangeIterator<int32_t>-;
#pragma link C++ class sigpx::RangeIterator<float>-;
#pragma link C++ class sigpx::RangeIterator<double>-;
#endif

#endif // SIGPX_FILTER_H
