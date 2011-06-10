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


#ifndef SIGPX_COMPREHENSIONS_H
#define SIGPX_COMPREHENSIONS_H

#include <limits>
#include <cstddef>
#include <stdint.h>

#include "Filter.h"


namespace sigpx {


template<typename tp_Type> class FindMax {
protected:
	tp_Type m_result; size_t m_index;

public:
	tp_Type result() const { return m_result; }
	size_t index() const { return m_index; }

	FindMax(Iterator<tp_Type> &it)
		: m_result(std::numeric_limits<tp_Type>::min()), m_index(0)
	{
		size_t pos = 0;
		while(!it.empty()) {
			tp_Type x = it.next();
			if (x > m_result) { m_result = x; m_index = pos; }
			++pos;
		}
	}
};


template<typename tp_Type> class FindMin {
protected:
	tp_Type m_result; size_t m_index;

public:
	tp_Type result() const { return m_result; }
	size_t index() const { return m_index; }

	FindMin(Iterator<tp_Type> &it)
		: m_result(std::numeric_limits<tp_Type>::max()), m_index(0)
	{
		size_t pos = 0;
		while(!it.empty()) {
			tp_Type x = it.next();
			if (x < m_result) { m_result = x; m_index = pos; }
			++pos;
		}
	}
};


} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::FindMax<int16_t>-;
#pragma link C++ class sigpx::FindMax<int32_t>-;
#pragma link C++ class sigpx::FindMax<float>-;
#pragma link C++ class sigpx::FindMax<double>-;

#pragma link C++ class sigpx::FindMin<int16_t>-;
#pragma link C++ class sigpx::FindMin<int32_t>-;
#pragma link C++ class sigpx::FindMin<float>-;
#pragma link C++ class sigpx::FindMin<double>-;
#endif

#endif // SIGPX_COMPREHENSIONS_H
