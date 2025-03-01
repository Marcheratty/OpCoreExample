#ifndef KALMAN_PARAMS_H
#define KALMAN_PARAMS_H

#define IDEAL

struct KalmanGains {
    float Qk_present;  // Process noise when data is available
    float Rk_present;  // Measurement noise when data is available
    float Qk_missing;  // Process noise when data is missing
    float Rk_missing;  // Measurement noise when data is missing
};

#ifndef IDEAL

// Define Kalman gains for position, velocity, and acceleration
constexpr KalmanGains kalman_position = {0.01f, 100.0f, 0.0000001f, 1e15f};
constexpr KalmanGains kalman_velocity = {0.01f, 9.0f, 0.0000001f, 1e15f};
constexpr KalmanGains kalman_acceleration = {0.1f, 4.0f, 0.0000001f, 1e15f};

#else

// Define Kalman gains for position, velocity, and acceleration
constexpr KalmanGains kalman_position =         {0.01f,     0.00001f,   0.0000001f,     1e15f};
constexpr KalmanGains kalman_velocity =         {0.01f,     0.00001f,   0.0000001f,     1e15f};
constexpr KalmanGains kalman_acceleration =     {0.1f,      0.00001f,   0.0000001f,     1e15f};

#endif


#endif // KALMAN_PARAMS_H
