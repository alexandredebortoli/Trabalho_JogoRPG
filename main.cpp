#include <iostream>
#include <time.h>

using namespace std;

struct Arma
{
    int minDano, maxDano;
};
struct Inimigo
{
    string nome;
    int vida;
    Arma arma;
};
struct Fase
{
    string nome;
    Inimigo inimigos[5];
};
struct Jogador
{
    int nivel;
    int vida;
    Arma arma;
};

Jogador jogador() 
{
    Jogador novoJogador;

    novoJogador.nivel = 1;
    novoJogador.vida = 300;
    novoJogador.arma.minDano = 1;
    novoJogador.arma.maxDano = 20;

    return novoJogador;
}

void declararInimigos(Inimigo &inimigo, string nome, int vida, int minDano, int maxDano)
{
    inimigo.nome = nome;
    inimigo.vida = vida;
    inimigo.arma.minDano = minDano;
    inimigo.arma.maxDano = maxDano;
}

Fase fase()
{
    Fase novaFase;

    novaFase.nome = "Universo Marvel";
    declararInimigos(novaFase.inimigos[0], "Mandarim", 10, 2, 10);
    declararInimigos(novaFase.inimigos[1], "Caveira Vermelha", 20, 2, 20);
    declararInimigos(novaFase.inimigos[2], "Killmonger", 30, 2, 30);
    declararInimigos(novaFase.inimigos[3], "Loki", 40, 2, 40);
    declararInimigos(novaFase.inimigos[4], "Thanos", 50, 2, 50);

    return novaFase;
}

template<typename Tipo>
bool morreu(Tipo personagem)
{
    if(personagem.vida <= 0) {
        return true;
    }
    else {
        return false;
    }
}

template<typename Atacante, typename Vitima>
Vitima ataque(Atacante atacante, Vitima vitima)
{
    vitima.vida -= rand() % (atacante.arma.maxDano - atacante.arma.minDano) + atacante.arma.minDano;

    return vitima;
}

bool jogarFase(Jogador jogador, Fase fase)
{
    cout << "\nEntrando em " << fase.nome << "...\n" << endl;
    cout << "- Jogador -\nVida: " << jogador.vida << "\nDano: " << jogador.arma.minDano << " - " << jogador.arma.maxDano << endl;

    for(int i = 0; i < 5; i++) {
        cout << "----------------\n" << endl;
        cout << "Inimigo: " << fase.inimigos[i].nome << endl;
        cout << "Vida: " << fase.inimigos[i].vida << endl;
        cout << "Dano: " << fase.inimigos[i].arma.minDano << " - " << fase.inimigos[i].arma.maxDano<< "\n" << endl;
        while(!morreu(fase.inimigos[i])) {
            jogador = ataque(fase.inimigos[i], jogador);
            fase.inimigos[i] = ataque(jogador, fase.inimigos[i]);

            cout << "O jogador atacou " << fase.inimigos[i].nome << " e ele ficou com " << fase.inimigos[i].vida << " de vida" << endl;
            cout << "O " << fase.inimigos[i].nome << " atacou ao mesmo tempo e o jogador ficou com " << jogador.vida << " de vida" << endl;

            if(morreu(fase.inimigos[i]))
                cout << fase.inimigos[i].nome << " foi morto!\n" << endl;
            if(morreu(jogador)) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    srand(time(NULL));
    Jogador novoJogador;
    novoJogador = jogador();
    Fase novaFase;
    novaFase = fase();

    if(!jogarFase(novoJogador, novaFase)) {
        cout << "Jogador morreu." << endl;
    }
    else {
        cout << "Jogador venceu." << endl;
    }
}