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
#include <limits>
#include <cstddef>
#include <cassert>
#include <iostream>
#include <sstream>
#include <stdint.h>

#include <TH1.h>


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
	
	///	@brief	Returns 0 if no data/entries
	virtual bool empty() const { return size() > 0; }
	
	///	@brief	Pure virtual, (Returns number of steps left to the maximum of the iterations in child class)
	virtual size_t size() const = 0;

	///	@brief	Pure virtual. (Returns number of steps left to the maximum of the iterations in child class)
	virtual tp_Type next() = 0;
	
	///	@brief	Resizes trg to n and fill it with data of attached vector
	///
	///	@par	trg	Vector to be filled
	///	@par	n	Number of entries to be filled into trg
	inline void fillTo(std::vector<tp_Type> &trg, size_t n) {
		assert(n <= size());
		trg.resize(n);
		for (size_t i=0; i<n; ++i) trg[i] = next();
	}

	///	@brief	Fills trig with data of attached vector
	///	@par	trg	Vector to be filled
	inline void fillTo(std::vector<tp_Type> &trg) { fillTo(trg, size()); }
	
	///	@brief	Fills TH1I histogram with data of attached vector
	///	@par	hist	Histogram to be filled
	inline void fillTo(TH1I &hist) { while (!empty()) hist.Fill(next()); }

	///	@brief	Fills TH1F histogram with data of attached vector
	///	@par	hist	Histogram to be filled
	inline void fillTo(TH1F &hist) { while (!empty()) hist.Fill(next()); }
	
	///	@brief	Finds position of value in attached vector
	///	@par	x	Value to be searched for
	/// Iterator will be advanced to the point where the value was found after this.
	inline ssize_t find(tp_Type x) {
		ssize_t pos = 0;
		while (!empty()) { if (next() == x) return pos; else ++pos; }
		return -1;
	}

	///	@brief	Find maximum of attached vector
	/// Iterator will be empty after this
	inline tp_Type max() {
		tp_Type result = std::numeric_limits<tp_Type>::min();
		while(!empty()) {
			tp_Type x = tp_Type(next());
			if (x > result) result = x;
		}
		return result;
	}

	///	@brief	Find minimum of  attached vector
	/// Iterator will be empty after this
	inline tp_Type min() {
		tp_Type result = std::numeric_limits<tp_Type>::max();
		while(!empty()) {
			tp_Type x = tp_Type(next());
			if (x < result) result = x;
		}
		return result;
	}

	///	@brief	Returns sum of entries from current entry till end of iteration
	/// Iterator will be empty after this
	inline double sum() {
		double result = 0;
		while(!empty()) result += double(next());
		return result;
	}
	
	///	@brief	Returns mean of entries from current iteration till end of iteration
	/// Iterator will be empty after this
	inline double mean() {
		double n = size();
		return sum() / n;
	}

	///	@brief	Returns scalar product of  vector v with attached vector
	///	@par	v	Vector to do scalar product with
	/// Iterator will be advanced after this by size of v steps
	inline double sprod(const std::vector<tp_Type> v) {
		double acc = 0;
		for (size_t i = 0; i < v.size(); ++i) acc += next() * v[i];
		return acc;
	}

	///	@brief	Prints contents of attached vector to stream
	///	@par	os	Output stream to print to
	std::ostream& print(std::ostream &os);
	
	///	@brief	Returns contents of attached vector as string
	std::string toString();

	///	@brief	Returns copy of  attached vector (from current iteration to end of iteration)
	inline std::vector<tp_Type> toVector()
		{ std::vector<tp_Type> trg; fillTo(trg, size()); return trg; }
	
		
	///	@brief	Destructor
	virtual ~Iterator() {}
};


template<typename tp_Type> std::ostream& Iterator<tp_Type>::print(std::ostream &os) {
	using namespace std;
	bool first = true;
	os << "(";
	if (sizeof(tp_Type) > 1) while (!empty()) {
		os << (!first ? ", " : "") << next();
		first = false;
	} while (!empty()) {
		os << (!first ? ", " : "") << int(next());
		first = false;
	}
	os << ")";
	return os;
}


template<typename tp_Type> std::string Iterator<tp_Type>::toString() {
	using namespace std;
	stringstream out;
	print(out);
	return out.str();
}



template<typename tp_Type> class RangeIterator: public Iterator<tp_Type> {
protected:
	const tp_Type m_until;
	const tp_Type m_step;
	tp_Type m_current;
public:
	bool empty() const { return m_current >= m_until; }
	size_t size() const { return (m_current < m_until) ? (m_until - m_current) / m_step : 0; }

	tp_Type next() { tp_Type result = m_current; m_current += m_step; return result; }

	RangeIterator(tp_Type from, tp_Type until, tp_Type step = 1): m_until(until), m_step(step), m_current(from) {}
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
