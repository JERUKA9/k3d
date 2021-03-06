#python

import k3d
import testing

setup = testing.setup_mesh_modifier_test("PolyGrid", "SelectBoundaryEdges")
setup.modifier.mesh_selection = k3d.geometry.selection.create(0)


testing.require_valid_mesh(setup.document, setup.modifier.get_property("output_mesh"))
testing.require_similar_mesh(setup.document, setup.modifier.get_property("output_mesh"), "mesh.selection.SelectBoundaryEdges", 1)

