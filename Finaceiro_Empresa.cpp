#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

typedef struct { int mat, filho, optrans;
			    char nome[20], cargo[20];
				float salario, salfamilia, salbruto, trans, salliquido, fgts, totalfunc;   
				} TFin;

FILE *pfin; 
TFin fin_aux, fin_nulo;

typedef struct { int transref, transcod;
				 char transnome[20];
				 float transvalor, cofins, pis, liquido;
			   }  TTrans;
			   
FILE *ptrans;
TTrans trans_aux, trans_nulo;

typedef struct { int ref;
				 float elet, agua, aluguel, seg, outros, despesas;
	
			   } TConta;
			   
FILE *pconta;
TConta conta_aux, conta_nulo;

void linha() 
{ 	int i; 
	for (i=1; i<=166; i++)  
	printf("_");
	printf("\n");
}

void cabec() 
{ system("cls"); 
printf("FINANCEIRO\n"); 
linha(); 
}

void abre_arquivo1() 
{ pfin = fopen("fin.dat", "r+b"); 
if (pfin == NULL)  
pfin = fopen("fin.dat", "w+b"); 
}

void abre_arquivo2() 
{ ptrans = fopen("trans.dat", "r+b"); 
if (ptrans == NULL)  
ptrans = fopen("trans.dat", "w+b"); 
}

void abre_arquivo3() 
{ pconta = fopen("conta.dat", "r+b"); 
if (pconta == NULL)  
pconta = fopen("conta.dat", "w+b"); 
}

void inserirfunc()
{
	int resp; 
do { cabec();  
printf("\n\nCadastrar Novo Funcionário\n\n");  
printf("\nMatrícula....................: ");  
scanf("%d", &fin_aux.mat);  
printf("\nNome.........................: ");  
fflush(stdin);  
gets(fin_aux.nome);
printf("\nCargo........................: ");  
fflush(stdin);  
gets(fin_aux.cargo); 
printf("\nSalário......................: ");
scanf("%f", &fin_aux.salario);
if (fin_aux.salario <= 877){
	fin_aux.salfamilia = 45;
}
if (fin_aux.salario>877 && fin_aux.salario<= 1319){
	fin_aux.salfamilia = 31.71;
}
else{
	fin_aux.salfamilia = 0;
}
printf("\nVale Transporte (1-Sim/0-Não)? ");
scanf("%d",&fin_aux.optrans);
if (fin_aux.optrans == 1){
fin_aux.trans = (fin_aux.salario*6)/100;
}
if (fin_aux.optrans == 0){
fin_aux.trans = 0;
}
printf("\nPossui filho (1-Sim/0-Não)...? ");
scanf("%d",&fin_aux.filho);
if (fin_aux.filho==0){
	fin_aux.salfamilia = 0;
} 
fin_aux.salbruto = fin_aux.salario + fin_aux.salfamilia;
fin_aux.fgts = ((fin_aux.salbruto*8)/100);
fin_aux.salliquido = fin_aux.salbruto - fin_aux.fgts - fin_aux.trans;
fseek(pfin, 0, SEEK_END);  
fwrite(&fin_aux, sizeof(TFin), 1, pfin);  
printf("\n\nFuncionário cadastrado com sucesso! \n\n");  
printf("\nDeseja cadastrar outro (1-Sim/0-Não)? ");  
scanf("%d", &resp); 
} while (resp ==1); 
}

void mostre(int pos)
{ fseek(pfin, pos*sizeof(TFin), SEEK_SET); 
fread(&fin_aux, sizeof(TFin), 1, pfin); 
printf("\n\n"); linha(); 
printf("Matricula   Nome                   Cargo                  Salario Base   Filho   Salario Familia   Salario Bruto   FGTS(8%%)   Vale Transporte(6%%)   Salário Líquido\n"); 
linha(); 
printf("%9d   %-20s   %-20s   %12.2f   %5d   %15.2f   %13.2f   %9.2f   %19.2f   %15.2f\n",fin_aux.mat,fin_aux.nome,fin_aux.cargo,fin_aux.salario,fin_aux.filho,fin_aux.salfamilia,fin_aux.salbruto,fin_aux.fgts,fin_aux.trans,fin_aux.salliquido);        
linha(); 
}

