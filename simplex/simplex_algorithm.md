# 线性规划的单纯形法

### 线性规划简介:

线性规划(Linear Programming, LP)，是运筹学中研究较早、发展较快、应用广泛、方法较成熟的一个重要分支，它是辅助人们进行科学管理的一种数学方法。研究线性约束条件下线性目标函数的极值问题的数学理论和方法。英文缩写LP。它是运筹学的一个重要分支，广泛应用于军事作战、经济分析、经营管理和工程技术等方面。为合理地利用有限的人力、物力、财力等资源作出的最优决策，提供科学的依据。(来自百度百科)

### 线性规划问题:

在一般的线性规划问题中，我们希望优化一个满足一组线性不等式约束的线性函数。一直一组实数 <img src="http://latex.codecogs.com/gif.latex? (a_{1}, a_{2}...,a_{n})" border="0" /> ，对应的一组变量<img src="http://latex.codecogs.com/gif.latex? (x_{1}, x_{2}...,x_{n})" border="0" />。定义关于这些变量的一个线性函数:
<img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) = a_{1}x_{1} +  a_{2}x_{2} + ... + a_{n}x_{n} = \sum_{i=1}^{n}a_{i}x_{i}" border="0" /> 
那么等式<img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) = b" border="0" /> 和不等式 <img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) <= b" border="0" /> 以及 <img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) >= b" border="0" /> 都称为"线性约束"。并且不久之后我们即将看到，我们可以把两种不等式的约束形式统一为<img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) <= b'" border="0" /> 这种形式，然而之后在运行解决线性规划的单纯形法时又会将它变成等价的<img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) = b_{0}" border="0" /> 形式。

#### 描述线性规划问题:

线性规划问题的标准型:

如果我们已知n个实数<img src="http://latex.codecogs.com/gif.latex? c_{1}, c_{2}..., c_{n}" border="0" />与m个实数<img src="http://latex.codecogs.com/gif.latex? b_{1}, b_{2}..., b_{m}" border="0" />，以及n\*m个实数<img src="http://latex.codecogs.com/gif.latex? a_{ij}, i = 1,2,...,m, j=1,2,..,n" border="0" />，我们希望找到n个实数<img src="http://latex.codecogs.com/gif.latex? x_{1}, x_{2},...,x_{n}" border="0" />

最大化 <img src="http://latex.codecogs.com/gif.latex? \sum_{j=1}^{n}c_{j}x_{j}" border="0" />

满足约束 
<img src="http://latex.codecogs.com/gif.latex? \sum_{j=1}^{n}a_{ij}x_{j} <= b_{j}, i = 1, 2...,m" border="0" />
<img src="http://latex.codecogs.com/gif.latex? x_{j} >= 0, j = 1, 2,..., n" border="0" />

或者将分别将<img src="http://latex.codecogs.com/gif.latex? b_{1}, b_{2},...,b_{m}" border="0" />和<img src="http://latex.codecogs.com/gif.latex? c_{1}, c_{2}, ..., c_{n}" border="0" />和<img src="http://latex.codecogs.com/gif.latex? x_{1}, x_{2}, ..., x_{n}" border="0" />表示成向量b, c, x，构造m行n列矩阵<img src="http://latex.codecogs.com/gif.latex? A = (a_{ij})" border="0" />。那么标准型也可以写作:

最大化 <img src="http://latex.codecogs.com/gif.latex? c^Tx" border="0" />

满足约束 
<img src="http://latex.codecogs.com/gif.latex? Ax <= b" border="0" />
<img src="http://latex.codecogs.com/gif.latex? x >= 0" border="0" />

对于不满足标准型形式的线性规划，我们可以想办法将它转化为标准型:

