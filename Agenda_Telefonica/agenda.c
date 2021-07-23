 #include<stdio.h>
  #include<stdlib.h>
  #include<string.h>

      struct agenda_telefonica{
          char nome[25];
          char email[25];
          /*struct enderecos{
              char pais[25];
              char estado[25];
              char cidade[25];
              char bairro[25];
              char rua[25];
              int cep;
              int numero;
          }*/
          int telefone;
          char data_aniversario[10];
          char observacao[100];
      };

  void preencher_agenda(struct agenda_telefonica *ponteiro_contatos);
  void busca_contato(struct agenda_telefonica *ponteiro_contatos);
  void busca_mes_do_aniversario(struct agenda_telefonica *ponteiro_contatos);
  void busca_mesedia_do_aniversario(struct agenda_telefonica *ponteiro_contatos);
  void retira_pessoas(struct agenda_telefonica *ponteiro_contatos);
  void imprime_agenda(struct agenda_telefonica *ponteiro_contatos);
  void menu(struct agenda_telefonica *ponteiro_contatos);

  int main()
  {

      struct agenda_telefonica contatos[2];
      struct agenda_telefonica *ponteiro_contatos;
      ponteiro_contatos = contatos;

      for(int i = 0; i < 2; i++){
          printf("\n\nNome: ");
          fflush(stdin);
          gets(contatos[i].nome);
          printf("\n\nEmail: ");
          fflush(stdin);
          gets(contatos[i].email);
          printf("\n\nData de aniversario: ");
          fflush(stdin);
          gets(contatos[i].data_aniversario);
          printf("\n\nObservacao: ");
          fflush(stdin);
          gets(contatos[i].observacao);
          printf("\n\nTelefone: ");
          scanf("%d", &contatos[i].telefone);
      }

      menu(ponteiro_contatos);

      return 0;
  }

  void menu(struct agenda_telefonica *ponteiro_contatos)
  {

      printf("\n\n\n------------------------------------ MENU -------------------------------------\n>> OPCOES\n> (1) Buscar contato\n> (2) Buscar contato po mes de aniversario\n> (3) Buscar contato por mes e dia de aniversario\n> (3) Excluir contato\n> (4) Imprimir agenda");
      int opcao;
      printf("\n> Opcao: ");
      scanf("%d", &opcao);

      switch (opcao)
      {
      case 1:
      busca_contato(ponteiro_contatos);
      break;
      case 2:
      busca_mes_do_aniversario(ponteiro_contatos);
      break;
      busca_mesedia_do_aniversario(ponteiro_contatos);
      case 3:
      retira_pessoas(ponteiro_contatos);
      break;
      case 4:
      imprime_agenda(ponteiro_contatos);
      break;
      }
  }

  void busca_contato(struct agenda_telefonica *ponteiro_contatos)
  {

      char nome_busca[25];

      printf("\n\n> Procura: ");
      fflush(stdin);
      gets(nome_busca);

      for(int i = 0; i < 2; i++){

          if ( strncmp(ponteiro_contatos[i].nome ,nome_busca, sizeof(nome_busca)))
          {
          printf("\n\n\n\t\t> Contato");
          printf("\n\nNome: %s", ponteiro_contatos[i].nome);
          printf("\n\nEmail: %s", ponteiro_contatos[i].email);
          printf("\n\nData de aniversario: %s", ponteiro_contatos[i].data_aniversario);
          printf("\n\nObservacao: %s", ponteiro_contatos[i].observacao);
          printf("\n\nTelefone: %d", ponteiro_contatos[i].telefone);
          }
      }
  }

  void busca_mes_do_aniversario(struct agenda_telefonica *ponteiro_contatos)
  {
      char mes_de_aniversario[2],mes[2];
      printf("\n\n>Procura: ");
      fflush(stdin);
      gets(mes_de_aniversario);

      //strncmp(const char *str1, const char *str2, size_t n)
      for(int i =0; i < 2; i++)
      {
          mes[0]=ponteiro_contatos[i].data_aniversario[4];
          mes[1]=ponteiro_contatos[i].data_aniversario[5];

          if( strcmp(mes_de_aniversario,mes))
          {
              printf("\n\n\n\t\tContato %i", i++);
              printf("\n\nNome: %s", ponteiro_contatos[i].nome);
              printf("\n\nEmail: %s", ponteiro_contatos[i].email);
              printf("\n\nData de aniversario: %s", ponteiro_contatos[i].data_aniversario);
              printf("\n\nObservacao: %s", ponteiro_contatos[i].observacao);
              printf("\n\nTelefone: %d", ponteiro_contatos[i].telefone);
          }
      }
  }

  void busca_mesedia_do_aniversario(struct agenda_telefonica *ponteiro_contatos)
  {
      char diaemes_de_aniversario[5];
      printf("\n\n>Procura: ");
      fflush(stdin);
      gets(diaemes_de_aniversario);

      //strncmp(const char *str1, const char *str2, size_t n)
      for(int i =0; i < 2; i++)
      {
          if(  strncmp(ponteiro_contatos[i].data_aniversario,diaemes_de_aniversario,5))
          {
              printf("\n\n\n\t\tContato %i", i++);
              printf("\n\nNome: %s", ponteiro_contatos[i].nome);
              printf("\n\nEmail: %s", ponteiro_contatos[i].email);
              printf("\n\nData de aniversario: %s", ponteiro_contatos[i].data_aniversario);
              printf("\n\nObservacao: %s", ponteiro_contatos[i].observacao);
              printf("\n\nTelefone: %d", ponteiro_contatos[i].telefone);
          }
      }
  }

  void retira_pessoas(struct agenda_telefonica *ponteiro_contatos)
  {
      char selecionadop_eclusao[25];
      printf("\n\nExcluir: ");
      fflush(stdin);
      gets(selecionadop_eclusao);

      for(int i = 0; i < 2; i++)
      {
          if(strncmp(selecionadop_eclusao,ponteiro_contatos[i].nome,sizeof(ponteiro_contatos[i].nome)))
          {
              ponteiro_contatos[i] = ponteiro_contatos[i+1];
          }
      }

  }

  void imprime_agenda(struct agenda_telefonica *ponteiro_contatos)
  {
      int opcao, nome;
      char nome_imprimir[25];

      printf("\n\n> Procurar: ");
      fflush(stdin);
      gets(nome_imprimir);

      for(int i = 0; i < 2; i++){

          if ( strcmp(ponteiro_contatos[i].nome ,nome_imprimir)){
              nome =i;    
          }
      }

      printf("\n\nSelecione uma opcao\n(1) Imprimir nome, telefone, email\n(2)Imprimir todos os dados\n> Opcao: ");
      scanf("%d", &opcao);

      switch (opcao)
      {
          case 1:
              printf("\n\n> Nome: %s", ponteiro_contatos[nome].nome);
              printf("\n> Telefone: %i", ponteiro_contatos[nome].telefone);
              break;

          case 2:
              printf("\n\nNome: %s", ponteiro_contatos[nome].nome);
              printf("\n\nEmail: %s", ponteiro_contatos[nome].email);
              printf("\n\nData de aniversario: %s", ponteiro_contatos[nome].data_aniversario);
              printf("\n\nObservacao: %s", ponteiro_contatos[nome].observacao);
              printf("\n\nTelefone: %d", ponteiro_contatos[nome].telefone);
              break;
      }
  }
