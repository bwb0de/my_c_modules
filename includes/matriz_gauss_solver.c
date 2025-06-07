void gaussSolver(int n, double A[n][n], double b[n], double X[n]) {
    int i, j, k, l, m;
    //ETAPA DE ESCALONAMENTO
    for (k = 0; k < n - 1; k++) {
        double max = fabs(A[k][k]);
        int maxIndex = k;
        //procura o maior k-ésimo coeficiente em módulo
        for (i = k + 1; i < n; i++) {
            if (max < fabs(A[i][k])) {
                max = fabs(A[i][k]);
                maxIndex = i;
            }
        }
        if (maxIndex != k) {
            /*
             troca a equação k pela equação com o
             maior k-ésimo coeficiente em módulo
             */
            for (j = 0; j < n; j++) {
                double temp = A[k][j];
                A[k][j] = A[maxIndex][j];
                A[maxIndex][j] = temp;
            }
            double temp = b[k];
            b[k] = b[maxIndex];
            b[maxIndex] = temp;
        }
        //Se A[k][k] é zero, então a matriz dos coeficiente é singular
        //det A = 0
        if (A[k][k] == 0) {
            printf("A matriz dos coeficientes é singular\n");
            return;
        } else {
            //realiza o escalonamento
            for (m = k + 1; m < n; m++) {
                double F = -A[m][k] / A[k][k];
                A[m][k] = 0; //evita uma iteração
                b[m] = b[m] + F * b[k];
                for (l = k + 1; l < n; l++) {
                    A[m][l] = A[m][l] + F * A[k][l];
                }
            }
        }
    }
    //ETAPA DE RESOLUÇÃO DO SISTEMA
    for (i = n - 1; i >= 0; i--) {
        X[i] = b[i];
        for (j = i + 1; j < n; j++) {
            X[i] = X[i] - X[j] * A[i][j];
        }
        X[i] = X[i] / A[i][i];
    }
}
