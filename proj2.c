/* iaed-23 - ist1103687 - project2.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "project2.h"

/* Funções para parsing do input */

/* Le espaços. Devolve 0 se chegou ao final de linha ou 1 caso contrário. */
int leEspacos() {
    int c;
    while ((c = getchar()) == ' ' || c == '\t');
    if (c == '\n') 
        return 0;
    ungetc(c, stdin);
    return 1;
}

/* Le um nome para a string que recebe como parametro. */
void leNome(char s[]) {
    int i = 0, c;
    s[0] = getchar();
    if (s[0] != '"') {
        i = 1;
        while ((c = getchar()) != ' ' && c != '\t' && c != '\n')
            s[i++] = c;
        ungetc(c, stdin);
    }
    else {
        while((c = getchar()) != '"')
            s[i++] = c;
    }
    s[i++] = '\0';
}

/* Le todo o texto até ao final de linha. */
void leAteFinalLinha(){
	char c = getchar();
	while (c != '\n')
		c = getchar();
}

/*                              FUNÇÕES PARA TRATAR COMANDOS                                 */

/*FUNÇÕES PARA TRATAR AS CARREIRAS*/

/* Mostra no output a carreira
   input: c <nome_da_carreira> 
   Função que lista todo o contiúdo da carreira que está na ListaCarreiras
   caso já tenha sido criada uma carreira com esse nome.*/
void mostraCarreira(Carreira *carreira) {
    int numLigacoes =carreira->numLigacoes;
    printf("%s ", carreira->nome);
    if (numLigacoes > 0) {

        printf("%s ", carreira->lig_carreira->_ligacaoDaParagem->p_origem->nome);
        printf("%s ", ultimaLigacao(carreira->lig_carreira->_ligacaoDaParagem)->p_destino->nome);
        printf("%d ", numLigacoes+1);
        printf("%.2f ", carreira->custoTotal);
        printf("%.2f\n", carreira->duracaoTotal);
    }
    else 
        printf("%d %.2f %.2f\n", 0, 0.0, 0.0);
}

/* Mostra no output a carreira
   input: c [ <nome-da-carreira> [ inverso ] ]
   Função que lista todas as ligações da carreira
   por ordem inversa de criação da Carreira*/
void mostraLigacoesCarreira(Carreira *p_carreira, int inverso) {                               
    int l, numLigacoes = p_carreira->numLigacoes;

    if (numLigacoes == 0) 
        return;
    if (inverso == FALSO) {
        for (l = 0; l < numLigacoes; l++) {
            printf("%s, ", p_carreira->lig_carreira->_ligacaoDaParagem->p_origem->nome);
            if (p_carreira->lig_carreira->lc_next != NULL){
                p_carreira->lig_carreira = p_carreira->lig_carreira->lc_next;
            }
        }
        printf("%s\n", p_carreira->lig_carreira->_ligacaoDaParagem->p_destino->nome);
    }
    /*else {
        for (l = numLigacoes-1; l >= 0; l--) {
            idLigacao = _carreiras[i].idLigacoes[l];
            printf("%s, ", _paragens[_ligacoes[idLigacao].idDestino].nome);
        }
        idLigacao = _carreiras[i].idLigacoes[0];
        printf("%s\n", _paragens[_ligacoes[idLigacao].idOrigem].nome);
    }*/
}

/* Mostra todas as carreiras. 
   input: c
   Função que lista todas as carreiras por ordem de criação*/
void listaCarreiras(Carreira *_ListaCarreiras) {
    /* começando no inicio da lista enquanto o proximo nao for NULL imprimo o nome da carreira*/
    while (_ListaCarreiras != NULL){
        /* input: c <nome_da_carreira>
        Função que lista todo o contiúdo da carreira que está na ListaCarreiras
        caso já tenha sido criada uma carreira com esse nome.
        */
        mostraCarreira(_ListaCarreiras);
        /*próxima posição da minha linked list*/
        _ListaCarreiras = _ListaCarreiras->nextCarreira;
    }
}

/* Procura uma carreira por nome.
   Devolve carreira do tipo Carreira ou NAO_ENCONTRADO se não existe. */
Carreira *encontraCarreira(char nomeCarreira[], Carreira *_ListaCarreiras) {
    /*percorre a linked list */
    while(_ListaCarreiras!= NULL){
        if (strcmp(_ListaCarreiras->nome, nomeCarreira) == 0)
            /*se já existe devolve a carreira com o noeCarreira pois são iguais */
            return _ListaCarreiras;
        /*percorre a linked list */
        _ListaCarreiras = _ListaCarreiras->nextCarreira;
    }
    return NULL;

}

