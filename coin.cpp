#include <bits/stdc++.h>

using namespace std;

#define BLOCK_SIZE 1024 // amount of data per block
#define ALL(x) (x).begin(), (x).end()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // read file
    FILE* fp = fopen("Pitcoin.txt", "r");
    if (!fp) {
        fprintf(stderr, "Error: Could not open file 'Pitcoin_sample.txt'\n");
        return 1;
    }

    int dataCnt;
    fscanf(fp, "%d", &dataCnt);
    vector<long long> times(dataCnt);
    vector<double> prices(dataCnt);
    for (int i = 0; i < dataCnt; i++) {
        fscanf(fp, "%lld %lf", &times[i], &prices[i]);
    }
    fclose(fp);

    // min/max per blocks
    int blockCnt = (dataCnt + BLOCK_SIZE - 1) / BLOCK_SIZE;
    vector<double> blockMinPrice(blockCnt, 1e18);
    vector<double> blockMaxPrice(blockCnt, -1e18);
    for (int i = 0; i < dataCnt; i++) {
        int blockIdx = i / BLOCK_SIZE;
        blockMinPrice[blockIdx] = min(blockMinPrice[blockIdx], prices[i]);
        blockMaxPrice[blockIdx] = max(blockMaxPrice[blockIdx], prices[i]);
    }

    // get input
    int queryCnt;
    scanf("%d", &queryCnt);

    while (queryCnt--) {
        long long startTime, endTime;
        scanf("%lld %lld", &startTime, &endTime);

        // index of start, end
        auto startIt = upper_bound(ALL(times), startTime);
        auto endIt   = upper_bound(ALL(times), endTime);
        int startIdx = distance(times.begin(), startIt) - 1;
        int endIdx   = distance(times.begin(), endIt) - 1;

        if (endIdx < 0 && startIdx < 0) {
            printf("%.3f %.3f\n", prices[0], prices[0]);
            continue;
        }
        if (startIdx < 0) startIdx = 0;
        if (endIdx < 0) endIdx = 0;
        if (startIdx > endIdx) {
            if (startIdx < dataCnt) {
                printf("%.3f %.3f\n", prices[startIdx], prices[startIdx]);
            }
            continue;
        }

        double minPrice = 1e18;
        double maxPrice = -1e18;

        // block index
        int startBlockIdx = startIdx / BLOCK_SIZE;
        int endBlockIdx   = endIdx / BLOCK_SIZE;
        if (startBlockIdx == endBlockIdx) { // if min and max is in the same block
            for (int i = startIdx; i <= endIdx; ++i) {
                minPrice = min(minPrice, prices[i]);
                maxPrice = max(maxPrice, prices[i]);
            }
        } else {
            // search left block
            for (int i = startIdx; i < (startBlockIdx + 1) * BLOCK_SIZE; ++i) {
                minPrice = min(minPrice, prices[i]);
                maxPrice = max(maxPrice, prices[i]);
            }
            // search middle block
            for (int b = startBlockIdx + 1; b < endBlockIdx; ++b) {
                minPrice = min(minPrice, blockMinPrice[b]);
                maxPrice = max(maxPrice, blockMaxPrice[b]);
            }
            // search right block
            for (int i = endBlockIdx * BLOCK_SIZE; i <= endIdx; ++i) {
                minPrice = min(minPrice, prices[i]);
                maxPrice = max(maxPrice, prices[i]);
            }
        }
        printf("%.3f %.3f\n", minPrice, maxPrice);
    }

    return 0;
}