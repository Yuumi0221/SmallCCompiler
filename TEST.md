# Yuumi's Compiler - Test Specification

> version 1.2        by Yuumi        2022.12.29

[TOC]

## 概述

此文件为 Yuumi's Compiler 的测试说明文档，程序使用方法及程序设计请参考 [README.md](README.md) 文件。

### 测试环境

- Windows 64位操作系统

### 基本测试流程

参考 [README.md](README.md) 文件中的程序使用方法进行测试。

1. 运行程序
2. 导入测试代码
3. 如有需要，进行程序输入
4. 编译运行，查看结果
5. 根据需要修改代码
6. 再次编译运行，查看结果

## 测试用例描述

| 测试编号 | 测试目标     | 测试用例   | 测试步骤                                             | 测试结果                                                     |
| -------- | ------------ | ---------- | ---------------------------------------------------- | ------------------------------------------------------------ |
| 1        | 程序基本功能 | test_1.txt | 基本测试流程，无修改                                 | 正确输出 1-100 之间的素数                                    |
| 2        | 程序基本功能 | test_2.txt | 基本测试流程，输入6 32，无修改                       | 正确输出两个整数的最小公倍数 96                              |
| 3        | 程序基本功能 | test_3.txt | 基本测试流程，无修改                                 | 正确输出 1-100 中的所有偶数                                  |
| 4        | 程序基本功能 | test_4.txt | 基本测试流程，无修改                                 | 正确输出 i, j, k 中最大的数                                  |
| 5        | 程序报错功能 | test_4.txt | 将第 9, 12, 17, 20 行最后的分号去掉                  | 正确输出四个报错：<br />You may have missed a ';' in line 10<br />You may have missed a ';' in line 13<br />You may have missed a ';' in line 18<br />You may have missed a ';' in line 21<br />4 errors in smallC program |
| 6        | 程序报错功能 | test_4.txt | 将第 8 行的 k 改为 o                                 | 正确输出一个报错：<br />Symbol does not exist in line 8<br />1 errors in smallC program |
| 7        | 程序报错功能 | test_1.txt | 在第 1 行后添加 const a=3;<br />将第 6 行的 i 改为 a | 正确输出一个报错：<br />Symbol should not be a constant in line 7<br/>1 errors in smallC program |

