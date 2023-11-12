# CSC501_A2-SIMD-SKYLINE

# SIMD Computation Project

## Overview
This project implements a Skyline computation algorithm in both scalar and SIMD versions. The goal is to analyze the performance difference between the two implementations.

This project uses a naive method to solve the Skyline problem, which means it compares a point with every other points in the data set. It adopts the key findings in the V-skyline paper, which aims at utilizing SIMD instructions to perform dominance tests faster.  

## Prerequisites
- C++ compiler with support for SSE2 (for SIMD implementation)
- [Optional] Performance analysis tool in Visual studio 2022 Community.

## Build Instructions
To build the project, follow these steps:
1. Clone the repository: `git clone https://github.com/your-username/skyline-computation.git`
2. Navigate to the project directory: `cd skyline-computation`
3. Build the scalar version: `g++ skyline_scalar.cpp -o skyline_scalar`
4. Build the SIMD version: `g++ -msse2 skyline_simd.cpp -o skyline_simd`

## Usage
- Run the scalar version: `./skyline_scalar`
- Run the SIMD version: `./skyline_simd`

## License
This project is licensed under the [MIT License](LICENSE).

## Acknowledgments
- [Reference Paper on Skyline Computation](https://example.com/skyline-paper)](https://doi.org/10.1145/1893173.1893176)
