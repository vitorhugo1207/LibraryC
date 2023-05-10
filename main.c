#include <stdio.h> 
#include <string.h> 

#define LIVROS "livros.dat"
#define CLIENTES "clientes.dat"
#define VENDAS "vendas.dat"
#define AUTHORS "authors.dat"
#define MAXCART 10 //Max number of the cart
#define MAXAUTHOR 5 //Max number of author that a book have
#define MAXBOOK 5 //Max number of book per author

struct reg_livro{ 
 int codigo; 
 char titulo[30]; 
 float preco; 
 int codAuthor[MAXAUTHOR];
}; 

struct reg_cliente{
  int codigo;
  char nome[40];
  char fone[20];
  char email[30];	
};

struct reg_venda{
  int codvenda;  //Código da venda (ou pedido)	
  int codcliente; //Código do Cliente que comprou
  int codlivro[MAXCART];  //Código do Livro vendido
  int qtde[MAXCART];  //Qtde vendida deste item
  float desconto[MAXCART]; //Desconto aplicado a este item
};

struct reg_author{
  int codAuthor;
  int codLivro[MAXBOOK];
  char name[30];
};

void consultarCodigoLivro(){
  FILE *fplivro;
  struct reg_livro livro;
  int cod, achou=0;	
	
  //Solicitar o codigo do livro a ser Localizado
  printf("\nDigite o codigo do livro a ser localizado: ");
  fflush(stdin); scanf("%i",&cod);
  
  //Abrir o Arquivo
  if ((fplivro = fopen(LIVROS,"rb"))==NULL){ //consistência da Abertura do Arquivo
  	printf("\nErro ao abrir o Arquivo %s",LIVROS);
  	return;  //Volta para o Programa Principal
  } 
  
  //Ler registro por registro até encontrar o Livro 
  while ((achou==0) && (fread(&livro,sizeof(livro),1,fplivro)==1)){
  	printf("\nProcessando livro codigo: %i",livro.codigo);
  	if (livro.codigo==cod){
  	  printf("\nCodigo: %i\nTitulo: %s\nPreco: %5.2f",livro.codigo,livro.titulo,livro.preco);	
  	  achou = 1; //Sinaliza que encontrou o livro
  	  //break;
	}
  }
  
  if (achou==0){
  	printf("\nNenhum livro localizado com este codigo!");
  }
  //Fechar o Arquivo
  fclose(fplivro);	

  system("pause");
}//Fim consultarCodigoLivro()

void consultarTituloLivro(){
  FILE *fplivro;
  struct reg_livro livro;
  char tit[30];
  int achou=0;	
	
  //Solicitar o Titulo do livro a ser Localizado
  printf("\nDigite o Titulo do livro a ser localizado: ");
  fflush(stdin); gets(tit);
  
  //Abrir o Arquivo
  if ((fplivro = fopen(LIVROS,"rb"))==NULL){ //consistência da Abertura do Arquivo
  	printf("\nErro ao abrir o Arquivo %s",LIVROS);
  	return;  //Volta para o Programa Principal
  } 
  
  //Ler registro por registro até encontrar o Livro 
  while ((achou==0) && (fread(&livro,sizeof(livro),1,fplivro)==1)){
  	if (strcmp(livro.titulo,tit)==0){
  	  printf("\nCodigo: %i\nTitulo: %s\nPreco: %5.2f",livro.codigo,livro.titulo,livro.preco);	
  	  achou = 1; //Sinaliza que encontrou o livro
  	  //break;
	}
  }
  
  if (achou==0){
  	printf("\nNenhum livro localizado com este codigo!");
  }
  //Fechar o Arquivo
  fclose(fplivro);	
	
  system("pause");
}//Fim consultarTituloLivro()

