#include "vector.h"

vector initVector() {
    vector v;
    for (int i = 0; i < 256; i++) {
        v.array[i] = 0;
    }
    v.SIZE = 0;
    return v;
}
void pushbackVector(vector* vec, int32_t val) {
    if ((*vec).SIZE < 256) {
        (*vec).array[(*vec).SIZE] = val;
        (*vec).SIZE += 1;
    }else{
        printf("Max is 256!\n");
    }
}
void popbackVector(vector* vec) {
    if ((*vec).SIZE > 0) {
        (*vec).SIZE -= 1;
        (*vec).array[(*vec).SIZE] = 0;
    }else{
        printf("Min is 0!\n");
    }
}
void clearVector(vector* vec) {
    while((*vec).SIZE!=0){
        (*vec).array[(*vec).SIZE-1] = 0;
        (*vec).SIZE -=1;
    }
}
void eraseVector(vector* vec, int index) {
  if (index < 0 || index >= (*vec).SIZE) return; 

    for (int i = index; i < (*vec).SIZE - 1; i++) {
        (*vec).array[i] = (*vec).array[i + 1]; 
    }
    (*vec).SIZE -= 1;
    (*vec).array[(*vec).SIZE] = 0; 
}

