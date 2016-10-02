#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct fila_contato{
        char nome[20], sobrenome[20], favorito;
        char apelido[20], email[20], endereco[30];
        int telefone;
        struct fila_contato *prox;
        struct fila_contato *ant;
}fila_contato;


typedef struct fila_letra{
        fila_contato *letra;
        char info;
        struct fila_letra *prox;
        struct fila_letra *ant;
}fila_letra;


fila_letra *busca_letra(fila_letra *p, char x){   //funçao para verificar se a primeira letra do contato criado, é uma nó da fila das iniciais.
        while(p != NULL){
            if(p->info == x)    //se ja tiver a letra inicial...
               return p;    //retorna o endereço do nó da inicial.
            p = p->prox;
        }
        return NULL;
}

void favoritar(fila_letra *primeira_letra, fila_contato *contato){
     system("cls");
     printf("\n > Favoritar\n\n");  //mostra todos os contatos
     fila_letra *p = primeira_letra;
     fila_contato *k;
     for(p = primeira_letra; p != NULL; p = p->prox){
           printf("\n\n    # %c", p->info);
           printf("\n\n");
           for(k = p->letra; k != NULL; k = k->prox){
                if(k->favorito != 's'){
                     printf("      ");
                     puts(k->nome);
                }
                else if(k->favorito == 's'){
                     printf("     *");
                     puts(k->nome);
                }
           }
     }
     printf("\n\n\n");
     printf(" Qual Nome do Contato a Favoritar: ");
     char escolha[20];
     fflush(stdin);
     gets(escolha);
     strupr(escolha);
     p = primeira_letra;
     p = busca_letra(p, escolha[0]);
     if(p == NULL)
          printf(" \n\n Nome Nao Encontrado!");
     else{
         int aux = 0;
         k = p->letra;
         while(aux == 0 && k != NULL){          
              if(strcmp(k->nome, escolha) == 0)
                  aux++;
              else
                 k = k->prox;
         }
         if(aux == 1 && k->favorito == 'n'){
              fila_contato *aux = p->letra;
              if(k->ant == NULL){  //se o selecionado for o unico da fila.
                    k->favorito = 's';
                    p->letra = k;
              }
              else if(aux->favorito == 'n'){  //se nao tiver nenhum favorito
                    if(k->prox == NULL){   //se o selecionado for o ultimo da fila
                         k->ant->prox = NULL;  //o penultimo passa a ser o ultimo.
                         k->ant = NULL;  
                         aux->ant = k;  //o que era primeiro, passa a ser o segundo.
                         k->prox = aux;  //selecionado passa a ser o primeiro.
                         k->favorito = 's';
                         p->letra = k;
                    }
                    else{  //o selecionado esta entre outros dois.
                         k->ant->prox = k->prox;
                         k->prox->ant = k->ant;  //o selecionado sai do meio
                         k->ant = NULL;
                         k->prox = aux;  //passa a ser o primeiro.
                         aux->ant = k;   //o antigo primeiro passa a ser o segundo.
                         k->favorito = 's';
                         p->letra = k;
                    }
              }
              else{   //se ja existir contatos favoritos
                   while(aux->favorito == 's')  //procura o primeiro nao favorito
                         aux = aux->prox;
                   if(aux == k)  //se ele for o primeiro nao favorito.
                          k->favorito = 's';
                   else{  //existe favoritos e nao favoritos na lista.
                          if(k->prox == NULL){  //se o selecionado for o ultimo.
                               k->ant->prox = NULL; 
                               k->ant = aux->ant;
                               k->prox = aux;
                               aux->ant->prox = k;
                               aux->ant = k;
                               k->favorito = 's';
                          }
                          else{  //se o selecionado estiver no meio.
                               k->ant->prox = k->prox;
                               k->prox->ant = k->ant;
                               k->ant = aux->ant;
                               k->prox = aux;
                               aux->ant = k;
                               k->ant->prox = k;
                               k->favorito = 's';
                          }
                   }
              }
              system("cls");
              printf("\n > Favoritar\n\n");
              for(p = primeira_letra; p != NULL; p = p->prox){
                  printf("\n\n    # %c", p->info);
                  printf("\n\n");
                  for(k = p->letra; k != NULL; k = k->prox){
                       if(k->favorito != 's'){
                          printf("      ");
                          puts(k->nome);
                       }
                       else if(k->favorito == 's'){
                          printf("     *");
                          puts(k->nome);
                       }
                  }
              }
         }
         else if(aux == 1 && k->favorito == 's')
             printf("\n\n Nome ja eh Favorito");
         else
             printf("\n\n Nome Nao Encontrado");
     }   
}