void alterarLivro(){
  FILE *fplivro;
  struct reg_livro livro;
  int cod, achou=0;	
  char opc;
	
  //Solicitar o codigo do livro a ser Alterado
  printf("\nDigite o codigo do livro a ser Alterado: ");
  fflush(stdin); scanf("%i",&cod);
  
  //Localizar e mostrar os dados do Livro
  //Abrir o Arquivo
  if ((fplivro = fopen(LIVROS,"rb+"))==NULL){ //consistência da Abertura do Arquivo
  	printf("\nErro ao abrir o Arquivo %s",LIVROS);
  	return;  //Volta para o Programa Principal
  } 
  
  //Ler registro por registro até encontrar o Livro 
  while ((achou==0) && (fread(&livro,sizeof(livro),1,fplivro)==1)){
  	if (livro.codigo==cod){
  	  printf("\nCodigo: %i\nTitulo: %s\nPreco: %5.2f",livro.codigo,livro.titulo,livro.preco);	
  	  achou = 1; //Sinaliza que encontrou o livro
	}
  }
  
  if (achou==0){
  	printf("\nNenhum livro localizado com este codigo!");
  	fclose(fplivro);
  	return; //Retorna ao Menu Principal
  }

  //Pedir os novos dados
  printf("\nDeseja alterar o Titulo(S/N)? ");
  fflush(stdin); scanf("%c",&opc); 
  
  if ((opc=='s') || (opc=='S')){
  	printf("\nDigite o novo Titulo: ");
  	fflush(stdin); gets(livro.titulo);
  }

  printf("\nDeseja alterar o Preco(S/N)? ");
  fflush(stdin); scanf("%c",&opc); 
  
  if ((opc=='s') || (opc=='S')){
  	printf("\nDigite o novo Preco: ");
  	fflush(stdin); scanf("%f",&livro.preco);
  }  
  
  //Deslocar o ponteiro do arquivo para o registro anterior
  fseek(fplivro,-sizeof(livro),1);
  
  //Gravar a alteração no Arquivo
  fwrite(&livro,sizeof(livro),1,fplivro);
   
  //Fechar o Arquivo
  fclose(fplivro);
  
  //Dar uma mensagem de feedback para o usuário
  printf("\nLivro Alterado com Sucesso.");

  system("pause");
}//Fim alterarLivro()

void excluirLivro(){
  FILE *fplivro, *fplivrosnew;
  struct reg_livro livro;
  int cod, achou=0;	
  char opc;
	
  //Solicitar o codigo do livro a ser Excluído
  printf("\nDigite o codigo do livro a ser Excluido: ");
  fflush(stdin); scanf("%i",&cod);
  
  //Localizar e mostrar os dados do Livro
  //Abrir o Arquivo
  if ((fplivro = fopen(LIVROS,"rb"))==NULL){ //consistência da Abertura do Arquivo
  	printf("\nErro ao abrir o Arquivo %s",LIVROS);
  	return;  //Volta para o Programa Principal
  } 
  
  //Ler registro por registro até encontrar o Livro 
  while ((achou==0) && (fread(&livro,sizeof(livro),1,fplivro)==1)){
  	if (livro.codigo==cod){
  	  printf("\nCodigo: %i\nTitulo: %s\nPreco: %5.2f",livro.codigo,livro.titulo,livro.preco);	
  	  achou = 1; //Sinaliza que encontrou o livro
	}
  }
  
  fclose(fplivro);
  
  if (achou==0){
  	printf("\nNenhum livro localizado com este codigo!");
  	return; //Retorna ao Menu Principal
  }
  
  //Pedir Confirmação
  printf("\nConfirma Exclusao(S/N)? ");
  fflush(stdin); scanf("%c",&opc); 
  
  if ((opc=='n') || (opc=='N')){
  	printf("\nExclusao Cancelada!");
  	return; //Retorna ao Menu Principal
  } 
  
  //Exclusao Confirmada - Excluir o Livro
  fplivro = fopen(LIVROS,"rb");
  fplivrosnew = fopen("livrosnew.dat","wb");
  
  //Copiar todos os livros, menos o livro a ser excluído, para um
    //arquivo temporário - livrosnew.dat
  while(fread(&livro,sizeof(livro),1,fplivro)==1){
  	if (livro.codigo!=cod){ //Se o livro lido NÃO for o livro sendo excluido
  		fwrite(&livro,sizeof(livro),1,fplivrosnew);//Grava no temporário
	  }
  }
  fclose(fplivro);
  fclose(fplivrosnew);
  
  //Excluir o arquivo antigo
  system("del livros.dat");
  
  //Renomear o arquivo temporário para livros.dat
  system("ren livrosnew.dat livros.dat");
  
  //Dar um msg de feedback para o usuário
  printf("\nLivro Excluido com Sucesso.");	

  system("pause");
}//Fim excluirLivro()