/* Procura se uma paragem existe numa carreira.
   Se existir, devolve o indice da primeira ligação que usa
   a paragem. Caso contrário, devolve NAO_ENCONTRADO. */
int encontraParagemCarreira(Carreira *p_carreira, Paragem *p_paragem) {                    /*TRATAR DESTA FUNÇÃOOOOOOOO*/
    int numLigacoes = p_carreira->numLigacoes;
    int i;
    Ligacao *ligacao;
    for (i = 0; i < numLigacoes; i++) {
        ligacao = p_carreira->lig_carreira->_ligacaoDaParagem;
        if (ligacao->p_origem == p_paragem)
            return i;
    }
    ligacao = ultimaLigacao(p_carreira->lig_carreira->_ligacaoDaParagem);
    if (ligacao->p_destino == p_paragem)
        return numLigacoes;
    return NAO_ENCONTRADO;
}

/*Função ultimaCarreira*/
Carreira *ultimaCarreira(Carreira *_ListaCarreiras){
    if(_ListaCarreiras != NULL){
        /*percorre a lista até ao fim*/
        while(_ListaCarreiras->nextCarreira != NULL ){
            /*uso de linked lists*/
            _ListaCarreiras = _ListaCarreiras->nextCarreira;
        }
    }
    /*Devolve a ultima carreira*/
    return _ListaCarreiras;

}

/* Cria uma carreira nova. */
/* input : c <nome_da_carreira>
   output : devolve uma lista com as carreiras e cria todo o conteúdo presente na struct Carreira*/
Carreira *criaCarreira(char nomeCarreira[], Carreira *_ListaCarreiras) {

    Carreira *newC;

    /*aloca memória da minha carreira*/
    if((newC = ((Carreira*)malloc(sizeof(Carreira)))) == NULL){
        exit(EXIT_FAILURE);
    }  
    newC->custoTotal =0.0;
    newC->duracaoTotal = 0.0;
    newC->numLigacoes = 0;
    /*preciso de inicializar pois aloco a memória da próxima carreira mais para a frente no projt2*/
    newC->nextCarreira = NULL;

    /*aloca memória do tamanho do nome da carreira*/
    if((newC->nome = ((char*)malloc(sizeof(char) * (strlen(nomeCarreira)+1)))) == NULL){
        exit(EXIT_FAILURE);
    } 
    /*aloca memória do tamanho da minha lista de ligações presentes na minha carreira*/
    if((newC->lig_carreira = ((LigacoesDaCarreira *)malloc(sizeof(LigacoesDaCarreira)))) ==NULL){
        exit(EXIT_FAILURE);
    }
    /*preciso de inicializar pois aloco a memória da próxima ligação da minha carreira 
    mais para a frente no projt2*/
    newC->lig_carreira->lc_next = NULL;
    strcpy(newC->nome, nomeCarreira);
    if(_ListaCarreiras == NULL){
        _ListaCarreiras =newC;
    }
    else{
        /*função que devolve a próxima carreira presente da lista que é a minha carreira criada agora (newC) */
        ultimaCarreira(_ListaCarreiras)->nextCarreira = newC;
    }
    /*Adicionando cada carreira que vou criando na lista*/
    return _ListaCarreiras;
}

/* Verifica se a string é um prefixo de tamanho pelo menos 3 da
   palavra inverso. */
int verificaInversoOk(char s[]) {
    char inv[] = "inverso";
    int size = strlen(s), i;

    if (size < 3 || size > 7)
        return FALSO;
    for (i = 0; i < size; i++)
        if (inv[i] != s[i])
            return FALSO;
    return VERDADE;
}

/* Função para tratar do comando 'c'.
   Devolve a carreira que vou adicionando na ListaCarreiras (criada na main)
   para puder usar nos outros comandos*/
