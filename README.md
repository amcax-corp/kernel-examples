[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)


### Each example can be executed with the cmake command as follows:

#### 一、 Set system environment variables

1. Click Environment variables

2. Click Create

3. Decompress the downloaded AMCAXKernel package and add its path to CMAKE_PREFIX_PATH

<div align = left><img src="https://s2.loli.net/2024/09/30/abp5NK68YvyXQuR.jpg" width=50%; height=auto></div>


#### 二、 Open the terminal

	1. Switch to the example folder for each module

	2. mkdir build

	3. cd build

	4. cmake ..

	5. cmake --build . --config release or cmake --build . --config debug

	6. cd .\Release\ or cd .\Debug\

	7. .\test.exe

##### example1 of part is used as an example

1. Switch to the example1 folder

<div align = left><img src="https://s2.loli.net/2024/08/20/fxNGCTsyzEDBoY6.png" width=45%; height=auto></div>

2. mkdir build

<div align = left><img src="https://s2.loli.net/2024/08/20/k9ZqWcXLtCbIABu.png" width=45%; height=auto></div>

3. cd build

<div align = left><img src="https://s2.loli.net/2024/08/20/uswo18SMBEcdt6U.png" width=45%; height=auto></div>

4. cmake ..

<div align = left><img src="https://s2.loli.net/2024/08/20/uhj8y5Wrw4xkmls.png" width=90%; height=auto></div>

5. cmake --build . --config release

<div align = left><img src="https://s2.loli.net/2024/08/20/6qiu8cCgxHJnOjS.png" width=45%; height=auto></div>

6. cd .\Release\

<div align = left><img src="https://s2.loli.net/2024/08/20/hiTR6GFPtal4M5j.png" width=45%; height=auto></div>

7. ./test.exe

<div align = left><img src="https://s2.loli.net/2024/08/20/8KxPpD6lQW4TX5H.png" width=45%; height=auto></div>

Note:Some examples rely on Conan for managing third-party libraries. Please refer to [Conan official website](https://conan.io/) for detailed guidance.Additionally, our core library is compiled using MSVC 2022.​