void cadastrarCliente(){
 struct reg_cliente cliente;
 FILE *fpcliente; //Variável para manipular o Arquivo de Clientes
 char op;
 
 //Entrada dos dados do Livro
 printf("\nCadastro de Cliente: ");
 printf("\n Codigo: ");
 fflush(stdin);	scanf("%i",&cliente.codigo);
 printf(" Nome: ");
 fflush(stdin);	gets(cliente.nome);
 printf(" Fone: ");
 fflush(stdin);	gets(cliente.fone);
 printf(" Email: ");
 fflush(stdin);	gets(cliente.email);


 printf("\nG r a v a r ?(S/N) ");
 fflush(stdin); scanf("%c",&op);
 if ((op=='S') || (op=='s')){
 	//Abrir o arquivo
 	fpcliente = fopen(CLIENTES,"ab"); //Modo "ab" para acrescentar um novo Cliente no arquivo binário 
 	fwrite(&cliente,sizeof(cliente),1,fpcliente); //Gravar no arquivo
 	printf("\nCliente Cadastrado com sucesso.");
 	fclose(fpcliente); //Fecha o arquivo	
 }else{
 	printf("\nCadastro Cancelado!");
 }	

 system("pause");
}//Fim cadastrarCliente()

void listarClientes(){
  FILE *fpcliente;
  struct reg_cliente cliente;	
	
  //Abrir o Arquivo
  if ((fpcliente = fopen(CLIENTES,"rb"))==NULL){
  	printf("\nErro na abertura do arquivo!!");
  	return;
  }
  
  //Ler registo	por registro e mostrar na tela
  printf("\n##### Relatorio de Todos os Clientes ######");
  printf("\nCodigo Nome                           Fone            Email               ");
  while (fread(&cliente,sizeof(cliente),1,fpcliente)==1){
    printf("\n%-6i %-30s %-15s %-20s",cliente.codigo,cliente.nome,cliente.fone,cliente.email);
  }  
  
  //Fechar o Arquivo
  fclose(fpcliente);	

  system("pause");
}//Fim listarClientes()

struct reg_cliente localizarCliente(int codcli){
  FILE *fpcliente;
  struct reg_cliente cliente;
  int achou=0;	
	

  //Abrir o Arquivo
  if ((fpcliente = fopen(CLIENTES,"rb"))==NULL){ //consistência da Abertura do Arquivo
  	printf("\nErro ao abrir o Arquivo %s",LIVROS);
  	return;  //Volta para o Programa Principal
  } 
  
  //Ler registro por registro até encontrar o Livro 
  while ((achou==0) && (fread(&cliente,sizeof(cliente),1,fpcliente)==1)){
  	if (cliente.codigo==codcli){
  	  achou = 1; //Sinaliza que encontrou o Cliente
	}
  }
  
  if (achou==0){
  	cliente.codigo = -1; //Sinaliza que NÃO LOCALIZOU O CLIENTE
  }
  //Fechar o Arquivo
  fclose(fpcliente);	
	 
  return cliente;	
 	
 }//Fim localizarCliente()

struct reg_livro localizarLivro(int codlivro){
  FILE *fplivro;
  struct reg_livro livro;
  int achou=0;	
	

