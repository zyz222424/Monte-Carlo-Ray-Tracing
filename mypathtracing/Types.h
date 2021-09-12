#pragma once

#include <cmath>
#include <Eigen/Eigen>  
#include <random>

/// vector type, use Eigen matrix
typedef Eigen::Matrix<float, 3, 1> Vec3f;

/// @brief clamp to some range
/// @param num num to clamp
/// @param left left of range
/// @param right right of range
inline void clampfloat(float& num, float left, float right)
{
	if (num > right)
		num = right;
	else if (num < left)
		num = left;

}

inline void Clamp(Vec3f &num, float left, float right) {
    for (int i = 0; i < 3; ++i) {
        if (num(i) > right) {
            num(i) = right;
        } else if (num(i) < left) {
            num(i) = left;
        }
    }
}

/// @brief fast rand
// Ref: https://software.intel.com/en-us/articles/fast-random-number-generator-on-the-intel-pentiumr-4-processor
inline int fastrand() {  //快速取得随机数
    static int g_seed = 0;
    g_seed++;
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}

/// @brief get random float from 0 to 1
/// @retval random float from 0 to 1
inline float Rand01() {     //得到0-1之间随机的浮点数
    return float(fastrand()) / 0x7FFF;
}


