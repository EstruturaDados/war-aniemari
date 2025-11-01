#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
} Usuario;

typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    char editora[100];
    int edicao;
    int disponivel; // 1 = disponivel, 0 = emprestado
} Livro;

typedef struct {
    int id;
    Usuario *usuario;
    Livro *livro;
    char dataEmprestimo[11];
    char dataDevolucao[11];
} Emprestimo;

// Funcoes
Usuario* criarUsuario(int id);
Livro* criarLivro(int id);
Emprestimo* criarEmprestimo(int id, Usuario *usuarios, int qtdUsuarios, Livro *livros, int qtdLivros);
void listarUsuarios(Usuario *usuarios, int qtd);
void listarLivros(Livro *livros, int qtd);
void listarEmprestimos(Emprestimo *emprestimos, int qtd);
void liberarMemoria(Usuario *usuarios, Livro *livros, Emprestimo *emprestimos);

int main() {
    Usuario *usuarios = NULL;
    Livro *livros = NULL;
    Emprestimo *emprestimos = NULL;
    int qtdUsuarios = 0, qtdLivros = 0, qtdEmprestimos = 0;
    int opcao;

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Criar usuario\n");
        printf("2. Criar livro\n");
        printf("3. Criar emprestimo\n");
        printf("4. Listar usuarios\n");
        printf("5. Listar livros\n");
        printf("6. Listar emprestimos\n");
        printf("0. Sair\n");
        printf("==========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                usuarios = realloc(usuarios, (qtdUsuarios + 1) * sizeof(Usuario));
                if (usuarios == NULL) {
                    printf("Erro ao alocar memoria para usuarios.\n");
                    exit(1);
                }
                usuarios[qtdUsuarios] = *criarUsuario(qtdUsuarios + 1);
                qtdUsuarios++;
                break;
            case 2:
                livros = realloc(livros, (qtdLivros + 1) * sizeof(Livro));
                if (livros == NULL) {
                    printf("Erro ao alocar memoria para livros.\n");
                    exit(1);
                }
                livros[qtdLivros] = *criarLivro(qtdLivros + 1);
                qtdLivros++;
                break;
            case 3:
                if (qtdUsuarios == 0 || qtdLivros == 0) {
                    printf("Cadastre pelo menos um usuario e um livro antes de realizar emprestimos.\n");
                    break;
                }
                emprestimos = realloc(emprestimos, (qtdEmprestimos + 1) * sizeof(Emprestimo));
                if (emprestimos == NULL) {
                    printf("Erro ao alocar memoria para emprestimos.\n");
                    exit(1);
                }
                Emprestimo *novo = criarEmprestimo(qtdEmprestimos + 1, usuarios, qtdUsuarios, livros, qtdLivros);
                if (novo != NULL) {
                    emprestimos[qtdEmprestimos] = *novo;
                    qtdEmprestimos++;
                }
                break;
            case 4:
                listarUsuarios(usuarios, qtdUsuarios);
                break;
            case 5:
                listarLivros(livros, qtdLivros);
                break;
            case 6:
                listarEmprestimos(emprestimos, qtdEmprestimos);
                break;
            case 0:
                liberarMemoria(usuarios, livros, emprestimos);
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}

// Funcoes auxiliares

Usuario* criarUsuario(int id) {
    Usuario *u = malloc(sizeof(Usuario));
    if (u == NULL) {
        printf("Erro ao alocar memoria para usuario.\n");
        exit(1);
    }
    u->id = id;
    printf("Digite o nome do usuario: ");
    fgets(u->nome, 100, stdin);
    u->nome[strcspn(u->nome, "\n")] = '\0';
    return u;
}

Livro* criarLivro(int id) {
    Livro *l = malloc(sizeof(Livro));
    if (l == NULL) {
        printf("Erro ao alocar memoria para livro.\n");
        exit(1);
    }
    l->id = id;
    printf("Titulo: ");
    fgets(l->titulo, 100, stdin);
    l->titulo[strcspn(l->titulo, "\n")] = '\0';
    printf("Autor: ");
    fgets(l->autor, 100, stdin);
    l->autor[strcspn(l->autor, "\n")] = '\0';
    printf("Editora: ");
    fgets(l->editora, 100, stdin);
    l->editora[strcspn(l->editora, "\n")] = '\0';
    printf("Edicao: ");
    scanf("%d", &l->edicao);
    getchar();
    l->disponivel = 1;
    return l;
}

Emprestimo* criarEmprestimo(int id, Usuario *usuarios, int qtdUsuarios, Livro *livros, int qtdLivros) {
    Emprestimo *e = calloc(1, sizeof(Emprestimo));
    if (e == NULL) {
        printf("Erro ao alocar memoria para emprestimo.\n");
        exit(1);
    }

    printf("\n--- Usuarios disponiveis ---\n");
    listarUsuarios(usuarios, qtdUsuarios);
    printf("\n--- Livros disponiveis ---\n");
    listarLivros(livros, qtdLivros);

    int idUsuario, idLivro;
    printf("\nDigite o ID do usuario: ");
    scanf("%d", &idUsuario);
    printf("Digite o ID do livro: ");
    scanf("%d", &idLivro);
    getchar();

    if (idUsuario < 1 || idUsuario > qtdUsuarios || idLivro < 1 || idLivro > qtdLivros) {
        printf("ID invalido.\n");
        free(e);
        return NULL;
    }

    if (livros[idLivro - 1].disponivel == 0) {
        printf("Livro ja esta emprestado.\n");
        free(e);
        return NULL;
    }

    e->id = id;
    e->usuario = &usuarios[idUsuario - 1];
    e->livro = &livros[idLivro - 1];
    printf("Data do emprestimo (dd/mm/aaaa): ");
    fgets(e->dataEmprestimo, 11, stdin);
    getchar();
    printf("Data da devolucao (dd/mm/aaaa): ");
    fgets(e->dataDevolucao, 11, stdin);
    getchar();

    livros[idLivro - 1].disponivel = 0;
    return e;
}

void listarUsuarios(Usuario *usuarios, int qtd) {
    printf("\n--- Lista de Usuarios ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("ID: %d | Nome: %s\n", usuarios[i].id, usuarios[i].nome);
    }
}

void listarLivros(Livro *livros, int qtd) {
    printf("\n--- Lista de Livros ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("ID: %d | Titulo: %s | Autor: %s | Disponivel: %s\n",
               livros[i].id, livros[i].titulo, livros[i].autor,
               livros[i].disponivel ? "Sim" : "Nao");
    }
}

void listarEmprestimos(Emprestimo *emprestimos, int qtd) {
    printf("\n--- Lista de Emprestimos ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("Emprestimo #%d\n", emprestimos[i].id);
        printf("Usuario: %s\n", emprestimos[i].usuario->nome);
        printf("Livro: %s\n", emprestimos[i].livro->titulo);
        printf("Data do Emprestimo: %s\n", emprestimos[i].dataEmprestimo);
        printf("Data da Devolucao: %s\n\n", emprestimos[i].dataDevolucao);
    }
}

void liberarMemoria(Usuario *usuarios, Livro *livros, Emprestimo *emprestimos) {
    free(usuarios);
    free(livros);
    free(emprestimos);
}