  //Abrir o Arquivo
  if ((fplivro = fopen(LIVROS,"rb"))==NULL){ //consistência da Abertura do Arquivo
  	printf("\nErro ao abrir o Arquivo %s",LIVROS);
  	return;  //Volta para o Programa Principal
  } 
  
  //Ler registro por registro até encontrar o Livro 
  while ((achou==0) && (fread(&livro,sizeof(livro),1,fplivro)==1)){
  	if (livro.codigo==codlivro){
  	  achou = 1; //Sinaliza que encontrou o livro
	}
  }
  
  if (achou==0){
  	livro.codigo = -1; //Sinaliza que NÃO LOCALIZOU O LIVRO
  }
  //Fechar o Arquivo
  fclose(fplivro);	
	 
  return livro;	
 	
 }//Fim localizarLivro()
 
struct reg_author findAuthor(int codAuthor){
  FILE *fpauthor;
  struct reg_author author = {-1, ' ', {0}};

  if ((fpauthor = fopen(AUTHORS,"rb"))==NULL){
  	printf("\nErro ao abrir o Arquivo %s",AUTHORS);
  	return author;
  } 

  while (fread(&author,sizeof(author),1,fpauthor)==1){
  	if (author.codAuthor==codAuthor){
  	  fclose(fpauthor);
      return author;
	  }
  }

  fclose(fpauthor);
  return author;
}

void listarLivros(){
  FILE *fplivro;
  FILE *fpauthor;
  struct reg_livro livro;
  struct reg_author author;
  
  //Abrir o Arquivo
  if ((fplivro = fopen(LIVROS,"rb"))==NULL){ //consistência da Abertura do Arquivo
  	printf("\nErro ao abrir o Arquivo %s",LIVROS);
  	return;  //Volta para o Programa Principal
  } 
  if ((fpauthor = fopen(AUTHORS,"rb"))==NULL){ 
  	printf("\nErro ao abrir o Arquivo %s",AUTHORS);
  	return;
  } 

  printf("\n####  Relatorio de Todos os Livros  ####");
  //Ler registro por registro e mostrar na tela 
  while (fread(&livro,sizeof(livro),1,fplivro)==1){ 
    printf("\nCodigo: %-6i", livro.codigo);
    printf("\nTitulo: %-30s", livro.titulo);
    printf("\nAutor(es): ");

    for(int i = 0; i < MAXAUTHOR; i++){
      author = findAuthor(livro.codAuthor[i]);
      printf("%-30s", author.name);
      if(author.codLivro[i] == -1){
        break;
      }
    }

    printf("\nPreco: %5.2f", livro.preco);
    printf("\n----");
    // printf("\n%-6i %-30s %-30s %5.2f",livro.codigo,livro.titulo,author.name,livro.preco);
  }
  //Fechar o Arquivo	
  fclose(fplivro);	

  printf("\n");
  system("pause");
}//Fim listarLivros()

void registerAuthor(){
  FILE *fpauthor;
  struct reg_author author;
  
  printf("\nDigite o codigo do autor: ");
  fflush(stdin); scanf("%i", &author.codAuthor);

  printf("\nDigite o nome do autor:");
  fflush(stdin); gets(author.name);

  for(int i = 0; i < MAXAUTHOR; i++){
    author.codLivro[i] = -1;
  }

  fpauthor = fopen("authors.dat", "ab");
  fwrite(&author,sizeof(author),1,fpauthor);
  fclose(fpauthor);

  system("pause");
}

void addBooktoAuthor(int codAuthor, int codBook){
  FILE *fpauthor;
  struct reg_author author;
  int find = 0;

  if ((fpauthor = fopen(AUTHORS,"rb+"))==NULL){
  	printf("\nErro ao abrir o Arquivo %s",AUTHORS);
  	return;
  } 

  while ((find==0) && (fread(&author,sizeof(author),1,fpauthor)==1)){
  	if (author.codAuthor==codAuthor){
  	  find = 1;
	  }
  }
  if (find==0){
  	printf("\nNenhum autor localizado com este codigo!");
  	fclose(fpauthor);
  	return;
  }

  for(int i = 0; i < MAXAUTHOR; i++){
    if(author.codLivro[i] == -1){
      author.codLivro[i] = codBook;
      fseek(fpauthor,-sizeof(author),SEEK_CUR);
      fwrite(&author,sizeof(author),1,fpauthor);
      break;
    }
  }

  fclose(fpauthor);
}

