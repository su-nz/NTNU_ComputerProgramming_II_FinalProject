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
    vec.SIZE +=1;
    vec.array[SIZE-1] = val;
}
void popbackVector(vector* vec) {
    vec.array[SIZE-1] = 0;
    vec.SIZE -=1;
}
void clearVector(vector* vec) {
    while(vec.SIZE!=0){
        vec.array[SIZE-1] = 0;
        vec.SIZE -=1;
    }
}
void eraseVector(vector* vec, int index) {
  int newsize = vec.SIZE-1 ; 
  vec.array[index] = 0;
  for(int i = index ; i < newsize ; i++){
      vec.array[index] = vec.array[index+1];
  }
  vec.SIZE-- ;
}
