# 🚀 Projeto BitDogLab - Controle de Servomotor com PWM  

## 📖 Descrição  

Este projeto demonstra o controle de um **servomotor** utilizando **PWM (Pulse Width Modulation)** no **Raspberry Pi Pico W**. A simulação ocorre no **Wokwi**, permitindo o ajuste preciso do ângulo do servomotor. Além disso, o **BitDogLab** é utilizado para experimentos adicionais com um **LED RGB**.

## ✨ Funcionalidades  

- ⚙️ **Controle de Servomotor via PWM**:
  - Configuração do **PWM na GPIO 22** com **50Hz** (período de 20ms).
  - Controle de posições fixas:
    - **180°** → Duty Cycle de **2.400µs**.
    - **90°** → Duty Cycle de **1.470µs**.
    - **0°** → Duty Cycle de **500µs**.
  - Movimentação suave entre **0° e 180°**, com incrementos de **±5µs**.

- 💡 **Experimento com LED RGB**:
  - O LED na **GPIO 12** altera sua iluminação conforme a movimentação do servomotor.

## ✅ Requisitos  

✔ Implementação de **PWM** para controle de posição.  
✔ Ajuste de ângulos com espera de **5 segundos** em cada posição fixa.  
✔ Simulação no **Wokwi**.  
✔ Código estruturado e comentado utilizando **Pico SDK**.  

---

## 🔌 Hardware Utilizado  

| Componente          | Conexão GPIO  |  
| ------------------- | ------------ |  
| Servomotor         | GPIO 22       |  
| LED RGB            | GPIO 12       |  
| Raspberry Pi Pico W | -            |  

---

## 🚀 Como Executar  

### 🔧 Instalação  

1. Clone o repositório:  
   ```sh
   git clone https://github.com/ElissonNadson/BitDogLab_Controle_servomotor_PWM.git  
   cd BitDogLab_Controle_servomotor_PWM  
   ```  
2. Configure o **Pico SDK** conforme as instruções oficiais.  
3. Importe o projeto no **Wokwi** para simulação.  

### ▶️ Compilação  

```sh
mkdir build  
cd build  
cmake ..  
make  
```  

Após a compilação, o firmware pode ser carregado na simulação **Wokwi**.  

---

## 📷 Fluxo do Projeto  
https://raw.githubusercontent.com/ElissonNadson/BitDogLab_Controle_servomotor_PWM/refs/heads/main/Untitled%20Diagram%20(11).png

### 📊 Estrutura do Código  

```
BitDogLab_Controle_servomotor_PWM/  
├── src/                 # Código fonte  
├── include/             # Arquivos de cabeçalho  
├── tests/               # Testes para validação  
├── README.md            # Documentação do projeto  
└── CMakeLists.txt       # Configuração do CMake  
```  

### 🎥 Demonstração  

🔗 Assista ao vídeo demonstrativo:  


---

💡 Desenvolvido com ❤️ por **Elisson Nadson**.  
```  
