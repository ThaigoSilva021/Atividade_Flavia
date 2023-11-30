#include <iostream>
#include <string.h>
#include <Windows.h>
#include <locale>

struct Contato
{
	char nome[20];
	char telefone[20];
	char email[20];
	char status;
};

int calcularTamanho(FILE *);
void cadastrarContato(FILE *);
void consultarContato(FILE *);
void gerarArquivoTexto(FILE *);
void excluirContato(FILE *);

int main()
{
	int opcao;
	FILE *arquivo;

	if ((arquivo = fopen("dados1.dat", "rb+")) == NULL)
	{
		if ((arquivo = fopen("dados1.dat", "wb+")) == NULL)
		{
			printf("Falha ao abrir o arquivo!\n");
			system("pause");
		}
	}

	do
	{
		system("CLS");
		printf("\n======= AGENDA ======= \n");
		printf("1. Cadastrar\n");
		printf("2. Consultar por código\n");
		printf("3. Gerar arquivo\n");
		printf("4. Excluir registro\n");
		printf("5. Sair\n");
		printf("===========Contatos:%d=\n", calcularTamanho(arquivo));
		printf("Opção:");
		scanf("%d", &opcao);
		switch (opcao)
		{
		case 1:
			cadastrarContato(arquivo);
			break;
		case 2:
			consultarContato(arquivo);
			break;
		case 3:
			gerarArquivoTexto(arquivo);
			break;
		case 4:
			excluirContato(arquivo);
			break;
		case 5:
			fclose(arquivo);
		}
	} while (opcao != 5);
}

void cadastrarContato(FILE *arquivo)
{
	Contato contato;
	char confirma;
	contato.status = ' ';
	fflush(stdin);

	printf("Cadastrando novo registro:\n");
	printf("\nNúmero do registro:%d\n", calcularTamanho(arquivo) + 1);
	printf("Nome..........:");
	gets(contato.nome);
	printf("Telefone......:");
	gets(contato.telefone);
	printf("E-mail........:");
	gets(contato.email);
	printf("\nConfirma <s/n>:");
	fflush(stdin);
	scanf("%c", &confirma);

	if (toupper(confirma) == 'S')
	{
		printf("\nGravando...\n\n");
		fseek(arquivo, 0, SEEK_END);
		fwrite(&contato, sizeof(Contato), 1, arquivo);
	}
	system("pause");
}

void consultarContato(FILE *arquivo)
{
	Contato contato;
	int numero;
	printf("\nConsulta pelo código\n");
	printf("\nInforme o Código...:");
	scanf("%d", &numero);
	if ((numero <= calcularTamanho(arquivo)) && (numero > 0))
	{
		fseek(arquivo, (numero - 1) * sizeof(Contato), SEEK_SET);
		fread(&contato, sizeof(Contato), 1, arquivo);
		if (contato.status == ' ')
		{
			printf("\nNome......:%s", contato.nome);
			printf("\nTelefone..:%s", contato.telefone);
			printf("\nE-mail....:%s\n\n", contato.email);
		}
		else
			printf("\nRegistro excluído! \n");
	}
	else
	{
		printf("\nNúmero de registro inválido!\n");
	}
	system("pause");
}

void gerarArquivoTexto(FILE *arquivo)
{
	char nomeArquivoTexto[20];
	printf("Nome do arquivo texto:");
	scanf("%s", nomeArquivoTexto);
	strcat(nomeArquivoTexto, ".txt");
	FILE *arquivoTexto = fopen(nomeArquivoTexto, "w");
	if (!arquivoTexto)
	{
		printf("Não foi possível criar esse arquivo!\n");
		system("pause");
	}
	fprintf(arquivoTexto, "Nome                Telefone    E-mail                   Status\n");
	fprintf(arquivoTexto, "================================================================\n");
	int numero;
	Contato contato;
	for (numero = 0; numero < calcularTamanho(arquivo); numero++)
	{
		fseek(arquivo, numero * sizeof(Contato), SEEK_SET);
		fread(&contato, sizeof(Contato), 1, arquivo);
		fprintf(arquivoTexto, "%-20s%-12s%-25s- %c\n", contato.nome, contato.telefone, contato.email, contato.status);
	}
	fprintf(arquivoTexto, "================================================================\n");
	fclose(arquivoTexto);
}

void excluirContato(FILE *arquivo)
{
	Contato contato;
	char confirma;
	int numero;

	printf("\nInforme o código do registro para excluir\n");
	scanf("%d", &numero);
	if ((numero <= calcularTamanho(arquivo)) && (numero > 0))
	{
		fseek(arquivo, (numero - 1) * sizeof(Contato), SEEK_SET);
		fread(&contato, sizeof(Contato), 1, arquivo);
		if (contato.status == ' ')
		{
			printf("\nNome......:%s", contato.nome);
			printf("\nTelefone..:%s", contato.telefone);
			printf("\nE-mail....:%s\n", contato.email);
			printf("\nConfirma a exclusão: <s/n>\n");
			getchar();
			scanf("%c", &confirma);

			if (toupper(confirma) == 'S')
			{
				printf("\nExcluindo...\n\n");
				fseek(arquivo, (numero - 1) * sizeof(Contato), SEEK_SET);
				contato.status = '*';
				fwrite(&contato, sizeof(Contato), 1, arquivo);
			}
		}
		else
			printf("Registro inexistente! \n");
	}
	else
	{
		printf("\nNúmero de registro inválido!\n");
	}
	system("pause");
}

