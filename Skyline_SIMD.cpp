#include <iostream>
#include <emmintrin.h> // Include for SSE2 intrinsics
#include <vector>
#include <random>

const int numDimensions = 4; // Number of dimensions in the data

// SIMD Skyline computation
void skylineSIMD(__m128i* points, int numPoints) {
    for (int i = 0; i < numPoints; ++i) {
        bool isDominatedByOthers = false;

        for (int j = 0; j < numPoints; ++j) {
            // Perform SIMD comparisons for four dimensions at once
            __m128i gtMask = _mm_cmpgt_epi32(points[i], points[j]); // GT (greater-than) comparison

            // Simulate GE (greater-than-or-equal) using bitwise OR
            __m128i geMask = _mm_or_si128(gtMask, _mm_cmpeq_epi32(points[i], points[j]));

            // Extract integer values from the SIMD results
            int gtAnyBitResult = _mm_movemask_epi8(gtMask);
            int geAllBitsResult = _mm_movemask_epi8(geMask);

            // Check if point i is dominated by any other point
            if (gtAnyBitResult == 0 && geAllBitsResult == 0) {
                isDominatedByOthers = true;
                break;
            }
        }

        // Print the point if it is not dominated by others
        if (!isDominatedByOthers) {
            std::cout << "Point " << i << " is in the Skyline." << std::endl;
        }

    }
}

int main() {
    const int numPoints = 100;
    __m128i points[numPoints];

    // Generate 100 random 4-dimensional points
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < numPoints; ++i) {
        // Initialize points (for simplicity, using 4D points as integers)
        int data[numDimensions] = { dist(gen), dist(gen), dist(gen), dist(gen) };
        points[i] = _mm_set_epi32(data[3], data[2], data[1], data[0]);
    }

    skylineSIMD(points, numPoints);

    return 0;
}
