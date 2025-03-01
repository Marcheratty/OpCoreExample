#ifndef KALMANFUSION_H
#define KALMANFUSION_H

#include <iostream>
#include <cmath>
#include <OpCore/Matrix.h>
#include <cmath> 
#include <config/KalmanParams.h>

class KalmanFusion {
public:
    OpCore::Matrix<float, 9, 9> A_trans;
    OpCore::Matrix<float, 9, 3> B_trans;
    OpCore::Matrix<float, 9, 9> C_trans;
    OpCore::Matrix<float, 9, 1> x_t;
    OpCore::Matrix<float, 9, 1> Xk;
    OpCore::Matrix<float, 9, 1> Xk_1;

    OpCore::Matrix<float, 9, 9> Fk;
    OpCore::Matrix<float, 9, 3> Bk;
    OpCore::Matrix<float, 9, 9> Hk;
    OpCore::Matrix<float, 9, 1> Zk;
    OpCore::Matrix<float, 9, 9> Rk;
    OpCore::Matrix<float, 9, 9> Qk;
    OpCore::Matrix<float, 9, 9> Pk;
    OpCore::Matrix<float, 9, 9> Sk;
    OpCore::Matrix<float, 9, 9> Kk;

    float deltaT;
    bool firstUpdate;

    // Constructor
    KalmanFusion(const OpCore::Matrix<float, 3, 1>& p_0, const OpCore::Matrix<float, 3, 1>& dp_0, const OpCore::Matrix<float, 3, 1>& ddp_0, float deltaT);

    void kalman_estimate(const OpCore::Matrix<float, 3, 1>& p, const OpCore::Matrix<float, 3, 1>& dp, const OpCore::Matrix<float, 3, 1>& ddp);
    void getState(OpCore::Matrix<float, 3, 1>& p, OpCore::Matrix<float, 3, 1>& dp, OpCore::Matrix<float, 3, 1>& ddp);
};

#endif // KALMANFUSION_H

