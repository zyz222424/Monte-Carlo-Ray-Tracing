#pragma once

#include "Ray.h"
#include "Types.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

/// @class AABB
class AABB {
public:
    /// left buttom of AABB
    Vec3f m_min;
    /// right top of AABB
    Vec3f m_max;

    /// @brief constructor of AABB
    explicit AABB() : m_min(Vec3f(FLT_MAX, FLT_MAX, FLT_MAX)),
        m_max(Vec3f(-FLT_MAX, -FLT_MAX, -FLT_MAX)) {};   //��ʼ����Χ��

    /// @brief constructor of AABB
    explicit AABB(Vec3f min_val, Vec3f high_val) : m_min(min_val),
        m_max(high_val) {};         //��ʼ����Χ��

    /// @brief merge two AABB
    static AABB Merge(const AABB &bbox1, const AABB &bbox2);    //��Χ�еĺϲ�

    /// @brief get center of AABB along given axis
    /// @param axis the axis given
    inline float Center(int axis) {
        return (m_min(axis) + m_max(axis)) / 2;   //�Ը����������е�
    }

    /// @brief get center of AABB
    inline Vec3f Center() {
        return (m_min + m_max) / 2;       //�õ�AABB���е�
    }

    /// @brief ray intersect with AABB
    /// @param ray the ray to test intersection
    bool Intersect(Ray &ray);
};
