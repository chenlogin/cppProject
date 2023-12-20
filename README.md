# C++ Project

## 编辑器：vs2022

## 目录结构

- src /：源代码文件夹，其中存放所有的.cpp文件和主程序文件。
- include /：头文件夹，其中存放所有的.h文件。
- lib /：库文件夹，可能包含需要的库文件。
- bin /：可执行文件文件夹，它通常用于存储从源代码编译出来的二进制文件。
- test /：测试文件夹，存放所有的测试代码和测试数据。
- doc /：文档文件夹，用于存储项目的文档，比如设计文档，用户手册等。
- Makefile或者CMakeLists.txt：这些文件用于描述如何构建项目。在C++项目中，通常使用make或者cmake工具来进行项目的构建。
- .gitignore：如果你使用git作为版本控制系统，那么你可能为了忽略掉编译过程中生成的临时文件，需要在项目根目录下创建.gitignore文件。

## 功能说明

- device.cpp
	- 获取磁盘容量，电池电量等设备信息
- imgReader.cpp
	- 图像识别
		- 读取图像:通过 OpenCV 的 imread 函数读取图像。
		- 进行图像预处理:可能包括灰度化、滤波、二值化等，有助于更好的识别填涂号。
		- 寻找和识别填涂号：可以使用 OpenCV 提供的 findContours 函数来寻找填涂号的位置。然后利用诸如 countNonZero 函数或直方图分析来判断哪些填涂号被涂过。
	- 根据标引区域，识别第一道选择题的作答结果。
	- 阈值设定，轮廓获取仅供参考
- 识别分类
	- 试卷摆正：扫描页上中下6个定位点，判断标引区域内的涂黑比例在一定范围内，认为纸张是摆正的
  	- 填涂号识别：通过opencv灰度、二值等处理后识别
	- 数字、勾叉等图形类：使用不同AI模型对大数据集训练，获取可接收的识别结果
- 大模型训练
	- 数据准备：数据是模型训练的基础，首先需要收集大量的带标签的训练数据。在图像识别中，数据通常是成对的图像和标签。
	- 数据预处理：包括尺寸归一化、去噪、增强等，使数据更适合模型的训练。
	- 设定模型架构：可以选择现有的深度学习模型，如CNN（卷积神经网络）等，或者自定义模型结构。模型的大小、深度、广度等参数可根据数据量大小和计算资源情况来设定。
	- 模型训练：通过大量迭代计算，使模型通过学习训练数据，逐渐减小模型预测结果和实际标签之间的差别。训练过程中的关键参数包括学习率、批次大小、优化方法等。
	- 模型验证和测试：在测试集上验证模型的性能，通过比较不同模型和鲁棒性检查，选择最优模型。
