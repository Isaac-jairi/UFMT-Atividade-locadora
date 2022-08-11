#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <locale.h>

using std::string;

typedef struct genero
{
    int codigo;
    char nome[80];
    bool ativo;
} Genero;

typedef struct cliente
{
    int codigo;
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
    int codigo;
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
    int codigo;
    char dataloca[9];
    char datadevo[9];
    float valortotal;
    float juro;
    float desc;
    int codcliente;
    int codfunc;
    int pagamento;//1-a vista 2- a prazo
    bool ativo;
    bool pago;
} Locacao;

typedef struct locacaoTemFilmes
{
    int codigo;
	int codFilme;
	int codLocacao;
    bool ativo;

}LocacaoTemFilmes;

typedef struct devolucao
{
	int codigo;
	int codLocacao;
	char dataloca[9];
	char datadevo[9];
	float valororiginal;
	float valorpago;
	int diasatraso;
    bool ativo;
}Devolucao;

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
        printf("N�o h� Generos cadastrados!\n");
    }
    else
    {
    	printf("Digite o codigo do Genero que deseja deletar: ");
	    scanf("%d", &cod);	
	    fflush(stdin);
	    
    	FILE *tFilme;
	    Filme tempFilme;
	    int contFK = 0;
	    tFilme = fopen("tFilme.txt", "a+");
	
	    if (tFilme != NULL)
	    {
	        while (fread(&tempFilme, sizeof(Filme), 1, tFilme))
	        {
	            if(tempFilme.codgenero == cod)
					contFK++;
	        } 
	    }
	    fclose(tFilme);
	    
    	if(contFK == 0 ){
    		
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
			printf("N�o foi possivel deletar pois algum filme esta usando esse g�nero!\n");
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
        tempCli.codigo = codCliente;
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
            std::cout<<temp.ativo<<"-"<<temp.codigo<<"\n";
            if (temp.ativo == true)
            {
                (cont % 2 == 0) ? SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE):  SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);//alterna cor console
                
                printf("Codigo: %d\nNome: %s\nRG: %s\nCPF: %s\nE-Mail: %s\nCelular: %s\nEndereco: %s\nData nascimento: %s\n", temp.codigo, temp.nome, temp.rg, temp.cpf, temp.email, temp.cel, temp.endereco, temp.datanasc);
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
void deletaCliente(){//verificar se alum filme esta cadastrado com esse genero
    FILE *tCliente;
    Cliente temp;
    int cont = 0;
    int cod;
    tCliente = fopen("tCliente.txt", "r+");
    if (tCliente != NULL)
    {
        while (fread(&temp, sizeof(Cliente), 1, tCliente))
        {
            cont++;
        }
        fclose(tCliente);
    }
    if (cont == 0)
    {
        printf("Não há Cliente cadastrados!\n");
    }
    else
    {
    	printf("Digite o codigo do Cliente que deseja deletar: ");
	    scanf("%d", &cod);	
	    fflush(stdin);
	    
    	FILE *tLocacao;
	    Locacao tempLocacao;
	    int contFK = 0;
	    tLocacao = fopen("tLocacao.txt", "a+");
	
	    if (tLocacao != NULL)
	    {
	        while (fread(&tempLocacao, sizeof(Locacao), 1, tLocacao))
	        {
	            if(tempLocacao.codcliente == cod)
					contFK++;
	        } 
	    }
	    fclose(tLocacao);
	    
    	if(contFK == 0 ){
    		
	        tCliente = fopen("tCliente.txt", "r+");
	        if (tCliente != NULL)
	        {
	            while (fread(&temp, sizeof(Cliente), 1, tCliente))
	            {
	                if (temp.codigo == cod)
	                {
	                	cod--;
	                    temp.ativo = false;
						fseek(tCliente, cod*sizeof(Cliente), SEEK_SET);
						
	                    fwrite(&temp, sizeof(Cliente), 1, tCliente);
	                    fclose(tCliente);
	                    printf("Cliente deletado com sucesso!\n");
	                    break;
	                }
	            }
	        }
		}else{
			printf("Não foi possivel deletar pois esse cliente esta locando um filme!\n");
		}
        
    }
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
        
        printf("Digite a classifica��o do Filme: ");
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
        printf("Nao ha Filmes cadastrados!\n");
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

//Funcionario
void cadastraFuncionario(int &codFuncionario){
    FILE *tFuncionario;
    tFuncionario = fopen("tFuncionario.txt", "a+");

    if (tFuncionario != NULL)
    {
        Funcionario tempFun;
        codFuncionario++;
        tempFun.codigo = codFuncionario;
        tempFun.ativo = true;

        printf("Digite o nome do Funcionario: ");
        scanf("%[^\n]", &tempFun.nome);
        fflush(stdin);
        
        printf("Digite a data de nascimento do Funcionario: ");
        scanf("%[^\n]", &tempFun.datanasc);
        fflush(stdin);
        
        printf("Digite o RG do Funcionario: ");
        scanf("%[^\n]", &tempFun.rg);
        fflush(stdin);
        
        printf("Digite o CPF do Funcionario: ");
        scanf("%[^\n]", &tempFun.cpf);
        fflush(stdin);
        
        printf("Digite o celular do Funcionario: ");
        scanf("%[^\n]", &tempFun.cel);
        fflush(stdin);
        
        printf("Digite o E-Mail do Funcionario: ");
        scanf("%[^\n]", &tempFun.email);
        fflush(stdin);
        
        printf("Digite a data de admissao do Funcionario: ");
        scanf("%[^\n]", &tempFun.dataadm);
        fflush(stdin);
        

        fwrite(&tempFun, sizeof(Funcionario), 1, tFuncionario);

        fclose(tFuncionario);
    }
}
void contFuncionario(int &codFuncionario){
    FILE *tFuncionario;
    Funcionario temp;
    int cont = 0;
    tFuncionario = fopen("tFuncionario.txt", "a+");

    if (tFuncionario != NULL)
    {
        while (fread(&temp, sizeof(Funcionario), 1, tFuncionario))
        {
            cont++;
        }
        codFuncionario = cont;     
        fclose(tFuncionario);
    }
}
void listarFuncionario(int &codFuncionario, HANDLE hConsole){
    
    FILE *tFuncionario;
    Funcionario temp;
    int cont = 0;
    int contTotal = 0;
    tFuncionario = fopen("tFuncionario.txt", "a+");

    if (tFuncionario != NULL)
    {
        while (fread(&temp, sizeof(Funcionario), 1, tFuncionario))
        {
            std::cout<<temp.ativo<<"-"<<temp.codigo<<"\n";
            if (temp.ativo == true)
            {
                (cont % 2 == 0) ? SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE):  SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);//alterna cor console
                
                printf("Codigo: %d\nNome: %s\nData de nascimento: %s\nRG: %s\nCPF: %s\nCelular: %s\nE-Mail: %s\nData de admissao: %s\n", temp.codigo, temp.nome, temp.datanasc, temp.rg, temp.cpf, temp.cel, temp.email, temp.dataadm);
                fflush(stdin);

                cont++;
            }
            contTotal++;
        }
        codFuncionario = contTotal;     
        fclose(tFuncionario);
    }
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);
}
void deletaFuncionario(){//verificar se alum filme esta cadastrado com esse genero
    FILE *tFuncionario;
    Funcionario temp;
    int cont = 0;
    int cod;
    tFuncionario = fopen("tFuncionario.txt", "r+");
    if (tFuncionario != NULL)
    {
        while (fread(&temp, sizeof(Funcionario), 1, tFuncionario))
        {
            cont++;
        }
        fclose(tFuncionario);
    }
    if (cont == 0)
    {
        printf("Não há Funcionarios cadastrados!\n");
    }
    else
    {
        printf("Digite o codigo do Funcionario que deseja deletar: ");
        scanf("%d", &cod);
       
        fflush(stdin);
        tFuncionario = fopen("tFuncionario.txt", "r+");
        if (tFuncionario != NULL)
        {
            while (fread(&temp, sizeof(Funcionario), 1, tFuncionario))
            {
                if (temp.codigo == cod)
                {
                    cod--;
                    temp.ativo = false;
                    fseek(tFuncionario, cod*sizeof(Funcionario), SEEK_SET);

                    fwrite(&temp, sizeof(Funcionario), 1, tFuncionario);
                    fclose(tFuncionario);
                    printf("Funcionario deletado com sucesso!\n");
                    break;
                }
            }
        }
    }
}

