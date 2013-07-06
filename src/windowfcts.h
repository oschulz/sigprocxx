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


#ifndef SIGPX_WINDOWFCTS_H
#define SIGPX_WINDOWFCTS_H

#include <TMath.h>

#include "Filter.h"


namespace sigpx {

///@brief	class containing Hamming Window
template<typename tp_Type> class HammingWindow: public Iterator<tp_Type> {
protected:
///	Size of the Hamming Window
	const size_t m_N;
///	current position in Window; initialized with 0
	size_t m_pos;
public:
	bool empty() const { return m_pos >= m_N; }
///	@brief	Returns remaining window size
	size_t size() const { return m_N - m_pos; }

///	@brief	Returns value of the current position and incremets m_pos after that
	tp_Type next() { return 0.54 - 0.46 * cos((2*TMath::Pi() * m_pos++) / (m_N - 1)); }

///	@brief	Construtor
///	@param	n	size of the Hamming Window
///	Initializes a Hamming Window of size n and current position 0
	HammingWindow(size_t n): m_N(n), m_pos(0) {}
};


} // namespace sigpx

#endif // SIGPX_WINDOWFCTS_H
