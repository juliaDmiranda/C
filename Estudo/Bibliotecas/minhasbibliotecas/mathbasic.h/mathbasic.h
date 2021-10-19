int som(int a,int b){
    return a+b;}

int sub(int a,int b){
    return a - b;
}

int somIntervalo(int a, int b){
    int som = 0;
    for (int i = a; i <= b; i++)
        som+=i;
    return som;
}