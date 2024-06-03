#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
//#include <iomanip>

// Caminhos dos arquivos de texto como Banco de Dados
const std::string FUNCIONARIOS_FILE = "funcionarios.txt";
const std::string CLIENTES_FILE = "clientes.txt";


struct Funcionario {
    int idFunc;
    std::string nomeFunc;
    std::string dataNascimento;
    double salario;
    int horasBase;
    double salHora;
    double salDia;
    double salPagar;
};


struct Cliente {
    int idCliente;
    std::string razaoSocial;
    std::string endereco;
};


// Funções para leitura e escrita dos arquivos de texto como Banco de Dados
std::vector<Funcionario> readFuncionarios() {
    std::vector<Funcionario> funcionarios;
    std::ifstream file(FUNCIONARIOS_FILE);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Funcionario func;
        iss >> func.idFunc >> std::ws;
        std::getline(iss, func.nomeFunc, ';');
        std::getline(iss, func.dataNascimento, ';');
        iss >> func.salario >> func.horasBase >> func.salHora >> func.salDia >> func.salPagar;
        funcionarios.push_back(func);
    }

    return funcionarios;
}


void writeFuncionarios(const std::vector<Funcionario>& funcionarios) {
    std::ofstream file(FUNCIONARIOS_FILE);
    for (const auto& func : funcionarios) {
        file << func.idFunc << " " << func.nomeFunc << ";" << func.dataNascimento << ";" << func.salario
             << " " << func.horasBase << " " << func.salHora << " " << func.salDia << " " << func.salPagar << std::endl;
    }
}


std::vector<Cliente> readClientes() {
    std::vector<Cliente> clientes;
    std::ifstream file(CLIENTES_FILE);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Cliente cliente;
        iss >> cliente.idCliente >> std::ws;
        std::getline(iss, cliente.razaoSocial, ';');
        std::getline(iss, cliente.endereco, ';');
        clientes.push_back(cliente);
    }

    return clientes;
}


void writeClientes(const std::vector<Cliente>& clientes) {
    std::ofstream file(CLIENTES_FILE);
    for (const auto& cliente : clientes) {
        file << cliente.idCliente << " " << cliente.razaoSocial << ";" << cliente.endereco << std::endl;
    }
}


