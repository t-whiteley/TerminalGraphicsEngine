#include "LINALG.h"

Matrix::Matrix(int h, int w) {
    y = h;
    x = w;

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            vals[i][j] = 0.0; // Initialize all elements to 0
        }
    }
}


void Matrix::print() {
    std::cout << "[\n";
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            std::cout << vals[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "]\n\n";
}


void Matrix::fill(float num) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            vals[i][j] = num;
        }
    }
}


void Matrix::normalize() {
    float mag = 0.0;
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            mag += vals[i][j] * vals[i][j];
        }
    }
    mag = std::sqrt(mag);
    if (mag != 0) {
        for (int i = 0; i < y; ++i) {
            for (int j = 0; j < x; ++j) {
                vals[i][j] /= mag;
            }
        }
    }

}


void Matrix::scale(float n) {
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            vals[i][j] *= n;
        }
    }
}


void Matrix::multiply(Matrix& n, Matrix& dest) {
    assert(x == n.y);
    assert(dest.y == x);
    assert(dest.x == n.x);

    for (int i = 0; i < dest.y; i++) {
        for (int j = 0; j < dest.x; j++) {

            float num = 0;
            for (int k = 0; k < x; k++) {
                num += vals[i][k] * n.vals[k][j];
            }
            dest.vals[i][j] = num;
        }
    }
}


void Matrix::cross_product3(Matrix& vector1, Matrix& dest) {
    assert(y == 3 && x == 1 && vector1.y == 3 && vector1.x == 1);
    assert(dest.y == 3 && dest.x == 1);

    dest.vals[0][0] = vals[1][0] * vector1.vals[2][0] - vals[2][0] * vector1.vals[1][0];
    dest.vals[1][0] = vals[2][0] * vector1.vals[0][0] - vals[0][0] * vector1.vals[2][0];
    dest.vals[2][0] = vals[0][0] * vector1.vals[1][0] - vals[1][0] * vector1.vals[0][0];
}


void Matrix::transpose(Matrix& dest) {
    assert(dest.x == x && dest.y == y);

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            dest.vals[j][i] = vals[i][j];
        }
    }
}


void Matrix::Vector3_toHG(Matrix& dest) {
    assert(y==3 && x==1);
    assert(dest.y==4 && dest.x==1);

    dest.vals[0][0] = vals[0][0];
    dest.vals[1][0] = vals[1][0];
    dest.vals[2][0] = vals[2][0];
    dest.vals[3][0] = 1;
}

void Matrix::HG_toVector3(Matrix& dest) {
    assert(y==4 && x==1);
    assert(dest.y == 3 && dest.x == 1);

    dest.vals[0][0] = vals[0][0];
    dest.vals[1][0] = vals[1][0];
    dest.vals[2][0] = vals[2][0];

    if (vals[3][0] != 0) {
        dest.scale(1/vals[3][0]);
    }
}



Matrix Vector3(float x, float y, float z) {
    Matrix m(3, 1);
    m.vals[0][0] = x;
    m.vals[1][0] = y;
    m.vals[2][0] = z;
    return m;
}
Matrix RotX(float d_theta) {
    float cosTheta = cos(d_theta);
    float sinTheta = sin(d_theta);
    Matrix rotX(4, 4);
    rotX.fill(0);
    rotX.vals[0][0] = 1;
    rotX.vals[1][1] = cosTheta;
    rotX.vals[1][2] = -sinTheta;
    rotX.vals[2][1] = sinTheta;
    rotX.vals[2][2] = cosTheta;
    rotX.vals[3][3] = 1;
    return rotX;
}
Matrix RotY(float d_theta) {
    float cosTheta = cos(d_theta);
    float sinTheta = sin(d_theta);
    Matrix rotY(4, 4);
    rotY.fill(0);
    rotY.vals[0][0] = cosTheta;
    rotY.vals[0][2] = sinTheta;
    rotY.vals[1][1] = 1;
    rotY.vals[2][0] = -sinTheta;
    rotY.vals[2][2] = cosTheta;
    rotY.vals[3][3] = 1;
    return rotY;
}
Matrix RotZ(float d_theta) {
    float cosTheta = cos(d_theta);
    float sinTheta = sin(d_theta);
    Matrix rotZ(4, 4);
    rotZ.fill(0);
    rotZ.vals[0][0] = cosTheta;
    rotZ.vals[0][1] = -sinTheta;
    rotZ.vals[1][0] = sinTheta;
    rotZ.vals[1][1] = cosTheta;
    rotZ.vals[2][2] = 1;
    rotZ.vals[3][3] = 1;
    return rotZ;
}
Matrix Trans(float dx, float dy, float dz) {
    Matrix trans(4, 4);
    trans.fill(0);
    trans.vals[0][0] = 1;
    trans.vals[1][1] = 1;
    trans.vals[2][2] = 1;
    trans.vals[3][3] = 1;
    trans.vals[0][3] = dx;
    trans.vals[1][3] = dy;
    trans.vals[2][3] = dz;
    return trans;
}