//locacao
void cadastraLocacao(int &codlocacaoTemFilmes, int &codLocacao, int codfunc, int codcliente, int &codFilme, HANDLE hConsole){
    FILE *tLocacao;
    tLocacao = fopen("tLocacao.txt", "a+");

    float valorTotal;
    if (tLocacao != NULL)
    {
        Locacao tempLoc;
        codLocacao++;
        tempLoc.codigo = codLocacao;
        tempLoc.ativo = true;

        tempLoc.codcliente = codcliente;
        tempLoc.codfunc = codfunc;

        printf("Digite o numero referente ao tipo de pagamento: \n1-A vista \n2-A prazo");
        scanf("%d", &tempLoc.pagamento);
        fflush(stdin);

        int menufilmes = 0;
        int qtdFilmes = 0;
        do
        {
            qtdFilmes++;

            printf("Digite 1 para adicionar um filme a locacao ou 0 para sair: ");
            scanf("%d", &menufilmes);
            fflush(stdin);
            if (menufilmes == 1 )
            {
                int codAddFilme = 0;
                listarFilme(codFilme, hConsole);

                printf("Digite o codigo do filme que deseja adicionar: ");
                scanf("%d", &codAddFilme);
                fflush(stdin);

                FILE *tFilme;

                Filme temp;
                tFilme = fopen("tFilme.txt", "a+");

                if (tFilme != NULL)
                {
                    while (fread(&temp, sizeof(Filme), 1, tFilme))
                    {
                        if (temp.ativo == true)
                        {
                            if (temp.codigo == codFilme)
                            {
                                valorTotal += temp.valor;
                                
                            }
                        }
                    }   
                }

                FILE *tlocacaoTemFilmes;
                tlocacaoTemFilmes = fopen("tlocacaoTemFilmes.txt", "a+");

                if (tlocacaoTemFilmes != NULL)
                {
                    locacaoTemFilmes tempFilme;
                    codlocacaoTemFilmes++;
                    tempFilme.codigo = codlocacaoTemFilmes;
                    tempFilme.ativo = true;

                    tempFilme.codLocacao = tempLoc.codigo;
                    tempFilme.codFilme = codAddFilme;
                    fwrite(&tempFilme, sizeof(locacaoTemFilmes), 1, tlocacaoTemFilmes);

                    fclose(tlocacaoTemFilmes);
                }
            }
            
        } while (menufilmes != 0);
        
        int qtdDiasDevolucao = qtdFilmes > 3 ? 4 : 3;

        char diaChar[2];

        _strdate(tempLoc.dataloca);
        
        int dia;
        char c[3];
        c[0]=tempLoc.dataloca[0];
        c[1]=tempLoc.dataloca[1];
        dia=atoi(c) + qtdDiasDevolucao;

        sprintf(diaChar, "%d", dia);

        strcpy(tempLoc.datadevo, tempLoc.dataloca);
        
        tempLoc.datadevo[0]=diaChar[0];
        tempLoc.datadevo[1]=diaChar[1];


        tempLoc.valortotal = valorTotal;

        tempLoc.juro = valorTotal;

        tempLoc.desc = valorTotal - (valorTotal * 0.05);


        fwrite(&tempLoc, sizeof(Locacao), 1, tLocacao);
        system("cls");
        printf("Locacao cadastrada com sucesso!\n");
        fclose(tLocacao);
    }
}
void contLocacao(int &codLocacao){
    FILE *tLocacao;
    Locacao temp;
    int cont = 0;
    tLocacao = fopen("tLocacao.txt", "a+");

    if (tLocacao != NULL)
    {
        while (fread(&temp, sizeof(Locacao), 1, tLocacao))
        {
            cont++;
        }
        codLocacao = cont;     
        fclose(tLocacao);
    }
}