Carreira *carreiras( Carreira *_ListaCarreiras) {
    /*  Variável local    */
    char _buffer[MAX_TAMANHO_LINHA];
    char s[MAX_TAMANHO_LINHA];
    int fimLinha = leEspacos();
    Carreira *p_c;
    /*aloco memória da carreira que crio e faço a verificação se existe espaço para colocar contiúdo lá*/
    if((p_c = ((Carreira*)malloc(sizeof(Carreira)))) == NULL){
        exit(EXIT_FAILURE);
    }
    /* input sem argumentos: c
       input com argumentos: c <nome_da_carreira> (caso esta carreira já tenha sido criada, 
       lista o contiúdo da carreira).Enquanto não chega ao `/0' avalia que input e dado e 
       listaCarreiras a partir da minha lista Carreiras(onde estão lá todos que vão sendo criadas).*/
    if (!fimLinha) {
        listaCarreiras(_ListaCarreiras);
        return _ListaCarreiras;
    }

    leNome(s);
    /*encontraCarreira(): devolve a carreira presente na 
    listaDaCarreiras que vai corresponder à p_c*/
    p_c = encontraCarreira(s, _ListaCarreiras);
    fimLinha = leEspacos();
    if (!fimLinha) {
        if (p_c == NULL)
            /*não existe por isso cria uma nova com o nome atribuido no input*/
            return criaCarreira(s, _ListaCarreiras);
        else{
            /*existe, por isso mostra as carreiras consoante o input passado*/
            mostraLigacoesCarreira(p_c, FALSO); 

        }
    }
    else {
        leNome(_buffer);
        if (verificaInversoOk(_buffer)){
            /*mostraLigacoesCarreira(p_c, VERDADE);*/
        }
        else
            printf("incorrect sort option.\n");
        leAteFinalLinha();
    }
    return _ListaCarreiras;
}


/* Le nome de carreira e paragens de uma ligacao. */
void leNomesComando(char nomeCarreira[], char nomeOrigem[], char nomeDestino[]) {
    leEspacos();
    leNome(nomeCarreira);
    leEspacos();
    leNome(nomeOrigem);
    leEspacos();
    leNome(nomeDestino);
}


/*->FUNÇÕES PARA TRATAR AS PARAGENS*/

/*Última paragem*/
Paragem *ultimaParagem(Paragem *_ListaParagens){
    if(_ListaParagens != NULL){
        /*percorre a lista até ao fim*/
        while(_ListaParagens->next != NULL ){
            /*uso de linked lists*/
            _ListaParagens = _ListaParagens->next;
        }
    }
    return _ListaParagens;

}

/* Mostra uma paragem. 
   input: p <nome_da_paragem> 
   Função que lista todo o contiúdo da paragem que está na ListaParagens
   caso já tenha sido criada uma carreira com esse nome.*/
void mostraParagem(Paragem *_paragem) {
    printf("%s: %16.12f %16.12f %d\n", _paragem->nome, _paragem->latitude, 
            _paragem->longitude, _paragem->numCarreiras);
}

/* Mostra todas as paragens. 
   input: p 
   Função que lista todas as paragens que estão na ListaParagens 
   e o conteúdo de cada paragem*/
void listaParagens(Paragem *_ListaParagens) {
    /*enquanto houver paragens na ListaPargens*/
    while (_ListaParagens != NULL){

        mostraParagem(_ListaParagens);
        /*próxima posição da minha linked list*/
        _ListaParagens = _ListaParagens->next;
    }
}

/* Verifica se existe uma paragem com um determinado nome.
   Se existir devolve o indice. Caso contrário, devolve NAO_ENCONTRADO. */
Paragem *encontraParagem(char nomeParagem[], Paragem *_ListaParagens) {
    if (_ListaParagens != NULL){
        while(_ListaParagens!= NULL){
            if (strcmp(_ListaParagens->nome, nomeParagem) == 0)
            /*se já existe devolve a paragem com o nomeParagem pois são iguais */
                return _ListaParagens;
            /*passa para próxima paragem da list link*/
            _ListaParagens = _ListaParagens->next;
            
        }
    }
    /*não existe carreira*/
    return NULL;
}


/* Cria uma nova paragem. 
* input : p <nome_da_paragem>
   output : devolve uma lista com as paragens e cria todo o conteúdo presente na struct Paragem*/
