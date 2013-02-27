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


#ifndef SIGPX_WINDOWFCTS_H
#define SIGPX_WINDOWFCTS_H

#include <TMath.h>

#include "Filter.h"


namespace sigpx {


template<typename tp_Type> class HammingWindow: public Iterator<tp_Type> {
protected:
	const size_t m_N;
	size_t m_pos;
public:
	bool empty() const { return m_pos >= m_N; }
	size_t size() const { return m_N - m_pos; }

	tp_Type next() { return 0.54 - 0.46 * cos((2*TMath::Pi() * m_pos++) / (m_N - 1)); }

	HammingWindow(size_t n): m_N(n), m_pos(0) {}
};


} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::HammingWindow<float>;
#pragma link C++ class sigpx::HammingWindow<double>;
#endif

#endif // SIGPX_WINDOWFCTS_H