int procura(int matp) 
{ int p; 
p = 0; 
rewind(pfin); 
fread(&fin_aux, sizeof(TFin), 1, pfin); 
while (feof(pfin)==0) 
{ if (fin_aux.mat == matp)   
return p;  
else  
{ 
fread(&fin_aux, sizeof(TFin), 1, pfin);  
p++;
} 
} 
return -1; 
}

int procuranome(char nomep[20])
{
	int retorno, p;
	p = 0;
	rewind(pfin); 
	fread(&fin_aux, sizeof(TFin), 1, pfin);
	while (feof(pfin)==0)
	{
		retorno = strcmp(nomep,fin_aux.nome);
		if (retorno == 0)
		return p;
		else
		{ 
			fread(&fin_aux, sizeof(TFin), 1, pfin);  
			p++;
		} 
	} 
return -1; 
}


void consultar() 
{int opcao, resp, matcon, posicao;
char nomecon[20];
do{ cabec();  
printf("\n\nConsultar Funcionário\n\n\n");
printf("\n\nConsultar por (1-Matrícula/2-Nome)? ");
scanf("%d",&opcao);
if (opcao == 1){
printf("Matricula do Funcionário: ");  
scanf("%d", &matcon);  
posicao = procura(matcon);  
if (posicao == -1)
printf("\n\nMatrícula não encontrada! \n\n");   
else   mostre(posicao);
}
if (opcao == 2){
printf("Nome do Funcionário: ");
fflush(stdin);
gets(nomecon);
posicao = procuranome(nomecon);
if (posicao == -1)
printf("\n\nNome não encontrado! \n\n");   
else  mostre(posicao);
}
printf("\n\nDeseja consultar outro (1-Sim/0-Não)? ");  
scanf("%d", &resp); 
} while (resp == 1);
}

void remover()
{
	int matrem, conf, resp, posicao;
 fin_nulo.mat = 0; fin_nulo.salario = 0; 
 do{ cabec();  printf("\n\nExcluir Funcionario\n\n\n");  
 printf("Matricula: ");  
 scanf("%d", &matrem);  
 posicao = procura(matrem);  
 if (posicao == -1)   
 printf("\nFuncionário não encontrado!!\a");  
 else  
 { mostre(posicao);   
 printf("\n\nDeseja remover o Funcionáro (1-Sim/0-Não)? ");   
 scanf("%d", &conf);   
 if (conf == 1)   
 { fseek(pfin,posicao*sizeof (TFin),SEEK_SET);    
 fwrite(&fin_nulo, sizeof(TFin), 1, pfin);    
 printf("\n\nFuncionário excluído com sucesso!");   
 }
 else    
 printf("\nExclusão cancelada!");  
 }  
 printf("\n\n\nDeseja excluir outro (1-Sim/0-Não)? ");  
 scanf("%d", &resp); 
 } while (resp ==1); 
}

void listagemfunc()
{
cabec(); 
 printf("\n\nListagem Geral\n\n\n"); 
 linha(); 
 printf("Matricula   Nome                   Cargo                  Salario Base   Filho   Salario Familia   Salario Bruto   FGTS(8%%)   Vale Transporte(6%%)   Salário Líquido\n");  
 linha(); 
 rewind(pfin); 
 fread(&fin_aux, sizeof(TFin), 1, pfin); 
 while (feof(pfin)==0) 
 { if (fin_aux.mat != 0)  
 printf("%9d   %-20s   %-20s   %12.2f   %5d   %15.2f   %13.2f   %9.2f   %19.2f   %15.2f\n",fin_aux.mat,fin_aux.nome,fin_aux.cargo,fin_aux.salario,fin_aux.filho,fin_aux.salfamilia,fin_aux.salbruto,fin_aux.fgts,fin_aux.trans,fin_aux.salliquido);
fread(&fin_aux, sizeof(TFin), 1, pfin); 
} linha(); 
printf("tecle enter para voltar ao menu..."); 
getche(); 
}

