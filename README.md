# ⚙️ CPU Scheduler Project

<div align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" />
  <img src="https://img.shields.io/badge/Assembly-x86-654FF0?style=for-the-badge&logo=assemblyscript&logoColor=white" />
  <img src="https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white" />
  <img src="https://img.shields.io/badge/Operating_Systems-2E8B57?style=for-the-badge&logo=linux&logoColor=white" />
  <img src="https://img.shields.io/badge/Kernel-FCC624?style=for-the-badge&logo=linux&logoColor=black" />
</div>

<div align="center">
  <img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">
</div>

> **📚 Academic Project Notice**  
> This project was developed during our **third year** of the Computer Engineering program at the University of Buenos Aires. _This repository **does not** reflect our current programming level or professional skills. It is kept here as an academic and knowledge record._

---

## 🤖 About

**sched** is a comprehensive **CPU scheduling system** implementation developed for the **Operating Systems (7508)** course at **FIUBA (Méndez–Fresia)**. This project explores different scheduling algorithms through kernel-level implementations, providing hands-on experience with process management and system-level programming.

### 🎯 Scheduling Algorithms
- **🔄 Round-Robin (RR)** — Time-slice based fair scheduling
- **📊 Priority-Based** — Process priority-driven scheduling

### 🔧 Technical Features
- **Kernel-level implementation** in C
- **Docker support**
- **Automated testing** with comprehensive grade system
- **Multiple compilation modes** for different schedulers

---

## 📋 Prerequisites

- **Linux Environment** with kernel development tools
- **C Compiler** (GCC recommended)
- **Make** build system
- **Docker** (optional, for containerized development)

---

## 🛠️ Compilation

### Default Compilation (Round-Robin)
```bash
make
```

### Scheduler-Specific Compilation

**🔄 Round-Robin Scheduler**:
```bash
make <target> USE_RR=1
```

**📊 Priority Scheduler**:
```bash
make <target> USE_PR=1
```

---

## 🧪 Testing & Validation

### Run Complete Test Suite
```bash
make grade
```

This command runs comprehensive tests to validate both scheduling algorithms and their performance characteristics.

---

## 🐳 Docker Development

The project includes a convenient `dock` script for containerized development:

| Command | Description |
|---------|-------------|
| `./dock build` | Creates project image using provided Dockerfile |
| `./dock run` | Launches container from the built image |
| `./dock exec` | Opens new shell in existing container |

### Docker Workflow
```bash
# Build development environment
$ ./dock build

# Start container
$ ./dock run

# Inside container - run any makefile commands:
$ make grade
$ make qemu-nox

# In another terminal, access running container
$ ./dock exec
```

> **💡 Tip**: The container uses [mount volumes](https://docs.docker.com/storage/volumes/), so changes made outside the container are automatically visible inside.

---

### 📖 Theoretical Component
Detailed theoretical answers and analysis are available in the `sched.md` file included in this repository.

---

## 🔧 Development Tools

### Code Formatting
Apply consistent code style:
```bash
$ make format
```

Commit formatting changes:
```bash
$ git add .
$ git commit -m "format: apply code formatter"
```

---

<div align="center">
  <img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">
  
  **Built with ⚙️ C, ASM & 🐳 Docker at Universidad de Buenos Aires**
</div>
