Compile commands : 
g++ -Wall -c "%f" ChequeredFloor.cpp Triangle.cpp Cube.cpp Tetrahedron.cpp Cone.cpp Cylinder.cpp Plane.cpp Color.cpp Object.cpp Sphere.cpp Vector.cpp

Build commands:
g++ -Wall -o "%e" ChequeredFloor.cpp Triangle.cpp Cube.cpp Tetrahedron.cpp Cone.cpp Cylinder.cpp Plane.cpp Color.cpp "%f" Sphere.cpp Vector.cpp Object.cpp -lGL -lGLU -lglut
