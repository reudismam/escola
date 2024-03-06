#include <stdio.h>

typedef struct {
    int mat;
    char nome[10];
    float media;
} estudante;

void cadastrar() {
    FILE* file = fopen("estudante.b", "ab");
    estudante e;
    printf("Informe os dados do estudante\n");
    scanf("%d %s %f", &e.mat, e.nome, &e.media);
    fwrite(&e, sizeof(estudante), 1, file);
    fclose(file);
}

void buscar(int mat) {
    FILE* file = fopen("estudante.b", "rb");
    estudante e;
    int entrou = 0;
    while (fread(&e, sizeof(estudante), 1, file)) {
        if (e.mat == mat) {
            printf("%d %s %f\n", e.mat, e.nome, e.media);
            entrou = 1;
        }
    }
    if (!entrou) {
        printf("Aluno nao encontrado\n");
    }
    fclose(file);
}

void listar() {
    FILE* file = fopen("estudante.b", "rb");
    estudante e;
    while (fread(&e, sizeof(estudante), 1, file)) {
        printf("%s\n", e.nome);
    }
    fclose(file);
}

int tamanho() {
    FILE* file = fopen("estudante.b", "rb");
    estudante e;
    int cont=0;
    while (fread(&e, sizeof(estudante),1, file)) {
       cont++;
    }
    fclose(file);
    return cont;
}

void excluir(int mat) {
    int n = tamanho();
    estudante v[n];
    FILE* file = fopen("estudante.b", "rb");
    estudante e;
    int i = 0;
    while (fread(&e, sizeof(estudante), 1, file)) {
        v[i] = e;
        i++;
    }
    fclose(file);
    file = fopen("estudante.b", "wb");;
    for (i = 0; i < n; i++) {
        if (v[i].mat != mat) {
            fwrite(&v[i], sizeof(estudante), 1, file);
        }
    }
    fclose(file);
}

void menu() {
    printf("escolha uma opcao\n");
    printf("1 - cadastrar\n");
    printf("2 - listar\n");
    printf("3 - buscar\n");
    printf("4 - tamanho\n");
    printf("5 - excluir\n");
    printf("0 - sair\n");

}


int main() {
    int op;
    menu();
    scanf("%d", &op);

    while (op != 0) {
        if (op == 1) {
            cadastrar();
        }
        else if (op == 2) {
            listar();
        }
        else if (op == 3) {
            int mat;
            printf("Informe a matricula desejada:");
            scanf("%d", &mat);
            buscar(mat);
        }
        else if (op == 4) {
            int n = tamanho();
            printf("tamanho: %d\n", n);
        }
        else if (op == 5) {
            int mat;
            printf("Informe a matricula desejada:");
            scanf("%d", &mat);
            buscar(mat);
            excluir(mat);
        }
        menu();
        scanf("%d", &op);
    }
}