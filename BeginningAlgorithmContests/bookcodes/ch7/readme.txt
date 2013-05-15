第七章 暴力求解法

7.2 枚举排列
  pp.cpp(无重复元素，递归)
  pp2.cpp(有重复元素，递归)
  pp3.cpp(有重复元素，STL)

7.3 子集生成
7.3.1 增量构造法 subset.cpp
7.3.2 位向量法   subset2.cpp
7.3.3 二进制法   subset3.cpp

7.4 回溯法
7.4.1 八皇后问题 queen.c(生成-测试法), queen2.c(回溯法), queen3.c(优化的回溯法)
7.4.2 素数环     524.cpp(生成-测试法), 524b.cpp(回溯法)
7.4.3 困难的串   129.cpp

7.5 隐式图搜索
7.5.2 倒水问题   water.cpp(书上无此代码)
7.5.3 八数码问题
  8.cpp(STL集合+取值为int的单射)
  8b.cpp(哈希表)
  8c.cpp(全排列的编码/解码)
  8d.cpp(STL集合+memcmp)
  8a.in(有解输入数据), 8b.in(无解输入数据)

注意：为了比较queen2.c和queen3.c的时间效率，请调大n的值。