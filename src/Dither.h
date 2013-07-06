// Copyright (C) 2010-2011 Oliver Schulz <oliver.schulz@tu-dortmund.de>

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


#ifndef SIGPX_DITHER_H
#define SIGPX_DITHER_H

#include <cmath>
#include <stdint.h>

#include <TRandom3.h>

#include "Filter.h"


namespace sigpx {


///	@brief 	class that generates triangular noise
class TrigNoiseGen {
protected:
	TRandom3 rnd;
public:
  inline double operator()() {
    double r = rnd.Uniform();
    return (r >= 0.5) ? - sqrt(2 - 2*r) + 1 : sqrt(2*r) - 1;
  }
};



template<typename From, typename To> class Dither: public Mapper<From, To> {
protected:
	TrigNoiseGen s_noiseGen;
public:
	inline To operator()(From x) { return x + s_noiseGen(); }
};


} // namespace sigpx

#endif // SIGPX_DITHER_H
