#include <iostream>
#include <emmintrin.h>
#include <vector>
#include <random>
#include <chrono>
#include <omp.h>

const int numDimensions = 4;

void skylineSIMD(int* pointsData, int numPoints, std::vector<int>& skylineIndices) {
    __m128i* points = (__m128i*)pointsData;

    #pragma omp parallel for
    for (int i = 0; i < numPoints; ++i) {
        bool isDominatedByOthers = false;

        for (int j = 0; j < numPoints; ++j) {
            __m128i gtMask = _mm_cmpgt_epi32(points[i], points[j]);
            __m128i geMask = _mm_or_si128(gtMask, _mm_cmpeq_epi32(points[i], points[j]));

            int gtAnyBitResult = _mm_movemask_epi8(gtMask);
            int geAllBitsResult = _mm_movemask_epi8(geMask);

            if (gtAnyBitResult == 0 && geAllBitsResult == 0) {
                isDominatedByOthers = true;
                break;
            }
        }

        #pragma omp critical
        {
            if (!isDominatedByOthers) {
                skylineIndices.push_back(i);
            }
        }
    }
}

int main() {
    const int numPoints = 10000;
    int pointsData[numPoints * numDimensions];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < numPoints * numDimensions; ++i) {
        pointsData[i] = dist(gen);
    }

    std::vector<int> skylineIndices;

    int numThreads = 8; 
    omp_set_num_threads(numThreads);

    
    auto start = std::chrono::high_resolution_clock::now();

    skylineSIMD(pointsData, numPoints, skylineIndices);


    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;


    std::cout << "Skyline Points: ";
    for (int index : skylineIndices) {
        std::cout << index << " ";
    }
    std::cout << std::endl;
    return 0;
}
