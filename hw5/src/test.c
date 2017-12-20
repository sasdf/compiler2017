int a[10][3*(2+4)], b, c;
int d, e[1+2+3][2][3];
float f;

int bb(){
    int a, b, c;
    return c;
}

int aa(){
    int a=2, b=1, c= 1;
    //int d[100];
    //for (int i = 0; i < 100; ++i)
    //    d[i] = 0xdeadbeef;
    bb();
    int *p = alloca(10);
    return 1;
}

float _start(int argc, int argv){
    int a[10][3*(2+4)], b, c;
    int d, e[1+2+3][2][3];
    float f;
    {
        int jizz[10][10][10];
        float yee;
    }
    aa();
    return 0;
}
