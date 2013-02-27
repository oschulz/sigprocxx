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


#include "WlDecomp.h"

#include <blitzwave/WaveletDecomp.h>

#include "util.h"
#include "VectorOps.h"

using namespace std;


namespace {
	using namespace std;
	using namespace blitz;
	using namespace bwave;

	template<typename Num> Array<Num, 1> blitzArrayT(std::vector<Num> &data) {
		// Create a blitz array on data, (data is used directly, not copied):
		Num *buffer = sigpx::VectorOps::buffer(data);
		int size = data.size();
		return Array<Num, 1>(buffer, shape(size), neverDeleteData);
	}

	template<typename Num> int decomp1T(const WaveletDecomp<1> &decomp, std::vector<Num> &data) {
		// Apply the decomposition on the data (in situ):
		Array<Num, 1> array = blitzArrayT(data);
		return decomp.apply(array)(0);
	}

	template<typename Num> int recomp1T(const WaveletDecomp<1> &decomp, std::vector<Num> &data) {
		// Apply the inverse of the decomposition on the data (in situ):
		Array<Num, 1> array = blitzArrayT(data);
		return decomp.applyInv(array)(0);
	}
}



namespace sigpx {

class WlDecomp::State {
public:
	static const bwave::Wavelet& getWavelet(const std::string &waveletSpec);
	const bwave::Wavelet &wavelet;
	State(const std::string &waveletSpec) : wavelet(getWavelet(waveletSpec)) {}
};

const bwave::Wavelet& WlDecomp::State::getWavelet(const std::string &waveletSpec) {
	using namespace bwave;
	if (waveletSpec == "HAAR") return WL_HAAR;
	else if (waveletSpec == "D_4") return WL_D_4;
	else if (waveletSpec == "LEG_5_3") return WL_LEG_5_3;
	else if (waveletSpec == "CUBIC_SPLINE") return WL_CUBIC_SPLINE;
	else if (waveletSpec == "CDF_1_1") return WL_CDF_1_1;
	else if (waveletSpec == "CDF_2_2") return WL_CDF_2_2;
	else if (waveletSpec == "CDF_3_1") return WL_CDF_3_1;
	else if (waveletSpec == "CDF_3_3") return WL_CDF_3_3;
	else if (waveletSpec == "CDF_4_2") return WL_CDF_4_2;
	else if (waveletSpec == "CDF_9_7") return WL_CDF_97;
	else throw invalid_argument(string("Unsupported wavelet type: ") + waveletSpec);
}


class WlDecomp1::State1 : public WlDecomp::State {
public:
	bwave::WaveletDecomp<1> decomp;

	State1(const std::string &waveletSpec, int maxLevel)
		: State(waveletSpec), decomp(wavelet, bwave::NONSTD_DECOMP, maxLevel)
	{}
};



WlDecomp1::WlDecomp1(const std::string &waveletSpec, int maxLevel)
	: m_state(new State1(waveletSpec, maxLevel))
{}


WlDecomp1::~WlDecomp1() {
	if (m_state != 0) delete m_state;
}



int WlDecomp1F::apply(std::vector<Num> &data) const
	{ decomp1T(m_state->decomp, data); }

int WlDecomp1F::applyInv(std::vector<Num> &data) const
	{ recomp1T(m_state->decomp, data); }



int WlDecomp1I::apply(std::vector<Num> &data) const
	{ decomp1T(m_state->decomp, data); }

int WlDecomp1I::applyInv(std::vector<Num> &data) const
	{ recomp1T(m_state->decomp, data); }


} // namespace sigpx