void cadastrarLivro(){
  FILE *fplivro; //Descritor do Arquivo
  struct reg_livro livro;
  struct reg_author author;
  char opc, confirm;
  int codAuthor;

  // for(int i = 0; i < MAXAUTHOR; i++){
  //   livro.codAuthor[i] = -1;
  // }
  
  printf("\nCadastro de Livro:\n");
  //Pedir os dados do Livro
  printf("\nDigite o Codigo: ");
  fflush(stdin); scanf("%i",&livro.codigo);
  printf("Titulo: ");
  fflush(stdin); gets(livro.titulo);
  printf("Preco: ");
  fflush(stdin); scanf("%f",&livro.preco);

  for(int i = 0; i < MAXAUTHOR; i++){
    printf("\nDigite o codigo do author: ");
    fflush(stdin); scanf("%i", &codAuthor);
    author = findAuthor(codAuthor);
    
    if(author.codAuthor == -1){
      printf("\nAutor nao encontrado! Retornando para o menu...");
      return;
    }

    livro.codAuthor[i] = author.codAuthor;
    addBooktoAuthor(author.codAuthor, livro.codigo);
    printf("Autor cadastrado: %-30s", author.name);

    printf("\nDeseja atribuir mais um autor para esse livro? (S/N)");
    fflush(stdin); scanf("%s", &confirm);
    if((confirm == 'N') || (confirm == 'n')){
      break;
    }
  }
  
  //Pedir Confirmação
  printf("\nGravar Livro?(S/N): ");
  fflush(stdin); scanf("%c",&opc);
  if ((opc=='S')||(opc=='s')){
    //Armazenar os dados do Livro no arquivo
    //Abrir o Arquivo
    fplivro = fopen("livros.dat","ab"); 
    //Gravar
    fwrite(&livro,sizeof(livro),1,fplivro);
    //Fechar o Arquivo
    fclose(fplivro);
  	printf("\nLivro Gravado com Sucesso.\n");
  }else{
  	printf("\nOperacao Cancelada!\n");
  }

  system("pause");
}//Fim cadastrarLivro()