void deletaLocacao(){//verificar se alum Locacao esta cadastrado com esse genero
    FILE *tLocacao;
    Locacao temp;
    int cont = 0;
    int cod;
    tLocacao = fopen("tLocacao.txt", "r+");
    if (tLocacao != NULL)
    {
        while (fread(&temp, sizeof(Locacao), 1, tLocacao))
        {
            cont++;
        }
        fclose(tLocacao);
    }
    if (cont == 0)
    {
        printf("Nao ha Locacoes cadastrados!\n");
    }
    else
    {
        printf("Digite o codigo da Locacao que deseja deletar: ");
        scanf("%d", &cod);
        
        fflush(stdin);
        tLocacao = fopen("tLocacao.txt", "r+");
        if (tLocacao != NULL)
        {
            while (fread(&temp, sizeof(Locacao), 1, tLocacao))
            {
                if (temp.codigo == cod)
                {
                	cod--;
                    temp.ativo = false;
                    fseek(tLocacao, cod*sizeof(Locacao), SEEK_SET);
                    fwrite(&temp, sizeof(Locacao), 1, tLocacao);
                    fclose(tLocacao);
                    printf("Locacao deletada com sucesso!\n");
                    break;
                }
            }
        }
    }
}

void listarLocacao(int &codLocacao, HANDLE hConsole){
    FILE *tLocacao;
    Locacao tempLocacao;
    int cont = 0;
    int contTotal = 0;
    char nomeClienteTemp[80];
    char nomeFuncionarioTemp[80];
    tLocacao = fopen("tLocacao.txt", "a+");

    if (tLocacao != NULL)
    {
        while (fread(&tempLocacao, sizeof(Locacao), 1, tLocacao))
        {
            std::cout<<tempLocacao.ativo<<"-"<<tempLocacao.codigo<<"\n";
            if (tempLocacao.ativo == true)
            {
                (cont % 2 == 0) ? SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE):  SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);//alterna cor console
                
				FILE *tCliente;
			    Cliente tempCliente;
			    
			    tCliente = fopen("tCliente.txt", "a+");
			    if (tCliente != NULL)
			    {
			        while (fread(&tempCliente, sizeof(Cliente), 1, tCliente))
			        {
			            if (tempCliente.ativo == true)
			            {
			            	if(tempCliente.codigo == tempLocacao.codcliente){
			            		strcpy(nomeClienteTemp, tempCliente.nome);
							}
			            }
			        }   
			    }
			    fclose(tCliente);

				FILE *tFuncionario;
			    Funcionario tempFuncionario;
                
			    tFuncionario = fopen("tFuncionario.txt", "a+");
			    if (tFuncionario != NULL)
			    {
			        while (fread(&tempFuncionario, sizeof(Funcionario), 1, tFuncionario))
			        {
			            if (tempFuncionario.ativo == true)
			            {
			            	if(tempFuncionario.codigo == tempLocacao.codfunc){
			            		strcpy(nomeFuncionarioTemp, tempFuncionario.nome);
							}
			            }
			        }   
			    }
			    fclose(tFuncionario);
			    
                printf("Codigo: %d \nData de devolucao: %s \nData de locacao:%s \nNome do cliente: %s \nNome do funcionario: %s \nTipo de pagamento: %s\nValor total: %f \n  \n", tempLocacao.codigo, tempLocacao.datadevo, tempLocacao.dataloca, nomeClienteTemp, nomeFuncionarioTemp, tempLocacao.pagamento == 1 ? "A vista" : "A prazo", tempLocacao.valortotal);

                cont++;
            }
            contTotal++;
        }
        codLocacao = contTotal;     
    }
    fclose(tLocacao);
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);
}
void listarLocacaoEmAtraso(int &codLocacao, HANDLE hConsole){
    FILE *tLocacao;
    Locacao tempLocacao;
    int cont = 0;
    int contTotal = 0;
    char nomeClienteTemp[80];
    char nomeFuncionarioTemp[80];
    tLocacao = fopen("tLocacao.txt", "a+");

    char dataConsulta[9];
    printf("Informe a data Para verificacao XX/XX/XX: ");
    scanf("%s", dataConsulta);
    fflush(stdin);

    int diaPesquisa, dia;
    char c[3];
    c[0]=dataConsulta[0];
    c[1]=dataConsulta[1];
    diaPesquisa=atoi(c);

    if (tLocacao != NULL)
    {
        while (fread(&tempLocacao, sizeof(Locacao), 1, tLocacao))
        {
            c[0]=tempLocacao.datadevo[0];
            c[1]=tempLocacao.datadevo[1];
            dia=atoi(c);

            if(dia>diaPesquisa){
                std::cout<<tempLocacao.ativo<<"-"<<tempLocacao.codigo<<"\n";
                if (tempLocacao.ativo == true)
                {
                    (cont % 2 == 0) ? SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE):  SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);//alterna cor console
                    
                    FILE *tCliente;
                    Cliente tempCliente;
                    
                    tCliente = fopen("tCliente.txt", "a+");
                    if (tCliente != NULL)
                    {
                        while (fread(&tempCliente, sizeof(Cliente), 1, tCliente))
                        {
                            if (tempCliente.ativo == true)
                            {
                                if(tempCliente.codigo == tempLocacao.codcliente){
                                    strcpy(nomeClienteTemp, tempCliente.nome);
                                }
                            }
                        }   
                    }
                    fclose(tCliente);

                    FILE *tFuncionario;
                    Funcionario tempFuncionario;
                    
                    tFuncionario = fopen("tFuncionario.txt", "a+");
                    if (tFuncionario != NULL)
                    {
                        while (fread(&tempFuncionario, sizeof(Funcionario), 1, tFuncionario))
                        {
                            if (tempFuncionario.ativo == true)
                            {
                                if(tempFuncionario.codigo == tempLocacao.codfunc){
                                    strcpy(nomeFuncionarioTemp, tempFuncionario.nome);
                                }
                            }
                        }   
                    }
                    fclose(tFuncionario);
                    
                    printf("Codigo: %d \nData de devolucao: %s \nData de locacao:%s \nNome do cliente: %s \nNome do funcionario: %s \nTipo de pagamento: %s\nValor total: %f \n  \n", tempLocacao.codigo, tempLocacao.datadevo, tempLocacao.dataloca, nomeClienteTemp, nomeFuncionarioTemp, tempLocacao.pagamento == 1 ? "A vista" : "A prazo", tempLocacao.valortotal);

                    cont++;
                }
            }
            contTotal++;
        }
        codLocacao = contTotal;     
    }
    fclose(tLocacao);
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);
}

