// K-3D
// Copyright (c) 1995-2008, Timothy M. Shead
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

#include "metadata_keys.h"
#include "primitive_validation.h"
#include "selection.h"
#include "string_cast.h"
#include "torus.h"

namespace k3d
{

namespace torus
{

/////////////////////////////////////////////////////////////////////////////////////////////
// const_primitive

const_primitive::const_primitive(
	const mesh::matrices_t& Matrices,
	const mesh::materials_t& Materials,
	const mesh::doubles_t& MajorRadii,
	const mesh::doubles_t& MinorRadii,
	const mesh::doubles_t& PhiMin,
	const mesh::doubles_t& PhiMax,
	const mesh::doubles_t& SweepAngles,
	const mesh::selection_t& Selections,
	const mesh::table_t& ConstantAttributes,
	const mesh::table_t& UniformAttributes,
	const mesh::table_t& VaryingAttributes
		) :
	matrices(Matrices),
	materials(Materials),
	major_radii(MajorRadii),
	minor_radii(MinorRadii),
	phi_min(PhiMin),
	phi_max(PhiMax),
	sweep_angles(SweepAngles),
	selections(Selections),
	constant_attributes(ConstantAttributes),
	uniform_attributes(UniformAttributes),
	varying_attributes(VaryingAttributes)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////
// primitive

primitive::primitive(
	mesh::matrices_t& Matrices,
	mesh::materials_t& Materials,
	mesh::doubles_t& MajorRadii,
	mesh::doubles_t& MinorRadii,
	mesh::doubles_t& PhiMin,
	mesh::doubles_t& PhiMax,
	mesh::doubles_t& SweepAngles,
	mesh::selection_t& Selections,
	mesh::table_t& ConstantAttributes,
	mesh::table_t& UniformAttributes,
	mesh::table_t& VaryingAttributes
		) :
	matrices(Matrices),
	materials(Materials),
	major_radii(MajorRadii),
	minor_radii(MinorRadii),
	phi_min(PhiMin),
	phi_max(PhiMax),
	sweep_angles(SweepAngles),
	selections(Selections),
	constant_attributes(ConstantAttributes),
	uniform_attributes(UniformAttributes),
	varying_attributes(VaryingAttributes)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////
// create

primitive* create(mesh& Mesh)
{
	mesh::primitive& generic_primitive = Mesh.primitives.create("torus");

	primitive* const result = new primitive(
		generic_primitive.structure["uniform"].create<mesh::matrices_t >("matrices"),
		generic_primitive.structure["uniform"].create<mesh::materials_t >("materials"),
		generic_primitive.structure["uniform"].create<mesh::doubles_t >("major_radii"),
		generic_primitive.structure["uniform"].create<mesh::doubles_t >("minor_radii"),
		generic_primitive.structure["uniform"].create<mesh::doubles_t >("phi_min"),
		generic_primitive.structure["uniform"].create<mesh::doubles_t >("phi_max"),
		generic_primitive.structure["uniform"].create<mesh::doubles_t >("sweep_angles"),
		generic_primitive.structure["uniform"].create<mesh::selection_t>("selections"),
		generic_primitive.attributes["constant"],
		generic_primitive.attributes["uniform"],
		generic_primitive.attributes["varying"]
		);

	result->selections.set_metadata_value(metadata::key::selection_component(), string_cast(selection::UNIFORM));

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// validate

const_primitive* validate(const mesh::primitive& Primitive)
{
	if(Primitive.type != "torus")
		return 0;

	try
	{
		require_valid_primitive(Primitive);

		const mesh::table_t& uniform_structure = require_structure(Primitive, "uniform");

		const mesh::table_t& constant_attributes = require_attributes(Primitive, "constant");
		const mesh::table_t& uniform_attributes = require_attributes(Primitive, "uniform");
		const mesh::table_t& varying_attributes = require_attributes(Primitive, "varying");

		const mesh::matrices_t& matrices = require_array<mesh::matrices_t >(Primitive, uniform_structure, "matrices");
		const mesh::materials_t& materials = require_array<mesh::materials_t >(Primitive, uniform_structure, "materials");
		const mesh::doubles_t& major_radii = require_array<mesh::doubles_t >(Primitive, uniform_structure, "major_radii");
		const mesh::doubles_t& minor_radii = require_array<mesh::doubles_t >(Primitive, uniform_structure, "minor_radii");
		const mesh::doubles_t& phi_min = require_array<mesh::doubles_t >(Primitive, uniform_structure, "phi_min");
		const mesh::doubles_t& phi_max = require_array<mesh::doubles_t >(Primitive, uniform_structure, "phi_max");
		const mesh::doubles_t& sweep_angles = require_array<mesh::doubles_t >(Primitive, uniform_structure, "sweep_angles");
		const mesh::selection_t& selections = require_array<mesh::selection_t>(Primitive, uniform_structure, "selections");

		require_metadata(Primitive, selections, "selections", metadata::key::selection_component(), string_cast(selection::UNIFORM));

		require_table_row_count(Primitive, constant_attributes, "constant", 1);
		require_table_row_count(Primitive, uniform_attributes, "uniform", uniform_structure.row_count());
		require_table_row_count(Primitive, varying_attributes, "varying", uniform_structure.row_count() * 4);

		return new const_primitive(matrices, materials, major_radii, minor_radii, phi_min, phi_max, sweep_angles, selections, constant_attributes, uniform_attributes, varying_attributes);
	}
	catch(std::exception& e)
	{
		log() << error << e.what() << std::endl;
	}

	return 0;
}

primitive* validate(mesh::primitive& Primitive)
{
	if(Primitive.type != "torus")
		return 0;

	try
	{
		require_valid_primitive(Primitive);

		mesh::table_t& uniform_structure = require_structure(Primitive, "uniform");

		mesh::table_t& constant_attributes = require_attributes(Primitive, "constant");
		mesh::table_t& uniform_attributes = require_attributes(Primitive, "uniform");
		mesh::table_t& varying_attributes = require_attributes(Primitive, "varying");

		mesh::matrices_t& matrices = require_array<mesh::matrices_t >(Primitive, uniform_structure, "matrices");
		mesh::materials_t& materials = require_array<mesh::materials_t >(Primitive, uniform_structure, "materials");
		mesh::doubles_t& major_radii = require_array<mesh::doubles_t >(Primitive, uniform_structure, "major_radii");
		mesh::doubles_t& minor_radii = require_array<mesh::doubles_t >(Primitive, uniform_structure, "minor_radii");
		mesh::doubles_t& phi_min = require_array<mesh::doubles_t >(Primitive, uniform_structure, "phi_min");
		mesh::doubles_t& phi_max = require_array<mesh::doubles_t >(Primitive, uniform_structure, "phi_max");
		mesh::doubles_t& sweep_angles = require_array<mesh::doubles_t >(Primitive, uniform_structure, "sweep_angles");
		mesh::selection_t& selections = require_array<mesh::selection_t>(Primitive, uniform_structure, "selections");

		require_metadata(Primitive, selections, "selections", metadata::key::selection_component(), string_cast(selection::UNIFORM));

		require_table_row_count(Primitive, constant_attributes, "constant", 1);
		require_table_row_count(Primitive, uniform_attributes, "uniform", uniform_structure.row_count());
		require_table_row_count(Primitive, varying_attributes, "varying", uniform_structure.row_count() * 4);

		return new primitive(matrices, materials, major_radii, minor_radii, phi_min, phi_max, sweep_angles, selections, constant_attributes, uniform_attributes, varying_attributes);
	}
	catch(std::exception& e)
	{
		log() << error << e.what() << std::endl;
	}

	return 0;
}

primitive* validate(pipeline_data<mesh::primitive>& Primitive)
{
  if(!Primitive.get())
    return 0;

	if(Primitive->type != "torus")
		return 0;

  return validate(Primitive.writable());
}

} // namespace torus

} // namespace k3d

