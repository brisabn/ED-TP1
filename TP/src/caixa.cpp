#include "caixa.hpp"

#include "msgassert.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

// Email
Email::Email()
{
  msg = " ";
  prioridade = -1;
}
Email::Email(int c)
{
  avisoAssert(c <= 9 && c >= 1, "Prioridade inválida");
  msg = " ";
  prioridade = c;
}

void Email::Imprime()
{
  cout << this->msg << endl;
}

// Célula de email
Celula_Email::Celula_Email()
{
  email.prioridade = -1;
  prox = NULL;
}

// Lista encadeada da caixa de entrada
Caixa::Caixa()
{
  tamanho = 0;
  primeiro = new Celula_Email();
  ultimo = primeiro;
}

Caixa::~Caixa() {}

Email Caixa::RemoveInicio()
{
  erroAssert(tamanho > 0, "Lista vazia");

  Email aux;
  Celula_Email *p;
  p = primeiro->prox;
  primeiro->prox = p->prox;
  tamanho--;

  // deleta o primeiro da lista
  if (primeiro->prox == NULL)
    ultimo = primeiro;
  aux = p->email;
  delete p;
  return aux;
}

void Caixa::InserePrioridade(Email item, int prioridade)
{
  Celula_Email *p, *q, *nova;

  q = primeiro;
  p = q;

  // compara do início até o fim da lista se a prioridade é a mesma
  for (int i = 1; i <= tamanho; i++)
  {
    q = q->prox;
    if ((q->email).prioridade >= prioridade)
    {
      p = q;
    }
  }

  // a nova célula tem o item como email e é inserida na posição de prioridade
  nova = new Celula_Email();
  nova->email = item;
  nova->prox = p->prox;
  p->prox = nova;
  tamanho++;

  if (nova->prox == NULL)
    ultimo = nova;
};

Email Caixa::Pesquisa(int c)
{
  erroAssert(tamanho > 0, "Lista vazia");

  Email aux;
  Celula_Email *p;
  p = primeiro->prox;
  aux.prioridade = -1;

  // enquanto não chegar ao final da lista, confere se a prioridade do email da célula é o do parâmetro
  while (p != NULL)
  {
    if (p->email.prioridade == c)
    {
      aux = p->email;
      break;
    }
    p = p->prox;
  }
  return aux;
};

void Caixa::ImprimeInicio()
{
  erroAssert(tamanho > 0, "Lista vazia");

  // imprime do próximo ao primeiro, ou seja, o início
  Celula_Email *p;
  p = primeiro->prox;
  p->email.Imprime();
};