#python

import testing

setup = testing.setup_mesh_source_test("NurbsDisk")
testing.image_comparison(setup.document, setup.camera_to_bitmap.get_property("output_bitmap"), "mesh.source.nurbs_disk", 0.008)

