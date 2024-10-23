#include <stdio.h>
#include <string.h>

#define MAX_TURMAS 10
#define MAX_ALUNOS 50
#define NUM_NOTAS 5
#define FREQUENCIA_MINIMA 75.0
#define MEDIA_MINIMA 60.0

typedef struct {
    char nome[50];
    int matricula;
    float notas[NUM_NOTAS]; // P1, P2, E1, E2, T1
    float media;
    int frequencia; // Frequência em percentual
    char situacao[15]; // "Aprovado" ou "Reprovado"
} Aluno;

typedef struct {
    char nome[50];
    Aluno alunos[MAX_ALUNOS];
    int num_alunos;
} Turma;

typedef struct {
    Turma turmas[MAX_TURMAS];
    int num_turmas;
} Professor;

// Funções
void menu(Professor *professor);
void funcao_cadastra_turma(Professor *professor);
void funcao_cadastra_aluno(Turma *turma);
void funcao_cadastra_notas(Turma *turma);
void funcao_calcula_media(Aluno *aluno);
void funcao_imprimir_dados(Turma *turma);
void funcao_imprimir_lista(Turma *turma, int tipo);
void funcao_imprimir_situacao(Turma *turma, int matricula);

int main() {
    Professor professor = { .num_turmas = 0 };
    menu(&professor);
    return 0;
}

