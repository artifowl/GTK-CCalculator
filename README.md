# 📱 GTK CCalculator

A simple desktop calculator built using **C** and **GTK4**. It supports basic arithmetic operations including addition, subtraction, multiplication, division, decimal input, number sign switching, and input clearing.

## 🖼️ GUI Tech Stack
- Language: C
- GUI Library: GTK 4
- Build tool: GCC

## 🧰 Dependencies

To build and run this application, you need:

- `GTK4`
- `glib-2.0`
- A C compiler such as `gcc`
- `pkg-config`

### On Ubuntu / Debian-based systems:

```bash
sudo apt update
sudo apt install libgtk-4-dev build-essential
```

### On Arch Linux:
```bash
sudo pacman -S gtk4 base-devel
```

### On MacOS (with Homebrew):
```bash
brew install gtk4
```

### 🔨 Compilation
You can compile the project using gcc. Make sure calculator_logic.h and its corresponding C file are in the same directory.
```bash
gcc -o calculator main.c calculator_logic.c `pkg-config --cflags --libs gtk4`
```
This will generate an executable called calculator.

Or you can just use the Makefile.
```bash
make
```


