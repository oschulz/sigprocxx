// $Id$

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


#include "VLEncoding.h"

#include <iostream>


namespace sigpx {


void VLEncoding::enc(std::vector<char> &enc, const std::vector<int16_t> &v) { encSigned(enc, v); }
void VLEncoding::enc(std::vector<char> &enc, const std::vector<int32_t> &v) { encSigned(enc, v); }
void VLEncoding::enc(std::vector<char> &enc, const std::vector<int64_t> &v) { encSigned(enc, v); }

void VLEncoding::enc(std::vector<char> &enc, const std::vector<uint16_t> &v) { encUnsigned(enc, v); }
void VLEncoding::enc(std::vector<char> &enc, const std::vector<uint32_t> &v) { encUnsigned(enc, v); }
void VLEncoding::enc(std::vector<char> &enc, const std::vector<uint64_t> &v) { encUnsigned(enc, v); }

void VLEncoding::dec(const std::vector<char> &enc, std::vector<int16_t> &v) { decSigned(enc, v); }
void VLEncoding::dec(const std::vector<char> &enc, std::vector<int32_t> &v) { decSigned(enc, v); }
void VLEncoding::dec(const std::vector<char> &enc, std::vector<int64_t> &v) { decSigned(enc, v); }

void VLEncoding::dec(const std::vector<char> &enc, std::vector<uint16_t> &v) { decUnsigned(enc, v); }
void VLEncoding::dec(const std::vector<char> &enc, std::vector<uint32_t> &v) { decUnsigned(enc, v); }
void VLEncoding::dec(const std::vector<char> &enc, std::vector<uint64_t> &v) { decUnsigned(enc, v); }


} // namespace sigpx
