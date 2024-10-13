/* C/C++ standard libraries */
#include <iostream>
#include <algorithm>

/* Third-party libraries */
#include <igl/read_triangle_mesh.h>
#include <igl/remove_duplicate_vertices.h>
#include <igl/opengl/glfw/Viewer.h>

/* Local inclusions */
#include "thinwalls.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <input_filepath> <thickness_threshold>" << std::endl;
		return 1;
	}

	// Import mesh
	Eigen::MatrixXd OV;
	Eigen::MatrixXi OF;
	if (!igl::read_triangle_mesh(argv[1], OV, OF))
	{
		std::cerr << "Error: Unable to import mesh from file " << argv[1] << "\n";
		return 1;
	}

	// Remove duplicate Vertices
	Eigen::MatrixXd V;
	Eigen::MatrixXi F;
	Eigen::MatrixXi SVI;
	Eigen::MatrixXi SVJ;
	igl::remove_duplicate_vertices(OV, OF, 0.0, V, SVI, SVJ, F);

	// Detect thin-walls
	double thicknessThreshold = std::stod(argv[2]);
	std::vector< bool > flaggedVertices = ThinWalls::evaluate(V, F, thicknessThreshold);

	// Check if the vector contains any true values
	bool containsThinWalls = std::any_of(flaggedVertices.begin(), flaggedVertices.end(), [](bool val) {
		return val;
	});

	if (containsThinWalls)
	{
		std::cout << "3D model contains thin walls \n";
	}
	else
	{
		std::cout << "3D model dosen't contain thin walls \n";
	}

	// Color in red the flagged vertices
	Eigen::MatrixXd Color = Eigen::MatrixXd::Constant(V.rows(), 3, 1);
	for (int i = 0; i < flaggedVertices.size(); i++)
	{
		if (flaggedVertices[i])
			Color.row(i) << 1, 0, 0;
	}

	// Viewer
	igl::opengl::glfw::Viewer viewer;
	viewer.data().set_mesh(V, F);
	viewer.data().set_colors(Color);
	viewer.launch();

	return 0;
}