void listarLocacaoEspecifica(int &codLocacao, HANDLE hConsole){
    FILE *tLocacao;
    Locacao tempLocacao;
    int cont = 0;
    int contTotal = 0;
    char nomeClienteTemp[80];
    char nomeFuncionarioTemp[80];
    tLocacao = fopen("tLocacao.txt", "a+");

    char datalocacaoConsulta[9];
    printf("Informe a data de locação XX/XX/XX: ");
    scanf("%s", datalocacaoConsulta);
    fflush(stdin);

    int diaPesquisa, dia;
    char c[3];
    c[0]=datalocacaoConsulta[0];
    c[1]=datalocacaoConsulta[1];
    diaPesquisa=atoi(c);

    if (tLocacao != NULL)
    {
        while (fread(&tempLocacao, sizeof(Locacao), 1, tLocacao))
        {
            c[0]=tempLocacao.dataloca[0];
            c[1]=tempLocacao.dataloca[1];
            dia=atoi(c);
            if (tempLocacao.ativo == true)
            {
                //std::cout<<tempLocacao.ativo<<"-"<<tempLocacao.codigo<<"\n";
                if(diaPesquisa == dia){
                    (cont % 2 == 0) ? SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE):  SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);//alterna cor console
                    
                    FILE *tCliente;
                    Cliente tempCliente;
                    
                    tCliente = fopen("tCliente.txt", "a+");
                    if (tCliente != NULL)
                    {
                        while (fread(&tempCliente, sizeof(Cliente), 1, tCliente))
                        {
                            if (tempCliente.ativo == true)
                            {
                                if(tempCliente.codigo == tempLocacao.codcliente){
                                    strcpy(nomeClienteTemp, tempCliente.nome);
                                }
                            }
                        }   
                    }
                    fclose(tCliente);

                    FILE *tFuncionario;
                    Funcionario tempFuncionario;
                    
                    tFuncionario = fopen("tFuncionario.txt", "a+");
                    if (tFuncionario != NULL)
                    {
                        while (fread(&tempFuncionario, sizeof(Funcionario), 1, tFuncionario))
                        {
                            if (tempFuncionario.ativo == true)
                            {
                                if(tempFuncionario.codigo == tempLocacao.codfunc){
                                    strcpy(nomeFuncionarioTemp, tempFuncionario.nome);
                                }
                            }
                        }   
                    }
                    fclose(tFuncionario);
                    
                    printf("Codigo: %d \nData de devolucao: %s \nData de locacao:%s \nNome do cliente: %s \nNome do funcionario: %s \nTipo de pagamento: %s\nValor total: %f \n  \n", tempLocacao.codigo, tempLocacao.datadevo, tempLocacao.dataloca, nomeClienteTemp, nomeFuncionarioTemp, tempLocacao.pagamento == 1 ? "A vista" : "A prazo", tempLocacao.valortotal);

                    cont++;
                }
            }
            contTotal++;
        }
        codLocacao = contTotal;     
    }
    fclose(tLocacao);
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);
}

