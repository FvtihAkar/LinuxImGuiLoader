# Linux ImGui Loader
Linux loader with imgui and api login


### Setup
# Arch
```sh
sudo pacman -S gdb glfw libcurl gcc
```
# Debian / Ubuntu
```sh
sudo apt install gdb glfw libcurl gcc
```
# Then

```sh
cd src
make clean && make
```

to open the loader execute:
```sh
sudo -E ./loader
```

You need to make an api to use login but you can disable it in the code.

You need to change the path of the so file in menu.cpp:65.

If you want to use the example .so file and target process:
```sh
g++ -fPIC -shared exampleSoToInject.cpp -o libexample.so
g++ exampleTarget.cpp -o target
```
then
```sh
./target
```

# To Do
- Download so file from api or use shellcode injection
- Make the GUI better
- Change injection method (because gdb is probably detected)
- Make it compatible with Windows (half completed because glfw and opengl is compatible with windows)

# References
https://github.com/ocornut/imgui - Gui library by ocornut <br/>
https://github.com/nlohmann/json - Json library by nlohmann
