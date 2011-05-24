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


#include "VectorOps.h"

#include <iostream>



using namespace std;


namespace sigpx {

std::ostream& VectorOps::print(std::ostream &os, const std::vector<uint8_t> &v) {
	cout << "(";
	for (size_t i = 0; i < v.size(); ++i) cout << ((i > 0) ? ", " : "") << uint16_t(v[i]);
	cout << ")";
	return cout;
}

std::ostream& VectorOps::print(std::ostream &os, const std::vector<int8_t> &v) {
	cout << "(";
	for (size_t i = 0; i < v.size(); ++i) cout << ((i > 0) ? ", " : "") << int16_t(v[i]);
	cout << ")";
	return cout;
}

void VectorOps::stuff(std::vector<char> &stuffed, std::vector<int32_t> &sizes, const std::vector<char> &v)
	{ stuffT(stuffed, sizes, v); }

void VectorOps::unstuff(const std::vector<char> &stuffed, const std::vector<int32_t> &sizes, size_t i, std::vector<char> &v)
	{ unstuffT(stuffed, sizes, i, v); }


std::ostream& VectorOps::print(std::ostream &os, const std::vector<int16_t> &v)
	{ return printT(os, v); }

std::ostream& VectorOps::print(std::ostream &os, const std::vector<uint16_t> &v)
	{ return printT(os, v); }

void VectorOps::stuff(std::vector<int16_t> &stuffed, std::vector<int32_t> &sizes, const std::vector<int16_t> &v)
	{ stuffT(stuffed, sizes, v); }

void VectorOps::unstuff(const std::vector<int16_t> &stuffed, const std::vector<int32_t> &sizes, size_t i, std::vector<int16_t> &v)
	{ unstuffT(stuffed, sizes, i, v); }


std::ostream& VectorOps::print(std::ostream &os, const std::vector<int32_t> &v)
	{ return printT(os, v); }

std::ostream& VectorOps::print(std::ostream &os, const std::vector<uint32_t> &v)
	{ return printT(os, v); }

void VectorOps::stuff(std::vector<int32_t> &stuffed, std::vector<int32_t> &sizes, const std::vector<int32_t> &v)
	{ stuffT(stuffed, sizes, v); }

void VectorOps::unstuff(const std::vector<int32_t> &stuffed, const std::vector<int32_t> &sizes, size_t i, std::vector<int32_t> &v)
	{ unstuffT(stuffed, sizes, i, v); }


} // namespace sigpx
