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
The program is designed to take an integer that will serve as the exponent of 2, defining the vector size. Scalar value is also taken from user input, while Vectors X and Y are initialized within the program.  

The functions, written in C and Assembly, to perform the required calculation was executed 30 times. Afterwards, the average execution time for each version were recorded. The values obtained **almost consistently showed that C takes more time to run compared to Assembly**. For 2^20, there's a difference of approximately 1 millisecond and for 2^24, there's at least a 15-millisecond difference. However, when the exponent is increased to 30, the time difference between C and Assembly became unpredictable. In the first set where the vectors contained whole numbers, Assembly became slightly slower than C but in the second set Assembly was again faster than C (by around 1000 milliseconds).


### Accuracy
For all instances, both C and Assembly resulted to the same output. Although the codes written in the aforementioned languages slightly differ with the format, the logic was closely similar. In C, the operation ( A * X[i] + Y[i] ) happens less frequently than its Assembly counterpart as it calculates for every 4 elements. On the other hand, Assembly performs the calculation one element at a time. Nonetheless, there were no problems in having a consistent output as the logic strictly followed A * X[i] + Y[i].


## Outputs
### Set 1: with no fractional part
Vector X is initialized as [ 1, ... , vector_size ]  
Vector Y is initialized as [ 11 + 0, ... , 11 + (vector_size - 1) ]  
![9](https://github.com/user-attachments/assets/356814cb-cefd-4d61-b019-f6d7fdb5580a)
### Set 2: with fractional part
Vector X is initialized as [ 25.83944 + 0, ... , 25.83944 + (vector_size - 1) ]  
Vector Y is initialized as [ 100.9324 + 0, ... , 100.9324 + (vector_size - 1) ]  
![14](https://github.com/user-attachments/assets/216d80ff-a94d-4d66-812e-2ef01641f712)

## Videos
