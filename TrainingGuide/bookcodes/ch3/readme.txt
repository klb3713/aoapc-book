《算法竞赛入门经典——训练指南》代码仓库

第三章例题代码

基础数据结构（Fundamental Data Structures）
例题 1  UVa11995  I Can Guess the Data Structure!
例题 2  UVa11991  Easy Problem from Rujia Liu
例题 3  LA3135    Argus
例题 4  UVa11997  K Smallest Sums
例题 5  LA3644    X-Plosives
例题 6  LA3027    Corporative Network

区间信息维护（Maintaining Interval Data）
例题 7  LA4329    Ping pong
例题 8  UVa11235  Frequent Values
例题 9  LA3938    Ray, pass me the dishes
例题10  UVa11992  Fast Matrix Operations 包含两个版本，即书上的版本和一个更具一般性（但效率较低）的版本

为了帮助初学者理解，另附：

动态范围最小值：dynamic_rmq.cpp
快速序列操作I： sequence1.cpp
快速序列操作II：sequence2.cpp

字符串算法（String Algorithms）
例题11  LA3942    Remember the Word
例题12  UVa11732  strcmp() Anyone?  注意本题的Trie采用左儿子/右兄弟法实现，值得借鉴
例题13  LA3026    Period
例题14  LA4670    Dominating Patterns
例题15  UVa11468  Substring
例题16  UVa11019  Matrix Matcher
例题17  UVa11107  Life Forms  倍增法实现的后缀数组，主算法为二分+线性扫描判定
例题18  LA4513    Stammering Aliens

为了帮助初学者理解，另附“简易搜索引擎”代码（预处理文本串，接受子串查询，可提交到UVa10679）
版本1：search_engine.cpp

排序二叉树（Binary Search Trees）
例题19  UVa11020  Efficient Solutions
例题20  LA5031    Graph and Queries  除了标准程序之外还有一个没有手工释放内存的版本，待程序执行完毕后由操作系统回收内存
例题21  UVa11922  Permutation Transformer
例题22  UVa11996  Jewel Magic

为了帮助初学者理解，另附：

名次树：ranktree.cpp
