# LowLevelGame

## ℹ️ About

An opportunity to do more with C++ by creating a game with SDL2. gotta love that low level code 

(I have not yet experienced the p̷̜͈̞̻̪͑̀̓͋͝ã̸͓̯̗̲̮͒i̸̥̣̮̠̔̓̀̓͗ṅ̷͙̗̮̹ of writing a physics engine from scratch)

## 💻 Dev Environment

> [!NOTE]
> Some IDEs like Clion can import the project using the included `CMakeLists.txt` file.

### 🍎 MacOS

- `brew install sdl2` — Install libraries with Homebrew.

That should be it, the included `CMakeLists.txt` will find the libraries in `/opt/homebrew/Cellar/sdl2/`.

> [!IMPORTANT]
> You may need to modify the path to `/usr/local/bin/brew` if you are on an Intel Mac.

### 🪟 Windows

Coming Soon™️

### 🐧 Linux

Assuming you have cmake ready, just download the sdl2 dependencies:

#### `apt` Users (e.g. Ubuntu & Debian)

```bash
# Make sure to `sudo apt update` first! Then install SDL2 dependencies:
sudo apt install libsdl2-dev
```

#### `yum` Users (e.g. Fedora & CentOS)

```bash
yum install SDL2-devel
```

#### People without a package manager??

Download the source zip from the latest [SDL release](https://github.com/libsdl-org/SDL/releases). 

Then extract and build.

```bash
cd <sdl folder>
# Configure the install
./configure
# Compile and install with make
make all
make install
```

## Having Issues?

~~Sounds like a skill issue ;)~~ Have fun debugging!
