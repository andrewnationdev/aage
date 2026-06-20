# AAGE (ANDREW ADVANCED GAME ENGINE) 

## 1. SOBRE O PROJETO

O AAGE é um esqueleto abstrato de uma engine de jogos 2D focado em baixo
nível e arquitetura de software modular. O projeto simula o ciclo de vida real
de um jogo (Game Loop) via terminal, gerenciando tempo dinâmico (deltaTime),
física linear, colisões com bordas e eventos de entrada (inputs simulados).

# 2. ARQUITETURA DE PASTAS

- `src/` Implementação do código-fonte (.cpp)
- `main.cpp` Ponto de entrada e controle do Game Loop
- `engine.cpp` Gerenciamento do ciclo de vida da engine
- `gameobject.cpp` Lógica de criação de entidades/objetos
- `include/` Arquivos de cabeçalho (.h)
- `engine.h` Definição do contexto global e assinaturas da engine
- `gameobject.h` Estruturas e propriedades dos objetos do jogo
- `build/` Pasta temporária criada para os binários (.o)
- `Makefile` Script de automação da compilação (GNU Make)

# 3. O CICLO DE VIDA DO GAME LOOP
Toda a execução da engine respeita rigidamente o seguinte fluxo por frame:

    [ engine_init ] -> Configura tela, objetos e variáveis de controle
         │
         ├──► [ engine_handle_input ] -> Lê e simula teclas (W, A, S, D)
         ├──► [ engine_update ]       -> Calcula física e colisões (deltaTime)
         └──► [ engine_render ]       -> Cospe os dados atualizados no terminal
         │
    [ engine_shutdown ] -> Encerra as threads e limpa a memória

# 4. ESTRUTURAS DE DADOS (STRUCTS)
* Vector2D: Armazena coordenadas bidimensionais (float x, float y).
* GameObject: Entidade do jogo com ID único, Vector2D posição e Vector2D velocidade.
* EngineContext: O "Gerentão" central. Guarda o estado se o jogo está rodando 
  (isRunning), a resolução (width, height), o array estático de objetos e a 
  quantidade de objetos ativos no frame.

# 5. REGRAS DA FÍSICA E COLISÃO
* Movimento: `posição = posição + (velocidade * deltaTime)`.
* Dimensões Padrão: `Largura (width) = 600.0 | Altura (height) = 800.0`.
* Rebote: Ao atingir os limites (X > width, X < 0 ou Y > height, Y < 0), a 
  velocidade do respectivo eixo é multiplicada por -1 e o objeto é reposicionado
  na borda para evitar que saia da tela.

## 6. COMO COMPILAR E EXECUTAR (LINUX/MACOS/MINGW)
Certifique-se de estar na raiz do projeto (onde o Makefile está localizado) 
e execute os comandos abaixo no terminal:

A) Para compilar o projeto:
   `$ make`

   (Isso criará a pasta 'build/' com os arquivos temporários e o executável final)

B) Para rodar o motor do jogo:
   `$ ./aage`

C) Para limpar os arquivos gerados (limpeza de build velha):
   `$ make clean`

## 7. CONFIGURAÇÃO DO RAYLIB

1. Baixe a versão oficial já compilada para Linux 64-bits

`wget https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_linux_amd64.tar.gz`

2. Descompacte o arquivo
`tar -xvf raylib-5.0_linux_amd64.tar.gz`

3. Mova os arquivos para o seu sistema reconhecer automaticamente

`sudo cp raylib-5.0_linux_amd64/include/raylib.h /usr/local/include/`

`sudo cp raylib-5.0_linux_amd64/lib/libraylib.a /usr/local/lib/`

## 8. IDEIAS PARA O FUTURO

* Para adicionar propriedades aos objetos (ex: vida, cor): altere 'gameobject.h'.
* Para mudar a lógica de exibição gráfica (ex: usar SDL2 ou Raylib): altere apenas 
  a função 'engine_render' dentro de 'engine.cpp'. O loop principal continuará 
  intacto.