void menuFuncionarios() {
    int opcao;
    do {
        std::cout << "Menu Cadastro de Funcionarios:\n";
        std::cout << "1. Incluir\n";
        std::cout << "2. Alterar\n";
        std::cout << "3. Excluir\n";
        std::cout << "4. Consultar Pelo ID\n";
        std::cout << "5. Listar\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha uma opcao: ";

        while (!(std::cin >> opcao)) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Entrada inválida! Por favor, insira um número: ";
        }

        std::vector<Funcionario> funcionarios = readFuncionarios();
        int idFunc;
        std::string nomeFunc, dataNascimento;
        double salario, salHora, salDia, salPagar;
        int horasBase;

        switch (opcao) {
            case 1: // Incluir
                system("cls");
                std::cout << "ID FUNCIONARIO     : "; std::cin >> idFunc;
                std::cin.ignore();
                std::cout << "NOME DO FUNCIONARIO: "; std::getline(std::cin, nomeFunc);
                std::cout << "DATA DE NASCIMENTO : "; std::getline(std::cin, dataNascimento);
                std::cout << "SALARIO CADASTRAL  : "; std::cin >> salario;
                //std::cout << "SALARIO CADASTRAL  : "; std::cin >> std::setprecision(2); salario;
                std::cout << "HORAS BASE MES-INT : "; std::cin >> horasBase;
                std::cout << "SALARIO HORA-DOUBLE: "; std::cin >> salHora;
                std::cout << "SALARIO DIA-DOUBLE : "; std::cin >> salDia;
                std::cout << "SAL. PAGAR - DOUBLE: "; std::cin >> salPagar;

                funcionarios.push_back({idFunc, nomeFunc, dataNascimento, salario, horasBase, salHora, salDia, salPagar});
                writeFuncionarios(funcionarios);
                break;

            case 2: // Alterar
                system("cls");
                std::cout << "Digite o ID do Funcionario a ser alterado: ";
                std::cin >> idFunc;
                std::cin.ignore();

                for (auto& func : funcionarios) {
                    if (func.idFunc == idFunc) {
                        std::cout << "Novo NOME DO FUNCIONARIO: "; std::getline(std::cin, nomeFunc);
                        std::cout << "Nova DATA DE NASCIMENTO : "; std::getline(std::cin, dataNascimento);
                        std::cout << "Novo SALARIO CADASTRAL  : "; std::cin >> salario;
                        std::cout << "Nova HORAS BASE MES-INT : "; std::cin >> horasBase;
                        std::cout << "Novo SALARIO HORA-DOUBLE: "; std::cin >> salHora;
                        std::cout << "Novo SALARIO DIA-DOUBLE : "; std::cin >> salDia;
                        std::cout << "Novo SAL. PAGAR - DOUBLE: "; std::cin >> salPagar;

                        func.nomeFunc = nomeFunc;
                        func.dataNascimento = dataNascimento;
                        func.salario = salario;
                        func.horasBase = horasBase;
                        func.salHora = salHora;
                        func.salDia = salDia;
                        func.salPagar = salPagar;
                        break;
                    }
                }
                writeFuncionarios(funcionarios);
                break;

            case 3: // Excluir
                system("cls");
                std::cout << "Digite o ID do Funcionario a ser excluido: ";
                std::cin >> idFunc;

                funcionarios.erase(std::remove_if(funcionarios.begin(), funcionarios.end(),
                    [idFunc](const Funcionario& func) { return func.idFunc == idFunc; }), funcionarios.end());
                writeFuncionarios(funcionarios);
                break;

            case 4: // Consultar
                system("cls");
                std::cout << "Digite o ID do Funcionario a ser consultado: ";
                std::cin >> idFunc;

                for (const auto& func : funcionarios) {
                    if (func.idFunc == idFunc) {
                        std::cout << "ID FUNCIONARIO     : " << func.idFunc << "\n";
                        std::cout << "NOME DO FUNCIONARIO: " << func.nomeFunc << "\n";
                        std::cout << "DATA DE NASCIMENTO : " << func.dataNascimento << "\n";
                        std::cout << "SALARIO CADASTRAL  : " << func.salario << "\n";
                        std::cout << "HORAS BASE MES-INT : " << func.horasBase << "\n";
                        std::cout << "SALARIO HORA-DOUBLE: " << func.salHora << "\n";
                        std::cout << "SALARIO DIA-DOUBLE : " << func.salDia << "\n";
                        std::cout << "SAL. PAGAR - DOUBLE: " << func.salPagar << "\n";
                        break;
                    }
                }
                break;

            case 5: // Listar
                system("cls");
                for (const auto& func : funcionarios) {
                    std::cout << "ID FUNCIONARIO     : " << func.idFunc << "\n";
                    std::cout << "NOME DO FUNCIONARIO: " << func.nomeFunc << "\n";
                    std::cout << "DATA DE NASCIMENTO : " << func.dataNascimento << "\n";
                    std::cout << "SALARIO CADASTRAL  : " << func.salario  << "\n";
                    //std::cout << "SALARIO CADASTRAL  : " <<std::setprecision(3)<< func.salario  << "\n";
                    std::cout << "HORAS BASE MES-INT : " << func.horasBase << "\n";
                    std::cout << "SALARIO HORA-DOUBLE: " << func.salHora << "\n";
                    std::cout << "SALARIO DIA-DOUBLE : " << func.salDia << "\n";
                    std::cout << "SAL. PAGAR - DOUBLE: " << func.salPagar << "\n";
                    std::cout << std::endl;
                }
                break;

            case 0:
                break;

            default:
                std::cout << "Opcao Invalida!" << std::endl;
                break;
        }
    } while (opcao != 0);
}



