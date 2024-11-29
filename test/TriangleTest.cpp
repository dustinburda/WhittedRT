//
// Created by Dustin on 11/25/24.
//

#include <gtest/gtest.h>

#include "../include/Triangle.h"

TEST(TriangleTest, InTriangle)
{
   Triangle t (Point<double, 3> {0.0, 0.0, 0.0}, Point<double, 3> {1.0, 0.0, 0.0}, Point<double, 3> {0.5, 0.866, 0.0}, nullptr);
   std::array<double, 3> coordinates {0.0, 0.0, 0.0};

   coordinates = t.BarycentricCoordinates(Point3d {0.0, 0.0, 0.0});

   coordinates = t.BarycentricCoordinates(Point3d {1.0, 0.0, 0.0});
   //
   coordinates = t.BarycentricCoordinates(Point3d {0.5, 0.866, 0.0});


   Vector<double, 3> v1 {t.Points()[0][0], t.Points()[0][1], t.Points()[0][2] };
   Vector<double, 3> v2 {t.Points()[1][0], t.Points()[1][1], t.Points()[1][2] };
   Vector<double, 3> v3 {t.Points()[2][0], t.Points()[2][1], t.Points()[2][2] };

   double l1 = coordinates[0];
   double l2 = coordinates[1];
   double l3 = coordinates[2];

   auto bary_hit_point = l1 * v1 + l2 * v2 + l3 * v3;





}

