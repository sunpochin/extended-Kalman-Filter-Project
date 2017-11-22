[image3]: ./images/img3.png
[image4]: ./images/img4.png

# Extended Kalman Filter Project
Self-Driving Car Engineer Nanodegree Program

## Introduction:
In this project I implemented Extended Kalman filter to do sensor fusion, estimate the state of a moving object of interest with noisy lidar and radar measurements.

By correctly implementing sensor fusion, this implementation obtains RMSE values that are lower that the tolerance outlined in the project rubric: px, py, vx, vy output coordinates must have an RMSE <= [.11, .11, 0.52, 0.52] .

## Results Demo:
Simulation results are recorded as following youtube videos.

Video with Dataset 1:
https://youtu.be/E0pFsr8ao94

Video with Dataset 2:
https://youtu.be/tRFBBEhw9wU

## Program structure:
The main flow is in `main.cpp`, and the algorithm implementation is in:

`FusionEKF.cpp`, values initialization, and flow of "Measurement", "Prediction", Sensor fusion.

`KalmanFilter.cpp`, implementation Kalman filter for Lidar and Radar datas.

`tools.cpp`, helper functions to calculate `Jacobian` and `RMSE`.

### Illustration:
`KalmanFilter.cpp` illustrated (taken from udacity course video):
![alt text][image3]

`FusionEKF.cpp` illustrated (taken from udacity course video):
![alt text][image4]

## Setting up and Usage
1. git clone this repository.
2. Install `uWebSocketIO`. By running `install-ubuntu.sh` or `install-mac.sh`
3. Build main program:
  Once the install for uWebSocketIO is complete, the main program can be built and run by doing the following from the project top directory.
 1. mkdir build
 2. cd build
 3. cmake ..
 4. make
 5. ./ExtendedKF

4. Download and run simulator: This project involves the Term 2 Simulator which can be downloaded [here](https://github.com/udacity/self-driving-car-sim/releases)