int calcularTamanho(FILE *arquivo)
{
	fseek(arquivo, 0, SEEK_END);
	return ftell(arquivo) / sizeof(Contato);
}
	#include <iostream>
#include <fstream>
#include <iomanip>

struct Contato {
    char nome[20];
    char telefone[20];
    char email[20];
    char status;
};

void cadastrarContato(std::fstream &arquivo);
void consultarContato(std::fstream &arquivo);
void gerarArquivoTexto(std::fstream &arquivo);
void excluirContato(std::fstream &arquivo);
int calcularTamanho(std::fstream &arquivo);

int main() {
    std::fstream arquivo("dados1.dat", std::ios::in | std::ios::out | std::ios::binary);

    if (!arquivo) {
        arquivo.open("dados1.dat", std::ios::out | std::ios::binary);
    }

    int opcao;

    do {
        system("CLS");
        std::cout << "\n======= AGENDA ======= \n";
        std::cout << "1. Cadastrar\n";
        std::cout << "2. Consultar por código\n";
        std::cout << "3. Gerar arquivo\n";
        std::cout << "4. Excluir registro\n";
        std::cout << "5. Sair\n";
        std::cout << "===========Contatos:" << calcularTamanho(arquivo) << "=\n";
        std::cout << "Opção:";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                cadastrarContato(arquivo);
                break;
            case 2:
                consultarContato(arquivo);
                break;
            case 3:
                gerarArquivoTexto(arquivo);
                break;
            case 4:
                excluirContato(arquivo);
                break;
        }
    } while (opcao != 5);

    arquivo.close();

    return 0;
}

void cadastrarContato(std::fstream &arquivo) {
    Contato contato;
    char confirma;

    std::cout << "Cadastrando novo registro:\n";
    std::cout << "\nNúmero do registro:" << calcularTamanho(arquivo) + 1 << "\n";
    std::cout << "Nome..........:";
    std::cin.ignore();
    std::cin.getline(contato.nome, sizeof(contato.nome));
    std::cout << "Telefone......:";
    std::cin.getline(contato.telefone, sizeof(contato.telefone));
    std::cout << "E-mail........:";
    std::cin.getline(contato.email, sizeof(contato.email));
    std::cout << "\nConfirma <s/n>:";
    std::cin >> confirma;

    if (toupper(confirma) == 'S') {
        arquivo.write(reinterpret_cast<char*>(&contato), sizeof(Contato));
        std::cout << "\nGravando...\n\n";
    }

    system("pause");
}

void consultarContato(std::fstream &arquivo) {
    Contato contato;
    int numero;

    std::cout << "\nConsulta pelo código\n";
    std::cout << "\nInforme o Código...:";
    std::cin >> numero;

    arquivo.seekg((numero - 1) * sizeof(Contato), std::ios::beg);
    arquivo.read(reinterpret_cast<char*>(&contato), sizeof(Contato));

    if (contato.status != '*') {
        std::cout << "\nNome......:" << contato.nome;
        std::cout << "\nTelefone..:" << contato.telefone;
        std::cout << "\nE-mail....:" << contato.email << "\n\n";
    } else {
        std::cout << "\nRegistro excluído!\n";
    }

    system("pause");
}

void gerarArquivoTexto(std::fstream &arquivo) {
    char nomeArquivoTexto[20];

    std::cout << "Nome do arquivo texto:";
    std::cin >> nomeArquivoTexto;

    std::ofstream arquivoTexto(nomeArquivoTexto);

    arquivoTexto << std::left << std::setw(20) << "Nome"
                 << std::setw(12) << "Telefone"
                 << std::setw(25) << "E-mail"
                 << std::setw(5) << "Status" << "\n";
    arquivoTexto << "================================================================\n";

    arquivo.seekg(0, std::ios::beg);
    Contato contato;

    for (int numero = 0; numero < calcularTamanho(arquivo); ++numero) {
        arquivo.read(reinterpret_cast<char*>(&contato), sizeof(Contato));
        arquivoTexto << std::left << std::setw(20) << contato.nome
                     << std::setw(12) << contato.telefone
                     << std::setw(25) << contato.email
                     << std::setw(5) << contato.status << "\n";
    }

    arquivoTexto << "================================================================\n";

    std::cout << "Arquivo texto gerado com sucesso!\n";
}

void excluirContato(std::fstream &arquivo) {
    Contato contato;
    char confirma;
    int numero;

    std::cout << "\nInforme o código do registro para excluir\n";
    std::cin >> numero;

    arquivo.seekg((numero - 1) * sizeof(Contato), std::ios::beg);
    arquivo.read(reinterpret_cast<char*>(&contato), sizeof(Contato));

    if (contato.status != '*') {
        std::cout << "\nNome......:" << contato.nome;
        std::cout << "\nTelefone..:" << contato.telefone;
        std::cout << "\nE-mail....:" << contato.email << "\n";
        std::cout << "\nConfirma a exclusão: <s/n>\n";
        std::cin.ignore();
        std::cin >> confirma;

        if (toupper(confirma) == 'S') {
            arquivo.seekp((numero - 1) * sizeof(Contato), std::

