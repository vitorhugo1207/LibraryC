#include <stdio.h> 
#include <string.h> 

#define LIVROS "livros.dat"
#define CLIENTES "clientes.dat"
#define VENDAS "vendas.dat"

struct reg_livro{ 
 int codigo; 
 char titulo[30]; 
 float preco; 
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
  int codlivro;  //Código do Livro vendido
  int qtde;  //Qtde vendida deste item
  float desconto; //Desconto aplicado a este item
};

void cadastrarLivro(){
  FILE *fplivro; //Descritor do Arquivo
  struct reg_livro livro;
  char opc;
  
  printf("\nCadastro de Livro:\n");
  //Pedir os dados do Livro
  printf("\nDigite o Codigo: ");
  fflush(stdin); scanf("%i",&livro.codigo);
  printf("Titulo: ");
  fflush(stdin); gets(livro.titulo);
  printf("Preco: ");
  fflush(stdin); scanf("%f",&livro.preco);
  
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
  	printf("\nLivro Gravado com Sucesso.");
  }else{
  	printf("\nOperacao Cancelada!");
  }
}//Fim cadastrarLivro()

void listarLivros(){
  FILE *fplivro;
  struct reg_livro livro;
  
  //Abrir o Arquivo
  if ((fplivro = fopen(LIVROS,"rb"))==NULL){ //consistência da Abertura do Arquivo
  	printf("\nErro ao abrir o Arquivo %s",LIVROS);
  	return;  //Volta para o Programa Principal
  } 
  
  printf("\n####  Relatorio de Todos os Livros  ####");
  printf("\nCodigo Titulo                         Preco");
  //Ler registro por registro e mostrar na tela 
  while (fread(&livro,sizeof(livro),1,fplivro)==1){
  	printf("\n%-6i %-30s %5.2f",livro.codigo,livro.titulo,livro.preco);
  }
  
  //Fechar o Arquivo	
  fclose(fplivro);	
	
}//Fim listarLivros()

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

void efetuarVenda(){
  FILE *fpvenda;
  struct reg_venda venda;
  struct reg_cliente cliente;
  struct reg_livro livro;
  struct reg_venda cart[100];
  char opc, confirm;
  int x=0; // quantidade de indexs
  
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

  while(1){
    //Pedir o Código do Livro
    printf("Digite o Codigo do Livro: ");
    fflush(stdin); scanf("%i",&venda.codlivro);    
    //Localizar o Livro, mostrar e pedir confirmação
    livro = localizarLivro(venda.codlivro);
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
    fflush(stdin); scanf("%i",&venda.qtde);

    //Pedir o Desconto
    printf("\nDigite o Desconto: ");
    fflush(stdin); scanf("%f",&venda.desconto);	

    //Confirmar Venda
    printf("\nConfirma Venda(S/N)? ");
    fflush(stdin); scanf("%c",&opc);
    if ((opc=='n')||(opc=='N')){
      printf("\nVenda NAO Confirmado!");
      return; ////Retorna para o menu principal
    }

    cart[x] = venda;
    printf("\n Deseja adicionar mais itens? (S - Sim / N - Não)");
    fflush(stdin); scanf("%c", &confirm);
    if((confirm == 'n') || (confirm == 'N')){
      printf("Carrinho de pedidos:\n");
      printf("========================================\n");
      printf("Cliente: %s\n", cliente.nome);
      printf("Codigo pedido: %i\n", venda.codvenda);

      for(int i = 0; i < x; i++){
        livro = localizarLivro(cart[i].codlivro);
        printf("Titulo do livro: %s\n", livro.titulo);
        printf("Quantidade %i\n", cart[i].qtde);
        printf("Preco %5.2f\n", livro.preco);
        printf("Desconto %5.2f\n", cart[i].desconto);
        float total = livro.preco - cart[i].desconto;
        printf("Total do item %5.2f\n", total);
  
        printf("========================================\n");

        float totalAll = total + totalAll;
      }
      break;
    }
    x++;
  }
    
  //Gravar os dados no arquivo de Vendas
  //Abrir o Arquivo
  fpvenda = fopen(VENDAS,"ab");  
	//Gravar o registro da venda
	fwrite(&cart,sizeof(cart),1,fpvenda);
	//Fechar o Arquivo
	fclose(fpvenda);
	//Dar uma msg de feedback para o usuário
	printf("\n Venda Gravada com Sucesso.");
}//Fim efetuarVenda()

int main() { 
  int op;
  
  do {
  	printf("\n\n#########        Livraria Tech Info        #########");
  	printf("\n###                                                ###");
  	printf("\n### 1) Cadastrar um Livro                          ###");
  	printf("\n### 111) Cadastrar um Cliente                      ###");
  	printf("\n### 2) Listar todos os Livros                      ###");
  	printf("\n### 222) Listar todos os Clientes                  ###");
  	printf("\n### 3) Consultar Livro pelo Codigo                 ###");
  	printf("\n### 4) Consultar Livro pelo Titulo                 ###");
  	printf("\n### 5) Consultar Livro por Palavra chave o Titulo  ###");
  	printf("\n### 6) Alterar dados do Livro                      ###");
  	printf("\n### 7) Excluir um Livro                            ###");
  	printf("\n### 8) Efetuar Venda                               ###");
  	printf("\n### 0) Sair                                        ###");
  	printf("\n###                                                ###");
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
	} 	
  }while (op!=0);


}//Fim main()