Paragem *criaParagem(char nomeParagem[], double latitude, double longitude, Paragem *_ListaParagens) {
    Paragem *newP;

    /*aloca memória da minha paragem*/
    if((newP = ((Paragem*)malloc(sizeof(Paragem)))) == NULL){
        exit(EXIT_FAILURE);
    }
    newP->latitude =latitude;
    newP->longitude =longitude;
    newP->numCarreiras = 0;

    /*preciso de inicializar pois aloco a memória da próxima paragem da minha paragem 
    mais para a frente no projt2*/
    newP->next = NULL;

    /*aloca memória do tamanho do nome da carreira*/
    if((newP->nome = ((char*)malloc(sizeof(char)* (strlen(nomeParagem)+1)))) == NULL){
        exit(EXIT_FAILURE);
    }

    /*aloca memória do tamanho da minha lista das carreiras presentes na minha paragem*/
    if((newP->P_carreiras = ((CarreirasDaParagem*)malloc(sizeof(CarreirasDaParagem)))) == NULL){
        exit(EXIT_FAILURE);
    }
    strcpy(newP->nome, nomeParagem);
    if(_ListaParagens == NULL){
        _ListaParagens =newP;
    }
    else{
        /*função que devolve a próxima paragem presente da lista que é a minha paragem criada agora (newP) */
        ultimaParagem(_ListaParagens)->next= newP;
    }
    /*Adicionando cada paragem que vou criando na lista*/
    return _ListaParagens;
}


/* Função para tratar o comando 'p'.
   Devolve a paragem que vou adicionando na ListaParagens (criada na main)
   para puder usar nos outros comandos*/ 
Paragem *paragens(Paragem *_ListaParagens) {
    Paragem  *p_paragens;
    /*  Variáveis Locais    */
    char s[MAX_NOME_PARAGEM];
    int  fimLinha = leEspacos();

    /*aloco memória da paragem que crio e faço a verificação se existe espaço para colocar contiúdo lá*/
    if((p_paragens = ((Paragem*)malloc(sizeof(Paragem)))) == NULL){
        exit(EXIT_FAILURE);
    }
    /* input sem argumentos: p
       Enquanto não chega ao `/0' avalia que input e dado e listaParagens a partir da minha 
       lista Paragens(onde estão lá todos que vão sendo criadas)
    */
    if (!fimLinha) {
        listaParagens(_ListaParagens);
        return _ListaParagens;
    }
    leNome(s);
    fimLinha = leEspacos();
    if (!fimLinha) {
        p_paragens = encontraParagem(s, _ListaParagens);
        if (p_paragens == NULL)
            printf("%s: no such stop.\n", s);
        else{
            printf("%16.12f %16.12f\n", p_paragens->latitude, p_paragens->longitude);
        }
    }
    else {
        double latitude, longitude;
        scanf("%lf%lf", &latitude, &longitude);
        if (encontraParagem(s, _ListaParagens) == NULL)
        /*retorna uma nova paragem que não existe, ou sej acria uma nova*/
            return (criaParagem(s, latitude, longitude,_ListaParagens));
        else
            printf("%s: stop already exists.\n", s);
        leAteFinalLinha();
    }
    /*vai mudificando o que está na _ListaParegens que é a lista criada na main*/
    return _ListaParagens;
}


/* Funções para tratar as Ligações */

/*Última ligacao*/
Ligacao *ultimaLigacao(Ligacao *_ListaLigacoes){
    if(_ListaLigacoes != NULL){
        while(_ListaLigacoes->nextLigacao != NULL ){
            /*passa para a próxima ligação da minha linked list*/
            _ListaLigacoes = _ListaLigacoes->nextLigacao;
        }
    }
    /*retorna a útltima ligação pertencente da lista */
    return _ListaLigacoes;
}


/*Última ligacaoDaCarreira*/
LigacoesDaCarreira *ultimaLigacaoDaCarreira(LigacoesDaCarreira *_ListaLigacoes){
    if(_ListaLigacoes->lc_next != NULL){
        /*percorre a lista até ao fim*/
        while(_ListaLigacoes->lc_next != NULL ){
            /*uso de linked lists*/
            _ListaLigacoes = _ListaLigacoes->lc_next;
        }
    }
    return _ListaLigacoes;
}

/* Adiciona uma nova ligação. 
* input : l <nome-de-carreira> <paragem-origem> <paragem-destino> <custo> <duração>
   output : NADA (apenas adiciona ligações)*/
Ligacao *criaLigacao(Carreira *p_carreira, Paragem *p_origem, Paragem *p_destino,double custo, double duracao, Ligacao *_ListaLigacoes) {
    Ligacao *newL;
    /*aloca memória da minha Ligacao*/
    if((newL = ((Ligacao*)malloc(sizeof(Ligacao)))) == NULL){
        exit(EXIT_FAILURE);
    }
    newL->p_carreira = p_carreira;
    newL->p_origem =p_origem;
    newL->p_destino = p_destino;
    newL->custo = custo;
    newL->duracao = duracao;
    /*preciso de inicializar pois aloco a memória da próxima ligação da minha paragem 
    mais para a frente no projt2*/
    newL->nextLigacao = NULL;

    if(_ListaLigacoes == NULL){
        _ListaLigacoes = newL;
    }
    else{
        ultimaLigacao(_ListaLigacoes)->nextLigacao = newL;
    }
    /*vai adicionando as minhas ligações à lista criada na main*/
    return _ListaLigacoes;
}


