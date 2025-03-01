#include <iostream>
#include <OpCore/Matrix.h>
#include <OpCore/Vector.h>

int main() {
    // 1. Test Matrix creation
    OpCore::Matrix<float, 2, 2> mat1({1.0f, 2.0f, 3.0f, 4.0f});
    OpCore::Matrix<float, 2, 2> mat2({5.0f, 6.0f, 7.0f, 8.0f});
    
    // 2. Test Matrix addition
    auto mat_add = mat1 + mat2;
    std::cout << "Matrix Addition Result: \n";
    mat_add.print();
    
    // 3. Test Matrix multiplication
    OpCore::Matrix<float, 2, 3> mat3({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f});
    OpCore::Matrix<float, 3, 2> mat4({7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f});
    
    auto mat_mult = mat3 * mat4;
    std::cout << "Matrix Multiplication Result: \n";
    mat_mult.print();
    
    // 4. Test Matrix transposition
    auto mat_transpose = mat1.transpose();
    std::cout << "Matrix Transposition Result: \n";
    mat_transpose.print();
    
    // 5. Test Matrix inverse (only for square matrices)
    try {
        auto mat_inv = mat1.inverse();
        std::cout << "Matrix Inverse Result: \n";
        mat_inv.print();
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // 6. Test Vector creation
    OpCore::Vector<float, 3> vec1({1.0f, 2.0f, 3.0f});
    OpCore::Vector<float, 3> vec2({4.0f, 5.0f, 6.0f});
    
    // 7. Test Vector addition
    auto vec_add = vec1 + vec2;
    std::cout << "Vector Addition Result: ";
    vec_add.print();
    
    // 8. Test Vector dot product
    auto dot_prod = vec1.dot(vec2);
    std::cout << "Dot Product Result: " << dot_prod << std::endl;
    
    // 9. Test Vector scalar multiplication
    auto vec_scalar_mult = vec1 * 2.0f;
    std::cout << "Vector Scalar Multiplication Result: ";
    vec_scalar_mult.print();
    
    // 10. Test Vector concatenation
    OpCore::Vector<float, 2> vec3({7.0f, 8.0f});
    auto vec_concat = vec1.hconcat(vec3);
    std::cout << "Vector Horizontal Concatenation Result: ";
    vec_concat.print();
    
    return 0;
}
