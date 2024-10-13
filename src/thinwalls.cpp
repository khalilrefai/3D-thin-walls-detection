/* Third-party libraries */
#include <igl/find.h>
#include <igl/per_face_normals.h>
#include <igl/per_vertex_normals.h>

/* Local inclusions */
#include "./thinwalls.h"

std::vector< bool > ThinWalls::evaluate(Eigen::MatrixXd & V, Eigen::MatrixXi & F, double thickness)
{
	std::vector< bool > badTesselation = ThinWalls::detect(V, F, 0.001);
	std::vector< bool > flaggedVertices = ThinWalls::detect(V, F, thickness);

	for (int i = 0; i < badTesselation.size(); i++)
	{
		if (badTesselation[i])
		{
			flaggedVertices[i] = false;
		}
	}

	return flaggedVertices;
}

std::vector< bool > ThinWalls::detect(Eigen::MatrixXd & V, Eigen::MatrixXi & F, double thickness)
{
	// Compute vertex normals
	Eigen::MatrixXd vertexNormals;
	igl::per_vertex_normals(V, F, vertexNormals);

	// Erosion step
	Eigen::MatrixXd V_eroded = V - thickness / 2 * vertexNormals;

	// Compute face normals for both original and eroded vertices
	Eigen::MatrixXd N, N_eroded;
	igl::per_face_normals(V, F, N);
	igl::per_face_normals(V_eroded, F, N_eroded);

	// Compute the dot product between the original and eroded face normals
	Eigen::VectorXd deviation = (N_eroded.cwiseProduct(N)).rowwise().sum();

	// Detect normal deviation
	long maxLimit = LONG_MAX;
	deviation = (deviation.array() < 0.9).select(-maxLimit, deviation);
	deviation = (deviation.array() != -maxLimit).select(0, deviation);

	// Find indexes of thin faces
	Eigen::VectorXi Idx, Jdx;
	Eigen::VectorXd Vdx;
	igl::find(deviation, Idx, Jdx, Vdx);

	// Find vertices that belong to thin faces and flag them
	std::vector< bool > flaggedVertices(V.rows(), false);
	for (int i = 0; i < Idx.rows(); i++)
	{
		int faceIndex = Idx[i];
		for (int j = 0; j < 3; j++)
		{
			int vertexIndex = F(faceIndex, j);
			if (!flaggedVertices[vertexIndex])
				flaggedVertices[vertexIndex] = true;
		}
	}

	return flaggedVertices;
}
