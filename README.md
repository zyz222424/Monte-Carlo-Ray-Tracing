# Monte Carlo Path Tracing
计算机图形学作业二，Monte Carlo Path Tracing
1. ## 内容及要求

   - 实现蒙特卡洛光线追踪算法

   ## 开发环境

   - 操作系统：Win10 x64
   - 计算机配置：
   - CPU：Intel i5-9400
   - Memory：DDR4 8G
   - IDE: Microsoft Visual Studio 2019 x64
   - 依赖库：Eigen（高性能数学运算库）
   - 运行环境：Release X64
   
## 软件使用说明

### 程序启动

运行Release X64工程(双击Release目录下的mypathtrace.exe)，程序启动，选择一种模型进行加载，模型读取成功后会显示出当前渲染的配置环境，之后显示当前渲染进度，渲染成功后会显示渲染进行的时间。渲染成功后会存储为ppm文件。

### 配置文件说明

配置文件存储在data文件夹下的文件夹中，每个文件夹下的.scene文件存储了当前模型的配置信息。


   -   obj cornellbox.obj     模型的文件名
   -   resultdir result           存储文件的文件夹
   -   resultwidth 500          最终文件的宽
   -   resultheight 500         最终文件的高
   -   resultfov 20                  相机在y轴的视角
   -   modelcenteroffset 0 0 0        观察点与模型中心的偏移
   -   cameraeyeoffset 0 0 40         相机与观察点的偏移
   -   cameraupdirection 0 1 0        确定up的方向
   -   focusdist 0                                焦距，值为0时默认为cameraeyeoffset的欧氏距离
   -   aperture 2                                 光圈大小，初始值为2，可调，越大图片越模糊
   -   maxiterationdepthforray 20   光线递归深度的大小
   -   myiterate 100                             迭代次数，初始值为100
   -   sceneambient 0.2 0.2 0.2          环境光大小
   -   externallightillumination 0        外部光源的数量

   ## 软件使用说明

   ### 软件特点

   - 使用了kdtree进行空间分割，加速求交。
   - 支持反走样，每个像素会进行随机采样。
   - 支持景深功能，可以设置光圈的大小和焦距大小。
   - 运用了Monte Carlo重要性采样，使光线有更大概率抵达光源，加快收敛速度。
   - 使用Eigen高性能数学库，计算的速度比普通数学库提高了5倍。
   
   - 使用openmp并行加速，计算的速度提高了5倍。
   
   - 总体速度比使用普通数学库的单线程程序速度提高了25倍。
   
   - 配置文件较为灵活，可通过主要参数的设置配置渲染参数。
   
   - 最终的result文件名存储了这次渲染的主要信息。

---

## 数据结构说明

   - Types.h：主要用于保存通用的工具函数；
   - Utils：用于读取文件夹中的文件；
   - AbstractObject：实现了图形的基类；
   - Kdtree:：实现了kdtree数据结构，加速求交；
   - Model：用来读取模型的数据，存储模型的信息；
   - Parser：用来分析scene配置文件；
   -  Pathtracer：对场景进行渲染的类；
   -  Ray：生成光线的类；
   -  Scene：场景类，存储场景信息；
   -  SceneConfigLoader：用于渲染前场景的准备；
   -  SceneViewer：用于调用渲染函数和存储最终渲染图片。


## 性能表现

在配置为主频 2.9GHz 的Intel i5-9400 CPU，内存为DDR4 8G的笔记本上，进行10次迭代的时间：



| 是否openmp加速 | 是否运用了eigen库 | 运行时间 |
| :------------: | :---------------: | :------: |
|       是       |        是         | **2.1s** |
|       是       |        否         | **10s**  |
|       否       |        是         | **15s**  |
|       否       |        否         | **55s**  |

   从表中可以看出，本程序中的openmp和Eigen数学库有20多倍的加速。



   # 最终效果

   

   # 参考文献

   [1]Ray tracing in one weekend

   [2]Ray tracing the next week

   [3]Ray tracing in the rest of your life

   
