#ifndef USUARIOS_HPP
#define USUARIOS_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <string>

#include "caixa.hpp"

using namespace std;

class User
{
public:
    User();
    User(int c);
    void SetID(int c);
    int GetID();
    void Imprime();

public:
    int ID;
    Caixa caixa;
};

class Celula_user
{
public:
    Celula_user();

public:
    User item;
    Celula_user *prox;
    friend class Lista_Usuarios;
};

class Lista_Usuarios
{
public:
    int tamanho;
    Lista_Usuarios();
    int GetTamanho() { return tamanho; };
    bool Vazia() { return tamanho == 0; };

    ~Lista_Usuarios();

    User GetItem(int pos);
    void SetItem(User item, int pos);
    void InsereInicio(int ID);
    User RemovePosicao(int pos);

    Celula_user *Pesquisa(int c);
    bool ProcuraID(int ID);
    int PosID(int ID);

    void Imprime();
    void Limpa();

public:
    Celula_user *primeiro;
    Celula_user *ultimo;
    Celula_user *Posiciona(int pos, bool antes);
};

#endif