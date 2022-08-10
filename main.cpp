#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

using std::string;

typedef struct genero
{
    int codigo;
    char nome[80];
    bool ativo;
} Genero;

typedef struct cliente
{
    int codcliente;
    char nome[80];
    char rg[8];
    char cpf[11];
    char email[50];
    char cel[11];
    char endereco[50];
    char datanasc[10];
    bool ativo;
} Cliente;

typedef struct filme
{
    int codigo;
    char nome[30];
    int codgenero;
    int ano;
    int classificacao;
    float valor;
    bool ativo;
} Filme;

typedef struct funcionario
{
    int codfunc;
    char nome[80];
    char datanasc[10];
    char rg[8];
    char cpf[11];
    char cel[11];
    char email[50];
    char dataadm[10];
    bool ativo;
} Funcionario;

typedef struct locacao
{
    int codlocacao;
    char dataloca[10];
    char datadevo[10];
    float valortotal;
    float juro;
    float desc;
    int codcliente;
    int codfunc;
    char pagamento[1];
    bool ativo;
} Locacao;

//genero
void cadastraGenero(int &codGenero){
    FILE *tGenero;
    tGenero = fopen("tGenero.txt", "a+");

    if (tGenero != NULL)
    {
        Genero tempGen;
        codGenero++;
        tempGen.codigo = codGenero;
        tempGen.ativo = true;

        printf("Digite o nome do Genero: ");
        scanf("%[^\n]", &tempGen.nome);
        fflush(stdin);

        fwrite(&tempGen, sizeof(Genero), 1, tGenero);

        fclose(tGenero);
    }
}
void contGenero(int &codGenero){
    FILE *tGenero;
    Genero temp;
    int cont = 0;
    tGenero = fopen("tGenero.txt", "a+");

    if (tGenero != NULL)
    {
        while (fread(&temp, sizeof(Genero), 1, tGenero))
        {
            cont++;
        }
        codGenero = cont;     
        fclose(tGenero);
    }
}
void listarGenero(int &codGenero, HANDLE hConsole){
    
    FILE *tGenero;
    Genero temp;
    int cont = 0;
    int contTotal = 0;
    tGenero = fopen("tGenero.txt", "a+");

    if (tGenero != NULL)
    {
        while (fread(&temp, sizeof(Genero), 1, tGenero))
        {
            std::cout<<temp.ativo<<"-"<<temp.codigo<<"\n";
            if (temp.ativo == true)
            {
                (cont % 2 == 0) ? SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE):  SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);//alterna cor console
                
                printf("%d - %s \n", temp.codigo, temp.nome);
                fflush(stdin);

                cont++;
            }
            contTotal++;
        }
        codGenero = contTotal;     
        fclose(tGenero);
    }
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);
}
void deletaGenero(){//verificar se alum filme esta cadastrado com esse genero
    FILE *tGenero;
    Genero temp;
    int cont = 0;
    int cod;
    tGenero = fopen("tGenero.txt", "r+");
    if (tGenero != NULL)
    {
        while (fread(&temp, sizeof(Genero), 1, tGenero))
        {
            cont++;
        }
        fclose(tGenero);
    }
    if (cont == 0)
    {
        printf("Não há Generos cadastrados!\n");
    }
    else
    {
    	
    	if(){
    		printf("Digite o codigo do Genero que deseja deletar: ");
	        scanf("%d", &cod);
	        
			
				
	        fflush(stdin);
	        tGenero = fopen("tGenero.txt", "r+");
	        if (tGenero != NULL)
	        {
	            while (fread(&temp, sizeof(Genero), 1, tGenero))
	            {
	                if (temp.codigo == cod)
	                {
	                	cod--;
	                    temp.ativo = false;
						fseek(tGenero, cod*sizeof(Genero), SEEK_SET);
						
	                    fwrite(&temp, sizeof(Genero), 1, tGenero);
	                    fclose(tGenero);
	                    printf("Genero deletado com sucesso!\n");
	                    break;
	                }
	            }
	        }
		}else{
			
		}
        
    }
}
//cliente
void cadastraCliente(int &codCliente){
    FILE *tCliente;
    tCliente = fopen("tCliente.txt", "a+");

    if (tCliente != NULL)
    {
        Cliente tempCli;
        codCliente++;
        tempCli.codcliente = codCliente;
        tempCli.ativo = true;

        printf("Digite o nome do Cliente: ");
        scanf("%[^\n]", &tempCli.nome);
        fflush(stdin);
        
        printf("Digite o RG do Cliente: ");
        scanf("%[^\n]", &tempCli.rg);
        fflush(stdin);
        
        printf("Digite o CPF do Cliente: ");
        scanf("%[^\n]", &tempCli.cpf);
        fflush(stdin);
        
        printf("Digite o E-Mail do Cliente: ");
        scanf("%[^\n]", &tempCli.email);
        fflush(stdin);
        
        printf("Digite o celular do Cliente: ");
        scanf("%[^\n]", &tempCli.cel);
        fflush(stdin);
        
        printf("Digite o endereco do Cliente: ");
        scanf("%[^\n]", &tempCli.endereco);
        fflush(stdin);
        
        printf("Digite a data de nascimento do Cliente: ");
        scanf("%[^\n]", &tempCli.datanasc);
        fflush(stdin);
        

        fwrite(&tempCli, sizeof(Cliente), 1, tCliente);

        fclose(tCliente);
    }
}
void contCliente(int &codCliente){
    FILE *tCliente;
    Cliente temp;
    int cont = 0;
    tCliente = fopen("tCliente.txt", "a+");

    if (tCliente != NULL)
    {
        while (fread(&temp, sizeof(Cliente), 1, tCliente))
        {
            cont++;
        }
        codCliente = cont;     
        fclose(tCliente);
    }
}
void listarCliente(int &codCliente, HANDLE hConsole){
    
    FILE *tCliente;
    Cliente temp;
    int cont = 0;
    int contTotal = 0;
    tCliente = fopen("tCliente.txt", "a+");

    if (tCliente != NULL)
    {
        while (fread(&temp, sizeof(Cliente), 1, tCliente))
        {
            std::cout<<temp.ativo<<"-"<<temp.codcliente<<"\n";
            if (temp.ativo == true)
            {
                (cont % 2 == 0) ? SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE):  SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);//alterna cor console
                
                printf("Codigo: %d\nNome: %s\nRG: %s\nCPF: %s\nE-Mail: %s\nCelular: %s\nEndereco: %s\nData nascimento: %s\n", temp.codcliente, temp.nome, temp.rg, temp.cpf, temp.email, temp.cel, temp.endereco, temp.datanasc);
                fflush(stdin);

                cont++;
            }
            contTotal++;
        }
        codCliente = contTotal;     
        fclose(tCliente);
    }
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);
}

