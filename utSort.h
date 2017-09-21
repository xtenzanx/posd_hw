#ifndef HW1_H
#define HW1_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
#include <vector>

using namespace std;

TEST (Sort, sortByIncreasingPerimeter) {
    Rectangle rec(1, 2, 2, 2);
    Circle cir(1, 2, 2);
    vertex v1 = {1, 4};
    vertex v2 = {2, 1};
    vertex v3 = {4, 3};
    Triangle tri(v1, v2, v3);
    list<Shape *> Shapes;
    Shapes.push_back(&cir);
    Shapes.push_back(&tri);
    Shapes.push_back(&rec);
    Sort sort;
    sort.sortByIncreasingPerimeter(&Shapes);
    ASSERT_EQ(" name:r, perimeter= 8 name:t, perimeter= 9.15298 name:c, perimeter= 12.5664", sort.sortPerimeterOut(&Shapes));

    // cout << "rectangle " << rec.perimeter() << endl;
    // cout << "triangle " << tri.perimeter() << endl;
    // cout << "circle " << cir.perimeter() << endl;
}

TEST (Sort, sortByDecreasingPerimeter) {
    Rectangle rec(1, 2, 2, 2);
    Circle cir(1, 2, 2);
    vertex v1 = {1, 4};
    vertex v2 = {2, 1};
    vertex v3 = {4, 3};
    Triangle tri(v1, v2, v3);
    list<Shape *> Shapes;
    Shapes.push_back(&rec);
    Shapes.push_back(&tri);
    Shapes.push_back(&cir);
    Sort sort;
    sort.sortByDecreasingPerimeter(&Shapes);
    ASSERT_EQ(" name:c, perimeter= 12.5664 name:t, perimeter= 9.15298 name:r, perimeter= 8", sort.sortPerimeterOut(&Shapes));
    // cout << "circle " << cir.perimeter() << endl;
    // cout << "triangle " << tri.perimeter() << endl;
    // cout << "rectangle " << rec.perimeter() << endl;
}

TEST (Sort, sortByIncreasingArea) {
    Rectangle rec(1, 2, 3, 3);
    Circle cir(1, 2, 3);
    vertex v1 = {1, 4};
    vertex v2 = {2, 1};
    vertex v3 = {4, 3};
    Triangle tri(v1, v2, v3);
    list<Shape *> Shapes;
    Shapes.push_back(&rec);
    Shapes.push_back(&tri);
    Shapes.push_back(&cir);
    Sort sort;
    sort.sortByIncreasingArea(&Shapes);
    ASSERT_EQ(" name:t, area= 4 name:r, area= 9 name:c, area= 28.2743", sort.sortAreaOut(&Shapes));
    // cout << "triangle " << tri.area() << endl;
    // cout << "rectangle " << rec.area() << endl;
    // cout << "circle " << cir.area() << endl;
}

TEST (Sort, sortByDecreasingArea) {
    Rectangle rec(1, 2, 3, 3);
    Circle cir(1, 2, 3);
    vertex v1 = {1, 4};
    vertex v2 = {2, 1};
    vertex v3 = {4, 3};
    Triangle tri(v1, v2, v3);
    list<Shape *> Shapes;
    Shapes.push_back(&rec);
    Shapes.push_back(&tri);
    Shapes.push_back(&cir);
    Sort sort;
    sort.sortByDecreasingArea(&Shapes);
    ASSERT_EQ(" name:c, area= 28.2743 name:r, area= 9 name:t, area= 4", sort.sortAreaOut(&Shapes));
    // cout << "circle " << cir.area() << endl;
    // cout << "rectangle " << rec.area() << endl;
    // cout << "triangle " << tri.area() << endl;
}

TEST (Sort, sortByIncreasingCompactness) {
    Rectangle rec(1, 2, 3, 3);
    Circle cir(1, 2, 3);
    vertex v1 = {1, 4};
    vertex v2 = {2, 1};
    vertex v3 = {4, 3};
    Triangle tri(v1, v2, v3);
    list<Shape *> Shapes;
    Shapes.push_back(&rec);
    Shapes.push_back(&tri);
    Shapes.push_back(&cir);
    Sort sort;
    sort.sortByIncreasingCompactness(&Shapes);
    ASSERT_EQ(" name:t, area= 0.0477458 name:r, area= 0.0625 name:c, area= 0.0795775", sort.sortCompactnessOut(&Shapes));
    // cout << "triangle " << tri.area()/tri.perimeter()/tri.perimeter() << endl;
    // cout << "rectangle " << rec.area()/rec.perimeter()/rec.perimeter() << endl;
    // cout << "circle " << cir.area()/cir.perimeter()/cir.perimeter() << endl;
}

#endif