void inserirconta()
{
int resp; 
do { cabec();  
printf("\n\nCadastrar Contas\n\n");
printf("\nDigitar mês e ano (MMAAAA): ");
scanf("%d", &conta_aux.ref);
printf("\nEletricidade..............: ");  
scanf("%f", &conta_aux.elet);  
printf("\nÁgua......................: ");  
scanf("%f", &conta_aux.agua); 
printf("\nAluguel...................: ");
scanf("%f", &conta_aux.aluguel); 
printf("\nSegurança.................: ");    
scanf("%f", &conta_aux.seg);
printf("\nOutros Gastos.............: ");    
scanf("%f", &conta_aux.outros);
conta_aux.despesas = conta_aux.elet + conta_aux.agua + conta_aux.aluguel + conta_aux.seg + conta_aux.outros;
fseek(pconta, 0, SEEK_END);  
fwrite(&conta_aux, sizeof(TConta), 1, pconta);
printf("\n\nContas cadastradas com sucesso! \n\n");  
printf("\nDeseja cadastrar outro mês/referência? (1-Sim/0-Não)? ");  
scanf("%d", &resp); 
} while (resp ==1); 	
}

void listagemcontas()
{
cabec(); 
 printf("\n\nListagem de Contas\n\n\n"); 
 linha(); 
 printf("Mês/Referência   Água   Eletricidade   Aluguel   Segurança   Outros   Total\n"); 
 linha(); 
 rewind(pconta); 
 fread(&conta_aux, sizeof(TConta), 1, pconta); 
 while (feof(pconta)==0) 
 { if (conta_aux.ref != 0)  
 printf("%14d   %4.2f   %12.2f   %7.2f   %9.2f   %6.2f   %5.2f\n", conta_aux.ref,conta_aux.agua,conta_aux.elet,conta_aux.aluguel,conta_aux.seg,conta_aux.outros,conta_aux.despesas); 
fread(&conta_aux, sizeof(TConta), 1, pconta); 
} linha(); 
printf("tecle enter para voltar ao menu..."); 
getche(); 
}

void inserirreceita()
{
	int resp; 
do { cabec();  
printf("\n\nCadastro de Receita\n\n");
printf("\nDigitar mês e ano (MMAAAA): ");
scanf("%d",&trans_aux.transref);
printf("\nCódigo da Transação.......: ");
scanf("%d",&trans_aux.transcod);
printf("\nNome da Transação.........: ");
fflush(stdin);  
gets(trans_aux.transnome);
printf("\nValor......................: ");
scanf("%f",&trans_aux.transvalor);
trans_aux.cofins = (trans_aux.transvalor*6)/100;
trans_aux.pis = (trans_aux.transvalor*0.65)/100;
trans_aux.liquido = trans_aux.transvalor - trans_aux.cofins - trans_aux.pis;
fseek(ptrans, 0, SEEK_END);  
fwrite(&trans_aux, sizeof(TTrans), 1, ptrans);
printf("\n\nReceita cadastrada com sucesso! \n\n");  
printf("\nDeseja cadastrar outra Receita? (1-Sim/0-Não)? ");  
scanf("%d", &resp); 
} while (resp ==1); 	
}