//filme
void cadastraFilme(int &codFilme, int codGenero){
    FILE *tFilme;
    tFilme = fopen("tFilme.txt", "a+");

    if (tFilme != NULL)
    {
        Filme tempFil;
        codFilme++;
        tempFil.codigo = codFilme;
        tempFil.ativo = true;
		
		fflush(stdin);
        printf("Digite o nome do Filme: ");
        scanf("%[^\n]", &tempFil.nome);
        fflush(stdin);
        
        printf("Digite o ano do Filme: ");
        scanf("%d", &tempFil.ano);
        fflush(stdin);
        
        printf("Digite a classificação do Filme: ");
        scanf("%d", &tempFil.classificacao);
        fflush(stdin);
        
        printf("Digite o valor do Filme: ");
        scanf("%f", &tempFil.valor);
        fflush(stdin);
        
		tempFil.codgenero = codGenero;
        fwrite(&tempFil, sizeof(Filme), 1, tFilme);

        fclose(tFilme);
    }
}
void contFilme(int &codFilme){
    FILE *tFilme;
    Filme temp;
    int cont = 0;
    tFilme = fopen("tFilme.txt", "a+");

    if (tFilme != NULL)
    {
        while (fread(&temp, sizeof(Filme), 1, tFilme))
        {
            cont++;
        }
        codFilme = cont;     
        fclose(tFilme);
    }
}
void listarFilme(int &codFilme, HANDLE hConsole){
    
    FILE *tFilme;
    Filme tempFilme;
    int cont = 0;
    int contTotal = 0;
    char nomeFilmeTemp[30];
    tFilme = fopen("tFilme.txt", "a+");

    if (tFilme != NULL)
    {
        while (fread(&tempFilme, sizeof(Filme), 1, tFilme))
        {
            //std::cout<<temp.ativo<<"-"<<temp.codigo<<"\n";
            if (tempFilme.ativo == true)
            {
                (cont % 2 == 0) ? SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE):  SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);//alterna cor console
                
				FILE *tGenero;
			    Genero tempGenero;
			    
			    tGenero = fopen("tGenero.txt", "a+");
			    if (tGenero != NULL)
			    {
			        while (fread(&tempGenero, sizeof(Genero), 1, tGenero))
			        {
			            if (tempGenero.ativo == true)
			            {
			            	if(tempGenero.codigo == tempFilme.codgenero){
			            		strcpy(nomeFilmeTemp, tempGenero.nome);
							}
			            }
			        }   
			        fclose(tGenero);
			    }
			    
                printf("Codigo: %d \nNome: %s \nAno:%d \nPara maiores de: %d \nValor: %f \nGenero: %s\n\n", tempFilme.codigo, tempFilme.nome, tempFilme.ano, tempFilme.classificacao, tempFilme.valor, nomeFilmeTemp);

                cont++;
            }
            contTotal++;
        }
        codFilme = contTotal;     
        fclose(tFilme);
    }
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);
}
void deletaFilme(){//verificar se alum filme esta cadastrado com esse genero
    FILE *tFilme;
    Filme temp;
    int cont = 0;
    int cod;
    tFilme = fopen("tFilme.txt", "r+");
    if (tFilme != NULL)
    {
        while (fread(&temp, sizeof(Filme), 1, tFilme))
        {
            cont++;
        }
        fclose(tFilme);
    }
    if (cont == 0)
    {
        printf("Não há Filmes cadastrados!\n");
    }
    else
    {
        printf("Digite o codigo do Filme que deseja deletar: ");
        scanf("%d", &cod);
        
        fflush(stdin);
        tFilme = fopen("tFilme.txt", "r+");
        if (tFilme != NULL)
        {
            while (fread(&temp, sizeof(Filme), 1, tFilme))
            {
                if (temp.codigo == cod)
                {
                	cod--;
                    temp.ativo = false;
                    fseek(tFilme, cod*sizeof(Filme), SEEK_SET);
                    fwrite(&temp, sizeof(Filme), 1, tFilme);
                    fclose(tFilme);
                    printf("Filme deletado com sucesso!\n");
                    break;
                }
            }
        }
    }
}