// Função para exibir o menu principal
void menu(Professor *professor) {
    int opcao, turma_selecionada;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Turma\n");
        printf("2. Cadastrar Alunos\n");
        printf("3. Cadastrar Notas\n");
        printf("4. Imprimir Dados\n");
        printf("5. Imprimir Lista de Situações\n");
        printf("6. Imprimir Situação de um Aluno\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer após ler a opção

        switch (opcao) {
            case 1:
                funcao_cadastra_turma(professor);
                break;
            case 2:
                if (professor->num_turmas > 0) {
                    printf("Selecione a turma (0 a %d): ", professor->num_turmas - 1);
                    scanf("%d", &turma_selecionada);
                    getchar();
                    if (turma_selecionada >= 0 && turma_selecionada < professor->num_turmas) {
                        funcao_cadastra_aluno(&professor->turmas[turma_selecionada]);
                    } else {
                        printf("Turma inválida.\n");
                    }
                } else {
                    printf("Nenhuma turma cadastrada.\n");
                }
                break;
            case 3:
                if (professor->num_turmas > 0) {
                    printf("Selecione a turma para cadastrar notas (0 a %d): ", professor->num_turmas - 1);
                    scanf("%d", &turma_selecionada);
                    getchar();
                    if (turma_selecionada >= 0 && turma_selecionada < professor->num_turmas) {
                        funcao_cadastra_notas(&professor->turmas[turma_selecionada]);
                    } else {
                        printf("Turma inválida.\n");
                    }
                } else {
                    printf("Nenhuma turma cadastrada.\n");
                }
                break;
            case 4:
                if (professor->num_turmas > 0) {
                    printf("Selecione a turma para imprimir os dados (0 a %d): ", professor->num_turmas - 1);
                    scanf("%d", &turma_selecionada);
                    getchar();
                    if (turma_selecionada >= 0 && turma_selecionada < professor->num_turmas) {
                        funcao_imprimir_dados(&professor->turmas[turma_selecionada]);
                    } else {
                        printf("Turma inválida.\n");
                    }
                } else {
                    printf("Nenhuma turma cadastrada.\n");
                }
                break;
            case 5:
                if (professor->num_turmas > 0) {
                    printf("Selecione a turma para imprimir a lista de situações (0 a %d): ", professor->num_turmas - 1);
                    scanf("%d", &turma_selecionada);
                    getchar();
                    if (turma_selecionada >= 0 && turma_selecionada < professor->num_turmas) {
                        printf("1. Todos os alunos\n2. Apenas aprovados\n3. Apenas reprovados\nEscolha: ");
                        int tipo;
                        scanf("%d", &tipo);
                        getchar();
                        funcao_imprimir_lista(&professor->turmas[turma_selecionada], tipo);
                    } else {
                        printf("Turma inválida.\n");
                    }
                } else {
                    printf("Nenhuma turma cadastrada.\n");
                }
                break;
            case 6:
                if (professor->num_turmas > 0) {
                    printf("Selecione a turma para consultar um aluno (0 a %d): ", professor->num_turmas - 1);
                    scanf("%d", &turma_selecionada);
                    getchar();
                    if (turma_selecionada >= 0 && turma_selecionada < professor->num_turmas) {
                        int matricula;
                        printf("Digite a matrícula do aluno: ");
                        scanf("%d", &matricula);
                        getchar();
                        funcao_imprimir_situacao(&professor->turmas[turma_selecionada], matricula);
                    } else {
                        printf("Turma inválida.\n");
                    }
                } else {
                    printf("Nenhuma turma cadastrada.\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

// Função para cadastrar uma turma
void funcao_cadastra_turma(Professor *professor) {
    if (professor->num_turmas < MAX_TURMAS) {
        Turma nova_turma;
        printf("Nome da turma: ");
        scanf(" %[^\n]%*c", nova_turma.nome);
        nova_turma.num_alunos = 0;
        professor->turmas[professor->num_turmas] = nova_turma;
        professor->num_turmas++;
        printf("Turma cadastrada com sucesso!\n");
    } else {
        printf("Número máximo de turmas atingido.\n");
    }
}

// Função para cadastrar um aluno
void funcao_cadastra_aluno(Turma *turma) {
    if (turma->num_alunos < MAX_ALUNOS) {
        Aluno novo_aluno;
        printf("Nome do aluno: ");
        scanf(" %[^\n]%*c", novo_aluno.nome);
        printf("Matrícula: ");
        scanf("%d", &novo_aluno.matricula);
        getchar();
        printf("Informe a frequência (0 a 100): ");
        scanf("%d", &novo_aluno.frequencia);
        getchar();

        for (int i = 0; i < NUM_NOTAS; i++) {
            novo_aluno.notas[i] = 0.0;
        }

        strcpy(novo_aluno.situacao, "Não definido");
        turma->alunos[turma->num_alunos] = novo_aluno;
        turma->num_alunos++;

        printf("Aluno cadastrado com sucesso!\n");
    } else {
        printf("Número máximo de alunos atingido para esta turma.\n");
    }
}

// Função para cadastrar notas e calcular a média
void funcao_cadastra_notas(Turma *turma) {
    int aluno_index;
    printf("Digite o número do aluno (0 a %d): ", turma->num_alunos - 1);
    scanf("%d", &aluno_index);
    getchar();

    if (aluno_index >= 0 && aluno_index < turma->num_alunos) {
        Aluno *aluno = &turma->alunos[aluno_index];
        printf("Informe as notas de P1, P2, E1, E2, T1:\n");
        for (int i = 0; i < NUM_NOTAS; i++) {
            scanf("%f", &aluno->notas[i]);
        }
        funcao_calcula_media(aluno);
    } else {
        printf("Aluno não encontrado.\n");
    }
}

// Função para calcular a média e definir a situação do aluno
void funcao_calcula_media(Aluno *aluno) {
    aluno->media = (aluno->notas[0] * 0.30) + (aluno->notas[1] * 0.50) +
                   (aluno->notas[2] * 0.05) + (aluno->notas[3] * 0.05) +
                   (aluno->notas[4] * 0.10);

    if (aluno->media >= MEDIA_MINIMA && aluno->frequencia >= FREQUENCIA_MINIMA) {
        strcpy(aluno->situacao, "Aprovado");
    } else {
        strcpy(aluno->situacao, "Reprovado");
    }

    printf("Média do aluno: %.2f\n", aluno->media);
}

// Função para imprimir os dados de todos os alunos de uma turma
void funcao_imprimir_dados(Turma *turma) {
    printf("\nDados da turma %s:\n", turma->nome);
    for (int i = 0; i < turma->num_alunos; i++) {
        Aluno *aluno = &turma->alunos[i];
        printf("Nome: %s, Matrícula: %d, Média: %.2f, Frequência: %d%%, Situação: %s\n",
               aluno->nome, aluno->matricula, aluno->media, aluno->frequencia, aluno->situacao);
    }
}

// Função para imprimir a lista de alunos por tipo de situação
void funcao_imprimir_lista(Turma *turma, int tipo) {
    printf("\nSituação dos alunos da turma %s:\n", turma->nome);
    for (int i = 0; i < turma->num_alunos; i++) {
        Aluno *aluno = &turma->alunos[i];
        if ((tipo == 1) || (tipo == 2 && strcmp(aluno->situacao, "Aprovado") == 0) ||
            (tipo == 3 && strcmp(aluno->situacao, "Reprovado") == 0)) {
            printf("Nome: %s, Matrícula: %d, Média: %.2f, Frequência: %d%%, Situação: %s\n",
                   aluno->nome, aluno->matricula, aluno->media, aluno->frequencia, aluno->situacao);
        }
    }
}

// Função para imprimir a situação de um aluno específico
void funcao_imprimir_situacao(Turma *turma, int matricula) {
    for (int i = 0; i < turma->num_alunos; i++) {
        Aluno *aluno = &turma->alunos[i];
        if (aluno->matricula == matricula) {
            printf("\nDados do aluno:\n");
            printf("Nome: %s\nMatrícula: %d\nMédia: %.2f\nFrequência: %d%%\nSituação: %s\n",
                   aluno->nome, aluno->matricula, aluno->media, aluno->frequencia, aluno->situacao);
            for (int j = 0; j < NUM_NOTAS; j++) {
                printf("Nota %d: %.2f\n", j + 1, aluno->notas[j]);
            }
            return;
        }
    }
    printf("Aluno com matrícula %d não encontrado.\n", matricula);
}