void listagemreceita()
{
	float transtotal;
	cabec(); 
 printf("\n\nListagem de Receita\n\n\n"); 
 linha(); 
 printf("Mês/Referência   Código   Nome da Transação      Valor Recebido   COFINS(3%%)   PIS(0,65%%)   Líquido\n"); 
 linha(); 
 rewind(ptrans); 
 fread(&trans_aux, sizeof(TTrans), 1, ptrans); 
 while (feof(ptrans)==0) 
 { if (trans_aux.transcod != 0)  
 printf("%14d   %6d   %-20s   %14.2f   %10.2f   %10.2f   %7.2f\n", trans_aux.transref,trans_aux.transcod,trans_aux.transnome,trans_aux.transvalor,trans_aux.cofins,trans_aux.pis,trans_aux.liquido);
 transtotal = transtotal + trans_aux.liquido;
fread(&trans_aux, sizeof(TTrans), 1, ptrans);
} linha();
printf("\n\nTotal Recebido: R$ %.2f\n\n", transtotal);
linha();
printf("tecle enter para voltar ao menu..."); 
getche();
}

int procuraref(int refp) 
{ int p; 
p = 0; 
rewind(pconta); 
fread(&conta_aux, sizeof(TConta), 1, pconta); 
while (feof(pconta)==0) 
{ if (conta_aux.ref == refp)   
return p;  
else  
{ 
fread(&conta_aux, sizeof(TConta), 1, pconta);  
p++;
} 
} 
return -1; 
}


int procurareftrans(int refp) 
{ int p; 
p = 0; 
rewind(ptrans); 
fread(&trans_aux, sizeof(TTrans), 1, ptrans); 
while (feof(ptrans)==0) 
{ if (trans_aux.transref == refp)   
return p;  
else  
{ 
fread(&trans_aux, sizeof(TTrans), 1, ptrans);  
p++;
} 
} 
return -1; 
}


void balancomes()
{
	int refop, posicao, resp;
	float totalcontas, totaltrans, totalfunc, balancomen;
	do {
		cabec();
		printf("\n\nBalanco do Mês\n\n");
		linha();
		printf("\nDigitar mês e ano (MMAAAA): ");
		scanf("%d",&refop);
		posicao = procurareftrans(refop);
		if (posicao == -1)   
			printf("\n\nReferência não cadastrada! \n\n");   
		else{
			printf("\n\nReferência %d",refop);
			fseek(ptrans, posicao*sizeof(TTrans), SEEK_SET); 
			fread(&trans_aux, sizeof(TTrans), 1, ptrans);
			totaltrans = totaltrans + trans_aux.liquido;
		}
		printf("\n\nReceita Mensal R$ %.2f\n",totaltrans);
		posicao = procuraref(refop);
		if (posicao == -1)   
			printf("\n\nReferência não cadastrada! \n\n");   
		else{
			printf("\n\nReferência %d",refop);
			fseek(pconta, posicao*sizeof(TConta), SEEK_SET); 
			fread(&conta_aux, sizeof(TConta), 1, pconta);
			printf("\n\nDespesas Contas R$ %.2f\n",conta_aux.despesas);
			totalcontas = conta_aux.despesas;
		}
		rewind(pfin); 
 		fread(&fin_aux, sizeof(TFin), 1, pfin); 
 		while (feof(pfin)==0) 
 		{ if (fin_aux.mat != 0)  
 		totalfunc = totalfunc + fin_aux.salbruto;
		fread(&fin_aux, sizeof(TFin), 1, pfin);
		}
		printf("\n\nDespesas Funcionários R$ %.2f\n",totalfunc);
		linha();
		balancomen = (totaltrans - totalcontas - totalfunc);
		printf("\n\nBalanço Mensal R$ %.2f\n",balancomen);
		linha();
		printf("\n\nDeseja consultar outro (1-sim/0-nao)? ");  
		scanf("%d", &resp);
	}while (resp == 1); 
}

void balanco()
{
		int op;
		int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR CmdLine,int CmdShiw);
                   {
 MessageBox(NULL, "FLUXO DE CAIXA","INFORMACAO", MB_OK | MB_ICONINFORMATION);
}
do{ cabec();
printf("\n\nOpções: \n\n\n");
printf("   1- Consulta por Mês \n\n");     
printf("   0- Sair\n\n");
linha();  
printf("Entre com a opção desejada: ");  
scanf("%d", &op);  
switch(op)  
{ 	case 1: balancomes(); break;     
	case 0: fclose(pfin); break;
		default: printf("\n\n\aOpção inválida!");
		break;
} 
} while (op != 0);
}

