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


	template<typename Num> Array<Num, 1> blitzArrayT(const std::vector<Num> &data) {
		// Create a blitz array on data, (data is used directly, not copied):
		const Num *buffer = sigpx::VectorOps::buffer(data);
		int size = data.size();
		return Array<Num, 1>(const_cast<Num*>(buffer), shape(size), neverDeleteData);
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


	void getCoeffLocation1(const WaveletDecomp<1> &decomp, size_t dataSize, int index, size_t &from, size_t &to, size_t &stride) {
		int i = index;
		// Remark: i>=0 specifies phi(i) coeff,
		//          i<0 specifies psi(-i) coeff;
		int n = dataSize;
		
		if (decomp.storageMode()==NESTED_COEFFS) {
			// Remark: coefficient location in data(l)
			//         for phi(i):       0 <= l <= n-1, stride = 2^i
			//         for psi(i): 2^(i-1) <= l <= n-1, stride = 2^i
			stride = i>=0 ? 1 << i : 1 << -i;
			from = ( i>=0 ? 0 : 1 << (-i-1) );
			to = from + (n-1 - from) / stride * stride;
		} else if (decomp.storageMode()==SEPARATED_COEFFS) {
			// Remark: coefficient location in data(l)
			//         for phi(i):           0 <= l <= ceil(n/2^i)-1
			//         for psi(i): ceil(n/2^i) <= l <= ceil(n/2^(i-1))-1
			// Remark: ceil(n/2^i) = (n + (1<<i) - 1) >> i;
			stride = 1;
			from = ( i>=0 ? 0 : (n + (1<<-i) - 1) >> -i );
			to = ( i>=0 ? ( (n + (1<<i) - 1) >> i) - 1
			                : ( (n + (1<<(-i-1)) - 1) >> (-i-1) ) - 1 );
		} else assert(false);

		assert( from <= to);
		assert( to < n);
	}


	template<class Num> sigpx::VectorView<Num> getCoeffs1T(const WaveletDecomp<1> &decomp, std::vector<Num> &data, int index) {
		size_t from = 0, to = 0, stride = 0;
		getCoeffLocation1(decomp, data.size(), index, from, to, stride);
		return sigpx::VectorView<Num>(data, from, to + stride, stride);
	}


	template<typename Num> void getIndices1T(const WaveletDecomp<1> &decomp, const std::vector<Num> &data, std::vector<int> &indices) {
		Array<Num, 1> array = blitzArrayT(data);
		Array<TinyVector<int,1>, 1> idx( decomp.indices(array) );
		indices.resize(idx.rows());
		for (int i=0; i<idx.rows(); ++i) indices[i] = idx(i)(0);
	}



	template<typename Num> void getIndexAxis1T(const WaveletDecomp<1> &decomp, const std::vector<Num> &data, std::vector<int> &axis) {
		axis.resize(data.size());
		std::vector<int> indices;
		getIndices1T(decomp, data, indices);
		for (int i=0; i<indices.size(); ++i) {
			int idx = indices[i];
			size_t from=0, to=0, stride=0;
			getCoeffLocation1(decomp, data.size(), idx, from, to, stride);
			for (size_t j = from; j <= to; j += stride) axis[j] = idx;
		}
	}

	template<typename Num> void copyCoeffsT(const WaveletDecomp<1> &decomp, const std::vector<Num> &data, const WaveletDecomp<1> &decomp2, std::vector<Num> &data2) {
		std::vector<int> indices;
		getIndices1T(decomp, data, indices);
		for (int i=0; i<indices.size(); ++i) {
			int idx = indices[i];
			size_t from=0, to=0, stride=0;
			getCoeffLocation1(decomp, data.size(), idx, from, to, stride);
			size_t from2=0, to2=0, stride2=0;
			getCoeffLocation1(decomp2, data2.size(), idx, from2, to2, stride2);
			size_t j = from, j2 = from2;
			while ((j <= to) && (j2 <= to2)) {
				data2[j2] = data[j];
				j += stride; j2 += stride2;
			}
		}
	}


} // namespace



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
	static const bwave::CoeffStorage getCoeffStorage(const std::string &coeffStorage);

	int decMaxLevel;
	bwave::CoeffStorage decCoeffStorage;
	bwave::WaveletDecomp<1> decomp;

	State1(const std::string &waveletSpec, int maxLevel, const std::string &coeffStorage)
		: State(waveletSpec), decMaxLevel(maxLevel),
		  decCoeffStorage(getCoeffStorage(coeffStorage)),
		  decomp(wavelet, bwave::NONSTD_DECOMP, decMaxLevel, decCoeffStorage)
	{}
};


const bwave::CoeffStorage WlDecomp1::State1::getCoeffStorage(const std::string &coeffStorage) {
	using namespace bwave;
	if (coeffStorage == "nested") return NESTED_COEFFS;
	else if (coeffStorage == "separated") return SEPARATED_COEFFS;
	else throw invalid_argument(string("Invalid coefficient storage scheme: ") + coeffStorage);
}


