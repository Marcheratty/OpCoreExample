#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <Filters/KalmanFusion.h>

using namespace OpCore;

// Function to read CSV file
std::vector<std::vector<float>> readCSV(const std::string& filepath) {
    std::vector<std::vector<float>> data;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<float> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stof(cell));
        }

        data.push_back(row);
    }

    file.close();
    return data;
}

// Function to write CSV file
void writeCSV(const std::string& filepath, const std::vector<std::vector<float>>& data) {
    std::ofstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filepath << std::endl;
        return;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }

    file.close();
}

int main() {
    std::string inputFile = "/home/nessy/Desktop/testOpCore/data/real.csv";
    std::string outputFile = "/home/nessy/Desktop/testOpCore/data/result.csv";

    // Read data from CSV file
    std::vector<std::vector<float>> rawData = readCSV(inputFile);
    if (rawData.empty()) {
        std::cerr << "No data read from CSV file!" << std::endl;
        return 1;
    }

    // Initialize Kalman Filter
    float deltaT = 0.01f;
    Matrix<float, 3, 1> p_0 = {0.0f, 0.0f, 0.0f};
    Matrix<float, 3, 1> dp_0 = {0.0f, 0.0f, 0.0f};
    Matrix<float, 3, 1> ddp_0 = {0.0f, 0.0f, 0.0f};
    KalmanFusion kf(p_0, dp_0, ddp_0, deltaT);

    std::vector<std::vector<float>> filteredData;

    // Process each row with the Kalman filter
    for (const auto& row : rawData) {
        if (row.size() < 9) continue; // Ensure the row has enough data

        Matrix<float, 3, 1> p = {row[0], row[1], row[2]};
        Matrix<float, 3, 1> dp = {row[3], row[4], row[5]};
        Matrix<float, 3, 1> ddp = {row[6], row[7], row[8]};

        kf.kalman_estimate(p, dp, ddp);

        // Get filtered values
        Matrix<float, 3, 1> p_filtered, dp_filtered, ddp_filtered;
        kf.getState(p_filtered, dp_filtered, ddp_filtered);

        // Save filtered results
        filteredData.push_back({
            p_filtered(0,0), p_filtered(1,0), p_filtered(2,0),
            dp_filtered(0,0), dp_filtered(1,0), dp_filtered(2,0),
            ddp_filtered(0,0), ddp_filtered(1,0), ddp_filtered(2,0)
        });
    }

    // Write filtered results to CSV
    writeCSV(outputFile, filteredData);
    std::cout << "Filtered data saved to: " << outputFile << std::endl;

    kf.Pk.print();

    return 0;
}