//locacaoTemFilmes
void contLocacaoTemFilmes(int &codlocacaoTemFilmes){
    FILE *tlocacaoTemFilmes;
    locacaoTemFilmes temp;
    int cont = 0;
    tlocacaoTemFilmes = fopen("tlocacaoTemFilmes.txt", "a+");

    if (tlocacaoTemFilmes != NULL)
    {
        while (fread(&temp, sizeof(locacaoTemFilmes), 1, tlocacaoTemFilmes))
        {
            cont++;
        }
        codlocacaoTemFilmes = cont;     
        fclose(tlocacaoTemFilmes);
    }
}


//devolucao
void cadastraDevolucao(int &coddevolucao, int codLocacao){
    FILE *tdevolucao;
    tdevolucao = fopen("tdevolucao.txt", "a+");

    if (tdevolucao != NULL)
    {
        devolucao tempDev;
        coddevolucao++;
        tempDev.codigo = coddevolucao;
        tempDev.ativo = true;

        tempDev.codLocacao = codLocacao;



        printf("Informe a data de devolução XX/XX/XX: ");
        scanf("%s", tempDev.datadevo);
        fflush(stdin);
        
        FILE *tLocacao;

        Locacao tempLoc;
        tLocacao = fopen("tLocacao.txt", "a+");

        if (tLocacao != NULL)
        {
            while (fread(&tempLoc, sizeof(Locacao), 1, tLocacao))
            {
                if (tempLoc.ativo == true)
                {
                    if (tempLoc.codigo == codLocacao)
                    {
                        strcpy(tempDev.dataloca, tempLoc.dataloca);
                        
                    }
                }
            }   
        }
        fclose(tLocacao);

        
        // if datadevo > dataloca, valorpago =  valortotal * diasatraso

        int diaLocacao, diaDevolucao, diaDevolucaoReal;
        char c[3];

        c[0]=tempLoc.dataloca[0];
        c[1]=tempLoc.dataloca[1];
        diaLocacao=atoi(c);

        c[0]=tempLoc.datadevo[0];
        c[1]=tempLoc.datadevo[1];
        diaDevolucao=atoi(c);
        
        c[0]=tempDev.datadevo[0];
        c[1]=tempDev.datadevo[1];
        diaDevolucaoReal=atoi(c);

        tempDev.valororiginal = tempLoc.valortotal;
        tempDev.diasatraso = diaDevolucaoReal-diaDevolucao;

        if(diaDevolucaoReal>diaDevolucao){
            tempDev.valorpago = tempLoc.juro * (diaDevolucaoReal-diaDevolucao);
        }
        else{
            if (tempLoc.pagamento == 1){
                tempDev.valorpago = tempLoc.desc;
                
            }else{
                tempDev.valorpago = tempLoc.valortotal;
            }
        }
        

        fwrite(&tempDev, sizeof(devolucao), 1, tdevolucao);
        system("cls");
        printf("Devolucao cadastrada com sucesso!\n");
        fclose(tdevolucao);

        Locacao tempLocacao;
        tLocacao = fopen("tLocacao.txt", "r+");
        if (tLocacao != NULL)
        {
            while (fread(&tempLocacao, sizeof(Locacao), 1, tLocacao))
            {
                if (tempLocacao.codigo == codLocacao)
                {
                	codLocacao--;
                    tempLocacao.ativo = false;
                    fseek(tLocacao, codLocacao*sizeof(Locacao), SEEK_SET);
                    fwrite(&tempLocacao, sizeof(Locacao), 1, tLocacao);
                    fclose(tLocacao);
                    break;
                }
            }
        }

    }
}