fila_letra *excluir(fila_letra *primeira_letra, fila_contato *contato){
     fila_letra *p;
     fila_contato *k = contato;
     fila_contato *aux2;
     fila_letra *aux3;
     int op;
     do{
         system("cls");
         printf("\n > Excluir Contato \n\n");
         printf("\n 1. Excluir Todos os Contatos por Letra.");
         printf("\n 2. Excluir Contato por Nome.");
         printf("\n 3. Voltar ao Menu.");
         printf("\n\n\n");
         printf(" Opcao: ");
         scanf("%d",&op);
         if(op == 1){
                system("cls");
                printf("\n > Excluir Todos os Contatos por Letra.\n\n");
                printf("\n Letras Disponiveis:  ");
                for(p = primeira_letra; p != NULL; p = p->prox)
                              printf("%c  ", p->info);
                printf("\n\n\n\n Excluir Contatos com a Letra:  ");
                char a;
                fflush(stdin);
                scanf("%c", &a);
                strupr(&a);  //escolhe a letra e deixa ela maiuscula
                p = primeira_letra;
                int aux = 0;
                while(aux == 0 && p != NULL){  //procura a letra na fila
                     if(p->info == a)  
                          aux++;
                     else
                          p = p->prox;
                }
                if(aux == 1){  //se encontra a letra...
                       k = p->letra;  //passa para a fila dos contatos
                       while(k != NULL){  //laço para excluir todos os contatos.
                               aux2 = k;  
                               k = k->prox;
                               free(aux2);
                       }
                       p->letra = NULL;  //letra nao aponta para contato nenhum
                       if(p->prox == NULL && p->ant == NULL){  //se a letra escolhida for a unica...
                                  free(p);  //so removi ela 
                                  printf("\n\n Removido.");
                                  return NULL;  //e limpa o cabeça
                       }
                       else if(p->prox == NULL){  //se a leta for a ultima da fila...
                               p->ant->prox = NULL;
                               free(p);
                               printf("\n\n Removido.");
                               return primeira_letra;
                       }
                       else if(p->ant == NULL){  //se a letra for a primeira da fila...
                               aux3 = primeira_letra->prox;
                               free(p);
                               aux3->ant = NULL;
                               printf("\n\n Removido.");
                               return aux3;
                       }
                       else{  //se ela estiver entre duas letras...
                               p->ant->prox = p->prox;
                               p->prox->ant = p->ant;
                               free(p);
                               printf("\n\n Removido.");
                               return primeira_letra;
                       }
                }
                else{
                       printf("\n\n Letra Nao Encontrada!");
                       return primeira_letra;
            	}
                printf("\n\n\n");
                system("pause");
         }
         else if(op == 2){
               system("cls");
               printf("\n > Excluir Todos os Contatos por Nome.\n\n");
               for(p = primeira_letra; p != NULL; p = p->prox){  //mostra os contatos disponiveis
                    printf("\n\n    # %c", p->info);
                    printf("\n\n");
                    for(k = p->letra; k != NULL; k = k->prox){
                         if(k->favorito != 's'){
                              printf("      ");
                              puts(k->nome);
                         }
                         else if(k->favorito == 's'){
                              printf("     *");
                              puts(k->nome);
                         }
                    }
                }
                printf("\n\n\n"); 
                printf(" Qual Nome do Contato a Excluir: ");
                char escolha[20];
                fflush(stdin);
                gets(escolha);
                strupr(escolha);
                p = primeira_letra;
                int aux = 0;
                while(aux == 0 && p != NULL){  //verifica se o inicial nome esta nas letras
                       if(p->info == escolha[0])
                            aux++;
                       else
                            p = p->prox;
                }
                if(p == NULL)
                      printf(" \n\n Nome Nao Encontrado!");
                else{
                      aux = 0;
                      k = p->letra;
                      while(aux == 0 && k != NULL){    //verifica se o nome esta nos contatos
                            if(strcmp(k->nome, escolha) == 0)
                                  aux++;
                            else
                                k = k->prox;
                      }
                }
               if(aux == 1){  //se estiver...
                     if(k->ant == NULL && k->prox == NULL){  //se o nome escolhida for o unico contato...
                          free(k);  //exclui o nome e tambem a inicia da letra
                          if(p->prox == NULL && p->ant == NULL){
                               free(p);
                               printf("\n\n Removido.");
                               return NULL;
                          }
                          else if(p->prox == NULL){  //se a letra escolhida for o ultimo contato...
                               p->ant->prox = NULL;
                               free(p);
                               printf("\n\n Removido.");
                               return primeira_letra;
                          }
                          else if(p->ant == NULL){  //se for a primeira...
                               aux3 = primeira_letra->prox;
                               free(p);
                               aux3->ant = NULL;
                               printf("\n\n Removido.");
                               return aux3;
                          }
                          else{  //se for do meio
                               p->ant->prox = p->prox;
                               p->prox->ant = p->ant;
                               free(p);
                               printf("\n\n Removido.");
                               return primeira_letra;
                          }
                     }
                     else if(k->ant == NULL){  //se o nome for o primeiro...
                          k->prox->ant = NULL;
                          p->letra = k->prox;
                          free(k);
                     }
                     else if(k->prox == NULL){  //ultimo
                          k->ant->prox = NULL;
                          free(k);
                     }
                     else{  //meio
                          k->ant->prox = k->prox;
                          k->prox->ant = k->ant;
                          free(k);
                     }
                     printf("\n\n Removido."); 
               }
               else
                   printf("\n\n Contato Nao Encontrado!");
               return primeira_letra;
         }
         else if(op == 3)
         	return primeira_letra;
     }while(op != 3);
}
     