/* Acrescenta uma nova ligação no fim de uma carreira. 
   Função que recebe uma carreira e uma ligação que tem o objetivo de à carreira 
   adicionar a ligação no fim e devolve a carreira modificada*/
Carreira *acrescentaLigacaoFim(Carreira *p_carreira, Ligacao *p_ligacao) {
    LigacoesDaCarreira *New_LC;
    int numLigacoesCarreira = p_carreira->numLigacoes;
    if (numLigacoesCarreira== 0){
        p_carreira->lig_carreira->_ligacaoDaParagem = p_ligacao;
		p_carreira->lig_carreira->lc_next = NULL;
    }
    else{
        New_LC = ((LigacoesDaCarreira *)malloc (sizeof(LigacoesDaCarreira)));

		New_LC->lc_next = NULL;
        New_LC->_ligacaoDaParagem=p_ligacao;
        ultimaLigacaoDaCarreira(p_carreira->lig_carreira)->lc_next = New_LC;
    }
    /*criação LigacoesDaCarreira*/
    p_carreira->custoTotal += p_ligacao->custo;
    p_carreira->duracaoTotal += p_ligacao->duracao;
    p_carreira->numLigacoes++;
    return p_carreira;
}

/* Acrescenta uma nova ligação no início de uma carreira. 
   Função que recebe uma carreira e uma ligação que tem o objetivo de à carreira 
   adicionar a ligação no início e devolve a carreira modificada*/
Carreira *acrescentaLigacaoInicio(Carreira *p_carreira, Ligacao *p_ligacao) {
    LigacoesDaCarreira *new_lc ;
    if((new_lc =((LigacoesDaCarreira*)malloc(sizeof(LigacoesDaCarreira))))== NULL){
        exit(EXIT_FAILURE);
    }
    /*criação LigacoesDaCarreira*/
    new_lc->_ligacaoDaParagem = p_ligacao;
    new_lc->lc_next = p_carreira->lig_carreira;
    p_carreira->lig_carreira = new_lc;
    p_carreira->custoTotal +=p_ligacao->custo;
    p_carreira->duracaoTotal += p_ligacao->duracao;
    p_carreira->numLigacoes++;
    return p_carreira;

}


/*Última carreiraDaParagem*/
void ultimaCarreiraDaParagem(CarreirasDaParagem **cp_paragem, CarreirasDaParagem *newCP){
	if (*cp_paragem == NULL){
		*cp_paragem= newCP;
	}
	else{
		CarreirasDaParagem *novaCP = *cp_paragem;
        /*percorre a lista até ao fim*/
		while (novaCP->cp_next != NULL){
            /*uso de linked lists*/
			novaCP = novaCP->cp_next;
		}
		novaCP->cp_next = newCP;
	}
}

/* Adiciona que existe uma nova carreira associada a uma paragem. 
   Função que à Paragem vai atribuir todas as carreiras que passam 
   por pela paragem e devolvea paragem*/
Paragem *adicionaCarreiraParagem(Paragem *p_paragem, Carreira *p_carreira) {
    CarreirasDaParagem *newCP;

    if((newCP = ((CarreirasDaParagem*)malloc(sizeof(CarreirasDaParagem)))) == NULL){
        exit(EXIT_FAILURE);
    }
    newCP->_carreirasDaParagem = p_carreira;
	newCP->cp_next = NULL;
	if (p_paragem->numCarreiras == 0 ){
		p_paragem->P_carreiras = newCP;
	}
	else{
/*		ultimaCarreiraDaParagem(p_paragem)->cp_next=newCP;*/
		ultimaCarreiraDaParagem(&(p_paragem->P_carreiras), newCP);

	}
    p_paragem->numCarreiras++;
    return p_paragem;
}

/* Adiciona primeira ligacao da carreira.
   Função que acrescenta a ligação à carreira e devolve essa carreira modificada.*/
Carreira *adicionaPrimeiraLigacao(Carreira *p_carreira, Paragem *p_origem, Paragem *p_destino, double custo, double duracao, Ligacao *_ListaLigacoes) {
    p_origem = adicionaCarreiraParagem(p_origem, p_carreira);
    if (p_origem != p_destino)
        p_destino = adicionaCarreiraParagem(p_destino, p_carreira);
    _ListaLigacoes = criaLigacao(p_carreira, p_origem, p_destino, custo, duracao, _ListaLigacoes);
    p_carreira = acrescentaLigacaoFim(p_carreira, ultimaLigacao(_ListaLigacoes));  
    return p_carreira;
}