double WlDecomp1::normFactor(int index) const {
	using namespace blitz;
	TinyVector<int, 1> idx(index);
	return m_state->decomp.normFactor(idx);
}


void WlDecomp1::getForwardFunc(size_t size,	int scale, int trans, std::vector<float> &func) const {
	blitz::Array<double, 1> array = m_state->wavelet.forwardFkt(size, scale, trans);
	func.resize(array.rows());
	for (int i = 0; i < array.rows(); ++i) func[i] = array(i); 
}


void WlDecomp1::getInverseFunc(size_t size,	int scale, int trans, std::vector<float> &func) const {
	blitz::Array<double, 1> array = m_state->wavelet.inverseFkt(size, scale, trans);
	func.resize(array.rows());
	for (int i = 0; i < array.rows(); ++i) func[i] = array(i); 
}


WlDecomp1::WlDecomp1(const std::string &waveletSpec, int maxLevel, const std::string &coeffStorage)
	: m_state(new State1(waveletSpec, maxLevel, coeffStorage))
{}


WlDecomp1::~WlDecomp1() {
	if (m_state != 0) delete m_state;
}



int WlDecomp1I::apply(std::vector<Num> &data) const
	{ decomp1T(m_state->decomp, data); }

int WlDecomp1I::applyInv(std::vector<Num> &data) const
	{ recomp1T(m_state->decomp, data); }

void WlDecomp1I::getIndices(const std::vector<Num> &data, std::vector<int> &indices) const
	{ getIndices1T(m_state->decomp, data, indices); }

void WlDecomp1I::getIndexAxis(const std::vector<Num> &data, std::vector<int> &axis) const
	{ getIndexAxis1T(m_state->decomp, data, axis); }

void WlDecomp1I::getCoeffLocation(const std::vector<Num> &data, int index, size_t &from, size_t &to, size_t &stride) const
	{ getCoeffLocation1(m_state->decomp, data.size(), index, from, to, stride); }

VectorView<int32_t> WlDecomp1I::getCoeffs(std::vector<Num> &data, int index) const
	{ getCoeffs1T(m_state->decomp, data, index); }
	

void WlDecomp1I::exportCoeffs(const std::vector<Num> &src, const std::string &coeffStorage, std::vector<Num> &trg) const {
	trg.resize(src.size());
	bwave::WaveletDecomp<1> decomp2(m_state->wavelet, bwave::NONSTD_DECOMP,
		m_state->decMaxLevel, m_state->getCoeffStorage(coeffStorage));
	copyCoeffsT<Num>(m_state->decomp, src, decomp2, trg);
}

void WlDecomp1I::importCoeffs(std::vector<Num> &trg, const std::string &coeffStorage, const std::vector<Num> &src) const {
	trg.resize(src.size());
	bwave::WaveletDecomp<1> decomp2(m_state->wavelet, bwave::NONSTD_DECOMP,
		m_state->decMaxLevel, m_state->getCoeffStorage(coeffStorage));
	copyCoeffsT<Num>(decomp2, src, m_state->decomp, trg);
}


int WlDecomp1F::apply(std::vector<Num> &data) const
	{ decomp1T(m_state->decomp, data); }

int WlDecomp1F::applyInv(std::vector<Num> &data) const
	{ recomp1T(m_state->decomp, data); }

void WlDecomp1F::getIndices(const std::vector<Num> &data, std::vector<int> &indices) const
	{ getIndices1T(m_state->decomp, data, indices); }

void WlDecomp1F::getIndexAxis(const std::vector<Num> &data, std::vector<int> &axis) const
	{ getIndexAxis1T(m_state->decomp, data, axis); }

void WlDecomp1F::getCoeffLocation(const std::vector<Num> &data, int index, size_t &from, size_t &to, size_t &stride) const
	{ getCoeffLocation1(m_state->decomp, data.size(), index, from, to, stride); }

VectorView<float> WlDecomp1F::getCoeffs(std::vector<Num> &data, int index) const
	{ getCoeffs1T(m_state->decomp, data, index); }

void WlDecomp1F::exportCoeffs(const std::vector<Num> &src, const std::string &coeffStorage, std::vector<Num> &trg) const {
	trg.resize(src.size());
	bwave::WaveletDecomp<1> decomp2(m_state->wavelet, bwave::NONSTD_DECOMP,
		m_state->decMaxLevel, m_state->getCoeffStorage(coeffStorage));
	copyCoeffsT<Num>(m_state->decomp, src, decomp2, trg);
}

void WlDecomp1F::importCoeffs(std::vector<Num> &trg, const std::string &coeffStorage, const std::vector<Num> &src) const {
	trg.resize(src.size());
	bwave::WaveletDecomp<1> decomp2(m_state->wavelet, bwave::NONSTD_DECOMP,
		m_state->decMaxLevel, m_state->getCoeffStorage(coeffStorage));
	copyCoeffsT<Num>(decomp2, src, m_state->decomp, trg);
}


} // namespace sigpx
