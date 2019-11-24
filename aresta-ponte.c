#include <stdio.h>
#include <stdlib.h>
#include "TG.h"
#include "TLSE.h"

int compara(TLSE* conj_a, TLSE* conj_b){
	TLSE* a = conj_a;
	while(a){
		TLSE* b = conj_b;
		while(b){
			if (a->info == b->info)
				return 0;
			b = b->prox;
		}
		a = a->prox;
	}
	return 1;
}

TLSE* conjunto(TG* g, TG* no, TLSE* visitados){
	TLSE* lista = NULL;
	TVIZ* v = no->prim_viz;
	while(v){
		if (!buscal(visitados, v->id_viz)){
			lista = inserel(lista, v->id_viz);
		}
		v = v->prox_viz;
	}
	if (!lista) return NULL;
	TLSE * atual = lista;
	while (atual->prox){
		if (!buscal(visitados, atual->info)){
			TG* no_aux = busca_no(g, atual->info);
			visitados = inserel(visitados, no_aux->id_no);
			TLSE* fim = atual;
			while (fim->prox){
				fim = fim->prox;
			}
			fim->prox = conjunto(g, no_aux, visitados);
		}
		atual = atual->prox;
	}
	return lista;
}

int e_ponte(TG *g, int x, int y){
	if(!g) return 0;
	TVIZ * aresta = busca_aresta(g, x, y); //verifica se a aresta existe
	if (!aresta) return 0;
	retira_aresta(g, x, y);
	TG* a = busca_no(g, x); TG* b = busca_no(g, y);
	int resp = compara(conjunto(g, a, NULL), conjunto(g, b, NULL));
	ins_aresta(g, x, y);
	return resp;
}

int main(){
	// >> gcc -o main aresta-ponte.c TG.c TLSE.c
	TG * grafo = inicializa();
	grafo = ins_no(grafo, 1);
	grafo = ins_no(grafo, 2);
	grafo = ins_no(grafo, 3);
	grafo = ins_no(grafo, 4);
	grafo = ins_no(grafo, 5);
	grafo = ins_no(grafo, 6);
	grafo = ins_no(grafo, 7);
	grafo = ins_no(grafo, 8);
	ins_aresta(grafo, 1, 2);
	ins_aresta(grafo, 1, 3);
	ins_aresta(grafo, 1, 4);
	ins_aresta(grafo, 2, 3);
	ins_aresta(grafo, 2, 4);
	ins_aresta(grafo, 3, 4);
	ins_aresta(grafo, 4, 5);
	ins_aresta(grafo, 5, 6);
	ins_aresta(grafo, 5, 7);
	ins_aresta(grafo, 5, 8);
	imprime(grafo);
	int ponte = e_ponte(grafo, 4, 5);
	printf("e_ponte = %d\n", ponte);
	ponte = e_ponte(grafo, 1, 3);
	printf("e_ponte = %d\n", ponte);
	ponte = e_ponte(grafo, 5, 8);
	printf("e_ponte = %d\n", ponte);
	return 0;
}