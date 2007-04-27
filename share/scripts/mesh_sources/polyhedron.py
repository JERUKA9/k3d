#python

import k3d

positions = [(-5, 0, 5), (5, 0, 5), (5, 0, -5), (-5, 0, -5)]

points = Output.create_points()
for position in positions:
	points.append(k3d.point3(position[0], position[1], position[2]))

polyhedra = Output.create_polyhedra()

first_faces = polyhedra.create_first_faces()
first_faces.assign([0])

face_counts = polyhedra.create_face_counts()
face_counts.assign([1])

types = polyhedra.create_types()
types.assign([k3d.polyhedron_type.polygons])

face_first_loops = polyhedra.create_face_first_loops()
face_first_loops.assign([0])

face_loop_counts = polyhedra.create_face_loop_counts()
face_loop_counts.assign([1])

face_materials = polyhedra.create_face_materials()
face_materials.assign([None])

loop_first_edges = polyhedra.create_loop_first_edges()
loop_first_edges.assign([0])

edge_points = polyhedra.create_edge_points()
edge_points.assign([0, 1, 2, 3])

clockwise_edges = polyhedra.create_clockwise_edges()
clockwise_edges.assign([1, 2, 3, 0])

Cs = polyhedra.writable_face_varying_data.create_array("Cs", "k3d::color")
Cs.assign([k3d.color(1, 0, 0), k3d.color(0, 1, 0), k3d.color(0, 0, 1), k3d.color(1, 1, 1)])
