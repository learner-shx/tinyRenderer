## 一个简单的光栅化渲染器
---
### 简介
一个为了巩固图形学基础知识而实现的简单的光栅化渲染器，

实现了obj模型解析，画线（Bresenham）与画三角形，数据结构（矩阵与向量）及其运算，MVP变换，仿照unity shader风格的shader，布林冯光照模型，phong着色等功能。也算是c++的复习。希望可以帮到同在学习的朋友。

以后或许会继续完善。

### 编译
`make`
### 运行
输入一个obj模型及其贴图（贴图为tga格式，文件名为obj文件加_tex）

可以获得使用Phong着色实现Blinn-Phong光照渲染的tga图片

示例：
`./main ./obj/diablo3_pose.obj `

则可在图片目录下生成渲染图片output.tga

![image](https://github.com/learner-shx/tinyRenderer/tree/master/output.png)

【由于仅作学习娱乐用途，并未考虑方便用户使用，或许以后会再改改。

如果想调整模型角度或位置，可以修改`transform.h`的开头几个变量。

### 参考资料
[Tiny renderer or how OpenGL works: software rendering in 500 lines of code](https://github.com/ssloy/tinyrenderer/wiki)