/* Adiciona uma nova ligação a uma carreira. 
   input: l <nome-de-carreira> <paragem-origem> <paragem-destino> <custo> <duração>
   output: NADA*/
Ligacao *adicionaLigacao(Carreira *p_Carreira, Paragem *p_OrigemNova, Paragem *p_DestinoNovo, double custo, double duracao, Ligacao *_ListaLigacoes) {

	int numLigacoesCarreira = p_Carreira->numLigacoes;
    if (numLigacoesCarreira == 0) {
            p_OrigemNova = adicionaCarreiraParagem(p_OrigemNova, p_Carreira);
            if (p_OrigemNova != p_DestinoNovo)
                p_DestinoNovo = adicionaCarreiraParagem(p_DestinoNovo, p_Carreira);
            _ListaLigacoes = criaLigacao(p_Carreira, p_OrigemNova, p_DestinoNovo, custo, duracao, _ListaLigacoes);
            p_Carreira = acrescentaLigacaoFim(p_Carreira, ultimaLigacao(_ListaLigacoes));  
    }
    else {
        struct _Ligacao *p_primLigacaoAtual = p_Carreira->lig_carreira->_ligacaoDaParagem;
        struct _Ligacao *p_ultimaLigacaoAtual = ultimaLigacaoDaCarreira(p_Carreira->lig_carreira)->_ligacaoDaParagem;
        if(p_primLigacaoAtual == NULL){
            exit(EXIT_FAILURE);
        }
        if(p_ultimaLigacaoAtual == NULL){
            exit(EXIT_FAILURE);
        }
        if (p_primLigacaoAtual->p_origem == p_DestinoNovo) 
        {
            if (encontraParagemCarreira(p_Carreira, p_OrigemNova) == NAO_ENCONTRADO)
                p_OrigemNova = adicionaCarreiraParagem(p_OrigemNova, p_Carreira);
            _ListaLigacoes = criaLigacao(p_Carreira, p_OrigemNova, p_DestinoNovo, custo, duracao, _ListaLigacoes);
            p_Carreira = acrescentaLigacaoInicio(p_Carreira, ultimaLigacao(_ListaLigacoes));
        }
        else if (p_ultimaLigacaoAtual->p_destino == p_OrigemNova) {
            if (encontraParagemCarreira(p_Carreira, p_DestinoNovo) == NAO_ENCONTRADO)
                p_DestinoNovo = adicionaCarreiraParagem(p_DestinoNovo, p_Carreira);
            _ListaLigacoes = criaLigacao(p_Carreira, p_OrigemNova, p_DestinoNovo, custo, duracao, _ListaLigacoes);
            p_Carreira = acrescentaLigacaoFim(p_Carreira, ultimaLigacao(_ListaLigacoes));
        }
        else 
            printf("link cannot be associated with bus line.\n");
    }
    return _ListaLigacoes;
}

/* Função para tratar o comando 'l'.   
   Devolve a ligação que vou adicionando na ListaLigacoes (criada na main)
   para puder usar nos outros comandos*/ 
