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
    int vectorSizes[] = {2e5, 2e5, 2e7};
    int results[2][3] = {
        {0,0,0},
        {0,0,0}
    };

    printf("Scalar value: ");
    scanf("%f", &scalar);

    printf("Vector X is initialized as [1, ... , vector_size ] \n");
    printf("Vector X is initialized as [ 11 + 0, ... , 11 + vector_size ] \n");


    for(int i = 0; i < 1; i++) {
        xC = (float*)malloc(vectorSizes[i] * sizeof(float));
        xAsm = (float*)malloc(vectorSizes[i] * sizeof(float));
        y = (float*)malloc(vectorSizes[i] * sizeof(float));

        for(int j = 0; j < 30; j++) {
            intializeVectors(xC, y, vectorSizes[i]);
            start = clock();
            cFunc(xC, xAsm, scalar, vectorSizes[i]);
            end = clock();
            results[0][i] += ((double)(end - start)) / CLOCKS_PER_SEC;
        }

        for(int j = 0; j < 30; j++) {
            intializeVectors(xAsm, y, vectorSizes[i]);
            start = clock();
            // asmFunc(vectorSizes[i], xAsm, y, scalar);
            cFunc(xAsm, xAsm, scalar, vectorSizes[i]);
            end = clock();
            results[1][i] += ((double)(end - start)) / CLOCKS_PER_SEC;
        }

        printf("C Output:");
        for(int j = 0; j < 10; j++) {
            printf("%f ", xC[j]);
        }
        printf("\nAsm Output:");
        for(int j = 0; j < 10; j++) {
            printf("%f ", xC[j]);
        }

        int isValid = 1;
        for(int j = 0; i < vectorSizes[i]; i++) {
            if(!are_floats_equal(xC[j], xAsm[j], epsilon)) {
                isValid = 0;
                break;
            }
        }

        printf("\nThe x86-64 output is %s\n", isValid? "correct" : "incorrect");

        free(xC);
        free(xAsm);
        free(y);

        printf("done");
    }

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", results[i][j]);
        }
        printf("\n");
    }

    return 0;
}
