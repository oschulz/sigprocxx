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


#ifndef SIGPX_FILTERS_H
#define SIGPX_FILTERS_H

#include <stdint.h>

#include "Filter.h"


namespace sigpx {


template<typename tp_Type> class DiffFilter: public Filter<tp_Type> {
protected:
	tp_Type m_last;
public:
	const tp_Type last() const { return m_last; }
	tp_Type operator()(tp_Type x) { tp_Type res = x - m_last; m_last = x; return res; }
	DiffFilter() : m_last(0)  {}
};


template<typename tp_Type> class SumFilter: public Filter<tp_Type> {
protected:
	tp_Type m_sum;
public:
	const tp_Type sum() const { return m_sum; }
	tp_Type operator()(tp_Type x) { m_sum += x; return m_sum; }
	SumFilter() : m_sum(0)  {}
};


template<typename From, typename To> class MovingSum: public Iterator<To> {
protected:
	const std::vector<From> &m_v;
	size_t m_N;
	size_t m_pos;
	To m_sum;
	bool m_firstRun;

	void init() {
		if (m_pos + m_N-1 >= m_v.size()) m_pos = m_v.size();
		else {
			for (size_t i = 0; i < m_N-1; ++i) m_sum += m_v[m_pos + i];
			m_pos += m_N-1;
		}
	}

public:
	bool empty() const { return m_pos >= m_v.size(); }
	size_t size() const { return m_v.size() - m_pos; }

	To next() {
		if (m_firstRun) m_firstRun = false;
		else m_sum -= m_v[m_pos - m_N];
		m_sum += m_v[m_pos];
		m_pos ++;
		return m_sum;
	}

	MovingSum(const std::vector<From> &v, size_t N, size_t start)
		: m_v(v), m_N(N), m_pos(start), m_sum(0), m_firstRun(true)
		{ init(); }

	MovingSum(const std::vector<From> &v, size_t N)
		: m_v(v), m_N(N), m_pos(0), m_sum(0), m_firstRun(true)
		{ init(); }
};


template<typename tp_Type> class LinCal: public Filter<tp_Type> {
protected:
	const tp_Type m_a;
	const tp_Type m_b;
public:
	tp_Type a() const { return m_a; }
	tp_Type b() const { return m_b; }
	tp_Type operator()(tp_Type x) { return m_a * x + m_b; }
	LinCal(tp_Type ca, tp_Type cb) : m_a(ca), m_b(cb) {}
};


template<typename tp_Type> class RCFilter: public Filter<tp_Type> {
protected:
	const tp_Type alpha;
	tp_Type y_1;

public:
	inline tp_Type operator()(tp_Type x) {
		tp_Type y = alpha * x + (1 - alpha) * y_1;
		y_1 = y; return y;
	}

	RCFilter(tp_Type rc, tp_Type initWith = 0)
		: alpha(1 / (1 + 1/rc)), y_1(initWith) {}
};


template<typename tp_Type> class CRFilter: public Filter<tp_Type> {
protected:
	const tp_Type alpha;
	tp_Type x_1, y_1;

public:
	inline tp_Type operator()(tp_Type x) {
		tp_Type y = alpha * (y_1 + x - x_1);
		x_1 = x; y_1 = y; return y;
	}

	CRFilter(tp_Type rc, tp_Type initWith = 0)
		: alpha(1 / (1 + 1/rc)), x_1(initWith), y_1(0) {}
};


} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::DiffFilter<int8_t>-;
#pragma link C++ class sigpx::DiffFilter<int16_t>-;
#pragma link C++ class sigpx::DiffFilter<int32_t>-;
#pragma link C++ class sigpx::DiffFilter<int64_t>-;
#pragma link C++ class sigpx::DiffFilter<float>-;
#pragma link C++ class sigpx::DiffFilter<double>-;

#pragma link C++ class sigpx::SumFilter<int8_t>-;
#pragma link C++ class sigpx::SumFilter<int16_t>-;
#pragma link C++ class sigpx::SumFilter<int32_t>-;
#pragma link C++ class sigpx::SumFilter<int64_t>-;
#pragma link C++ class sigpx::SumFilter<float>-;
#pragma link C++ class sigpx::SumFilter<double>-;

#pragma link C++ class sigpx::MovingSum<int16_t, int32_t>-;
#pragma link C++ class sigpx::MovingSum<int32_t, int32_t>-;
#pragma link C++ class sigpx::MovingSum<float, float>-;
#pragma link C++ class sigpx::MovingSum<float, double>-;

#pragma link C++ class sigpx::LinCal<float>-;
#pragma link C++ class sigpx::LinCal<double>-;

#pragma link C++ class sigpx::RCFilter<float>-;
#pragma link C++ class sigpx::RCFilter<double>-;

#pragma link C++ class sigpx::CRFilter<float>-;
#pragma link C++ class sigpx::CRFilter<double>-;

#endif

#endif // SIGPX_FILTERS_H