Ligacao *ligacoes(Carreira *_ListaCarreiras, Paragem *_ListaParagens, Ligacao *_ListaLigacoes) {
    char nomeCarreira[MAX_NOME_CARREIRA], nomeOrigem[MAX_NOME_PARAGEM], nomeDestino[MAX_NOME_PARAGEM];
    double custo, duracao;
    Carreira *p_carreira;
    Paragem *p_origem;
    Paragem *p_destino;
    /*aloco memória da carreira que tenha na ligação e verifico se existe espaço para colocar contiúdo lá*/
    if((p_carreira = ((Carreira*)malloc(sizeof(Carreira)))) == NULL){
        exit(EXIT_FAILURE);
    }

    /*aloco memória da paragem de origem que tenha na ligação e verifico se existe espaço para colocar contiúdo lá*/
    if((p_origem =((Paragem*)malloc(sizeof(Paragem)))) == NULL){
        exit(EXIT_FAILURE);
    }

    /*aloco memória da paragem de destino que tenha na ligação e verifico se existe espaço para colocar contiúdo lá*/
    if((p_destino = ((Paragem*)malloc(sizeof(Paragem)))) == NULL){
        exit(EXIT_FAILURE);
    }
    leNomesComando(nomeCarreira, nomeOrigem, nomeDestino);
    scanf("%lf%lf", &custo, &duracao);
    leAteFinalLinha();
    /*carreira encontrada?!*/
    p_carreira = encontraCarreira(nomeCarreira, _ListaCarreiras);
    if ( p_carreira == NULL)
        printf("%s: no such line.\n", nomeCarreira);
    else {
        /*paragem de origem encontrada?!*/
        p_origem = encontraParagem(nomeOrigem, _ListaParagens);
        if (p_origem == NULL) 
	    printf("%s: no such stop.\n", nomeOrigem);
	else {
        /*paragem de destino encontrada?!*/
	    p_destino = encontraParagem(nomeDestino, _ListaParagens);
	    if (p_destino == NULL)
	        printf("%s: no such stop.\n", nomeDestino);
	    else if (custo < 0.0 || duracao < 0.0)
	            printf("negative cost or duration.\n");
		else 
		    _ListaLigacoes = adicionaLigacao(p_carreira, p_origem, p_destino, custo, duracao, _ListaLigacoes);
	}
    }
    return _ListaLigacoes;
}


/* Funções para tratar as interseções */

/* Aplica Bubble Sort a um vector de identificadores de carreiras. */
void ordenaCarreiras(CarreirasDaParagem **carreiras) {
    int houveTroca = VERDADE;
    CarreirasDaParagem *c_atual;
	CarreirasDaParagem *c_anterior;
	
	if (*carreiras == NULL || (*carreiras)->cp_next == NULL) {
        /* lista vazia ou com apenas um elemento, já está ordenada*/
        return;
    }
    while (houveTroca) {
        houveTroca = FALSO;
        c_atual = *carreiras;
		c_anterior = NULL;
        while (c_atual->cp_next != c_anterior) {
			if (strcmp(c_atual->_carreirasDaParagem->nome, c_atual->cp_next->_carreirasDaParagem->nome) > 0) {
                CarreirasDaParagem *temp = c_atual->cp_next;
                c_atual->cp_next = temp->cp_next;
                temp->cp_next = c_atual;
                if (c_anterior == NULL) {
                    *carreiras = temp;
                } else {
                    c_anterior->cp_next= temp;
                }
                c_atual = temp;
                houveTroca = VERDADE;
            }
            c_anterior = c_atual;
            c_atual = c_atual->cp_next;
        }
    }
}

/*lista as interseções entre as carreiras
  input: i
  output:<nome-de-paragem> <número-de-carreiras>: <nome-de-carreira> ...
  Em que cada paragem está listada por ordem de criação 
  e o nome das carreiras de cada paragem listadas alfabéticamente*/
void intersecoes(Paragem * ListaParagens) {
    int /*i, c, idCarreira,*/ numCarreiras;
	Paragem *Lista_tmp;
	Lista_tmp = ((Paragem *)malloc(sizeof(Paragem)));
	Lista_tmp = ListaParagens;

    leAteFinalLinha();

	while (Lista_tmp != NULL)
	{
		numCarreiras = Lista_tmp->numCarreiras;
		if (numCarreiras > 1) {
			printf("%s %d:", Lista_tmp->nome, numCarreiras);
			ordenaCarreiras(&(Lista_tmp->P_carreiras));
			while (Lista_tmp->P_carreiras->_carreirasDaParagem!= NULL){
				printf(" %s", Lista_tmp->P_carreiras->_carreirasDaParagem->nome);
				Lista_tmp->P_carreiras = Lista_tmp->P_carreiras->cp_next;
			}
            printf("\n");
		}

	}
}

/* Funções para tratar a remoção das carreiras */

void freeCarreirasDaParagem(CarreirasDaParagem *cp) {
    CarreirasDaParagem *c_aux1 = cp, *c_aux2;
    while(c_aux1 != NULL){
        c_aux2 = c_aux1->cp_next;
        free(c_aux1->_carreirasDaParagem->nome);
        free(c_aux1);
        c_aux1 = c_aux2;
    }
}

CarreirasDaParagem *removeCarreiraDaParagem(CarreirasDaParagem *c_paragem, CarreirasDaParagem *prev, CarreirasDaParagem *atual)
{
	    if (atual == c_paragem){
			c_paragem = atual->cp_next;
			free (atual);
		return c_paragem;		
	}
	if (atual->cp_next== NULL)
		prev->cp_next = NULL;
	else{
		prev->cp_next= atual->cp_next;
	}
	free(atual);
	return c_paragem;
}

