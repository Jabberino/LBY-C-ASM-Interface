#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
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
    return fabs(a - b) < epsilon;
}

int main(void) {
    clock_t start, end;
    float* xC, * xAsm, * y;

    float epsilon = 0.00001f;
    size_t vector_size = 12;
    float scalar = 2.0f;

    xC = (float*)malloc(vector_size * sizeof(float));
    xAsm = (float*)malloc(vector_size * sizeof(float));
    y = (float*)malloc(vector_size * sizeof(float));
    intializeVectors(xC, y, vector_size);

    // C start
    start = clock();
    cFunc(xC, y, scalar, vector_size);
    end = clock();
    double C_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    // C end
    //------------------- C Sanity Check --------------------    //------------------- ASM Sanity Check ------------------
    printf("C SANITY CHECK \n");
    int isValid = 1;
    for (int i = 0; i < vector_size; i++) {
        if (i < 10) {
            printf("%f , ", xC[i]);
        }
        if (!are_floats_equal(xC[i], xC[i], epsilon)) {
            // printf("mismatch at %f, %f\n", asmAns[i], cAns[i]);
            isValid = 0;
            break;
        }
    }
    printf("The loop took %f seconds to execute\n", C_time);
    free(y);

    y = (float*)malloc(vector_size * sizeof(float));
    intializeVectors(xAsm, y, vector_size);

    // ASM start
    start = clock();
    //cFunc(xAsm, y, scalar, vector_size);
    asmFunc(vector_size, xAsm, y, scalar);
    end = clock();
    double asm_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    //------------------- ASM Sanity Check ------------------
    printf("ASM SANITY CHECK \n");
    for (int i = 0; i < vector_size; i++) {
        if (i < 10)
        printf("%f , ", xAsm[i]);
    }
    printf("The loop took %f seconds to execute\n", asm_time);
    // ASM end






    free(y);
    free(xC);
    free(xAsm);


    if (isValid) {
        printf("\nSuccess");
    }
    else {
        printf("\nFailed");
    }
    return 0;
}
