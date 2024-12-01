# LBY-C-ASM-Interface
## Table of Contents 
1. [Introduction](#introduction)
2. [Execution times and analysis](#execution-times-and-analysis)
3. [Outputs](#outputs)
4. [Videos](#videos)



## Introduction
This is a project for the Term 1, Year 2024-2025 CSARCH2 course.  
Where we create a C and X86-64 assembly program that solves the following equation:  

$Z[i] = A * X[i] + Y[i]$  
Where:  
$A$ is a scalar single-precision floating-point.  
$X, Y, Z$ is a vector containing single-precision floating-point values.

## Execution times and analysis

### Set 1: with no fractional part
  Vector X is initialized as [ 1, ... , vector_size ] 
  Vector Y is initialized as [ 11 + 0, ... , 11 + (vector_size - 1) ] 
  
| Vector Size | 2^20   | 2^24   | 2^30   | 
|-------------|--------|--------|--------|
| C           | 3.933333 | 49.133333 | 4253.533333 | 
| Assembly    | 2.766667 | 31.833333 | 4264.566667 |
| Same output | Yes    | Yes    | Yes    |

### Set 2: with fractional part
  Vector X is initialized as [ 25.83944 + 0, ... , 25.83944 + (vector_size - 1) ] 
  Vector Y is initialized as [ 100.9324 + 0, ... , 100.9324 + (vector_size - 1) ]
| Vector Size | 2^20   | 2^24   | 2^30   | 
|-------------|--------|--------|--------|
| C           | 3.133333 | 47.000000 | 3431.033333 | 
| Assembly    | 2.333337 | 31.600000 | 2427.500000 |
| Same output | Yes    | Yes    | Yes    |

*Note: The values are averages of 30 runs.*

### Performance
### Accuracy

## Outputs

## Videos