int main()
{
    // variaveis controladoras de codigo
    int codGenero = 1;
    int codFilme = 1;
    int codCliente = 1;
    int codFuncionario = 1;
    int codLocacao = 1;

    // Criação e inicialização dos arquivos.
    FILE *tGenero;
    FILE *tFilme;
    FILE *tCliente;
    FILE *tFuncionario;
    FILE *tLocacao;

    //define cor do console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);

    //contabiliza registros ou cria arquivo caso não exista
    contGenero(codGenero);
	contFilme(codFilme);
	contCliente(codCliente);
	
    int menu = 0;
    while (true)
    {
        printf("\n Bem vindo ao menu: ");
        printf("\n 1. Cadastro e Listar Genero ");
		printf("\n 2. Cadastro e Listar Filmes ");
		printf("\n 3. Cadastro e Listar Cliente ");
		printf("\n 4. Cadastro e Listar funcionario ");
		printf("\n 5. Cadastro e Listar Locacao ");
		printf("\n 6. Fazer Devolucao ");
		printf("\n 7. Excluir genero ");
		printf("\n 8. Excluir Filmes ");
		printf("\n 9. Excluir Cliente ");
		printf("\n 10. Excluir Funcionario ");
		printf("\n 11. Excluir Locacao ");
		printf("\n 12. Listar locacao data especifica ");
		printf("\n 13. Listar filmes em atraso ");
		printf("\n 14. Listar devolucao ");
		printf("\n 15. Sair \n");
        std::cin >> menu;
        fflush(stdin);
        
        int verificador;
        
        switch (menu)
        {
        case 1: // Cadastro e Listar Gênero
            system("CLS");
	        printf("1. Cadastrar genero\n");
	        printf("2. Listar genero\n");
	        scanf("%d", &verificador);
	        fflush(stdin);
	        if(verificador == 1){
	        	cadastraGenero(codGenero);
		        fflush(stdin);
		        system("CLS");
			}else{
				system("CLS");
				listarGenero(codGenero, hConsole);
				fflush(stdin);
			}
            break;
        case 2: // Cadastro e Listar Filmes
        	system("CLS");
        	printf("1. Cadastrar Filme\n");
        	printf("2. Listar filmes");
        	scanf("%d", &verificador);
        	
        	if(verificador == 1){
        		int opCadFilme;
	        	listarGenero(codGenero, hConsole);
	        	
	        	fflush(stdin);
	        	printf("Digite o codigo do genero referente ao filme que ira cadastrar: ");
	        	scanf("%d", &opCadFilme);
				cadastraFilme(codFilme,opCadFilme);
			}else{
				listarFilme(codFilme,hConsole);
			}
        	
            break;
        case 3: // Cadastro e Listar Cliente
            system("CLS");
	        printf("1. Cadastrar cliente\n");
	        printf("2. Listar cliente\n");
	        scanf("%d", &verificador);
	        fflush(stdin);
	        if(verificador == 1){
	        	cadastraCliente(codCliente);
		        fflush(stdin);
		        system("CLS");
			}else{
				system("CLS");
				listarCliente(codCliente, hConsole);
				fflush(stdin);
			}
            break;
        case 4: // Cadastro e Listar funcionário
            break;
        case 5: // Cadastro e Listar Locação
            break;
        case 6: // Fazer Devolução
            break;
        case 7: // Excluir gênero
        	deletaGenero();
            break;
        case 8: // Excluir Filmes
        	deletaFilme();
            break;
        case 9: // Excluir Cliente
            break;
        case 10: // Excluir Funcionário
            break;
        case 11: // Excluir Locação
            break;
        case 12: // Listar locação data especifica
            break;
        case 13: // Listar filmes em atraso
            break;
        case 14: // Listar devolução
            break;
        case 15: // Sair
            break;
        }
    }
}

