#ifndef CAIXA_HPP
#define CAIXA_HPP

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Email
{
public:
  Email();
  Email(int prioridade);
  void Imprime();

  int prioridade;
  string msg;
};

class Celula_Email
{
public:
  Celula_Email();

public:
  Email email;
  Celula_Email *prox;

  friend class Caixa;
};

class Caixa
{
public:
  int tamanho;
  Caixa();
  ~Caixa();

  void InserePrioridade(Email email, int prioridade);
  Email Pesquisa(int prioridade);

  Email RemoveInicio();
  void ImprimeInicio();

  Celula_Email *primeiro;
  Celula_Email *ultimo;
};

#endif