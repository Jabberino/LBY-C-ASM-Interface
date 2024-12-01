#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern float asmFunc(int vectorSize, float* input1, float* input2, float scalar);
void cFunc(float* input1, float* input2, float scalar, int vectorSize) {
    int i;
    for (i = 0; i < vectorSize - (vectorSize % 4); i += 4) {
        input1[i] = input1[i] * scalar;
        input1[i] = input1[i] + input2[i];
        input1[i + 1] = input1[i + 1] * scalar;
        input1[i + 1] = input1[i + 1] + input2[i + 1];
        input1[i + 2] = input1[i + 2] * scalar;
        input1[i + 2] = input1[i + 2] + input2[i + 2];
        input1[i + 3] = input1[i + 3] * scalar;
        input1[i + 3] = input1[i + 3] + input2[i + 3];
    }
    for (; i < vectorSize; i++) {
        input1[i] = input1[i] * scalar;
        input1[i] = input1[i] + input2[i];
    }

}
void intializeVectors(float* input1, float* input2, int vectorSize) {
    for (int i = 0; i < vectorSize; i++) {
        input1[i] = i + 1;
        input2[i] = i + 11;
    }

}
int are_floats_equal(float a, float b, float epsilon) {
    return (a - b) < epsilon;
}

int main(void) {
    // Declare clock and vectors
    clock_t start, end;
    float* xC, * xAsm, * y;

    // Declare and intialize parameters
    float epsilon = 0.00001f;
    float scalar = 2.0f;
    int vectorSize = 1;
    int vectorInput = 0;

    // Intialize results
    double cPerformance = 0;
    double asmPerformance = 0;


    printf("Vector size 2e^: ");
    scanf_s("%d"
        "", &vectorInput);
    vectorSize = vectorSize << vectorInput;
    printf("Scalar value: ");
    scanf_s("%f", &scalar);

    printf("Vector X is initialized as [1, ... , vector_size ] \n");
    printf("Vector X is initialized as [ 11 + 0, ... , 11 + vector_size ] \n");

    xC = (float*)malloc(vectorSize * sizeof(float));
    xAsm = (float*)malloc(vectorSize * sizeof(float));
    y = (float*)malloc(vectorSize * sizeof(float));

    for (int i = 0; i < 30; i++) { // run 30 times
        intializeVectors(xC, y, vectorSize);
        start = clock();
        cFunc(xC, y, scalar, vectorSize);
        end = clock();
        cPerformance += ((double)(end - start) * 1000.0 / CLOCKS_PER_SEC);
    }

     for(int i = 0; i < 30; i++) { // run 30 times
         intializeVectors(xAsm, y, vectorSize);
         start = clock();
         asmFunc(vectorSize, xAsm, y, scalar);
         end = clock();
         asmPerformance += ((double)(end - start) * 1000.0 / CLOCKS_PER_SEC);
     }


    printf("C Output  : ");
    for (int j = 0; j < 10; j++) {
        printf("%f ", xC[j]);
    }
    printf("\nAsm Output: ");
    for (int j = 0; j < 10; j++) {
        printf("%f ", xAsm[j]);
    }
    
    int isValid = 1;
    for (int j = 0; j < vectorSize; j++) {
        if (!are_floats_equal(xC[j], xAsm[j], epsilon)) {
            isValid = 0;
            break;
        }
    }

    printf("\nThe x86-64 output is %s\n\n", isValid ? "correct" : "incorrect");

    free(xC);
    free(xAsm);
    free(y);

    printf("After running 30 times: \n");
    printf("\nPerformance C  : %lfms\n", cPerformance / 30);
    printf("Performance ASM: %lfms\n", asmPerformance / 30);


    return 0;
}