void efetuarVenda(){
  FILE *fpvenda;
  struct reg_venda venda;
  struct reg_cliente cliente;
  struct reg_livro livro;
  char opc, confirmCont, confirmCart;
  int x=0; // quantidade de indexs
  double total, totalAll=0;
  
  //Entrada de Dados
  //Pedir o código da venda (nro. do pedido)
  printf("\nDigite o Codigo da Venda: ");
  fflush(stdin); scanf("%i",&venda.codvenda);

  //Pedir o Códio do cliente
  printf("Digite o Codigo do Cliente: ");
  fflush(stdin); scanf("%i",&venda.codcliente);    
  //Localizar o Cliente, mostrar e pedir confirmação
  cliente = localizarCliente(venda.codcliente);
  if (cliente.codigo==-1){
    printf("\nNenhum Cliente localizado com este codigo!");
    return; //Retorna para o menu principal
  }
  printf("\nCliente: %s",cliente.nome);
  printf("\nConfirma Cliente(S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  if ((opc=='n')||(opc=='N')){
    printf("\nCliente NAO Confirmado!");
    return; ////Retorna para o menu principal
  }

  for(int y = 0; y < MAXCART; y++){
    //Pedir o Código do Livro
    printf("Digite o Codigo do Livro: ");
    fflush(stdin); scanf("%i",&venda.codlivro[y]);    
    //Localizar o Livro, mostrar e pedir confirmação
    livro = localizarLivro(venda.codlivro[y]);
    if (livro.codigo==-1){
      printf("\nNenhum Livro localizado com este codigo!");
      return; //Retorna para o menu principal
    }
    printf("\nLivro: %s",livro.titulo);
    printf("\nConfirma Livro(S/N)? ");
    fflush(stdin); scanf("%c",&opc);
    if ((opc=='n')||(opc=='N')){
      printf("\nLivro NAO Confirmado!");
      return; ////Retorna para o menu principal
    }

    //Pedir a Qtde
    printf("\nDigite a quantidade: ");
    fflush(stdin); scanf("%i",&venda.qtde[y]);

    //Pedir o Desconto
    printf("\nDigite o Desconto: ");
    fflush(stdin); scanf("%f",&venda.desconto[y]);	

    //Confirmar Venda
    printf("\nConfirma Venda(S/N)? ");
    fflush(stdin); scanf("%c",&opc);
    if ((opc=='n')||(opc=='N')){
      printf("\nVenda NAO Confirmado!");
      return; ////Retorna para o menu principal
    }

    printf("\nDeseja adicionar mais itens? (S/N)");
    fflush(stdin); scanf("%c", &confirmCont);
    if((confirmCont == 'n') || (confirmCont == 'N')){
      printf("==========     Carrinho de pedidos:    ==========\n");
      printf("Cliente: %s\n", cliente.nome);
      printf("Codigo pedido: %i\n", venda.codvenda);

      for(int i = 0; i < y + 1; i++){
        printf("-------------------------------------------------\n");
        livro = localizarLivro(venda.codlivro[i]);
        printf("Titulo do livro: %s\n", livro.titulo);
        printf("Quantidade: %i\n", venda.qtde[i]);
        printf("Preco: %5.2f\n", livro.preco);
        printf("Desconto: %5.2f\n", venda.desconto[i]);
        total = livro.preco - venda.desconto[i];
        printf("Total da unidade: %5.2f\n", total);
        printf("Total: %5.2f\n", total*venda.qtde[i]);

        totalAll += (total*venda.qtde[i]);
      }
      printf("========     Total dos pedidos: %5.2f     ========\n", totalAll);
      break;
    }
  }

  printf("\nDeseja cancelar o carrinho? (S/N) ");
  fflush(stdin); scanf("%c", &confirmCart);
  if((confirmCart == 's') || (confirmCart == 'S')){
    return;
  }

  //Gravar os dados no arquivo de Vendas
  //Abrir o Arquivo
  fpvenda = fopen(VENDAS,"ab");  
	//Gravar o registro da venda
	fwrite(&venda,sizeof(venda),1,fpvenda);
	//Fechar o Arquivo
	fclose(fpvenda);
	//Dar uma msg de feedback para o usuário
	printf("\nVenda Gravada com Sucesso.");

  system("pause");
}//Fim efetuarVenda()

void showSolds(){
  FILE *fpvenda;

  struct reg_livro livro;
  struct reg_cliente cliente;
  struct reg_venda venda;

  double valuePaid, valueTotal;

  if((fpvenda = fopen(VENDAS, "rb"))==NULL){
  	printf("\nErro ao abrir o Arquivo %s",VENDAS);
  	return;  //Volta para o Programa Principal
  }

  printf("=============== Vendas ===============");
  while (fread(&venda, sizeof(venda),1,fpvenda)==1)
  {
    printf("\n--------------------------------------");
    printf("\nPedido numero: %i", venda.codvenda);
    cliente = localizarCliente(venda.codcliente);
    printf("\nCliente: %s", cliente.nome);
    printf("\n-------");

    valueTotal = 0;
    for(int i = 0; i < MAXCART; i++){
      livro = localizarLivro(venda.codlivro[i]);

      if(venda.codlivro[i] == NULL || livro.codigo == -1){
          printf("\nTotal Pago: %5.2f", valueTotal);
          break;
      };

      valuePaid = (livro.preco - venda.desconto[i])*venda.qtde[i];
      valueTotal += valuePaid;

      printf("\nCodigo do Livro: %i\nTitulo do Livro: %s\nQuantidade: %i\nPreco: %5.2f\nDesconto: %5.2f\nValor Pago: %5.2f", venda.codlivro[i], livro.titulo, venda.qtde[i], livro.preco, venda.desconto[i], valuePaid);

      printf("\n-------");

      if(venda.codlivro[i] == NULL || livro.codigo == -1){
        printf("\nTotal Pago: %5.2f", valueTotal);
      };
    }
  }
  printf("\n======================================");
  fclose(fpvenda);

  system("pause");
}

