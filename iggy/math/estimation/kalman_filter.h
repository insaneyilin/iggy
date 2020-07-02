// Copyright 2020 insaneyilin All Rights Reserved.
// Reference: modules/common/math/kalman_filter.h from ApolloAuto
#ifndef IGGY_MATH_ESTIMATION_KALMAN_FILTER_H_
#define IGGY_MATH_ESTIMATION_KALMAN_FILTER_H_

#include <Eigen/Dense>
#include <string>

#include "iggy/common/util/macros.h"
#include "iggy/math/util/matrix_util.h"

namespace iggy {
namespace math {
namespace estimation {

/**
 * @class KalmanFilter
 *
 * @brief Kalman filter.
 *
 * @param XN dimension of state
 * @param ZN dimension of observation
 * @param UN dimension of control
 */
template <typename T, size_t XN, size_t ZN, size_t UN>
class KalmanFilter {
 public:
  /**
   * @brief Constructor which defers initialization until the initial state
   * distribution parameters are set (with SetStateEstimate()),
   */
  KalmanFilter() {
    Reset();
  }

  /**
   * @brief Constructor with initial state params
   * @param x Mean of the state belief distribution
   * @param P Covariance of the state belief distribution
   */
  KalmanFilter(const Eigen::Matrix<T, XN, 1> &x,
               const Eigen::Matrix<T, XN, XN> &P)
      : KalmanFilter() {
    SetStateEstimate(x, P);
  }

  /**
   * @brief Reset member variables
   */
  void Reset() {
    x_.setZero();  // state
    F_.setIdentity();  // state transition matrix
    B_.setZero();  // control matrix in state transition
    H_.setIdentity();  // observation matrix

    P_.setZero();  // covariance of current state belief distribution
    Q_.setZero();  // process noise
    R_.setZero();  // measurement noise

    y_.setZero();  // innovation
    S_.setZero();  // innovation covariance
    K_.setZero();  // kalman gain

    inited_ = false;
  }

  /**
   * @brief Set the initial state belief distribution.
   *
   * @param x Mean of the state belief distribution
   * @param P Covariance of the state belief distribution
   */
  void SetStateEstimate(const Eigen::Matrix<T, XN, 1> &x,
                        const Eigen::Matrix<T, XN, XN> &P) {
    x_ = x;
    P_ = P;
    inited_ = true;
  }

  /**
   * @brief Destructor
   */
  virtual ~KalmanFilter() = default;

  /**
   * @brief Set the transition matrix under zero control.
   *
   * @param F New transition matrix
   */
  void SetTransitionMatrix(const Eigen::Matrix<T, XN, XN> &F) {
    F_ = F;
  }

  /**
   * @brief Set the covariance matrix of the transition noise.(process noise)
   *
   * @param Q New covariance matrix of the transition noise
   */
  void SetTransitionNoise(const Eigen::Matrix<T, XN, XN> &Q) {
    Q_ = Q;
  }

  /**
   * @brief Set the observation matrix, which maps states to observations.
   *
   * @param H New observation matrix
   */
  void SetObservationMatrix(const Eigen::Matrix<T, ZN, XN> &H) {
    H_ = H;
  }

  /**
   * @brief Set the covariance matrix of the observation noise.
   * (measurement noise)
   *
   * @param R New covariance matrix of the observation noise
   */
  void SetObservationNoise(const Eigen::Matrix<T, ZN, ZN> &R) {
    R_ = R;
  }

  /**
   * @brief Set the covariance matrix of current state belief distribution.
   *
   * @param P New state covariance matrix of current state
   */
  void SetStateCovariance(const Eigen::Matrix<T, XN, XN> &P) {
    P_ = P;
  }

  /**
   * @brief Set the control matrix in the state transition rule.
   *
   * @param B New control matrix
   */
  void SetControlMatrix(const Eigen::Matrix<T, XN, UN> &B) {
    B_ = B;
  }

  /**
   * @brief Get the system transition matrix under zero control.
   *
   * @return Transition matrix.
   */
  const Eigen::Matrix<T, XN, XN> &GetTransitionMatrix() const {
    return F_;
  }

  /**
   * @brief Get the covariance matrix of the transition noise.
   *
   * @return Covariance matrix of the transition noise
   */
  const Eigen::Matrix<T, XN, XN> &GetTransitionNoise() const {
    return Q_;
  }

  /**
   * @brief Get the observation matrix, which maps states to observations.
   *
   * @return Observation matrix
   */
  const Eigen::Matrix<T, ZN, XN> &GetObservationMatrix() const {
    return H_;
  }

  /**
   * @brief Get the covariance matrix of the observation noise.
   *
   * @return Covariance matrix of the observation noise
   */
  const Eigen::Matrix<T, ZN, ZN> &GetObservationNoise() const {
    return R_;
  }