void menuClientes() {
    int opcao;
    do {
        std::cout << "Menu Cadastro de Clientes:\n";
        std::cout << "1. Incluir\n";
        std::cout << "2. Alterar\n";
        std::cout << "3. Excluir\n";
        std::cout << "4. Consultar Pelo ID\n";
        std::cout << "5. Listar\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha uma opcao: ";

        while (!(std::cin >> opcao)) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Entrada inválida! Por favor, insira um número: ";
        }

        std::vector<Cliente> clientes = readClientes();
        int idCliente;
        std::string razaoSocial, endereco;

        switch (opcao) {
            case 1: // Incluir
                system("cls");
                std::cout << "ID CLIENTE     : "; std::cin >> idCliente;
                std::cin.ignore();
                std::cout << "NOME DO CLIENTE: "; std::getline(std::cin, razaoSocial);
                std::cout << "ENDERECO COMPLETO  : "; std::getline(std::cin, endereco);

                clientes.push_back({idCliente, razaoSocial, endereco});
                writeClientes(clientes);
                break;

            case 2: // Alterar
                system("cls");
                std::cout << "Digite o ID do Cliente a ser alterado: ";
                std::cin >> idCliente;
                std::cin.ignore();

                for (auto& cliRicci : clientes) {
                    if (cliRicci.idCliente == idCliente) {
                        std::cout << "Novo NOME DO CLIENTE: "; std::getline(std::cin, razaoSocial);
                        std::cout << "Nova ENDERECO COMPLETO  : "; std::getline(std::cin, endereco);

                        cliRicci.razaoSocial = razaoSocial;
                        cliRicci.endereco = endereco;
                        break;
                    }
                }
                writeClientes(clientes);
                break;

            case 3: // Excluir
                system("cls");
                std::cout << "Digite o ID do Cliente a ser excluido: ";
                std::cin >> idCliente;

                clientes.erase(std::remove_if(clientes.begin(), clientes.end(),
                    [idCliente](const Cliente& cliRicci) { return cliRicci.idCliente == idCliente; }), clientes.end());
                writeClientes(clientes);
                break;

            case 4: // Consultar
                system("cls");
                std::cout << "Digite o ID do Cliente a ser consultado: ";
                std::cin >> idCliente;

                for (const auto& cliRicci : clientes) {
                    if (cliRicci.idCliente == idCliente) {
                        std::cout << "ID CLIENTE     : " << cliRicci.idCliente << "\n";
                        std::cout << "NOME DO CLIENTE: " << cliRicci.razaoSocial << "\n";
                        std::cout << "ENDERECO COMPLETO  : " << cliRicci.endereco << "\n";
                        break;
                    }
                }
                break;

            case 5: // Listar
                system("cls");
                for (const auto& cliRicci : clientes) {
                    std::cout << "ID CLIENTE     : " << cliRicci.idCliente << "\n";
                    std::cout << "NOME DO CLIENTE: " << cliRicci.razaoSocial << "\n";
                    std::cout << "ENDERECO COMPLETO  : " << cliRicci.endereco << "\n";
                    std::cout << std::endl;
                }
                break;

            case 0:
                system("cls");
                break;

            default:
                std::cout << "Opcao Invalida!" << std::endl;
                break;
        }
    } while (opcao != 0);
}






int main() {
	system("cls");
    int opcao;

	while(opcao) {

        std::cout << "Menu Principal:\n";
        std::cout << "1. Cadastro Funcionarios\n";
        std::cout << "2. Cadastro de Clientes\n";
        std::cout << "0. Sair\n";
        std::cin >> opcao;


        switch(opcao) {
        	case 1:
        		system("cls");
        		menuFuncionarios();
        		break;

        	case 2:
				system("cls");
				menuClientes();
        		break;

        	case 0:
        		system("cls");
        		exit(0);
        		break;

        	default:
				continue;
		}


	}

	return 0;
}