void searchBookAuthor(){
  struct reg_author author;
  struct reg_livro livro;
  int codAuthor;

  printf("Digite o numero do autor: ");
  fflush(stdin); scanf("%i", &codAuthor);

  author = findAuthor(codAuthor);
  if(author.codAuthor == -1){
    printf("autor não encontrado!");
    return;
  }

  printf("\n----");
  printf("\nNome do Autor: %-30s", author.name);
  printf("\nLivros: ");

  for(int i = 0; i < MAXAUTHOR; i++){
    livro = localizarLivro(author.codLivro[i]);
    if(livro.codigo == -1){
      break;
    }
    printf("%-30s", livro.titulo);
  }
  
  printf("\n");
  system("pause");
}

int main() { 
  int op;

  do {
    system("cls");

  	printf("\n\n#########        Livraria Tech Info        #############");
  	printf("\n###                                                  ###");
  	printf("\n### 1) Cadastrar um Livro                            ###");
  	printf("\n### 11) Cadastrar um Autor                           ###");
  	printf("\n### 111) Cadastrar um Cliente                        ###");
  	printf("\n### 2) Listar todos os Livros                        ###");
  	printf("\n### 22) Listar todos as Vendas                       ###");
  	printf("\n### 222) Listar todos os Clientes                    ###");
  	printf("\n### 3) Consultar Livro pelo Codigo                   ###");
  	printf("\n### 4) Consultar Livro pelo Titulo                   ###");
  	printf("\n### 5) Consultar Livro por Palavra chave o Titulo    ###");
  	printf("\n### 6) Alterar dados do Livro                        ###");
  	printf("\n### 7) Excluir um Livro                              ###");
  	printf("\n### 8) Efetuar Venda (Limite do carrinho: %i itens)  ###", MAXCART);
  	printf("\n### 9) Procurar livro por autor                      ###");
  	printf("\n### 0) Sair                                          ###");
  	printf("\n###                                                  ###");
  	printf("\nOpcao-> ");
  	fflush(stdin); scanf("%i",&op);
  	
  	switch(op){
  	  case 1: //Cadastrar um novo Livro
  	    cadastrarLivro();
  	    break;	    
  	  case 111: //Cadastrar um novo Cliente
  	    cadastrarCliente();
  	    break;
  	  case 2: //Listar todos os Livros
  	    listarLivros();
  	    break;
  	  case 222: //Listar todos os Clientes
  	    listarClientes();
  	    break;  	    
  	  case 3: //Consultar Livro pelo Código
  	    consultarCodigoLivro();
  	    break;
  	  case 4: //Consultar Livro pelo Titulo
  	  	consultarTituloLivro();
  	  	break;
  	  case 6: //Alterar dados de um Livro
		    alterarLivro();
		    break;	
  	  case 7: //Excluir um Livro
		    excluirLivro();
		    break; 	
	    case 8: //Efetuar a Venda
	      efetuarVenda();
	      break; 	
      case 22:
        showSolds(); 	
        break;
      case 11:
        registerAuthor();
        break;
      case 9:
        searchBookAuthor();
        break;
      case 0:
        printf("\nSaindo...\n");
        system("exit");
        break;
	} 	
  }while (op!=0);


}//Fim main()