  /**
   * @brief Get the control matrix in the state transition rule.
   *
   * @return Control matrix
   */
  const Eigen::Matrix<T, XN, UN> &GetControlMatrix() const {
    return B_;
  }

  /**
   * @brief Get initialization flag
   *
   * @return True if the filter is initialized
   */
  bool IsInited() const {
    return inited_;
  }

  /**
   * @brief Get mean of the current state belief distribution
   *
   * @return current state
   */
  Eigen::Matrix<T, XN, 1> GetStateEstimate() const {
    return x_;
  }

  /**
   * @brief Get covariance of our current state belief distribution
   *
   * @return Covariance matrix of current state belief distribution
   */
  Eigen::Matrix<T, XN, XN> GetStateCovariance() const {
    return P_;
  }

  /**
   * @brief Updates the state belief distribution given the control input u.
   *
   * @param u Control input (by default, zero)
   * @return False if not the filter is not initialized
   */
  bool Predict(
      const Eigen::Matrix<T, UN, 1> &u = Eigen::Matrix<T, UN, 1>::Zero());

  /**
   * @brief Updates the state belief distribution given an observation z.
   *
   * @param z Observation
   * @return False if not the filter is not initialized
   */
  bool Correct(const Eigen::Matrix<T, ZN, 1> &z);

  /**
   * @brief Get debug string containing detailed information about the filter.
   *
   * @return Debug string
   */
  std::string DebugString() const;

 private:
  // Mean of current state belief distribution
  Eigen::Matrix<T, XN, 1> x_;

  // State transition matrix (without control input)
  Eigen::Matrix<T, XN, XN> F_;

  // Control matrix in state transition
  Eigen::Matrix<T, XN, UN> B_;

  // Observation matrix
  Eigen::Matrix<T, ZN, XN> H_;

  // Covariance of current state belief distribution
  Eigen::Matrix<T, XN, XN> P_;

  // Covariance of the state transition noise (process noise)
  Eigen::Matrix<T, XN, XN> Q_;

  // Covariance of observation noise (measurement noise)
  Eigen::Matrix<T, ZN, ZN> R_;

  // Innovation, use member variable to avoid memory re-allocation
  Eigen::Matrix<T, ZN, 1> y_;

  // Innovation covariance, use member variable to avoid memory re-allocation
  Eigen::Matrix<T, ZN, ZN> S_;

  // Kalman gain, use member variable to avoid memory re-allocation
  Eigen::Matrix<T, XN, ZN> K_;

  bool inited_ = false;
};

template <typename T, size_t XN, size_t ZN, size_t UN>
inline bool KalmanFilter<T, XN, ZN, UN>::Predict(
    const Eigen::Matrix<T, UN, 1> &u) {
  if (!inited_) {
    return false;
  }
  // update state with transition model
  x_ = F_ * x_ + B_ * u;
  // update state covariance
  P_ = F_ * P_ * F_.transpose() + Q_;
  return true;
}

template <typename T, size_t XN, size_t ZN, size_t UN>
inline bool KalmanFilter<T, XN, ZN, UN>::Correct(
    const Eigen::Matrix<T, ZN, 1> &z) {
  if (!inited_) {
    return false;
  }

  // innovation(residual)
  y_ = z - H_ * x_;
  // innovation covariance
  S_ = static_cast<Eigen::Matrix<T, ZN, ZN>>(H_ * P_ * H_.transpose() + R_);
  // kalman gain
  K_ = static_cast<Eigen::Matrix<T, XN, ZN>>(P_ * H_.transpose() *
                                             util::PseudoInverse<T, ZN>(S_));

  // update state & state covariance
  x_ = x_ + K_ * y_;
  P_ = static_cast<Eigen::Matrix<T, XN, XN>>(
      (Eigen::Matrix<T, XN, XN>::Identity() - K_ * H_) * P_);
  return true;
}

template <typename T, size_t XN, size_t ZN, size_t UN>
inline std::string KalmanFilter<T, XN, ZN, UN>::DebugString() const {
  Eigen::IOFormat clean_fmt(4, 0, ", ", " ", "[", "]");
  std::stringstream ss;
  ss << "F = " << F_.format(clean_fmt) << "\n"
     << "B = " << B_.format(clean_fmt) << "\n"
     << "H = " << H_.format(clean_fmt) << "\n"
     << "Q = " << Q_.format(clean_fmt) << "\n"
     << "R = " << R_.format(clean_fmt) << "\n"
     << "x = " << x_.format(clean_fmt) << "\n"
     << "P = " << P_.format(clean_fmt) << "\n";
  return ss.str();
}

}  // namespace estimation
}  // namespace math
}  // namespace iggy

#endif  // IGGY_MATH_ESTIMATION_KALMAN_FILTER_H_
