# GoGoFar

**GoGoFar** is an educational and experimental project implementing a **mini AUTOSAR Classic Platform** from scratch.  
The goal is to explore the architecture and runtime behavior of AUTOSAR Classic — including OS, RTE, and BSW layers — in a lightweight, modular, and configurable way.

---

## 🚗 Project Overview

GoGoFar provides simplified yet structured implementations of core AUTOSAR Classic components:

- **OS Layer (OSEK-like)**: Task, event, alarm, and resource management.  
- **RTE (Runtime Environment)**: Facilitates communication between Software Components (SWCs).  
- **BSW (Basic Software)**: Simplified service and driver modules.  
- **MCAL / Integration**: Hardware abstraction or stubs for testing.  
- **Configuration System**: Python and template-based code generation.  

This project is intended for **education**, **simulation**, and **embedded research**, and for production automotive ECUs.

---

## ⚙️ Project Structure
```
GoGoFar/
├── Build/
│   ├── Linker/               # Linker scripts (.ld)
│   ├── Scripts/              # Build and tool scripts
│   └── Build.bat             # Entry build script (gcc / tricore)
│
├── Configuration/
│   ├── Bsw/                  # Configuration of Basic Software modules
│   ├── DBC/                  # CAN/LIN database definitions
│   └── System/               # System-level and OS configuration
│
├── Generated/
│   ├── Bsw/                  # Generated Bsw
│   └── Rte/                  # Generated RTE layer
│
├── StaticCode/
│   ├── Application/          # Application-level SWCs or demos
│   ├── Bsw/                  # Basic software static code
│   └── IntegrationCode/      # Board- or platform-specific integration
│
└── Tools/                    # Helper utilities or configuration tools
```

---

## 🧰 Build Instructions

### Prerequisites
- **CMake 3.9+**
- **GCC** (for x86 native builds)
- **HighTec toolchain** (for cross-compilation)
- *(Optional)* **Python 3.x** for configuration generation

---

### 🏗️ Build Options

GoGoFar supports two toolchains for flexible development and testing.

#### **1️⃣ GCC (x86 Host Build)**
Used for fast simulation and debugging on PC.

```bash
cd Build
Build.bat gcc
```

**Output:**
```
/Build/output/
 ├── GoGoFar.exe      # Executable
 └── logs/            # Build logs
```

Run the binary:
```bash
output\GoGoFar.exe
```

---

#### **2️⃣ Tricore Cross-Compilation**
Used for building AUTOSAR applications targeting Infineon AURIX (Tricore).

```bash
cd Build
Build.bat tricore
```

**Output:**
```
/Build/output_tricore/
 ├── GoGoFar.elf      # Target ELF
 ├── GoGoFar.map      # Linker map
 └── logs/            # Build logs
```

---

## 🧭 Roadmap

- [ ] Implement RTE signal routing  
- [ ] Add COM stack simulation (CAN/LIN)  
- [ ] Extend MCAL support for Tricore  
- [ ] Integrate configuration GUI tool  
- [ ] Add timing & resource management simulation  

---

## ⚠️ Disclaimer
GoGoFar is **not** an official AUTOSAR implementation.  
It is a **research and learning project** built to understand the AUTOSAR Classic stack and embedded software fundamentals.

---

## 📄 License
This project is released under the [MIT License](LICENSE).

---

## 🧑‍💻 Author
Developed by **GoGoFar**  
Focused on embedded systems and AUTOSAR architecture learning.