void imprimir(fila_letra *primeira_letra, fila_contato *contato){
     int op;
     fila_letra *p;
     fila_contato *k;
     do{
          system("cls");
          printf("\n > Imprimir Contato \n\n");
          printf("\n 1. Todos os Contatos.");
          printf("\n 2. Por Letra.");
          printf("\n 3. Todos Favoritos.");
          printf("\n 4. Voltar ao Menu.");
          printf("\n\n\n");
          printf(" Opcao: ");
          scanf("%d", &op);
          if(op == 1){
                system("cls");
                printf("\n > Imprimir Todos os Contato \n");
                for(p = primeira_letra; p != NULL; p = p->prox){
                       printf("\n\n    # %c", p->info);
                       printf("\n\n");
                       for(k = p->letra; k != NULL; k = k->prox){
                             if(k->favorito != 's')
                                  printf("      %s %s (%s) -> %d \n      Email: %s\n      Endereco: %s\n\n", k->nome, k->sobrenome, k->apelido, k->telefone, k->email, k->endereco);
                             else if(k->favorito == 's')
                                  printf("     *%s %s (%s) -> %d \n      Email: %s\n      Endereco: %s\n\n", k->nome, k->sobrenome, k->apelido, k->telefone, k->email, k->endereco);
                       }
                }
                printf("\n\n\n");
                system("pause");
          }
          if(op == 2){
                system("cls");
                printf("\n > Imprimir Por Letra \n\n");
                printf("\n Letras Disponiveis:  ");
                for(p = primeira_letra; p != NULL; p = p->prox)
                              printf("%c  ", p->info);
                printf("\n\n\n\n Imprimir Contatos com a Letra:  ");
                char a;
                fflush(stdin);
                scanf("%c", &a);
                strupr(&a);
                p = primeira_letra;
                int aux = 0;
                while(aux == 0 && p != NULL){
                     if(p->info == a)
                          aux++;
                     else
                          p = p->prox;
                }
                if(aux == 1){
                    printf("\n\n    # %c\n\n", p->info);
                    for(k = p->letra; k != NULL; k = k->prox){
                             if(k->favorito != 's')
                                  printf("      %s %s (%s) -> %d \n      Email: %s\n      Endereco: %s\n\n", k->nome, k->sobrenome, k->apelido, k->telefone, k->email, k->endereco);
                             else if(k->favorito == 's')
                                  printf("     *%s %s (%s) -> %d \n      Email: %s\n      Endereco: %s\n\n", k->nome, k->sobrenome, k->apelido, k->telefone, k->email, k->endereco);
                    }
                }
                else
                    printf("\n\n Letra Nao Encontrada!");
                printf("\n\n\n");
                system("pause");
          }
          if(op == 3){
                system("cls");
                printf("\n > Imprimir Todos os Favoritos \n");
                for(p = primeira_letra; p != NULL; p = p->prox){
                       if(p->letra->favorito == 's'){
                             printf("\n\n    # %c", p->info);
                             printf("\n\n");
                       }
                       for(k = p->letra; k != NULL; k = k->prox){
                             if(k->favorito == 's')
                                  printf("     *%s %s (%s) -> %d \n      Email: %s\n      Endereco: %s\n\n", k->nome, k->sobrenome, k->apelido, k->telefone, k->email, k->endereco);
                       }
                }
                printf("\n\n\n");
                system("pause");
          }
     }while(op != 4);
}
 
