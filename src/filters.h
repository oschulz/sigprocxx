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


} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::DiffFilter<int8_t>-;
#pragma link C++ class sigpx::DiffFilter<uint8_t>-;
#pragma link C++ class sigpx::DiffFilter<int16_t>-;
#pragma link C++ class sigpx::DiffFilter<uint16_t>-;
#pragma link C++ class sigpx::DiffFilter<int32_t>-;
#pragma link C++ class sigpx::DiffFilter<uint32_t>-;
#pragma link C++ class sigpx::DiffFilter<int64_t>-;
#pragma link C++ class sigpx::DiffFilter<uint64_t>-;
#pragma link C++ class sigpx::DiffFilter<float>-;
#pragma link C++ class sigpx::DiffFilter<double>-;

#pragma link C++ class sigpx::SumFilter<int8_t>-;
#pragma link C++ class sigpx::SumFilter<uint8_t>-;
#pragma link C++ class sigpx::SumFilter<int16_t>-;
#pragma link C++ class sigpx::SumFilter<uint16_t>-;
#pragma link C++ class sigpx::SumFilter<int32_t>-;
#pragma link C++ class sigpx::SumFilter<uint32_t>-;
#pragma link C++ class sigpx::SumFilter<int64_t>-;
#pragma link C++ class sigpx::SumFilter<uint64_t>-;
#pragma link C++ class sigpx::SumFilter<float>-;
#pragma link C++ class sigpx::SumFilter<double>-;
#endif

#endif // SIGPX_FILTERS_H
