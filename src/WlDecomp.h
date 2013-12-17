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


#ifndef SIGPX_MCR_WLDECOMP_H
#define SIGPX_MCR_WLDECOMP_H

#include <string>
#include <vector>
#include <stdint.h>

#include "VectorView.h"


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
	double normFactor(int index) const;

	void getForwardFunc(size_t size,	int scale, int trans, std::vector<float> &func) const;
	void getInverseFunc(size_t size,	int scale, int trans, std::vector<float> &func) const;

	WlDecomp1(const WlDecomp1 &other);

	WlDecomp1(const WlDecomp1 &other, const std::string &coeffStorage);

	WlDecomp1(const std::string &waveletSpec, int maxLevel, const std::string &coeffStorage);

	virtual ~WlDecomp1();
};



class WlDecomp1I: public WlDecomp1 {
public:
	typedef int32_t Num;
	
	int apply(std::vector<Num> &data) const;
	int applyInv(std::vector<Num> &data) const;
	void getIndices(const std::vector<Num> &data, std::vector<int> &indices) const;
	void getIndexAxis(const std::vector<Num> &data, std::vector<int> &axis) const;
	void getCoeffLocation(const std::vector<Num> &data, int index, size_t &from, size_t &until, size_t &stride) const;
	VectorView<int32_t> getCoeffs(std::vector<Num> &data, int index) const;
	void exportCoeffs(const std::vector<Num> &src, const std::string &coeffStorage, std::vector<Num> &trg) const;
	void importCoeffs(std::vector<Num> &trg, const std::string &coeffStorage, const std::vector<Num> &src) const;

	WlDecomp1I(const WlDecomp1 &other, const std::string &coeffStorage)
		: WlDecomp1(other, coeffStorage) {}

	WlDecomp1I(const std::string &waveletSpec, int maxLevel = 0, const std::string &coeffStorage = "nested")
		: WlDecomp1(waveletSpec, maxLevel, coeffStorage) {}
};


class WlDecomp1F: public WlDecomp1 {
public:
	typedef float Num;
	
	int apply(std::vector<Num> &data) const;
	int applyInv(std::vector<Num> &data) const;
	void getIndices(const std::vector<Num> &data, std::vector<int> &indices) const;
	void getIndexAxis(const std::vector<Num> &data, std::vector<int> &axis) const;
	void getCoeffLocation(const std::vector<Num> &data, int index, size_t &from, size_t &until, size_t &stride) const;
	VectorView<float> getCoeffs(std::vector<Num> &data, int index) const;
	void exportCoeffs(const std::vector<Num> &src, const std::string &coeffStorage, std::vector<Num> &trg) const;
	void importCoeffs(std::vector<Num> &trg, const std::string &coeffStorage, const std::vector<Num> &src) const;

	WlDecomp1F(const WlDecomp1 &other, const std::string &coeffStorage)
		: WlDecomp1(other, coeffStorage) {}

	WlDecomp1F(const std::string &waveletSpec, int maxLevel = 0, const std::string &coeffStorage = "nested")
		: WlDecomp1(waveletSpec, maxLevel, coeffStorage) {}
};


} // namespace sigpx

#endif // SIGPX_MCR_WLDECOMP_H
