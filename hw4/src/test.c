int f(int a, int b){
    /*
    int c[10];
    */
    return a+b;
}

int main(){
    /*
    int a[10], c;
    a = 0;
    int b = a;
    a = c;
    */
    int a = 1;
    float b[10.6];
    {
        int a;
    }
    /*
    f(a, b);
    */
    a = f(a, b[0]);
    return 0;
}
