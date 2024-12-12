# Restaurate Threads/Semaforos

## Descrição do Projeto

O projeto consiste em um simulador de um restaurante, na qual foi utilizado conceitos de Threads e Semaforos aprendidos na disciplina de Sistemas Operacionais. O intuito é aprender de como colocar na prática esses conceitos, usando um ambiente de programação concorrente, simulando o funcionamento real de um restaurante com múltiplos clientes, garçons e um chef. 

## Equipe

- **Integrantes:**
    - Johnatas Luiz dos Santos - 13676388

## Funcionalidades do Projeto

O simulador de restaurante possui as seguintes funcionalidades:

1. **Clientes:**
   - Os clientes chegam ao restaurante e fazem pedidos.
   - Eles esperam pelo pedido e, quando recebem, come.
   - Após comer, ficam ociosos por um tempo antes de fazer um novo pedido.

2. **Garçons:**
   - Os garçons atendem os clientes, recebem os pedidos e os encaminham para o chef.
   - Após o chef preparar o pedido, os garçons entregam os pedidos aos clientes.

3. **Chef:**
   - O chef recebe os pedidos dos garçons e os prepara.
   - Após a preparação, notifica os garçons para que possam entregar os pedidos.

4. **Threads e Semáforos:**
   - Cada cliente, garçom e o chef são representados por threads.
   - Semáforos são utilizados para sincronizar as ações entre os clientes, garçons e o chef.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
restaurante/
├── include/
│   ├── Chef.h
│   ├── Customer.h
│   ├── Game.h
│   ├── Semaphore.h
│   ├── Wait.h
│   └── Waiter.h
├── lib/
│   └── SFML-2.5.1/
│       ├── include/
│       └── lib/
├── obj/
│   ├── Chef.o
│   ├── Customer.o
│   ├── Game.o
│   ├── Semaphore.o
│   ├── Wait.o
│   └── Waiter.o
├── src/
│   ├── Chef.cpp
│   ├── Customer.cpp
│   ├── Game.cpp
│   ├── main.cpp
│   ├── Semaphore.cpp
│   ├── Wait.cpp
│   └── Waiter.cpp
├── Makefile
└── README.md
```

## Instruções de Compilação e Execução

### Pré-requisitos

Foi utilizado o ambiente WSL (Windows Subsystem for Linux) para criação e desenvolvimento do projeto, uma vez que ele apresenta suporte nativo para as bibliotecas `std::thread`, necessárias para o uso de Threads e Semáforos

### Compilação

1. Navegue até o diretório do projeto:
   ```bash
   cd restaurante
   ```

2. Compile o projeto utilizando o Makefile:
   ```bash
   make
   ```

### Execução

1. Após a compilação, execute o programa:
   ```bash
   ./restaurante
   ```

2. A interface gráfica será exibida, mostrando os clientes, garçons e o chef interagindo no restaurante.

## Implementação de Threads e Semáforos

### Threads

- **Clientes:** Cada cliente é representado por uma thread que executa o método `Customer::run()`.
- **Garçons:** Cada garçom é representado por uma thread que executa o método `Waiter::run()`.
- **Chef:** O chef é representado por uma thread que executa o método `Chef::run()`.

### Semáforos

- **SemaphoreWaitingCustomer:** Usado para sincronizar a chegada de clientes e o atendimento por parte dos garçons.
- **SemaphoreWaitingOrder:** Usado para sincronizar a entrega de pedidos aos clientes.
- **SemaphoreOrderReady:** Usado para sincronizar o envio de pedidos ao chef.
- **SemaphoreOrderPrepared:** Usado para sincronizar a preparação de pedidos pelo chef e a entrega aos garçons.

## Manual do Jogo/Aplicativo

### Como Jogar/Utilizar

1. **Iniciar o Jogo:**
   - Execute o programa conforme as instruções acima.
   - A interface gráfica será exibida, mostrando os clientes, garçons e o chef.

2. **Interagir com o Jogo:**
   - Use as teclas `Up` e `Down` para aumentar ou diminuir o número de clientes no restaurante.

3. **Observar o Funcionamento:**
   - Observe como os clientes fazem pedidos, os garçons os atendem e o chef prepara os pedidos.
   - A cor dos círculos representa o estado atual de cada entidade:
     - **Cliente:**
       - Azul: Esperando
       - Amarelo: Comendo
       - Vermelho: Inativo
     - **Garçom:**
       - Branco: Esperando
       - Verde: Atendendo
     - **Chef:**
       - Vermelho: Esperando
       - Amarelo: Preparando
