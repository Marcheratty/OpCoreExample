#include <Filters/KalmanFusion.h>

// Constructor
KalmanFusion::KalmanFusion(const OpCore::Matrix<float, 3, 1>& p_0, const OpCore::Matrix<float, 3, 1>& dp_0, const OpCore::Matrix<float, 3, 1>& ddp_0, float deltaT)
    : deltaT(deltaT), firstUpdate(true)
{

    // Create 3x3 identity and zero matrices
    OpCore::Matrix<float, 3, 3> I = OpCore::Matrix<float, 3, 3>::eye();
    OpCore::Matrix<float, 3, 3> zeros3x3 = OpCore::Matrix<float, 3, 3>::zeros();
    OpCore::Matrix<float, 3, 6> zeros3x6 = OpCore::Matrix<float, 3, 6>::zeros();

    // Create scaled matrices
    OpCore::Matrix<float, 3, 3> I_dt = I * deltaT;
    OpCore::Matrix<float, 3, 3> I_dt2 = I * (0.5f * deltaT * deltaT);

    // Construct A_trans matrix
    OpCore::Matrix<float, 3, 9> row1 = I.hconcat(I_dt).hconcat(I_dt2);
    OpCore::Matrix<float, 3, 9> row2 = zeros3x3.hconcat(I).hconcat(I_dt);
    OpCore::Matrix<float, 3, 9> row3 = zeros3x3.hconcat(zeros3x3).hconcat(I);
    OpCore::Matrix<float, 9, 9> A_trans = row1.vconcat(row2).vconcat(row3);

    // Construct B_trans matrix
    OpCore::Matrix<float, 9, 3> B_trans = I_dt2.vconcat(I_dt).vconcat(I);

    // Construct C_trans matrix
    OpCore::Matrix<float, 3, 9> C_row1 = I.hconcat(zeros3x6);
    OpCore::Matrix<float, 3, 9> C_row2 = zeros3x3.hconcat(I).hconcat(zeros3x3);
    OpCore::Matrix<float, 3, 9> C_row3 = zeros3x6.hconcat(I);
    OpCore::Matrix<float, 9, 9> C_trans = C_row1.vconcat(C_row2).vconcat(C_row3);

    x_t = p_0.vconcat(dp_0).vconcat(ddp_0);
    Xk = x_t;
    Xk_1 = x_t;

    Fk = A_trans;
    Bk = B_trans;
    Hk = C_trans;

    Qk = OpCore::Matrix<float, 9, 9>::eye() * 0.1f;
    Rk = OpCore::Matrix<float, 9, 9>::eye() * 25.0f;
    Pk = OpCore::Matrix<float, 9, 9>::eye() * 100.0f;
}


