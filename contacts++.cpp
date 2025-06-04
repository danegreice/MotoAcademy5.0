#include <iostream>
#include <string>
using namespace std;

struct Node {
    string nome;
    string telefone;
    string email;
    Node* esquerda;
    Node* direita;

    Node(string nome, string telefone, string email) : nome(nome), telefone(telefone), email(email), esquerda(nullptr), direita(nullptr) {}
};

// Função para inserir um contato na árvore
Node* inserir(Node* raiz, string nome, string telefone, string email) {
    if (raiz == nullptr) {
        return new Node(nome, telefone, email);
    }

    if (nome < raiz->nome) {
        raiz->esquerda = inserir(raiz->esquerda, nome, telefone, email);
    } else if (nome > raiz->nome) {
        raiz->direita = inserir(raiz->direita, nome, telefone, email);
    }
    return raiz; // sem duplicatas
}

// Função para buscar um contato na árvore
Node* buscar(Node* raiz, string nome) {
    if (raiz == nullptr || raiz->nome == nome)
        return raiz;

    if (nome < raiz->nome)
        return buscar(raiz->esquerda, nome);
    else
        return buscar(raiz->direita, nome);
}

// Função auxiliar para encontrar o menor nome de uma subárvore
Node* encontrarMinimo(Node* raiz) {
    while (raiz && raiz->esquerda != nullptr)
        raiz = raiz->esquerda;
    return raiz;
}

// Função para remover um contato da árvore
Node* remover(Node* raiz, string nome) {
    if (raiz == nullptr){
        cout << "Contato nao encontrado!\n";
        return nullptr;
    }

    if (nome < raiz->nome) {
        raiz->esquerda = remover(raiz->esquerda, nome);
    } else if (nome > raiz->nome) {
        raiz->direita = remover(raiz->direita, nome);
    } else {
        // Caso 1: sem filhos
        if (raiz->esquerda == nullptr && raiz->direita == nullptr) {
            delete raiz;
            return nullptr;
        }
        // Caso 2: um filho
        else if (raiz->esquerda == nullptr) {
            Node* temp = raiz->direita;
            delete raiz;
            return temp;
        } else if (raiz->direita == nullptr) {
            Node* temp = raiz->esquerda;
            delete raiz;
            return temp;
        }
        // Caso 3: dois filhos
        Node* temp = encontrarMinimo(raiz->direita);
        raiz->nome = temp->nome;
        raiz->telefone = temp->telefone;
        raiz->email = temp->email;
        raiz->direita = remover(raiz->direita, temp->nome);
    }
    return raiz;
}

// Percurso em ordem
void emOrdem(Node* raiz) {
    if (raiz != nullptr) {
        emOrdem(raiz->esquerda);
        cout << raiz->nome << " - ";
        cout << raiz->telefone << " ";
        cout << "\n";
        emOrdem(raiz->direita);
    }
}

int main() {
    Node* raiz = nullptr;

    int opcao = -1;
    string nome, telefone, email;

    while (opcao != 0) {
        cout << "***************************\n";
        cout << "O que deseja fazer? \n";
        cout << "1 - Inserir contato \n";
        cout << "2 - Remover contato \n";
        cout << "3 - Buscar contato \n";
        cout << "4 - Listar contatos\n";
        cout << "0 - Sair \n";
        cout << "***************************\n";
        cin >> opcao;

    if (opcao == 1) {
        cout << " Digite o nome do contato: \n";
        cin >> nome;
        cout << " Digite o telefone do contato: \n";
        cin >> telefone;
        cout << " Digite o email do contato: \n";
        cin >> email;

        cout << "Inserindo " << nome << "...\n";
        raiz = inserir(raiz, nome, telefone, email);
    } else if (opcao == 2) {
        cout << " Digite o nome do contato que deseja remover: \n";
        cin >> nome;
        cout << "Removendo " << nome << "...\n";
        raiz = remover(raiz, nome);
    } else if (opcao == 3) {
        cout << " Digite o nome do contato que deseja buscar: \n";
        cin >> nome;
        cout << "Buscando " << nome << "...\n";
        Node* contato = buscar(raiz, nome);
        if (contato != nullptr) {
            cout << "Nome: " << contato->nome << endl;
            cout << "Telefone: " << contato->telefone << endl;
            cout << "Email: " << contato->email << endl;
        } else {
            cout << "Contato nao encontrado!\n";
        }
        
    } else if (opcao == 4) {
        if (raiz == nullptr) {
            cout << "Arvore vazia!\n";
            continue;
        }
        emOrdem(raiz);
    } else if (opcao == 0) {
        break;
    } else {
        cout << "Opção inválida!\n";
    }
    }
    return 0;
}
