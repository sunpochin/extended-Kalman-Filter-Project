#include "FusionEKF.h"
#include "tools.h"
#include "Eigen/Dense"
#include <iostream>
using namespace std;

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

/*
 * Constructor.
 */
FusionEKF::FusionEKF() {
  is_initialized_ = false;

  previous_timestamp_ = 0;

  // initializing matrices
  R_laser_ = MatrixXd(2, 2);
  R_radar_ = MatrixXd(3, 3);
  H_laser_ = MatrixXd(2, 4);
  Hj_ = MatrixXd(3, 4);

  //measurement covariance matrix - laser
  R_laser_ << 0.0225, 0,
        0, 0.0225;

  //measurement covariance matrix - radar
  R_radar_ << 0.09, 0, 0,
        0, 0.0009, 0,
        0, 0, 0.09;

  /**
  TODO:
    * Finish initializing the FusionEKF.
    * Set the process and measurement noises
  */

  cout << "FusionEKF constructor " << endl;
}

/**
* Destructor.
*/
FusionEKF::~FusionEKF() {}

void FusionEKF::ProcessMeasurement(const MeasurementPackage &measurement_pack) {

  int noise_ax = 9 ;
  int noise_ay = 9 ;
  cout << "ProcessMeasurement" << endl;
  float dt = (measurement_pack.timestamp_ - previous_timestamp_) / 1000000.0;
  previous_timestamp_ = measurement_pack.timestamp_;

  cout << " dt :" << dt << endl ;

  /*****************************************************************************
   *  Initialization
   ****************************************************************************/
  if (!is_initialized_) {
    /**
    TODO:
      * Initialize the state ekf_.x_ with the first measurement.
      * Create the covariance matrix.
      * Remember: you'll need to convert radar from polar to cartesian coordinates.
    */
    // first measurement
    cout << "EKF: " << endl;
    ekf_.x_ = VectorXd(4);
    ekf_.x_ << 1, 1, 1, 1;

    if (measurement_pack.sensor_type_ == MeasurementPackage::RADAR) {
      /**
      Convert radar from polar to cartesian coordinates and initialize state.
      */
    }
    else if (measurement_pack.sensor_type_ == MeasurementPackage::LASER) {
      /**
      Initialize state.
      */
      cout << "measurement_pack :" << endl ;
      // cout << "measurement_pack :" << measurement_pack.raw_measurements_ << endl ;
      ekf_.F_ = MatrixXd(4, 4) ;
      ekf_.F_ << 1, 0, dt, 0,
                0, 1, 0, dt,
                0, 0, 1, 0,
                0, 0, 0, 1 ;


      float dt_2 = dt * dt;
      float dt_3 = dt_2 * dt;
      float dt_4 = dt_3 * dt;
      //set the process covariance matrix Q
      ekf_.Q_ = MatrixXd(4, 4);
      ekf_.Q_ <<  dt_4/4*noise_ax, 0, dt_3/2*noise_ax, 0,
              			   0, dt_4/4*noise_ay, 0, dt_3/2*noise_ay,
              			   dt_3/2*noise_ax, 0, dt_2*noise_ax, 0,
              			   0, dt_3/2*noise_ay, 0, dt_2*noise_ay;

      // todo , P_ init is not correct?
      ekf_.P_ = MatrixXd(4, 4);
      ekf_.P_ << 1, 0, 0, 0,
        			  0, 1, 0, 0,
        			  0, 0, 1000, 0,
        			  0, 0, 0, 1000;



      // //measurement matrix
      // ekf_.H_ = MatrixXd(4, 4);
      // ekf_.H_ << 1, 0, 0, 0,
      //            0, 1, 0, 0,
      //            0, 0, 1, 0,
      //            0, 0, 0, 1;
      //measurement matrix
      ekf_.H_ = MatrixXd(2, 4);
      ekf_.H_ << 1, 0, 0, 0,
                 0, 1, 0, 0;

      //measurement covariance
      ekf_.R_ = MatrixXd(2, 2);
      ekf_.R_ << 0.0225, 0,
                 0, 0.0225;
      // ekf_.init();

    }

    // done initializing, no need to predict or update
    is_initialized_ = true;
    return;
  }

  /*****************************************************************************
   *  Prediction
   ****************************************************************************/
   cout << "*  Prediction :" << endl ;

  /**
   TODO:
     * Update the state transition matrix F according to the new elapsed time.
      - Time is measured in seconds.
     * Update the process noise covariance matrix.
     * Use noise_ax = 9 and noise_ay = 9 for your Q matrix.
   */

  ekf_.Predict();

  /*****************************************************************************
   *  Update
   ****************************************************************************/

  /**
   TODO:
     * Use the sensor type to perform the update step.
     * Update the state and covariance matrices.
   */


  if (measurement_pack.sensor_type_ == MeasurementPackage::RADAR) {
    // Radar updates
  } else {
    // Laser updates
    ekf_.Update(measurement_pack.raw_measurements_) ;
  }

  // print the output
  cout << "x_ = " << ekf_.x_ << endl;
  cout << "P_ = " << ekf_.P_ << endl;
}
