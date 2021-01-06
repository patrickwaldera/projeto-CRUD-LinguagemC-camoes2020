/*
TRABALHO 02 - Sistema de Cadastro de Clientes
Última atualização: 01/12/2020
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

//FUNÇÕES
void ftelainicial();// Função de apresentação (texto)
void fcreditos();// Informações da Faculdade/Aluno/Ano
void fsistema();// Menu principal
int verificarNumero(const char* str);// Verifica se a string digitada é composta por números
int limitarString(char* entrada, int qtd);// Limita a quantidade de caracteres por string para evitar conflitos

//CRUD
int fincluir(void);     // função para INCLUIR dados
void fpesquisar();  // função para PESQUISAR dados
int falterar(void);		// função para ALTERAR dados
int fexcluir(void);     // função para EXCLUIR dados
void flistar(void);     // função para lISTAR dados
int fordenar(void);    // função para ORDENAR dados

//STRUCT
typedef struct Item ITEM;
struct Item{
    int cod_item;
    char descricao_item[100];
};

typedef struct Clientes CLIENTE;
struct Clientes{
	char nome[50];
	char telefone[13];
	char endereco[155];
	char cpfcnpj[15];
	char data_compra[11];
	ITEM itens_comprados;
};

//MAIN
int main()
{
	FILE* arquivo;
	arquivo = fopen("clientes.txt", "ab");
	if(arquivo == NULL)
	{
		printf("\n [ERRO]: O arquivo não pode ser aberto!");
		getch();
		return 0;
	}
	fclose(arquivo);
	int opcao = 0;
	setlocale(LC_ALL, "Portuguese");
    ftelainicial();
    printf(" Escolha uma Opção:\n");
    printf("\n 1 - Acessar o sistema");
    printf("\n 2 - Sair\n");
    do
    {
    	fflush(stdin);
    	printf("\n Digite o número de uma das opções acima: ");
        scanf("%d", &opcao);
        if(opcao != 1 && opcao != 2)
		{
	    	printf("\n [ERRO]: Opção não reconhecida pelo sistema!");
		}
		else
		{
			switch (opcao)
    		{
    			case 1:
    			{
    				fsistema();
					break;
				}
				case 2:
				{
					break;
				}
				default: printf("\n [ERRO]: Opção não reconhecida pelo sistema!");
			}
		}
	}   	
	while(opcao != 1 && opcao != 2);
	return 0;
}

//INCLUIR
int fincluir(void)
{
	int existe = 0;
	FILE* arquivo;
	CLIENTE clt;
	CLIENTE aux;
	arquivo = fopen("clientes.txt", "rb");
	if(arquivo == NULL)
	{
		printf("\n [ERRO]: O arquivo não pode ser aberto!");
		getch();
	}
	else
	{
		fflush(stdin);
		printf ("\n Digite o nome: ");
		gets(clt.nome);
		strupr(clt.nome);
		limitarString(clt.nome, 50);
		while(fread(&aux, sizeof(CLIENTE), 1, arquivo) == 1)
		{
			if(strcmp(clt.nome, aux.nome) == 0)
			{
				existe++;
			}
		}
		if(existe > 0)
		{
			printf ("\n [ERRO]: Este nome já existe na base de dados, consulte usando a ferramenta pesquisar!");
			fclose(arquivo);
			getch();
			return 0;
		}
		else
		{
			fclose(arquivo);
			arquivo = fopen("clientes.txt", "ab");
		}  		
	
		do
		{
    		fflush(stdin);
    		printf (" Digite o telefone (somente números): ");
    		gets(clt.telefone);
    		limitarString(clt.telefone, 13);
		}
		while(!verificarNumero(clt.telefone));
		
		fflush(stdin);
		printf (" Digite o endereço: ");
		gets(clt.endereco);
		strupr(clt.endereco);
		limitarString(clt.endereco, 155);
		
		do
		{
			fflush(stdin);
    		printf (" Digite o CPF/CNPJ (somente números): ");
    		gets(clt.cpfcnpj);
			limitarString(clt.cpfcnpj, 15);	
		}
		while(!verificarNumero(clt.cpfcnpj));
		
		fflush(stdin);
		printf (" Cadastro da data de última compra do cliente, \n");
		printf (" Digite no formato DD/MM/AAAA: ");
		gets(clt.data_compra);
		limitarString(clt.data_compra, 11);  
		  
		do
		{
			fflush(stdin);      
    		printf (" Cadastro de item comprado - Código (0 a 999): ");
			scanf("%d", &clt.itens_comprados.cod_item);
		}
		while(clt.itens_comprados.cod_item > 999 || clt.itens_comprados.cod_item < 0);			
		
		fflush(stdin);
		printf (" Cadastro de item comprado - Descrição: ");
		gets(clt.itens_comprados.descricao_item);
		strupr(clt.itens_comprados.descricao_item);
		limitarString(clt.itens_comprados.descricao_item, 100);
		
		if((strlen(clt.nome)==0) || (strcmp(clt.nome,"0")==0) || (strlen(clt.telefone)==0) || (strcmp(clt.telefone,"0")==0) || (strlen(clt.endereco)==0) || (strcmp(clt.endereco,"0")==0)
		|| (strlen(clt.cpfcnpj)==0) || (strcmp(clt.cpfcnpj,"0")==0) || (strlen(clt.data_compra)==0) || (strcmp(clt.data_compra,"0")==0) || (strlen(clt.itens_comprados.descricao_item)==0)
		|| (strcmp(clt.itens_comprados.descricao_item,"0")==0))
		{
			printf ("\n [ERRO]: Nenhum registro pode ser nulo!");
			fclose(arquivo);
			getch();
			return 0;
		}
		
		fwrite(&clt, sizeof(CLIENTE), 1, arquivo);
		
		printf("\n Registro salvo com sucesso!\n");
    	getch();	
		fclose(arquivo);
	}
	return 1;
}
//PESQUISAR
void fpesquisar()
{
	int achou = 0;
    FILE* arquivo;
	CLIENTE clt;
	char nome[50];
	arquivo = fopen("clientes.txt", "rb");
	if(arquivo == NULL)
	{
		printf("\n [ERRO]: O arquivo não pode ser aberto!");
		getch();
	}
	else
	{
		fflush(stdin);
		printf("\n Digite o nome para pesquisar: ");
		gets(nome);
		strupr(nome);
		limitarString(nome, 50);
		while(fread(&clt, sizeof(CLIENTE), 1, arquivo) == 1)
		{
			if(strcmp(nome, clt.nome) == 0)
			{
				printf("\n Nome: %s\n", clt.nome);
				printf(" Telefone: %s\n", clt.telefone);
				printf(" Endereço: %s\n", clt.endereco);
				printf(" CPF/CNPJ: %s\n", clt.cpfcnpj);
				printf(" Data da última compra: %s\n", clt.data_compra);
				printf(" Código do último item comprado: %d - Descrição: %s\n", clt.itens_comprados.cod_item, clt.itens_comprados.descricao_item);
				printf("--------------------------------------------------------------\n");
				achou++;
			}
		}
		if(achou == 0)
		{
			printf("\n [ERRO]: Não existe um cadastro com esse nome.\n");
		}
	}
	fclose(arquivo);	
	getch();
	fsistema();
}
//ALTERAR
int falterar(void)
{
	int cont = 0, i, achou = 0, existe = 0;
	char nome[50];
    FILE* arquivo;
    FILE* temp;
	CLIENTE clt;
	CLIENTE ord[100];
	arquivo = fopen("clientes.txt", "rb");
	temp = fopen("tmp.txt","wb");
	if(arquivo == NULL || temp == NULL)
	{
		printf("\n [ERRO]: O arquivo não pode ser aberto!");
		getch();
	}
	else
	{
		while(fread(&clt, sizeof(CLIENTE), 1, arquivo) == 1)
		{
			strcpy(ord[cont].nome, clt.nome);
			strcpy(ord[cont].telefone, clt.telefone);
			strcpy(ord[cont].endereco, clt.endereco);
			strcpy(ord[cont].cpfcnpj, clt.cpfcnpj);
			strcpy(ord[cont].data_compra, clt.data_compra);
			ord[cont].itens_comprados.cod_item = clt.itens_comprados.cod_item;
			strcpy(ord[cont].itens_comprados.descricao_item, clt.itens_comprados.descricao_item);		 
			cont++;
		}
	
		fflush(stdin);
	  	printf("\n Digite o nome do cadastro que deseja alterar: ");
	  	gets(nome);
	  	strupr(nome);
	  	limitarString(nome, 50);
	  	for(i = 0; i < cont; i++)
	  	{
	  		if(strcmp(nome, ord[i].nome) == 0)
			{
				printf("\n Nome: %s\n", ord[i].nome);
				printf(" Telefone: %s\n", ord[i].telefone);
				printf(" Endereço: %s\n", ord[i].endereco);
				printf(" CPF/CNPJ: %s\n", ord[i].cpfcnpj);
				printf(" Data da última compra: %s\n", ord[i].data_compra);
				printf(" Código do último item comprado: %d - Descrição: %s\n", ord[i].itens_comprados.cod_item, ord[i].itens_comprados.descricao_item);
				printf("--------------------------------------------------------------\n\n");	
				
				int opcao = 0;
			  	printf(" Deseja editar esse registro?\n");
		    	printf("\n 1 - Sim");
		    	printf("\n 2 - Não\n");
			  	printf("\n Digite o número de uma das opções acima: ");
		        scanf("%d", &opcao);
				switch (opcao)
				{
					case 1:
					{
						fflush(stdin);
						printf ("\n Digite o nome: ");
			    		gets(ord[i].nome);
			    		strupr(ord[i].nome);
			    		int j;
			    		for(j = 0; j < cont; j++)
			    		{
							if(strcmp(ord[j].nome, ord[i].nome) == 0 && j != i)
							{
								existe++;
							}
						}
						if(existe > 0)
						{
							printf ("\n [ERRO]: Este nome já existe na base de dados!");
							fclose(temp);
				  			fclose(arquivo);
				  			remove("tmp.txt");		
							getch();
							return 0;
						} 		
			    		do
			    		{
				    		fflush(stdin);
				    		printf (" Digite o telefone (somente números): ");
				    		gets(ord[i].telefone);
			    		}
			    		while(!verificarNumero(ord[i].telefone));
			    		
			    		fflush(stdin);
			    		printf (" Digite o endereço: ");
			    		gets(ord[i].endereco);
			    		strupr(ord[i].endereco);
			    		
			    		do
						{
			    			fflush(stdin);
				    		printf (" Digite o CPF/CNPJ (somente números): ");
				    		gets(ord[i].cpfcnpj);	
						}
			    		while(!verificarNumero(ord[i].cpfcnpj));
			    		
			    		fflush(stdin);
			    		printf (" Cadastro da data de última compra do cliente, \n");
			    		printf (" Digite no formato DD/MM/AAAA: ");
			    		gets(ord[i].data_compra);   
						  
						do
						{
							fflush(stdin);      
				    		printf (" Cadastro de item comprado - Código (0 a 999): ");
							scanf("%d", &ord[i].itens_comprados.cod_item);
						}
						while(ord[i].itens_comprados.cod_item > 999 || ord[i].itens_comprados.cod_item < 0);			
						
						fflush(stdin);
			    		printf (" Cadastro de item comprado - Descrição: ");
			    		gets(ord[i].itens_comprados.descricao_item);
			    		strupr(ord[i].itens_comprados.descricao_item);
						
						if((strlen(ord[i].nome)==0) || (strcmp(ord[i].nome,"0")==0) || (strlen(ord[i].telefone)==0) || (strcmp(ord[i].telefone,"0")==0) || (strlen(ord[i].endereco)==0) || (strcmp(ord[i].endereco,"0")==0)
						|| (strlen(ord[i].cpfcnpj)==0) || (strcmp(ord[i].cpfcnpj,"0")==0) || (strlen(ord[i].data_compra)==0) || (strcmp(ord[i].data_compra,"0")==0) || (strlen(ord[i].itens_comprados.descricao_item)==0)
						|| (strcmp(ord[i].itens_comprados.descricao_item,"0")==0))
						{
							printf ("\n [ERRO]: Nenhum registro pode ser nulo!");
							fclose(temp);
				  			fclose(arquivo);
				  			remove("tmp.txt");
							getch();
							return 0;
						}
						break;
					}
					case 2:
					{
						fclose(temp);
			  			fclose(arquivo);
			  			remove("tmp.txt");
			  			return 0;
					}
					default: printf("\n [ERRO]: Opção não reconhecida pelo sistema!");
				}			
				achou++;			
			}
					
		}
		if(achou == 0)
		{
			printf("\n [ERRO]: Não existe um cadastro com esse nome.\n");
			fclose(temp);
		  	fclose(arquivo);
		  	remove("tmp.txt");
	  		getch();
	  		return 0;
		}
		//SALVAR
		for(i = 0; i < cont; i++)
		{
			fwrite(&ord[i], sizeof(CLIENTE), 1, temp);
		}
		fclose(temp);
	  	fclose(arquivo);	
	   	if(remove("clientes.txt") == 0 && rename("tmp.txt","clientes.txt") == 0)
	    {
	    	printf("\n Alteração realizada com sucesso!");
	   	}
		else
		{
	    	remove("tmp.txt");
	    }
    }
  	fclose(temp);
  	fclose(arquivo);
  	getch();
  	return 1;
}
//EXCLUIR
int fexcluir(void)
{
	int achou = 0;
	FILE* arquivo;
	FILE* temp;
	CLIENTE clt;
	char nome[50];
	arquivo = fopen("clientes.txt","rb");
	temp = fopen("tmp.txt","wb");
	if(arquivo == NULL || temp == NULL)
	{
  		printf("\n [ERRO]: O arquivo não pode ser aberto!\n");
  		getch();
	}
	else
	{
  		fflush(stdin);
  		printf(" Digite o nome a deletar: ");
  		gets(nome);
  		strupr(nome);
  		limitarString(nome, 50);
  		while(fread(&clt, sizeof(CLIENTE), 1, arquivo) == 1)
		{
   			if(strcmp(nome, clt.nome) == 0)
			{
    			printf("\n Nome: %s\n", clt.nome);
				printf(" Telefone: %s\n", clt.telefone);
				printf(" Endereço: %s\n", clt.endereco);
				printf(" CPF/CNPJ: %s\n", clt.cpfcnpj);
				printf(" Data da última compra: %s\n", clt.data_compra);
				printf(" Código do último item comprado: %d - Descrição: %s\n", clt.itens_comprados.cod_item, clt.itens_comprados.descricao_item);
				printf("--------------------------------------------------------------\n");
				achou++;
	   		}
			else
			{
	    		fwrite(&clt, sizeof(CLIENTE), 1, temp);//Grava os dados no arquivo temporário
	  		}
  		}
  		if(achou == 0)
		{
			printf("\n [ERRO]: Não existe um cadastro com esse nome.\n");
			fclose(temp);
	  		fclose(arquivo);
	  		remove("tmp.txt");
	  		getch();
	  		return 0;
		}
	  	fclose(arquivo);
	  	fclose(temp);
	  	fflush(stdin);
	  	
	  	int opcao = 0;
	  	printf(" Deseja excluir esse registro?\n");
    	printf("\n 1 - Sim");
    	printf("\n 2 - Não\n");
	  	printf("\n Digite o número de uma das opções acima: ");
        scanf("%d", &opcao);
		switch (opcao)
		{
			case 1:
			{
				if(remove("clientes.txt") == 0 && rename("tmp.txt","clientes.txt") == 0)
			    {
			    	printf("\n Registro excluído com sucesso!");
			   	}
				else
				{
			    	remove("tmp.txt");
			    }
				break;
			}
			case 2:
			{
				break;
			}
			default: printf("\n [ERRO]: Opção não reconhecida pelo sistema!");
		}
	  	fclose(temp);
	  	fclose(arquivo);
	  	getch();
 	} 
}
//LISTAR
void flistar(void)
{
	int cont = 0;
    FILE* arquivo;
	CLIENTE clt;
	arquivo = fopen("clientes.txt", "rb");
	if(arquivo == NULL)
	{
		printf("\n [ERRO]: O arquivo não pode ser aberto!");
		getch();
	}
	else
	{
		while(fread(&clt, sizeof(CLIENTE), 1, arquivo) == 1)
		{
			printf("\n Nome: %s\n", clt.nome);
			printf(" Telefone: %s\n", clt.telefone);
			printf(" Endereço: %s\n", clt.endereco);
			printf(" CPF/CNPJ: %s\n", clt.cpfcnpj);
			printf(" Data da última compra: %s\n", clt.data_compra);
			printf(" Código do último item comprado: %d - Descrição: %s\n", clt.itens_comprados.cod_item, clt.itens_comprados.descricao_item);
			printf("--------------------------------------------------------------\n");
			cont++;
		}
		if(cont > 0)
		{
			printf("\n O sistema possui %d registros.\n", cont);
		}
		else
		{
			printf("\n O sistema não possui registros.\n", cont);
		}
	}
	getch();
	fclose(arquivo);
}
//ORDENAR
int fordenar(void)
{
	int cont = 0;
    FILE* arquivo;
    FILE* temp;
	CLIENTE clt;
	CLIENTE ord[100];
	arquivo = fopen("clientes.txt", "rb");
	temp = fopen("tmp.txt","wb");
	if(arquivo == NULL || temp == NULL)
	{
		printf("\n [ERRO]: O arquivo não pode ser aberto!");
		getch();
	}
	else
	{
		while(fread(&clt, sizeof(CLIENTE), 1, arquivo) == 1)
		{
			strcpy(ord[cont].nome, clt.nome);
			strcpy(ord[cont].telefone, clt.telefone);
			strcpy(ord[cont].endereco, clt.endereco);
			strcpy(ord[cont].cpfcnpj, clt.cpfcnpj);
			strcpy(ord[cont].data_compra, clt.data_compra);
			ord[cont].itens_comprados.cod_item = clt.itens_comprados.cod_item;
			strcpy(ord[cont].itens_comprados.descricao_item, clt.itens_comprados.descricao_item);		 
			cont++;
		}
	
		if(cont == 0)
		{
			printf("\n [ERRO]: O sistema não possui registros.\n", cont);
			fclose(temp);
	  		fclose(arquivo);
			remove("tmp.txt");
			getch();
			return 0;
		}		
		//Ordenação
		int i, j;
		CLIENTE aux;
		for(i = 1; i < cont; i++)
		{
			aux = ord[i];
			for(j=i; (j>0) && (strcmp(aux.nome,ord[j-1].nome) < 0);j--)
				ord[j] = ord[j-1];
			ord[j] = aux;
		}
		//--------------------------------------------------------------
		for(i = 0; i < cont; i++)
		{
			fwrite(&ord[i], sizeof(CLIENTE), 1, temp);
		}
		fclose(temp);
	  	fclose(arquivo);	
	   	if(remove("clientes.txt") == 0 && rename("tmp.txt","clientes.txt") == 0)
	    {
	    	printf("\n Ordenação realizada com sucesso!");
	   	}
		else
		{
	    	remove("tmp.txt");
	    }
    }
  	fclose(temp);
  	fclose(arquivo);
  	getch();
}

//Menu Principal
void fsistema()
{
	int sair = 0, esc = 0, opcao = 0;
	do
	{
		system("cls");
		fcreditos();
     	printf("\n\n Escolha uma Opção:\n");
    	printf("\n 1 - Incluir");
    	printf("\n 2 - Pesquisar");
    	printf("\n 3 - Alterar");
    	printf("\n 4 - Excluir");
    	printf("\n 5 - Listar");
    	printf("\n 6 - Ordenar por ordem alfabética");
    	printf("\n 7 - Sair\n");
    	do
    	{
    		printf("\n Digite o número de uma das opções acima: ");
        	fflush(stdin);
        	scanf("%d", &opcao);
			switch (opcao)
    		{
    			case 1:
    			{
    				fincluir();
					break;
				}
				case 2:
				{
					fpesquisar();
					break;
				}
				case 3:
				{
					falterar();
					break;
				}
				case 4:
				{
					fexcluir();
					break;
				}
				case 5:
				{
					flistar();
					break;
				}
				case 6:
				{
					fordenar();
					break;
				}
				case 7:
				{
					sair = 1;
					exit(1);
					break;
				}
				default:
				{
					printf("\n [ERRO]: Opção não reconhecida pelo sistema!");
					getch();
					break;
				}					
			}
		}   	
		while(opcao < 1 && opcao > 7);
	}
	while(sair != 1);
}
//Verificar se a string é numérica
int verificarNumero(const char* str)
{
    char *stop = 0;
    strtoul (str, &stop, 10); 
    return (stop - str == strlen (str));
}
//Limita o tamanho da String
int limitarString(char* entrada, int qtd)
{
	int i = strlen(entrada);	
	if(i > qtd)// Limite do tamanho do nome do jogador
	{
		while(i != qtd)
		{
			entrada[i] = 0;
			i--;
		}
		entrada[qtd] = '\0';
	}
	return 1;
}
//Função que apresenta a tela inicial
void ftelainicial()
{
	printf("\t-----------------------------------------------------");
	printf("\n\t¦                   S I S T E M A                   ¦");
	printf("\n\t¦                        D E                        ¦");
	printf("\n\t¦                  C A D A S T R O                  ¦");
	printf("\n\t¦                        D E                        ¦");
	printf("\n\t¦                  C L I E N T E S                  ¦");
	printf("\n\t¦                                                   ¦");
    printf("\n\t¦ Desenvolvido por: Patrick Waldera                 ¦");
	printf("\n\t-----------------------------------------------------\n\n");
}
//Função que apresenta créditos do programa
void fcreditos()
{
	printf("FACULDADES INTEGRADAS CAMÕES - CADASTRO CLIENTE\t|\tALUNO: PATRICK WALDERA\t|\tANO:2020");
}


