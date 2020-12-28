#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void imprime_ajuda()
{
	printf("Ajuda do Tradutor Ascii <-> txt\n");
	printf("Sintaxe: \"./tradutor [ENTRADA] [FORMATO] [SAIDA]\"\n");
	printf("ENTRADA:\n");
	printf("-i [caminho/arquivo.txt]      : abre um arquivo com a entrada\n");
	printf("-t \"trecho a ser traduzido\"   : entra uma string a partir do terminal(\n");
	printf("FORMATO:\n");
	printf("-x                            : traduz de texto para ASCII hexadecimal\n");
	printf("-s 			      : traduz de hexadecimal para texto em string\n");
	printf("SAIDA:\n");
	printf("-o [caminho/arquivo.txt]      : escreve a traducao em um arquivo\n");
	printf("-p                            : imprime a traducao no terminal\n");
	printf("AJUDA:\n");
	printf("-h                            : imprime essa tela\n");
	printf("Exemplos de uso:\n");
	printf("1-\"./tradutor -i asciiencodedfile -s -o stringfile \"\n");
	printf("2-\"./tradutor -t \"texto com espacos\" -x -o encodedfile \"\n");
	printf("3-\"./tradutor -t \"texto com espacos\" -x -p \"\n");
}


int hex_para_decimal(char a) //toda conversão dessa função é feita baseada na tabela ASCII
{
	if ((int)a<58)
		return a-48;
	else
		return a-87;
}

int hex_para_ascii(char a, char b)
{
	int ai,bi;
	ai=hex_para_decimal(a);
	bi=hex_para_decimal(b);
	return (ai*16)+bi;
}

char decimal_para_hex(int a)
{
	if (a<10)
		return a+48;
	else
		return a+87;
}

void ascii_para_hex(char a,char string[])
{
	int dezena=(int)a/16;
	int unidade=(int)a%16;
	string[0]=decimal_para_hex(dezena);
	string[1]=decimal_para_hex(unidade);
}
void imprime_no_terminal(char formato_final, char*buffer)
{
	if (formato_final=='s')
	{
		for(int i=0; i<strlen(buffer);i=i+2)
		{
			printf("%c",hex_para_ascii(buffer[i],buffer[i+1]));
		}
	}
	else if (formato_final=='x')
		for(int i=0; i<strlen(buffer);i++)
		{	
			char string[2];
			ascii_para_hex(buffer[i],string);
			printf("%s",string);
		}	
}

int main(int argc, char *argv[])
{
	int opcao;
	char formato_final=0;
	char*buffer=NULL;
	
	if(argc==1)
		imprime_ajuda();
	while((opcao = getopt(argc,argv,"hi:t:xso:p")) !=-1)
	{
		switch(opcao){
			case 'h':
				imprime_ajuda();
				break; 
			case 'i':
		//		abre_arquivo(optarg);
				break;
			case 't':
				//buffer=(char*) malloc(sizeof(optarg));
				buffer=optarg;
				break;
			case 's':
				formato_final='s';
				break;
			case 'x':
				formato_final='x';
				break;
			case 'o':
				//imprime_no_arquivo(formato_final,optarg,buffer);
				break;
			case 'p':
				imprime_no_terminal(formato_final,buffer);
				break;
			case '?':
				printf("Comando não reconhecido\n");
				imprime_ajuda();
				break;
		}
	}
	//free(buffer);	
	return 0;
}
