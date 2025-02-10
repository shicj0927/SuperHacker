# 关于 SuperHacker

Super Hacker 是一个用于 Codeforces 中同时对多个人进行 Hack 的工具，原理是使用类似对拍的方法，随机生成数据后用各个程序运行得出结果，再将程序运行结果进行两两比对，如果不相同，那么其中至少有一个程序被成功 Hack。

Super Hacker 也可以用于对拍，目前虽没有专门开发相关功能，但只需将人数设置为 $2$ 人，分别放置暴力和自己的代码即可。

Super Hacker 使用 GNU 许可协议开源。

# 功能

- 自定义数据生成器
- 自定义输出比对器
- 支持最多 $100$ 份代码对拍（可以改代码增加，但注意效率）
- 保存所有运行数据和输入输出文件

# 文件要求

1. 文件放置
  ```
  +SuperHacker
  |---hacker.exe     (主程序)
  |---checker.exe    (自己创建)
  |---data.exe       (自己创建)
  |--+src            (自己创建)
  |  |---[name1].exe (自己创建)
  |  |---[name2].exe (自己创建)
  |  |---[...  ].exe (自己创建)
  |--+dat            (自动生成)
     |--+[seed]
     |--+[id]
        |---data.in
        |---[name1].out
        |---[name2].out
        |---[...  ].out
        |---result.txt
  ```
2. 代码文件

   被 hack 的代码，其中建议放一个题解代码，要求为可执行文件（exe），使用标准输入输出（stdio）。
   
3. data

   用于自动生成数据。

   程序从标准输入（stdin）读入一个整数，为这一组数据的随机种子，并且通过标准输出（stdout）输出生成的数据。

   例子：A+B Problem 的 data.cpp

   ```cpp
   #include<bits/stdc++.h>
   using namespace std;
   int main(){
   	int seed;
   	cin>>seed;
   	mt19937 Rand(seed);
   	cout<<Rand()<<" "<<Rand()<<endl;
   	return 0;
   }
   ```
   
5. checker

   用于文件比对。

   程序从配置文件（`.checker`）读入两个字符串，按照自定义规则完成比对后将结果输出到文件（`.result`），具体如下：

  |返回|意义|
  |:-:|:-:|
  |1|比对通过|
  |0|比对未通过|
  |-1|比对器错误|

# 输出解释

1. 命令行：比对结果
   
  |返回|意义|
  |:-:|:-:|
  |-|同一个代码，无需比对|
  |S|输出相同|
  |D|输出不同（程序暂停）|
  |E|比对器错误|
