#include "usuarios.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

#include "msgassert.h"

using namespace std;

string arquivo;

void parse_args(int argc, char const *argv[])
{
  // passa o arquivo a ser lido como argumento da linha de comando
  erroAssert(argv[1], "Sem arquivo para ser lido");
  arquivo = string(argv[1]);
}

int main(int argc, char const *argv[])
{
  parse_args(argc, argv);

  Lista_Usuarios users_list;

  ifstream myfile;
  string line, comando, texto;
  int i, ID, prioridade;

  myfile.open(arquivo);
  erroAssert(myfile, "Erro na abertura do arquivo");

  while (getline(myfile, line))
  {
    istringstream ss(line);
    i = 0;
    string token, aux;
    string arr[4];

    while (getline(ss, token, ' ')) // delimita comando, ID e prioridade
    {
      if (i < 3)
        arr[i] = token;
      i++;
    }

    if (line.length() > arr[0].length() + arr[1].length() + 3) // caso a linha lida seja maior o do comando + o ID
    {
      int pos = arr[0].length() + arr[1].length() + arr[2].length() + 3;
      aux = line.substr(pos); // corta a string depois do arr[2]

      int fim = aux.find("FIM");
      arr[3] = aux.substr(0, fim); // corta a string até chegar em FIM
    }

    comando = arr[0];
    if (arr[1].length() > 0)
      ID = stoi(arr[1]);
    if (arr[2].length() > 0)
      prioridade = stoi(arr[2]);
    texto = arr[3];

    if (comando == "CADASTRA")
    {
      if (users_list.ProcuraID(ID) == false)
      {
        users_list.InsereInicio(ID);
        cout << "OK: CONTA " << ID << " CADASTRADA" << endl;
      }
      else
      {
        cout << "ERRO: CONTA " << ID << " JA EXISTENTE" << endl;
      }
    }

    if (comando == "REMOVE")
    {
      if (users_list.ProcuraID(ID) == true)
      {
        users_list.RemovePosicao(users_list.PosID(ID));
        cout << "OK: CONTA " << ID << " REMOVIDA" << endl;
      }
      else
      {
        cout << "ERRO: CONTA " << ID << " NAO EXISTE" << endl;
      }
    }

    if (comando == "ENTREGA")
    {
      if (users_list.ProcuraID(ID) == true)
      {
        Email email;
        email.msg = texto;
        email.prioridade = prioridade;

        users_list.Pesquisa(ID)->item.caixa.InserePrioridade(email, prioridade);
        cout << "OK: MENSAGEM PARA " << ID << " ENTREGUE" << endl;
      }
      else
      {
        cout << "ERRO: CONTA " << ID << " NAO EXISTE" << endl;
      }
    }

    if (comando == "CONSULTA")
    {
      if (users_list.ProcuraID(ID) == true)
      {
        cout << comando << " " << ID << ": ";
        if (users_list.Pesquisa(ID)->item.caixa.tamanho == 0)
        {
          cout << "CAIXA DE ENTRADA VAZIA" << endl;
        }
        else
        {
          users_list.Pesquisa(ID)->item.caixa.ImprimeInicio();
          users_list.Pesquisa(ID)->item.caixa.RemoveInicio();
        }
      }
      else
      {
        cout << "ERRO: CONTA " << ID << " NAO EXISTE" << endl;
      }
    }
  }

  myfile.close();
  erroAssert(!myfile, "Erro no fechamento do arquivo");

  return 0;
}