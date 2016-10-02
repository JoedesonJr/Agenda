/*
Utilizando o conceito de filas, desenvolva um exerc�cio para gerenciar uma agenda de contatos
telef�nicos. Dos contatos deve-se saber o nome, sobrenome, apelido, n�mero de telefone,
email e endere�o.
Voc� deve criar uma fila encadeada para cada letra do alfabeto que possua nomes de contatos
que iniciem por ela. Sempre que um novo contato for adicionado, ele deve ser inserido no final
de sua fila. Caso n�o exista fila de uma letra de um novo contato, ela deve ser criada. A ordem
dos elementos de cada fila s� deve ser alterada caso o contato seja definido como favorito. Se
isto ocorrer, ele deve ir para o in�cio da fila, ficando atr�s apenas de outros favoritos (caso
existam). O programa deve permitir de forma din�mica a inser��o, visualiza��o e retirada de
novos contatos, bem como favoritar os existentes. As fun��es do exerc�cio devem ser definidas
em uma biblioteca denominada agenda.h.
*/

#include "agenda.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

main()
{
      int escolha;
      char op;
      fila_contato *contato;
      fila_letra *primeira_letra = NULL;  //cria um cabe�a somente para a fila das iniciais
      do{
          system("cls");
          printf("\n 1. Inserir.");
          printf("\n 2. Favoritar.");
          printf("\n 3. Imprimir.");
          printf("\n 4. Excluir Contato.");
          printf("\n 5. Sair.");
          printf("\n\n\n");
          printf(" Opcao: ");
          scanf("%d", &escolha);
          switch(escolha){
              case(1):
                  do{
                      primeira_letra = criar(primeira_letra, contato);
                      printf("\n\n\n Cadastrar novamente (s/n): ");
                      fflush(stdin);
                      scanf("%c", &op);
                  }while(op != 'n');
                  break;
              case(2):
                  do{
                      favoritar(primeira_letra, contato);
                      printf("\n\n\n Favoritar mais algum (s/n): ");
                      fflush(stdin);
                      scanf("%c", &op);
                  }while(op != 'n');
                  break;
              case(3):
                      imprimir(primeira_letra, contato);
                      break;
              case(4):
                  do{ 
                      primeira_letra = excluir(primeira_letra, contato);
                      printf("\n\n\n Excluir mais algum (s/n): ");
                      fflush(stdin);
                      scanf("%c", &op);
                  }while(op != 'n');
                  break;
          }
      }while(escolha != 5);
}