Paragem *removerCarreirasDaParagem(Paragem *p, char *car)
{
	CarreirasDaParagem *prev, *atual;
	Paragem *p_temp;
	int i ;
	p_temp = p;


	while (p_temp!=NULL){
		atual = p_temp->P_carreiras;
		prev = NULL;
		i = 0;
			while(atual != NULL){
				if ((strcmp(atual->_carreirasDaParagem->nome, car) == 0 )){
					p_temp->P_carreiras = removeCarreiraDaParagem(p_temp->P_carreiras, prev, atual);
					p_temp->numCarreiras--;
					i = 1;
				}
				if (i!=1){
					prev = atual;
					atual = atual->cp_next;
				}
				else 
				{atual = NULL;}
			}
			p_temp=p_temp->next;
		}
	return p;
}
/*Ligacao *removerCarreirasDasLigacoes(Ligacao *l, char *car)
{
}*/

void freeCarreiras(Carreira *c) {
    Carreira *c_aux1 = c, *c_aux2;
    while(c_aux1 != NULL){
        c_aux2 = c_aux1->nextCarreira;
        free(c_aux1->nome);
        free(c_aux1);
        c_aux1 = c_aux2;
    }
}

Carreira *removeCarreira(Carreira *carreira, Carreira *prev, Carreira *atual){
    if (atual == carreira){
		carreira = atual->nextCarreira;
		free (atual);
		return carreira;		
	}
	if (atual->nextCarreira == NULL)
		prev->nextCarreira = NULL;
	else{
		prev->nextCarreira = atual->nextCarreira;
	}
	free(atual);
	return carreira;
}

Carreira *remover(Carreira *c, Paragem *p/*, Ligacao *l*/){
    char *nome_carreira;
    Carreira *prev, *atual;
	atual = c;
    prev = NULL;
    /*aloca a memória do nome da Paragem inserida e verifica a sua lotação*/
	if((nome_carreira = (char *)malloc(MAX_TAMANHO_LINHA * sizeof(char))) == NULL){
		printf("No memory.\n");
		/*cuidado pois não posso ultrapassar o max de paragens possíveis*/
		freeCarreiras(c);
		exit(EXIT_FAILURE);
	}
	
	leNome(nome_carreira);
	leAteFinalLinha();
	if(encontraCarreira(nome_carreira, atual) == NULL){
		printf("%s: no such line.\n", nome_carreira);
		return c;
	}
	    p = removerCarreirasDaParagem( p,nome_carreira);
	    /*l = removerCarreirasDasLigacoes(l,nome_carreira);*/
		while(atual != NULL){
			if ((strcmp(atual->nome, nome_carreira) == 0 )){
				c = removeCarreira(c, prev, atual);
				return c;
			}
			prev = atual;
			atual = atual->nextCarreira;
		}
    leAteFinalLinha();
	return c;
}


/* Função MAIN */

int main() {
    int c;
    /*as minhas listas: substitui as variáveis globais que estava no projeto anterior 
    de cada tipo de estrutura*/
    Carreira *_ListaCarreiras = NULL;
    Paragem *_ListaParagens = NULL;
    Ligacao *_ListaLigacoes = NULL;
    do {
        c = getchar();
                switch(c) {
            case 'c':
                _ListaCarreiras = carreiras(_ListaCarreiras);
                break;
            case 'p':
                _ListaParagens = paragens(_ListaParagens);
                break;
            case 'l':
                _ListaLigacoes = ligacoes(_ListaCarreiras, _ListaParagens, _ListaLigacoes);
                break;
            case 'i':
                /*intersecoes(_ListaParagens);*/
                break;
            case 'r':
                _ListaCarreiras = remover(_ListaCarreiras,_ListaParagens/*,_ListaLigacoes*/);
                break;
            case 'e':
                /*elimina();*/
                break;
            case 'a':
                /*apaga_tudo();*/
                break;
            
	    case 'q':
            /*chamar função de dar free da linked lists*/
	        break;
            default:
	        /* Ignorar linhas em branco */
	        if (c == ' ' || c == '\t' || c == '\n') break;
        }
    } while (c != 'q');
    return 0;
}

/* gcc -O3 -Wall -Wextra -Werror -ansi -pedantic -g -o proj2 *.c 
    ver erros de memória mais específicos no valgrind com os testes:
            valgrind --leak-check=full ./proj2 <public-tests/test01.in*/