void KalmanFusion::kalman_estimate(const OpCore::Matrix<float, 3, 1>& p, const OpCore::Matrix<float, 3, 1>& dp, const OpCore::Matrix<float, 3, 1>& ddp) {
    // Process Noise Tuning: Adjust for available data
    OpCore::Matrix<float, 3, 9> Qk_p, Qk_dp, Qk_ddp, Rk_p, Rk_dp, Rk_ddp;
    OpCore::Matrix<float, 3, 1> X_p, X_dp, X_ddp;

    // Position
    if (p.isnan()) {
        Qk_p = OpCore::Matrix<float, 3, 3>::eye().hconcat(OpCore::Matrix<float, 3, 6>::zeros()) * kalman_position.Qk_missing;
        Rk_p = OpCore::Matrix<float, 3, 3>::eye().hconcat(OpCore::Matrix<float, 3, 6>::zeros()) * kalman_position.Rk_missing;
        X_p = Xk_1.submatrix<3, 1>(0, 0);
    } else {
        Qk_p = OpCore::Matrix<float, 3, 3>::eye().hconcat(OpCore::Matrix<float, 3, 6>::zeros()) * kalman_position.Qk_present;
        Rk_p = OpCore::Matrix<float, 3, 3>::eye().hconcat(OpCore::Matrix<float, 3, 6>::zeros()) * kalman_position.Rk_present;
        X_p = p;
    }

    // Velocity
    if (dp.isnan()) {
        Qk_dp = OpCore::Matrix<float, 3, 3>::zeros().hconcat(OpCore::Matrix<float, 3, 3>::eye()).hconcat(OpCore::Matrix<float, 3, 3>::zeros()) * kalman_velocity.Qk_missing;
        Rk_dp = OpCore::Matrix<float, 3, 3>::zeros().hconcat(OpCore::Matrix<float, 3, 3>::eye()).hconcat(OpCore::Matrix<float, 3, 3>::zeros()) * kalman_velocity.Rk_missing;
        X_dp = Xk_1.submatrix<3, 1>(3, 0);
    } else {
        Qk_dp = OpCore::Matrix<float, 3, 3>::zeros().hconcat(OpCore::Matrix<float, 3, 3>::eye()).hconcat(OpCore::Matrix<float, 3, 3>::zeros()) * kalman_velocity.Qk_present;
        Rk_dp = OpCore::Matrix<float, 3, 3>::zeros().hconcat(OpCore::Matrix<float, 3, 3>::eye()).hconcat(OpCore::Matrix<float, 3, 3>::zeros()) * kalman_velocity.Rk_present;
        X_dp = dp;
    }

    // Acceleration
    if (ddp.isnan()) {
        Qk_ddp = OpCore::Matrix<float, 3, 6>::zeros().hconcat(OpCore::Matrix<float, 3, 3>::eye()) * kalman_acceleration.Qk_missing;
        Rk_ddp = OpCore::Matrix<float, 3, 6>::zeros().hconcat(OpCore::Matrix<float, 3, 3>::eye()) * kalman_acceleration.Rk_missing;
        X_ddp = Xk_1.submatrix<3, 1>(6, 0);
    } else {
        Qk_ddp = OpCore::Matrix<float, 3, 6>::zeros().hconcat(OpCore::Matrix<float, 3, 3>::eye()) * kalman_acceleration.Qk_present;
        Rk_ddp = OpCore::Matrix<float, 3, 6>::zeros().hconcat(OpCore::Matrix<float, 3, 3>::eye()) * kalman_acceleration.Rk_present;
        X_ddp = ddp;
    }

    Qk = Qk_p.vconcat(Qk_dp).vconcat(Qk_ddp);
    Rk = Rk_p.vconcat(Rk_dp).vconcat(Rk_ddp);

    OpCore::Matrix<float, 9, 1> X = X_p.vconcat(X_dp).vconcat(X_ddp);

    // PREDICT STEP
    if (firstUpdate && dp == OpCore::Matrix<float, 3, 1>::zeros() && ddp == OpCore::Matrix<float, 3, 1>::zeros()) {
        Xk = Fk * Xk;
        firstUpdate = false;
    } else {
        Xk = Fk * Xk + Bk * ddp;
    }
    Pk = Fk * Pk * Fk.transpose() + Qk;

    // UPDATE STEP
    Zk = Hk * X;
    OpCore::Matrix<float, 9, 1> Zest = Hk * Xk;
    OpCore::Matrix<float, 9, 1> Yk = Zk - Zest;
    Sk = Hk * Pk * Hk.transpose() + Rk;
    Kk = Pk * Hk.transpose() * Sk.inverse();
    Xk = Xk + Kk * Yk;
    Pk = (OpCore::Matrix<float, 9, 9>::eye() - Kk * Hk) * Pk;
    Xk_1 = Xk;
}


void KalmanFusion::getState(OpCore::Matrix<float, 3, 1>& p, OpCore::Matrix<float, 3, 1>& dp, OpCore::Matrix<float, 3, 1>& ddp) {
    // Extract position, velocity, and acceleration estimates from the state vector Xk
    p = Xk.submatrix<3, 1>(0, 0);   // Extract the first 3 elements (position)
    dp = Xk.submatrix<3, 1>(3, 0);  // Extract the next 3 elements (velocity)
    ddp = Xk.submatrix<3, 1>(6, 0); // Extract the last 3 elements (acceleration)
}
