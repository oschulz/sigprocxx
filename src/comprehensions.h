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
#include <cmath>
#include <stdint.h>

#include <TLine.h>
#include <TMath.h>

#include "Filter.h"
#include "util.h"


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


template<typename tp_Type> class FindIntersect {
protected:
	tp_Type m_result; size_t m_index;

public:
	tp_Type result() const { return m_result; }
	size_t index() const { return m_index; }

	FindIntersect(Iterator<tp_Type> &it, tp_Type threshold, size_t nFilt = 1)
		: m_result(std::numeric_limits<tp_Type>::max()), m_index(0)
	{
		if (nFilt < 1) nFilt = 1;
		if (it.empty()) throw std::runtime_error("No intersect found.");

		tp_Type x = it.next();
		size_t pos = 0;
		m_result = x;
		m_index = pos;
		size_t counter = 0;
		if (x != threshold) {
			bool findHigher = x < threshold;
			while(!it.empty()) {
				x = it.next();
				++pos;
				if ((findHigher && (x >= threshold)) || (!findHigher && (x <= threshold))) {
					if (counter == 0) {
						m_result = x;
						m_index = pos;
					}
					if (counter >= nFilt-1)  return;
					else ++counter;
				} else { counter = 0; }
			}
			throw std::runtime_error("No intersect found.");
		}
	}
};



template<typename tp_Type> class LinearStatistics {
protected:
	int32_t m_n;
	tp_Type m_fromX, m_fromY, m_toX, m_toY;
	tp_Type m_sumX, m_sumXSqr, m_sumY, m_sumYSqr, m_sumXY;
	
	bool m_first;
	
	static tp_Type nan() { return std::numeric_limits<tp_Type>::quiet_NaN(); }

public:
	int32_t n() const { return m_n; }

	tp_Type fromX() const { return m_fromX; }
	tp_Type fromY() const { return m_fromY; }
	tp_Type toX() const { return m_toX; }
	tp_Type toY() const { return m_toY; }

	tp_Type sumX() const { return m_sumX; }
	tp_Type sumY() const { return m_sumY; }
	tp_Type sumXSqr() const { return m_sumXSqr; }
	tp_Type sumYSqr() const { return m_sumYSqr; }
	tp_Type sumXY() const { return m_sumXY; }

	tp_Type meanX() const { return sumX() / n(); }
	tp_Type meanY() const { return sumY() / n(); }
	tp_Type varX() const { return sumXSqr() / n() - meanX() * meanX(); }
	tp_Type varY() const { return sumYSqr() / n() - meanY() * meanY(); }
	tp_Type covXY() const { return sumXY() / n() - meanX() * meanY(); }
	
	tp_Type errX() const { return sqrt( (sumXSqr() - sumX() * meanX()) / (n() - 1) ); }
	tp_Type errY() const { return sqrt( (sumYSqr() - sumY() * meanY()) / (n() - 1) ); }
	
	tp_Type corrXY() const { return covXY() / sqrt(varX() * varY()); }


	tp_Type slope() const { return covXY() / varX(); }
	tp_Type offset() const { return meanY() - slope() * meanX(); }

	tp_Type slopeErr(tp_Type confLevel = 0) const {
		tp_Type korr = (confLevel > 0) ? TMath::StudentQuantile((1 - confLevel)/2, n(), false) : 1;
		return korr * sqrt( (varX()*varY() - covXY()*covXY()) / (n() - 2) ) / varX();
	}

	tp_Type offsetErr(tp_Type confLevel = 0) const
		{ return slopeErr(confLevel) * sqrt(sumXSqr() / n()); }

		
	TLine* toLine(Color_t lineColor = kBlack);
	void draw(Option_t* chopt = "", Color_t lineColor = kBlack);

	LinearStatistics(Iterator<tp_Type> &itX, Iterator<tp_Type> &itY)
		: m_n(0),
		  m_fromX(nan()), m_fromY(nan()), m_toX(nan()), m_toY(nan()),
		  m_sumX(nan()), m_sumXSqr(nan()), m_sumY(nan()), m_sumYSqr(nan()), m_sumXY(nan()),
		  m_first(true)
	{
		while (!itX.empty() && !itY.empty()) {
			tp_Type x = itX.next();
			tp_Type y = itY.next();

			if (m_first) {
				m_sumX = 0; m_sumXSqr = 0; m_sumY = 0, m_sumYSqr = 0, m_sumXY = 0,
				m_fromX = x; m_fromY = y;
				m_first = false;
			}
			m_toX = x; m_toY = y;
			
			m_n += 1;
	
			m_sumX += x;
			m_sumXSqr += x*x;
			m_sumY += y;
			m_sumYSqr += y*y;
			m_sumXY += x*y;
		}
	}

	LinearStatistics()
		: m_n(0),
		  m_fromX(nan()), m_fromY(nan()), m_toX(nan()), m_toY(nan()),
		  m_sumX(nan()), m_sumXSqr(nan()), m_sumY(nan()), m_sumYSqr(nan()), m_sumXY(nan()),
		  m_first(false)
	{}
};


template<typename tp_Type> TLine* LinearStatistics<tp_Type>::toLine(Color_t lineColor) {
	TLine *line = new TLine(fromX(), offset() + slope() * fromX(), toX(), offset() + slope() * toX());
	line->SetLineColor(lineColor);
	return line;
}


template<typename tp_Type> void LinearStatistics<tp_Type>::draw(Option_t* chopt, Color_t lineColor) {
	toLine(lineColor)->Draw(chopt);
}




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

#pragma link C++ class sigpx::FindIntersect<int16_t>-;
#pragma link C++ class sigpx::FindIntersect<int32_t>-;
#pragma link C++ class sigpx::FindIntersect<float>-;
#pragma link C++ class sigpx::FindIntersect<double>-;

#pragma link C++ class sigpx::LinearStatistics<float>-;
#pragma link C++ class sigpx::LinearStatistics<double>-;
#endif

#endif // SIGPX_COMPREHENSIONS_H
