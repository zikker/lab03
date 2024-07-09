#include "histogram.h"
#include <cassert>

void test_positive();
void test_negative();
void test_same();
void test_single();
void test_void();

void test_overline();
void test_invalid();

int main() {
    test_positive();
    test_negative();
    test_same();
    test_single();

    test_overline();
    test_invalid();
}

void test_positive(){
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}


void test_negative(){
    double min = 0, max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}


void test_same(){
    double min = 0, max = 0;
    find_minmax({5, 5, 5}, min, max);
    assert(min == 5);
    assert(max == 5);
}


void test_single(){
    double min = 0, max = 0;
    find_minmax({2}, min, max);
    assert(min == 2);
    assert(max == 2);
}


void test_void(){
    double min = 0, max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}


void test_overline(){
    string decoration = "overline";
    assert(check_decoration(decoration) == true);
}


void test_invalid(){
    string decoration = "line";
    assert(check_decoration(decoration) == false);

}