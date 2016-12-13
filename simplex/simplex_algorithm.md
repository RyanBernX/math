# 线性规划的单纯形法

### 线性规划简介:

线性规划(Linear Programming, LP)，是运筹学中研究较早、发展较快、应用广泛、方法较成熟的一个重要分支，它是辅助人们进行科学管理的一种数学方法。研究线性约束条件下线性目标函数的极值问题的数学理论和方法。英文缩写LP。它是运筹学的一个重要分支，广泛应用于军事作战、经济分析、经营管理和工程技术等方面。为合理地利用有限的人力、物力、财力等资源作出的最优决策，提供科学的依据。(来自百度百科)

### 线性规划问题:

在一般的线性规划问题中，我们希望优化一个满足一组线性不等式约束的线性函数。一直一组实数 <img src="http://latex.codecogs.com/gif.latex? (a_{1}, a_{2}...,a_{n})" border="0" /> ，对应的一组变量<img src="http://latex.codecogs.com/gif.latex? (x_{1}, x_{2}...,x_{n})" border="0" />。定义关于这些变量的一个线性函数:
<img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) = a_{1}x_{1} +  a_{2}x_{2} + ... + a_{n}x_{n} = \sum_{i=1}^{n}a_{i}x_{i}" border="0" /> 
那么等式<img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) = b" border="0" /> 和不等式 <img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) <= b" border="0" /> 以及 <img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) >= b" border="0" /> 都称为"线性约束"

