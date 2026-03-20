<div align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=000000,000428,004e92&height=200&section=header&text=Game2048InC&fontSize=60&fontColor=ffffff&animation=fadeIn&fontAlignY=35&descSize=20&descAlignY=60&descAlign=50" alt="Aesthetic Banner Game2048InC" width="100%">
</div>

<br>

<div align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="Linguagem C">
  <img src="https://img.shields.io/badge/GCC-F34B7D?style=for-the-badge&logo=gnu&logoColor=white" alt="Compilador GCC">
  <img src="https://img.shields.io/badge/CLI_Game-2C2C2C?style=for-the-badge" alt="Command Line Interface Game">
</div>

<br>

## Sobre o Projeto
**Game2048InC** é um jogo de puzzle desenvolvido inteiramente em **C puro** para ser executado nativamente no terminal. Inspirado no clássico 2048, este projeto reimagina a jogabilidade adicionando uma mecânica de física e gravidade: em vez de arrastar blocos horizontalmente, o jogador gerencia a queda dos números em um tabuleiro dinâmico de 10x5.

O objetivo do projeto foi construir um motor de jogo leve via linha de comando (CLI) do zero, lidando com manipulação avançada de matrizes, gerenciamento de estado e persistência de dados.

## Destaques Técnicos

O desenvolvimento deste jogo envolveu a criação de sistemas complexos de baixo nível:

* **Terminal Game Loop:** Renderização contínua do tabuleiro via interface de texto (ASCII Art) com limpeza dinâmica de *buffer* (compatível com Windows e Unix).
* **Física Customizada:** Algoritmos de varredura de matriz que calculam a gravidade, queda de blocos e fusão de valores idênticos (multiplicação de células) em tempo real.
* **Persistência de Dados (Ranking):** Sistema de *High Score* implementado com I/O de arquivos binários (`.bin`). O jogo lê, ordena e grava os dados do jogador (Nickname e Score) garantindo que o progresso não seja perdido ao fechar o terminal.
* **Gestão de Memória e Estruturas:** Uso intensivo de `structs` e matrizes bidimensionais para manter o estado do tabuleiro e a tabela de líderes.

## Como Executar

O jogo é leve, não possui dependências externas e pode ser compilado em qualquer ambiente com o GCC instalado.

**1. Clone o repositório:**
```bash
git clone [https://github.com/SEU_USUARIO/Game2048InC.git](https://github.com/SEU_USUARIO/Game2048InC.git)
