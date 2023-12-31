/* iaed-23 - ist1103687 - project2.h */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Definição Constantes */

#define VERDADE 1
#define FALSO 0
#define NAO_ENCONTRADO -1

#define ERRO_PARSING 1
#define EXIT_FAILURE 1
#define MAX_TAMANHO_LINHA 65535         /*mudificado pois preciso de allocar a memória da linha de comandos*/

#define MAX_NOME_PARAGEM 51
#define MAX_NOME_CARREIRA 21


/* Definicao de Tipos de Dados */

typedef struct _Carreira{
    /*como o nome da Carreira não tem máximo de caracteres, 
    tive que criar um apontador para o nome que está no buffer todo
    (linha de comandos que não ultrapassa o MAX_TAMANHO_LINHA)*/
    char *nome;
    double custoTotal;
    double duracaoTotal;
    /*lista onde estou a guardar as ligações da carreira*/
    struct _LigacoesDaCarreira *lig_carreira;
    /*struct _Ligacao *p_ligacao[MAX_LIGACOES];*/
    /*struct _Ligacao *p_ligacaoNEXT;*/
    int numLigacoes;
    /*Para ter lista de carreiras ligada;*/
    struct _Carreira *nextCarreira;
} Carreira;

/*Para reservar as carreiras de cada paragem*/
typedef struct _CarreirasDaParagem{
    /*linked para todas as carreiras que estão numa paragem específica*/
    struct _Carreira *_carreirasDaParagem;
    struct _CarreirasDaParagem *cp_next;
}CarreirasDaParagem;

/*Para reservar as  ligações de cada carreira*/
typedef struct _LigacoesDaCarreira{
    /*linked para todas as ligações que estão numa carreira específica*/
    struct _Ligacao *_ligacaoDaParagem;
    
    /* Estrutura que guarda ponteiros para o nome da ligacaoDaCarreira,
    *  da ligacaoDaCarreira a eliminar e, para 
    *  poder usar uma linked list, a ligacaoDaCarreira seguinte.
    */
    struct _LigacoesDaCarreira *lc_next;
}LigacoesDaCarreira;

typedef struct _Paragem{
    /*como o nome da Paragem não tem máximo de caracteres, 
    tive que criar um apontador para o nome que está no buffer todo
    (linha de comandos que não ultrapassa o MAX_TAMANHO_LINHA)*/
    char *nome;
    double latitude, longitude;
    int numCarreiras;
    /*lista onde estou a guardar as paragens das carreiras*/
    struct _CarreirasDaParagem *P_carreiras;

    /* Estrutura que guarda ponteiros para o nome da paragem, da paragem a eliminar e, para 
    *  poder usar uma linked list, a paragem seguinte.
    */
    struct _Paragem *next;
} Paragem;

typedef struct _Ligacao{
    /*onde estou a guardar a carreira da ligação feita */
    struct _Carreira *p_carreira;
    /*onde estou a guardar as paragens:origem e destino de cada ligação*/
    struct _Paragem *p_origem, *p_destino;
    double custo, duracao;

    /* Estrutura que guarda ponteiros para o nome da ligação, da ligação a eliminar e, para 
    *  poder usar uma linked list, a ligação seguinte.
    */
    struct _Ligacao *nextLigacao;
} Ligacao;


/*                              FUNÇÕES PRINCIPAIS DO PROJ2                                 */

/*  funções usadas no comando _c_:  */
Carreira *carreiras(Carreira *_ListaCarreiras);
int leEspacos();
void leNome(char s[]);
void leAteFinalLinha();
Carreira *encontraCarreira(char nomeCarreira[], Carreira *_ListaCarreiras);
Carreira *criaCarreira(char nomeCarreira[], Carreira *_ListaCarreiras);
void mostraLigacoesCarreira(Carreira *p_carreira, int inverso);
Carreira *ultimaCarreira(Carreira *_ListaCarreiras);
void ultimaCarreiraDaParagem(CarreirasDaParagem **cp_paragem, CarreirasDaParagem *newCP);

/*  funções usadas no comando _p_: */
Paragem *paragens(Paragem *_ListaParagens);
Paragem *ultimaParagem(Paragem *_ListaParagens);
void listaParagens(Paragem *_ListaParagens);
void mostraParagem(Paragem *_paragem);
Paragem *encontraParagem(char nomeParagem[], Paragem *_ListaParagens);
Paragem *criaParagem(char nomeParagem[], double latitude, double longitude, Paragem *_ListaParagens);

/*  funções usadas no comando _l_: */
Ligacao *ligacoes(Carreira *_ListaCarreiras, Paragem *_ListaParagens, Ligacao *_ListaLigacoes);
void leNomesComando(char nomeCarreira[], char nomeOrigem[], char nomeDestino[]);
void leNomesComando(char nomeCarreira[], char nomeOrigem[], char nomeDestino[]);
Carreira *encontraCarreira(char nomeCarreira[], Carreira *_ListaCarreiras);
Paragem *encontraParagem(char nomeParagem[], Paragem *_ListaParagens);
Ligacao *adicionaLigacao(Carreira *p_Carreira, Paragem *p_Origem, Paragem *p_Destino, double custo, double duracao, Ligacao *_ListaLigacoes);
Ligacao *ultimaLigacao(Ligacao *_ListaLigacoes);

/*  funções usadas no comando _i_: */
/*void intersecoes();
void ordenaCarreiras(int idCarreiras[], int numCarreiras)*/
