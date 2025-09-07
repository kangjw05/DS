#include <iostream>
#include <cmath>
#include <algorithm> // swap

using namespace std;

int main() {
    double PI = 3.14159265358979;
    double r1, r2, x1, x2, y1, y2;

    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    if (r1 < r2) {
        swap(x1, x2);
        swap(y1, y2);
        swap(r1, r2);
    }

    double d = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    double outer = sqrt(pow(d, 2) - pow(r1 - r2, 2));
    
    double theta = acos((r1 - r2) / d);

    // length of sector part
    double l1 = r1 * (PI - theta);
    double l2 = r2 * theta;

    double length = 2 * outer + 2 * l1 + 2 * l2;

    double area = (r1 + r2) * outer + r1 * l1 + r2 * l2;
    
    cout << floor(area) << " " << floor(length) << " " << theta;

    return 0;
}