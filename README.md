# 简介
这是一个cpu仿真的框架，其中集成sdb和一些外设
# 使用
1.你需要实现你的CPU的一个类并继承于框架中的ISA类，并实现ISA中的虚函数。
2.你需要实现实现一个main函数，其中实例化Monitor类和你CPU类，并将你的CPU类传入Monitor类中。
3.你需要在main函数的同文件中实现DPIC函数