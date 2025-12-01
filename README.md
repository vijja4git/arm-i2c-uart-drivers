# ARM I²C & UART Driver Library (C11)

This project is a production-style embedded firmware library implementing **I²C** and **UART** communication drivers for **ARM Cortex‑M** microcontrollers using **pure C11** and a simplified CMSIS-like hardware abstraction layer.  
It is designed as a **portfolio-ready, industry-standard example** of how professional embedded engineers architect low‑level firmware systems.

The project also includes:
- A modular driver architecture  
- Clean separation between hardware abstraction, drivers, and application logic  
- A sample sensor read/write workflow using I²C  
- UART-based debug logging  
- Documentation-ready comments (Doxygen‑friendly)  
- A folder structure aligned with real-world firmware teams

---

## 📁 Repository Structure

```
arm-drivers/
├── drivers/
│   ├── i2c.c
│   ├── i2c.h
│   ├── uart.c
│   └── uart.h
├── include/
│   ├── hal_i2c.h
│   ├── hal_uart.h
│   ├── hal_i2c.c
│   ├── hal_uart.c
│   └── board.h
├── src/
│   └── main.c
├── tests/
│   └── test_i2c_uart.c
├── Makefile / CMakeLists.txt
└── README.md
```

Below is an explanation of **what each directory and file does**.

---

## 📂 `drivers/` – Low-Level Peripheral Drivers

### **`i2c.c`**
Implements all I²C functionality:
- Initialization of I²C peripheral  
- Start/stop conditions  
- Write and read operations  
- Status checking  
- Blocking transfer APIs  
- Interrupt-driven transfer skeleton  
- Timeout protection  

### **`i2c.h`**
Header containing:
- Public API prototypes  
- Data structures (config, handles)  
- Status enums  
- Definitions for I²C operations  

---

### **`uart.c`**
Implements UART communication:
- UART initialization  
- TX/RX functions  
- Interrupt-driven ring buffer support  
- UART logging utilities (printf-style optional)  

### **`uart.h`**
Header exposing UART driver APIs and configuration structures.

---

## 📂 `include/` – Hardware Abstraction Layer + Board Config

### **`hal_i2c.h`**
A portable hardware abstraction layer that wraps platform-specific details.  
Allows the driver code to stay **vendor‑agnostic** and work on any Cortex‑M CMSIS‑compatible device.

Includes:
- Register access macros  
- Virtual register definitions for simulation  
- Abstracted initialization + transfer APIs  

---

### **`hal_uart.h`**
Provides UART-specific HAL abstractions, including:
- Register layout  
- Interrupt enable/disable wrappers  
- Clock and GPIO setup stubs  

---

### **`board.h`**
Hardware configuration file:
- CPU frequency  
- Peripheral base addresses  
- Pin mappings (SCL, SDA, TX, RX)  
- Useful for portability across boards  

---

## 📂 `src/` – Application Layer

### **`main.c`**
Example application that:
1. Initializes I²C and UART  
2. Reads sensor data over I²C  
3. Sends formatted logs over UART  
4. Demonstrates how real firmware uses driver APIs  

This is the file a recruiter/interviewer will look at first.

---

## 📂 `tests/` – Unit Tests (Host-Machine Simulation)

### **`test_i2c_uart.c`**
A standalone test file used to:
- Mock I²C and UART registers  
- Validate read/write APIs  
- Simulate firmware behavior on a PC  
- Enable CI/CD testing without hardware  

This is excellent for GitHub portfolio visibility.

---

## 🧰 Build System

You may build the project using:
- **Makefile** (simple, universal)  
- **CMakeLists.txt** (IDE/CI-friendly)  

Both support:
- Building drivers  
- Running tests  
- Enabling Doxygen generation  

---

## 📘 Documentation

The drivers and HAL include **Doxygen-style comments**.  
You can auto-generate HTML documentation by running:

```
doxygen Doxyfile
```

(We will generate the Doxyfile later.)

---

## 🏃 How This Project Works

This project is designed to behave like real embedded firmware **without requiring any physical hardware**.  
All peripheral registers (UART and I²C) are **simulated in software**, allowing the entire driver stack to run on a PC.

### 🔌 Hardware Simulation
The HAL layer (`hal_uart.c`, `hal_i2c.c`) simulates:
- UART TX/RX registers  
- I²C start/stop, ACK/NACK  
- Address match flag  
- Data register behavior  
- Sensor data response  

This means the drivers (`uart.c` and `i2c.c`) behave exactly as they would on a Cortex‑M MCU, but the logic executes on your computer.

### 📦 What Actually Happens
1. **main.c** initializes UART and I²C  
2. A fake I²C sensor value (`0x33`) is returned  
3. UART prints the formatted output using `putchar()`  
4. The whole loop runs 10 times and exits  

This produces console output identical to embedded UART logs.

---

## ▶️ How to Build & Run

### **1. Build the main firmware simulation**
Run:
```
make
```

This generates:
```
build/main
```

### **2. Run it**
```
./build/main
```

Expected output:
```
System Booting...
UART Initialized.
I2C Initialized.
System Ready.
Reading temperature sensor...
Sensor Value (Hex): 0x33
Loop iteration complete.
...
```

---

## 🧪 How to Run Unit Tests

Use:
```
make test
```

This builds and executes:
```
build/tests
```

Expected test results:
```
[UART] Read/Write test passed.
[I2C] Write test passed.
[I2C] Read test passed.
All tests passed successfully.
```

This confirms the I²C and UART drivers work even without real hardware.

---

## 🎯 Summary

This project shows:
- Professional embedded driver design  
- HAL abstraction for portability  
- Software-simulated peripherals  
- Testable firmware architecture  
- Clean build system (Makefile)  
- No hardware required to demonstrate skills  

Perfect for showcasing embedded engineering capabilities on GitHub.