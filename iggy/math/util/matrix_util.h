// Copyright 2020 insaneyilin All Rights Reserved.
#ifndef IGGY_MATH_UTIL_MATRIX_UTIL_H_
#define IGGY_MATH_UTIL_MATRIX_UTIL_H_

#include <Eigen/Dense>
#include <Eigen/SVD>

#define _USE_MATH_DEFINES
#include <cmath>

namespace iggy {
namespace math {
namespace util {

/**
 * @brief Computes the Moore-Penrose pseudo-inverse of a given square matrix,
 * rounding all eigenvalues with absolute value bounded by epsilon to zero.
 *
 * @param m The square matrix to be pseudo-inverted
 * @param epsilon A small positive real number (optional; default is 1.0e-6).
 *
 * @return Moore-Penrose pseudo-inverse of the given matrix.
 */
template <typename T, unsigned int N>
Eigen::Matrix<T, N, N> PseudoInverse(const Eigen::Matrix<T, N, N> &m,
                                     const double epsilon = 1.0e-6) {
  Eigen::JacobiSVD<Eigen::Matrix<T, N, N>> svd(
      m, Eigen::ComputeFullU | Eigen::ComputeFullV);
  return static_cast<Eigen::Matrix<T, N, N>>(
      svd.matrixV() *
      (svd.singularValues().array().abs() > epsilon)
          .select(svd.singularValues().array().inverse(), 0)
          .matrix()
          .asDiagonal() *
      svd.matrixU().adjoint());
}

/**
 * @brief Computes the Moore-Penrose pseudo-inverse of a given matrix,
 * rounding all eigenvalues with absolute value bounded by epsilon to zero.
 *
 * @param m The matrix to be pseudo-inverted
 * @param epsilon A small positive real number (optional; default is 1.0e-6).
 *
 * @return Moore-Penrose pseudo-inverse of the given matrix.
 */
template <typename T, unsigned int M, unsigned int N>
Eigen::Matrix<T, N, M> PseudoInverse(const Eigen::Matrix<T, M, N> &m,
                                     const double epsilon = 1.0e-6) {
  Eigen::Matrix<T, M, M> t = m * m.transpose();
  return static_cast<Eigen::Matrix<T, N, M>>(m.transpose() *
                                             PseudoInverse<T, M>(t));
}

}  // namespace util
}  // namespace math
}  // namespace iggy

#endif  // IGGY_MATH_UTIL_MATRIX_UTIL_H_