void receber()
{
	int op;
	int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR CmdLine,int CmdShiw);
                   {
 MessageBox(NULL, "RECEITAS","INFORMACAO", MB_OK | MB_ICONINFORMATION);
}
do{ cabec();
printf("\n\nOpções: \n\n\n");
printf("   1- Cadastrar Receita \n\n");     
printf("   2- Listar\n\n");  
printf("   0- Sair\n\n");
linha();  
printf("Entre com a opção desejada: ");  
scanf("%d", &op);  
switch(op)  
{ 	case 1: inserirreceita(); break;      
	case 2: listagemreceita(); break; 
	case 0: fclose(pfin); break;
		default: printf("\n\n\aOpção inválida!");
		break;
} 
} while (op != 0);
}

void contas()
{
	int op;
do{ cabec();
printf("\n\nOpções: \n\n\n");
printf("   1- Inserir\n\n");     
printf("   2- Listar\n\n");  
printf("   0- Sair\n\n");
linha();  
printf("Entre com a opção desejada: ");  
scanf("%d", &op);  
switch(op)  
{ 	case 1: inserirconta(); break;      
	case 2: listagemcontas(); break; 
	case 0: fclose(pfin); break;
		default: printf("\n\n\aOpção inválida!");
		break;
} 
} while (op != 0);
}

void funcionarios()
{
	int op;
	do{ cabec();  
printf("\n\nOpções: \n\n\n");  
printf("   1- Cadastrar Funcionario\n\n");
printf("   2- Remover Funcionário\n\n");    
printf("   3- Procurar Funcionário\n\n");  
printf("   4- Listar\n\n");
printf("   0- Sair\n\n");
linha();  
printf("Entre com a opção desejada: ");  
scanf("%d", &op);  
switch(op)  
{ 	case 1: inserirfunc(); break;
	case 2: remover(); break;      
	case 3: consultar(); break;
	case 4: listagemfunc(); break;
	case 0: fclose(pfin); break;
		default: printf("\n\n\aOpção inválida!");
		break;
} 
} while (op != 0); 
}

void pagar()
{
	int op;
	int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR CmdLine,int CmdShiw);
                   {
 MessageBox(NULL, "CONTAS A PAGAR","INFORMACAO", MB_OK | MB_ICONINFORMATION);
}
	do{ cabec();  
printf("\n\nOpções: \n\n\n");  
printf("   1- Funcionarios\n\n");     
printf("   2- Contas\n\n");  
printf("   0- Sair\n\n");   
linha();  
printf("Entre com a opção desejada: ");  
scanf("%d", &op);  
switch(op)  
{ 	case 1: funcionarios(); break;      
	case 2: contas(); break;
	case 0: fclose(pfin); break;
		default: printf("\n\n\aOpção inválida!");
		break;
} 
} while (op != 0); 
}

main() 
{ int op;
setlocale(LC_ALL, "Portuguese");
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR CmdLine,int CmdShiw);
                   {
 MessageBox(NULL, "PROGRAMA FINANCEIRO","INFORMACAO", MB_OK | MB_ICONINFORMATION);
 system("color 70");
}
abre_arquivo1();
abre_arquivo2();
abre_arquivo3(); 
do{ cabec();  
printf("\n\nOpções: \n\n\n");  
printf("   1- Contas a Pagar\n\n");     
printf("   2- Receitas\n\n");
printf("   3- Fluxo de Caixa\n\n");   
printf("   0- Sair\n\n");   
linha();  
printf("Entre com a opção desejada: ");  
scanf("%d", &op);  
switch(op)  
{ 	case 1: pagar(); break;      
	case 2: receber(); break;
	case 3: balanco(); break;
	case 0: fclose(pfin); break;
		default: printf("\n\n\aOpção inválida!");
		break;
} 
} while (op != 0); 
}
