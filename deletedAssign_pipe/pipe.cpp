#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>

using namespace std;

int x, y, d, h, w;

int main() {
    cin >> x >> y >> d >> h >> w;

    int t;

    cin >> t;
    vector<tuple<int, int>> points;
    string results[10];  // 결과 저장용 배열

    for (int i = 0; i < t; i++) {
        int tx, ty;
        cin >> tx >> ty;
        points.emplace_back(tx, ty);
    }
    int i = 0;

    for (const auto& point : points) {
        results[i] = is_in(point);
        i++;
    }

    return 0;
}

string is_in(tuple<int, int> point) {
    int tx = get<0>(point);
    int ty = get<1>(point);

    if((tx < (x-d) && ty < h) || (tx < w && ty < (y-d))) {
        return "IN";
    }
    else if((tx == (x-d) && ty > y) || (tx > x && ty == (y-d)) ||
    (tx == 0 && ty <= h) || (tx <= w && ty == 0) || 
    (tx <= (x-d) && ty == h) ||(tx == w && ty <= (y-d))) {
        return "ON";
    }
    else if(((x-d) <= tx <= x) && ((y-d) <= ty <= y)) {
        double distance = get_distance(point);
        if (distance == d) {
            return "ON";
        }
        else if(distance < d) {
            return "OUT";
        }
        else {
            return "IN";
        }
    }
    else return "OUT";
}

double get_distance(tuple<int, int> point) {
    int tx = get<0>(point);
    int ty = get<1>(point);
    double dis = sqrt(pow((x - tx), 2) + pow((y-ty), 2));
    return dis;
}