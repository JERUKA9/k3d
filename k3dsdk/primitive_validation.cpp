// K-3D
// Copyright (c) 1995-2009, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include "primitive_validation.h"

namespace k3d
{

void require_valid_primitive(const mesh::primitive& Primitive)
{
	/** \todo Implement something here */
}

const mesh::table_t& require_structure(const mesh::primitive& Primitive, const string_t& Name)
{
	const table* const structure = Primitive.structure.lookup(Name);

	if(!structure)
		throw std::runtime_error("[" + Primitive.type + "] primitive missing structure [" + Name + "]");

	return *structure;
}

mesh::table_t& require_structure(mesh::primitive& Primitive, const string_t& Name)
{
	table* const structure = Primitive.structure.writable(Name);

	if(!structure)
		throw std::runtime_error("[" + Primitive.type + "] primitive missing structure [" + Name + "]");

	return *structure;
}

const mesh::table_t& require_attributes(const mesh::primitive& Primitive, const string_t& Name)
{
	const table* const attributes = Primitive.attributes.lookup(Name);

	if(!attributes)
		throw std::runtime_error("[" + Primitive.type + "] primitive missing attributes [" + Name + "]");

	return *attributes;
}

mesh::table_t& require_attributes(mesh::primitive& Primitive, const string_t& Name)
{
	table* const attributes = Primitive.attributes.writable(Name);

	if(!attributes)
		throw std::runtime_error("[" + Primitive.type + "] primitive missing attributes [" + Name + "]");

	return *attributes;
}

void require_table_row_count(const mesh::primitive& Primitive, const table& Table, const string_t& TableName, const uint_t RowCount)
{
	if(0 == Table.column_count())
		return;

	if(Table.row_count() != RowCount)
	{
		std::ostringstream buffer;
		buffer << "[" << Primitive.type << "] table [" << TableName << "] incorrect length [" << Table.row_count() << "], expected [" << RowCount << "]";
		throw std::runtime_error(buffer.str());
	}
}

void require_metadata(const mesh::primitive& Primitive, const array& Array, const string_t& ArrayName, const string_t& MetadataName, const string_t& MetadataValue)
{
	if(Array.get_metadata_value(MetadataName) != MetadataValue)
	{
		std::ostringstream buffer;
		buffer << "[" << Primitive.type << "] primitive [" << ArrayName << "] array missing [" << MetadataName << "] metadata value [" << MetadataValue << "]";
		throw std::runtime_error(buffer.str());
	}
}

} // namespace k3d

