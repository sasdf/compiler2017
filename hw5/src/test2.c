int x() {
    return 1;
}

int MAIN() {
    int i;
    i = 0;
    x();
    if (i > 0) {
        write(i);
        i = i + 1;
    }else if (x() == 1) {
        write("x == 1\n");
        i = i + 1;
    }else{
        write("7122\n");
        i = i + 1;
    }
    return 0.5;
}