fila_letra *criar(fila_letra *primeira_letra, fila_contato *contato){
        system("cls");
        printf("\n > Criar Contato \n\n");
        fila_contato *novo = (fila_contato*) malloc (sizeof(fila_contato));  //cria inicialmente um novo contato
        printf("\n Nome: ");
        fflush(stdin);
        gets(novo->nome);
        strupr(novo->nome);
        printf("\n Sobrenome: ");
        fflush(stdin);
        gets(novo->sobrenome);
        strupr(novo->sobrenome);
        printf("\n Apelido: ");
        fflush(stdin);
        gets(novo->apelido);
        strupr(novo->apelido);
        printf("\n Telefone: ");
        scanf("%d", &novo->telefone);
        printf("\n Email: ");
        fflush(stdin);
        gets(novo->email);
        printf("\n Endereco: ");
        fflush(stdin);
        gets(novo->endereco);
        printf("\n Favorito (s/n): ");
        do{
           fflush(stdin);
           scanf("%c", &novo->favorito);
        }while(novo->favorito != 's' && novo->favorito != 'n');
        novo->prox = NULL;  //campo proximo sempre nulo, irá para o fim da fila.
        if(primeira_letra == NULL){   //se a fila das iniciais estiver vazia...
              novo->ant = NULL;   
              fila_letra *novo_letra = (fila_letra*) malloc (sizeof(fila_letra));   //cria a primeira inicial. 
              novo_letra->prox = NULL;   
              novo_letra->info = novo->nome[0];   //salva a primeira letra do contato.
              novo_letra->ant = NULL;
              novo_letra->letra = novo;   //aponta para o primeiro contato criado.
              return novo_letra;   //esse para a ser a primeira inicial da fila.
        }
        else{   //se ja tiver alguma inicial inserida.
                  fila_letra *verifica = primeira_letra;  
                  int aux = 0;
                  while(aux == 0 && verifica != NULL){  
                       if(verifica->info == novo->nome[0])  //verifica se tem algum letra igual a primeira letra do contato criado
                            aux++;
                       else
                            verifica = verifica->prox;
                  }
                  if(verifica == NULL){  //se nao tiver nenhum nó com a inicial do contato ...
                            novo->ant = NULL; 
                            fila_letra *novo_letra = (fila_letra*) malloc (sizeof(fila_letra));  //cria-se um novo nó...
                            novo_letra->info = novo->nome[0];  //com a inicial do novo contato criado.
                            novo_letra->letra = novo;   //aponta pro novo contato criado
                            fila_letra *p = primeira_letra;
                            aux = 0;
                            while(p != NULL){  //ordena a fila
                                    if(novo_letra->info > p->info){   //se a inicial criada for maior que a inicial existente ...
                                          novo_letra->ant = p;   //a inicial criada passa a apontar pra inicial existente.
                                          aux++;   
                                    }
                                    p = p->prox;
                            }
                            if(aux != 0){  //se for maior que alguma existente...
                                   if(novo_letra->ant->prox == NULL){  //se aponta para o ultimo existente da fila... vai para o fim da fila
                                            novo_letra->ant->prox = novo_letra;
                                            novo_letra->prox = NULL;
                                   }
                                   else{  //se nao, é inserido entre outros dois elementos.
                                            novo_letra->prox = novo_letra->ant->prox;
                                            novo_letra->ant->prox = novo_letra;
                                            novo_letra->prox->ant = novo_letra;
                                   }
                                   return primeira_letra;
                            }
                            else{  //se nao, vai pro inicio da fila
                                   novo_letra->ant = NULL;
                                   novo_letra->prox = primeira_letra;
                                   return novo_letra;
                            }
                  }
                  else{    //se tiver algum nó com a primeira letra do novo contato criado...
                          fila_contato *u = verifica->letra;
                          if(novo->favorito == 's'){  //se o novo contato for favorito
                                if(verifica->letra->favorito == 'n'){  //se nao tiver nenhum favorito na fila
                                       novo->ant = NULL;
                                       novo->prox = verifica->letra;
                                       novo->prox->ant = novo;
                                       verifica->letra = novo;  //novo contato passa a ser o primeiro da fila e o primeiro favorito.
                                       return primeira_letra;  
                                }
                                else{  //se ja tiver um contato na fila como favorito
                                       if(u->ant == NULL && u->prox == NULL){  //se o favorito da fila for o unico contato existente
                                             u->prox = novo;
                                             novo->ant = u;  //o contato criado passa a ser o segundo favorito...
                                             novo->prox = NULL;   //e ultimo da fila.
                                             return primeira_letra;
                                       }
                                       else{  //se existir contatos favoritos e nao favoritos.
                                           while(u->prox != NULL && u->favorito == 's')  //acha o primeiro contato nao favorito
                                                u = u->prox;
                                           if(u->prox == NULL ){  //se chegar no ultimo contato...
                                                if(u->favorito == 'n'){  //e ele for nao favorito
                                                    novo->ant = u->ant;  
                                                    u->ant = novo;
                                                    novo->prox = u;  //contato criado fica na frente dele.
                                                    novo->ant->prox = novo;  
                                                    return primeira_letra;
                                                }
                                                else{  //se todos forem favoritos... 
                                                     u->prox = novo;
                                                     novo->ant = u;
                                                     novo->prox = NULL;    //cria no final
                                                     return primeira_letra;
                                                }
                                           }
                                           else{  //o primeiro contato nao favorita ta no meio de outros contatos
                                                novo->prox = u; 
                                                novo->ant = u->ant;
                                                u->ant = novo;
                                                novo->ant->prox = novo;
                                                return primeira_letra;
                                           }
                                       }                
                                }
                          }
                           else{   //se o novo contato nao for favorito.  
                                while(u->prox != NULL)  //acha o ultimo contato da fila.
                                    u = u->prox;
                                novo->ant = u;  //inseri no final da fila.
                                u->prox = novo;
                                return primeira_letra;
                           }      
              }
        }
}
