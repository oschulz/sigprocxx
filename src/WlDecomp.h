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


#ifndef SIGPX_MCR_WLDECOMP_H
#define SIGPX_MCR_WLDECOMP_H

#include <string>
#include <vector>
#include "stdint.h"


namespace sigpx {


class WlDecomp {
protected:
	class State;

public:
	WlDecomp() {}
	virtual ~WlDecomp() {}
};



class WlDecomp1 : public WlDecomp {
protected:
	class State1;
	State1 *m_state;

public:
	WlDecomp1(const std::string &waveletSpec, int maxLevel = 0);
	virtual ~WlDecomp1();
};



class WlDecomp1I: public WlDecomp1 {
public:
	typedef int32_t Num;
	
	int apply(std::vector<Num> &data) const;
	int applyInv(std::vector<Num> &data) const;

	WlDecomp1I(const std::string &waveletSpec, int maxLevel = 0): WlDecomp1(waveletSpec) {}
};


class WlDecomp1F: public WlDecomp1 {
public:
	typedef float Num;
	
	int apply(std::vector<Num> &data) const;
	int applyInv(std::vector<Num> &data) const;

	WlDecomp1F(const std::string &waveletSpec, int maxLevel = 0): WlDecomp1(waveletSpec) {}
};


} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::WlDecomp-;
#pragma link C++ class sigpx::WlDecomp1-;
#pragma link C++ class sigpx::WlDecomp1I-;
#pragma link C++ class sigpx::WlDecomp1F-;
#endif

#endif // SIGPX_MCR_WLDECOMP_H