void listarDevolucao(int &codDevolucao, HANDLE hConsole){
    
    FILE *tDevolucao;
    Devolucao temp;
    int cont = 0;
    int contTotal = 0;
    tDevolucao = fopen("tDevolucao.txt", "a+");

    if (tDevolucao != NULL)
    {
        while (fread(&temp, sizeof(Devolucao), 1, tDevolucao))
        {
           // std::cout<<temp.ativo<<"-"<<temp.codigo<<"\n";
            if (temp.ativo == true)
            {
                (cont % 2 == 0) ? SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE):  SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);//alterna cor console
                
                printf("Codigo: %d \nCodigo da locacao: %d \nData locacao: %s \nData Devolucao: %s \nValor Original: %f \nValor pago: %f \nDias de atraso: %d\n\n", temp.codigo, temp.codLocacao, temp.dataloca, temp.datadevo, temp.valororiginal, temp.valorpago, temp.diasatraso <= 0 ? 0 : temp.diasatraso);
                fflush(stdin);

                cont++;
            }
            contTotal++;
        }
        codDevolucao = contTotal;     
        fclose(tDevolucao);
    }
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);
}

void contDevolucao(int &codDevolucao){
    FILE *tDevolucao;
    Devolucao temp;
    int cont = 0;
    tDevolucao = fopen("tDevolucao.txt", "a+");

    if (tDevolucao != NULL)
    {
        while (fread(&temp, sizeof(Devolucao), 1, tDevolucao))
        {
            cont++;
        }
        codDevolucao = cont;     
        fclose(tDevolucao);
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
    int codlocacaoTemFilmes = 1;
    int codDevolucao = 1;

    // Cria��o e inicializa��o dos arquivos.
    FILE *tGenero;
    FILE *tFilme;
    FILE *tCliente;
    FILE *tFuncionario;
    FILE *tLocacao;
    FILE *tlocacaoTemFilmes;
    FILE *tDevolucao;

    //define cor do console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);

    //contabiliza registros ou cria arquivo caso n�o exista
    contGenero(codGenero);
	contFilme(codFilme);
	contCliente(codCliente);
	contFuncionario(codFuncionario);
	contLocacao(codLocacao);
    contLocacaoTemFilmes(codlocacaoTemFilmes);
    contDevolucao(codDevolucao);

    
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
        case 1: // Cadastro e Listar G�nero
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
        case 4: // Cadastro e Listar funcion�rio
        system("CLS");
	        printf("1. Cadastrar Funcionario\n");
	        printf("2. Listar Funcionario\n");
	        scanf("%d", &verificador);
	        fflush(stdin);
	        if(verificador == 1){
	        	cadastraFuncionario(codFuncionario);
		        fflush(stdin);
		        system("CLS");
			}else{
				system("CLS");
				listarFuncionario(codFuncionario, hConsole);
				fflush(stdin);
			}
            break;
        case 5: // Cadastro e Listar Loca��o
        	system("CLS");
	        printf("1. Cadastrar Locacao\n");
	        printf("2. Listar Locacao\n");
	        scanf("%d", &verificador);
	        fflush(stdin);
	        
	        if(verificador == 1){
	        	int opLocFuncionario, opLocCliente;
		    	
		    	fflush(stdin);
				printf("Selecione o cliente: \n");
				listarCliente(codCliente, hConsole);
		        scanf("%d", &opLocCliente);
		        fflush(stdin);
		        
		        printf("Selecione o Funcionario: \n");
				listarFuncionario(codFuncionario, hConsole);
		        scanf("%d", &opLocFuncionario);
		        fflush(stdin);
				system("CLS");
                // print codLocacao
		        cadastraLocacao(codlocacaoTemFilmes, codLocacao, opLocFuncionario, opLocCliente, codFilme ,hConsole);
			}else{
				system("CLS");
                listarLocacao(codLocacao, hConsole);
			}
        	
            break;
        case 6: // Fazer Devolucao
            int codDevolucaoLocacao;

            system("CLS");
            listarLocacao(codLocacao, hConsole);
            printf("Digite o codigo da locacao que deseja devolver: ");
            scanf("%d", &codDevolucaoLocacao);
            fflush(stdin);
            cadastraDevolucao(codDevolucao, codDevolucaoLocacao);

            break;
        case 7: // Excluir g�nero
        	deletaGenero();
            break;
        case 8: // Excluir Filmes
        	deletaFilme();
            break;
        case 9: // Excluir Cliente
            system("CLS");
			deletaCliente();
			fflush(stdin);
            break;
        case 10: // Excluir Funcion�rio
            system("CLS");
			deletaFuncionario();
			fflush(stdin);
            break;
        case 11: // Excluir Loca��o
            system("CLS");
            deletaLocacao();
            break;
        case 12: // Listar loca��o data especifica
            system("CLS");
            listarLocacaoEspecifica(codLocacao, hConsole);
            break;
        case 13: // Listar filmes em atraso
            system("CLS");
            listarLocacaoEmAtraso(codLocacao, hConsole);
            break;
        case 14: // Listar devolu��o
            system("CLS");
            listarDevolucao(codDevolucao, hConsole);
            break;
        case 15: // Sair
            break;
        }
    }
}
