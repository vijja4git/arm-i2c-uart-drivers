

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

## 🌐 Project Website (Coming Next)

This project will be published as an interactive technical website demonstrating:
- Architecture diagrams  
- API documentation  
- Code walkthrough  
- Live animations of I²C/UART sequences  

This helps recruiters instantly understand your engineering capabilities.

---

## 🚀 What’s Next?

We will now begin writing the actual driver code:  
- `uart.c`  
- `i2c.c`  
- HAL layers  
- `main.c`  
- Doxygen documentation  

Just say **“Start writing the code”** or **“Begin with UART driver”**.