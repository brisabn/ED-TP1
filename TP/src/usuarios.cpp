#include "usuarios.hpp"

#include "msgassert.h"

#include <cmath>

using namespace std;

// Usuário
User::User()
{
  ID = -1; // item é vazio
}

User::User(int ID)
{
  avisoAssert(ID >= 0 && ID <= pow(10, 6), "ID inválido");
  this->ID = ID;
}

void User::SetID(int ID) { this->ID = ID; }

int User::GetID() { return ID; }

void User::Imprime()
{
  cout << this->ID << endl;
}

// Célula de usuário
Celula_user::Celula_user()
{
  item.SetID(-1);
  prox = NULL;
}

// Lista encadeada de usuários
Lista_Usuarios::Lista_Usuarios()
{
  tamanho = 0;
  primeiro = new Celula_user();
  ultimo = primeiro;
}

Lista_Usuarios::~Lista_Usuarios()
{
  Limpa();
  delete primeiro;
}

User Lista_Usuarios::GetItem(int pos)
{
  Celula_user *p;
  p = Posiciona(pos, true);
  return p->item;
}

void Lista_Usuarios::SetItem(User item, int pos)
{
  Celula_user *p;
  p = Posiciona(pos, true);
  p->item = item;
}

void Lista_Usuarios::InsereInicio(int ID)
{
  User item;
  item.ID = ID;

  // cria uma nova célula de usuário com o ID informadp
  Celula_user *nova;
  nova = new Celula_user();
  nova->item = item;
  nova->prox = primeiro->prox;
  primeiro->prox = nova;
  tamanho++;

  if (nova->prox == NULL)
    ultimo = nova;
};

Celula_user *Lista_Usuarios::Posiciona(int pos, bool antes = false)
{
  erroAssert(tamanho > pos || pos > 0, "Posição Inválida");

  Celula_user *p;
  int i;

  // caminha até chegar na posição requerida, o p estará nessa posição
  p = primeiro;
  for (i = 1; i < pos; i++)
  {
    p = p->prox;
  }
  if (!antes)
    p = p->prox;

  return p;
}

int Lista_Usuarios::PosID(int ID)
{
  Celula_user *p;
  int posicao, pos;

  // caminha nas posições da lista até achar a posição do ID fornecido
  p = primeiro;
  for (pos = 1; pos <= tamanho; pos++)
  {
    p = p->prox;
    if (p->item.ID == ID)
    {
      posicao = pos;
    }
  }
  return posicao;
}

User Lista_Usuarios::RemovePosicao(int pos)
{
  erroAssert(tamanho > 0, "Lista vazia");

  User aux;
  Celula_user *p, *q;

  // posiciona a célula na posição requerida, o próximo dele será o próximo do anterior
  p = Posiciona(pos, true);
  q = p->prox;
  p->prox = q->prox;
  tamanho--;

  aux = q->item;
  delete q;
  if (p->prox == NULL)
    ultimo = p;
  return aux;
}

Celula_user *Lista_Usuarios::Pesquisa(int ID)
{
  erroAssert(tamanho > 0, "Lista vazia");

  User aux;
  Celula_user *p;

  // pesquisa pelo ID fornecido até encontrar a sua célula
  p = primeiro->prox;
  aux.SetID(-1);
  while (p != NULL)
  {
    if (p->item.GetID() == ID)
    {
      aux = p->item;
      break;
    }
    p = p->prox;
  }
  return p;
};

bool Lista_Usuarios::ProcuraID(int ID)
{
  bool existe = false;
  User aux;
  Celula_user *p;

  // procura o ID e marca verdadeiro se ele existir
  if (tamanho != 0)
  {
    p = primeiro->prox;
    aux.SetID(-1);
    while (p != NULL)
    {
      if (p->item.GetID() == ID)
      {
        existe = true;
      }
      p = p->prox;
    }
  }

  return existe;
};

void Lista_Usuarios::Imprime()
{
  // imprime todos os usuários, caso necessário
  Celula_user *p;
  p = primeiro->prox;
  while (p != NULL)
  {
    p->item.Imprime();
    p = p->prox;
  }
};

void Lista_Usuarios::Limpa()
{
  Celula_user *p;
  p = primeiro->prox;
  while (p != NULL)
  {
    primeiro->prox = p->prox;
    delete p;
    p = primeiro->prox;
  }
  ultimo = primeiro;
  tamanho = 0;
};