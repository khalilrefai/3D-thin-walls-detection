#pragma once

/* C/C++ standard libraries */
#include <iostream>
#include <vector>

/* Third-party libraries */
#include <Eigen/Sparse>

namespace ThinWalls
{
	std::vector< bool > evaluate(Eigen::MatrixXd & V, Eigen::MatrixXi & F, double thickness);
	std::vector< bool > detect(Eigen::MatrixXd & V, Eigen::MatrixXi & F, double thickness);
}
