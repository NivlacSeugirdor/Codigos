#include <iostream>
#include <cstring> // Para strcpy
#include <cstdlib> // Para malloc e free

using namespace std;

typedef struct no{
    int id;
    char produto[50];
    struct no *esq;
    struct no *dir;
}no_abb;

typedef struct arvore{
    no_abb *raiz;
}abb;


/**
*	Função auxiliar para troca de informações entre nós
*/
void troca_infos(no_abb *primeiro, no_abb *segundo) {
    int id = primeiro->id;
    char produto[50];
    strcpy(produto, primeiro->produto);
    primeiro->id = segundo->id;
    segundo->id = id;
    strcpy(primeiro->produto, segundo->produto);
    strcpy(segundo->produto, produto);
}


/**
*	Função de inserção recursiva.
*/
no_abb* insere_no(no_abb *atual, no_abb *novo){
	if(atual == NULL){
		//Não há mais continuidade na árvore e, portanto, o nó novo é retornado como nó filho para o nó anterior. 
		return novo;
	}else if(atual->id > novo->id)
	{
		// se a id do nó atual é maior que o do novo nó, então o novo nó deve ser alocado em sua ramificação esquerda. 
		atual->esq = insere_no(atual->esq, novo);
	}else
	{
		// se a id for menor, então o novo nó eerá adicionado na ramificação direita.
		atual->dir = insere_no(atual->dir, novo);
	}
	return atual;
}


/**
*	Função para buscar o nó de menor id.
*/
no_abb* busca_menor_no(no_abb *raiz)
{
	no_abb *atual = raiz;
	while(atual->esq!=NULL){atual = atual->esq;}
	return atual;
}

/**
*	Função para buscar o nó de maior id.
*/
no_abb* busca_maior_no(no_abb *raiz)
{
	no_abb *atual = raiz;
	while(atual->dir!=NULL){atual = atual->dir;}
	return atual;
}


/**
*	Funções de busca por um nó especificado pelo usuário, respectivamente recursiva e iterativa
*/
no_abb* busca_no_rec(no_abb *atual, int alvo){
	if(atual->id == alvo)
	{
		return atual;
	}else if(atual->id > alvo)
	{
		return busca_no_rec(atual->esq, alvo);
	}else
	{
		return busca_no_rec(atual->dir, alvo);	
	}
}


no_abb* busca_no_it(no_abb *raiz, int alvo){
	no_abb *atual = raiz;
	while(atual!=NULL && atual->id!=alvo)
	{
		if(atual->id > alvo)
		{
			atual = atual->esq;
		}else if(atual->id < alvo)
		{
			atual = atual->dir;
		}
	}
	return atual;
}


/**
*	Função recursiva para remoção de nós
*/
no_abb* remove_no(no_abb *atual, int alvo)
{
	no_abb *auxiliar;
	if(atual == NULL){return atual;} //Se o nó não for encontrado, apenas retorna o atual que no caso terá valor NULL.
	else if(atual->id == alvo){
		if(atual->esq == NULL && atual->dir == NULL) //Se for um nó folha:
		{
			free(atual); // O nó é removido;
			return NULL; // A função retorna NULL.
		}else if( (atual->esq != NULL && atual->dir == NULL) || (atual->esq == NULL && atual->dir != NULL)) // Se tiver apenas 1 filho:
		{
			if(atual->dir == NULL){auxiliar = atual->esq;} // Salva o nó filho;
			else{auxiliar = atual->dir;}
			free(atual); // Elimina o nó alvo;
			return auxiliar; // Retorna o nó filho.
		}else{ // Se possuir dois nós filhos:
			auxiliar = busca_menor_no(atual->dir); //Busca o nó de menor id na ramificação direita;
			troca_infos(atual, auxiliar); //Troca as informações entre os dois nós selecionados (id, produto);
			atual->dir = remove_no(atual->dir, alvo); //Retoma a busca pelo nó a ser removido na ramificação da direita.  
		}
	}else if(atual->id > alvo)
	{
		atual->esq = remove_no(atual->esq, alvo);
	}else 
	{
		atual->dir = remove_no(atual->dir, alvo);	
	}

	return atual;
}

/**
*	Função para criação de nó
*/
no_abb* cria_no(int id, char produto[50])
{
	no_abb* novo = (no_abb*)malloc(sizeof(no_abb));
	novo->id = id;
	strcpy(novo->produto, produto);
	novo->esq = NULL;
	novo->dir = NULL;
	return novo;
}

/**
*	Função para mostrar os elementos da árvore
*/
void apresenta_abb(no_abb *raiz)
{
	if(raiz!=NULL){
		cout << "( " << raiz->id << " ";
		apresenta_abb(raiz->esq);
		apresenta_abb(raiz->dir);
		cout << ")";
	}
}


int main() {
    abb arvore;
    arvore.raiz = NULL;

    // Exemplo de uso: inserir um nó
    
    arvore.raiz = insere_no(arvore.raiz, cria_no(4, "Produto 1"));
    arvore.raiz = insere_no(arvore.raiz, cria_no(2, "Produto 2"));
    arvore.raiz = insere_no(arvore.raiz, cria_no(6, "Produto 3"));
    arvore.raiz = insere_no(arvore.raiz, cria_no(1, "Produto 4"));
    arvore.raiz = insere_no(arvore.raiz, cria_no(3, "Produto 5"));
    arvore.raiz = insere_no(arvore.raiz, cria_no(5, "Produto 6"));
    arvore.raiz = insere_no(arvore.raiz, cria_no(8, "Produto 7"));
    arvore.raiz = insere_no(arvore.raiz, cria_no(9, "Produto 8"));
    arvore.raiz = insere_no(arvore.raiz, cria_no(7, "Produto 9"));

    apresenta_abb(arvore.raiz);
    cout << "\n";

    //Exemplo de busca    	
    no_abb* no = busca_no_rec(arvore.raiz, 6);

    //Exemplo Remoção
    arvore.raiz = remove_no(arvore.raiz, 1);

    apresenta_abb(arvore.raiz);
    cout << "\n";

    arvore.raiz = remove_no(arvore.raiz, 6);

    apresenta_abb(arvore.raiz);
    cout << "\n";

    arvore.raiz = remove_no(arvore.raiz, 8);

    apresenta_abb(arvore.raiz);
    cout << "\n";

    return 0;
}