# BitDogLab_Controle_servomotor_PWM

## Descrição
Este projeto faz parte das atividades do **BitDogLab** e tem como objetivo demonstrar o controle de um **servomotor** utilizando **PWM** (Pulse Width Modulation) no microcontrolador **Raspberry Pi Pico W**, empregando o **Pico SDK**. A simulação é realizada no **Wokwi**, permitindo o ajuste do ângulo do servomotor em diferentes posições.

## Componentes Utilizados
- **Microcontrolador:** Raspberry Pi Pico W (Simulado no Wokwi)
- **Servomotor:** Micro servo padrão
- **Ambiente de Desenvolvimento:** VS Code + Pico SDK
- **Simulador:** Wokwi
- **BitDogLab** (para experimentos adicionais com LED RGB)

## Funcionalidades
- Configuração do **PWM** na **GPIO 22** com frequência de aproximadamente **50Hz** (período de 20ms).
- Controle de posições fixas:
  - **180°:** Duty Cycle de **2.400µs** (0,12%) com espera de 5 segundos.
  - **90°:** Duty Cycle de **1.470µs** (0,0735%) com espera de 5 segundos.
  - **0°:** Duty Cycle de **500µs** (0,025%) com espera de 5 segundos.
- Movimentação suave do servomotor entre **0° e 180°**, com incrementos de **±5µs** e atraso de **10ms**.
- Experimento com **LED RGB (GPIO 12)** utilizando **BitDogLab**, analisando a iluminação conforme o comportamento do servomotor.

## Estrutura do Projeto
```
BitDogLab_Controle_servomotor_PWM/
├── src/                 # Código fonte em C do projeto
├── include/             # Arquivos de cabeçalho
├── tests/               # Testes para validação das funcionalidades
├── README.md            # Documentação do projeto
└── CMakeLists.txt       # Configuração do CMake para compilação com o Pico SDK
```

## Requisitos
- **Hardware e Simulação:**
  - Raspberry Pi Pico W (simulado no Wokwi)
  - Servomotor micro servo padrão
- **Software:**
  - [Visual Studio Code](https://code.visualstudio.com/)
  - [Pico SDK](https://github.com/raspberrypi/pico-sdk)
  - [Wokwi Simulator](https://wokwi.com/)
  - CMake
  - Git

## Instalação e Configuração
1. **Clone o repositório:**
   ```bash
   git clone https://github.com/ElissonNadson/BitDogLab_Controle_servomotor_PWM.git
   cd BitDogLab_Controle_servomotor_PWM
   ```
2. **Configuração do Pico SDK:**
   Siga as instruções do [Pico SDK](https://github.com/raspberrypi/pico-sdk) para configurar o ambiente de desenvolvimento.
3. **Integração com o Wokwi:**
   Importe o projeto no Wokwi para realizar a simulação.

## Compilação
Para compilar o projeto, utilize os comandos abaixo:
```bash
mkdir build
cd build
cmake ..
make
```
Após a compilação, o firmware pode ser carregado na simulação via Wokwi.

## Testes
Testes foram implementados para verificar o funcionamento correto do **PWM** e da movimentação do servomotor. Consulte a pasta `tests/` para detalhes.

## Uso
- **O firmware inicia posicionando o servomotor em 180° e mantém essa posição por 5 segundos.**
- **Em seguida, alterna para 90° e depois para 0°, aguardando 5 segundos em cada posição.**
- **Posteriormente, entra em modo de movimentação suave entre 0° e 180°.**
- **Durante a execução, um LED RGB (GPIO 12) é utilizado para demonstrar alterações na iluminação.**

## Experimento com LED RGB
Durante o funcionamento, o LED RGB na **GPIO 12** é testado para observar alterações na iluminação com base na movimentação do servomotor.

## Vídeo Demonstrativo
Confira um vídeo demonstrativo da execução do projeto [aqui](https://www.dropbox.com/scl/fi/i32f4t9dqggn4c1durb4o/2025-02-04-08-52-05.mkv?rlkey=s6ofq9yumuts3h8chte052cuj&dl=0).

## Contribuições
1. Faça um fork deste repositório.
2. Crie uma branch com a sua feature:
   ```bash
   git checkout -b minha-feature
   ```
3. Realize os commits necessários:
   ```bash
   git commit -m "Descrição da feature implementada"
   ```
4. Envie sua branch para o repositório remoto:
   ```bash
   git push origin minha-feature
   ```
5. Abra um Pull Request detalhando as alterações.

## Licença
Este projeto está licenciado sob a [MIT License](LICENSE).

## Contato
- **Autor:** Elisson Nadson  
- **BitDogLab:** [Informações sobre o BitDogLab, se disponível]  
- **Email:** [Seu e-mail de contato]

