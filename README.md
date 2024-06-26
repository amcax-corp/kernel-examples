[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)


### Each example can be executed with the cmake command as follows:

#### 一、 Set system environment variables

1. Click Environment variables

2. Click Create

3. Decompress the downloaded AMCAXKernel package and add its path to CMAKE_PREFIX_PATH

<div align = left><img src="https://img2.imgtp.com/2024/05/27/tauqcQGz.png" width=50%; height=auto></div>


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

<div align = left><img src="https://img2.imgtp.com/2024/05/27/7v5UZRHL.png"  width=45%; height=auto></div>

2. mkdir build

<div align = left><img src="https://img2.imgtp.com/2024/05/27/eJtPm0k6.png"  width=23%; height=auto></div>

3. cd build

<div align = left><img src="https://img2.imgtp.com/2024/05/27/8s7yyzqm.png"  width=22%; height=auto></div>

4. cmake ..

<div align = left><img src="https://img2.imgtp.com/2024/05/27/8LjFXbIL.png"  width=90%; height=auto></div>

5. cmake --build . --config release

<div align = left><img src="https://img2.imgtp.com/2024/05/27/eLiGLMpv.png"  width=40%; height=auto></div>

<div align = left><img src="https://img2.imgtp.com/2024/05/27/JcdHAjrA.png"  width=19%; height=auto></div>

6. cd .\Release\

<div align = left><img src="https://img2.imgtp.com/2024/05/27/94z4bZtl.png"  width=30%; height=auto></div>

7. ./test.exe

<div align = left><img src="https://img2.imgtp.com/2024/05/27/MtxPq54H.png"  width=22%; height=auto></div>


​
