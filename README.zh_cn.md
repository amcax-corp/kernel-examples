[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 每一个 example 均可通过 cmake 命令执行，步骤如下：

#### 一、设置系统环境变量

1.点击环境变量

2.点击新建

3.将下载的 AMCAXKernel 包解压，然后添加其路径到 CMAKE_PREFIX_PATH 中

<div align = left><img src="https://img2.imgtp.com/2024/05/27/tauqcQGz.png" width=50%; height=auto></div>


#### 二、打开终端

	1. 切换到每个模块对应的 example 文件夹下
	
	2. mkdir build
	
	3. cd build
	
	4. cmake ..
	
	5. cmake --build . --config release 或 cmake --build . --config debug
	
	6. cd .\Release\ 或 cd .\Debug\
	
	7. .\test.exe

##### 以下以 part 的 example1 为例

1. 切换到 example1 文件夹下

<div align = left><img src="https://img2.imgtp.com/2024/05/27/7v5UZRHL.png" width=45%; height=auto></div>

2. mkdir build

<div align = left><img src="https://img2.imgtp.com/2024/05/27/eJtPm0k6.png" width=23%; height=auto></div>

3. cd build

<div align = left><img src="https://img2.imgtp.com/2024/05/27/8s7yyzqm.png" width=22%; height=auto></div>

4. cmake ..

<div align = left><img src="https://img2.imgtp.com/2024/05/27/8LjFXbIL.png" width=90%; height=auto></div>

5. cmake --build . --config release

<div align = left><img src="https://img2.imgtp.com/2024/05/27/eLiGLMpv.png" width=40%; height=auto></div>

<div align = left><img src="https://img2.imgtp.com/2024/05/27/JcdHAjrA.png" width=19%; height=auto></div>

6. cd .\Release\

<div align = left><img src="https://img2.imgtp.com/2024/05/27/94z4bZtl.png" width=30%; height=auto></div>

7. ./test.exe

<div align = left><img src="https://img2.imgtp.com/2024/05/27/MtxPq54H.png" width=22%; height=auto></div>


​	

