# 线性规划的单纯形法

### 线性规划简介:

线性规划(Linear Programming, LP)，是运筹学中研究较早、发展较快、应用广泛、方法较成熟的一个重要分支，它是辅助人们进行科学管理的一种数学方法。研究线性约束条件下线性目标函数的极值问题的数学理论和方法。英文缩写LP。它是运筹学的一个重要分支，广泛应用于军事作战、经济分析、经营管理和工程技术等方面。为合理地利用有限的人力、物力、财力等资源作出的最优决策，提供科学的依据。(来自百度百科)

### 线性规划问题:

在一般的线性规划问题中，我们希望优化一个满足一组线性不等式约束的线性函数。一直一组实数 <img src="http://latex.codecogs.com/gif.latex? (a_{1}, a_{2}...,a_{n})" border="0" /> ，对应的一组变量<img src="http://latex.codecogs.com/gif.latex? (x_{1}, x_{2}...,x_{n})" border="0" />。定义关于这些变量的一个线性函数:
<img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) = a_{1}x_{1} +  a_{2}x_{2} + ... + a_{n}x_{n} = \sum_{i=1}^{n}a_{i}x_{i}" border="0" /> 
那么等式<img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) = b" border="0" /> 和不等式 <img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) \le b" border="0" /> 以及 <img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) \ge b" border="0" /> 都称为"线性约束"。并且不久之后我们即将看到，我们可以把两种不等式的约束形式统一为<img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) \le b'" border="0" /> 这种形式，然而之后在运行解决线性规划的单纯形法时又会将它变成等价的<img src="http://latex.codecogs.com/gif.latex? f(x_{1}, x_{2}...,x_{n}) = b_{0}" border="0" /> 形式。

#### 描述线性规划问题:

##### 线性规划问题的标准型:

如果我们已知n个实数<img src="http://latex.codecogs.com/gif.latex? c_{1}, c_{2}..., c_{n}" border="0" />与m个实数<img src="http://latex.codecogs.com/gif.latex? b_{1}, b_{2}..., b_{m}" border="0" />，以及n\*m个实数<img src="http://latex.codecogs.com/gif.latex? a_{ij}, i = 1,2,...,m, j=1,2,..,n" border="0" />，我们希望找到n个实数<img src="http://latex.codecogs.com/gif.latex? x_{1}, x_{2},...,x_{n}" border="0" />

最大化 <img src="http://latex.codecogs.com/gif.latex? \sum_{j=1}^{n}c_{j}x_{j}" border="0" />

满足约束 
<img src="http://latex.codecogs.com/gif.latex? \sum_{j=1}^{n}a_{ij}x_{j} \le b_{i}, i = 1, 2...,m" border="0" />
<img src="http://latex.codecogs.com/gif.latex? x_{j} \ge 0, j = 1, 2,..., n" border="0" />

或者将分别将<img src="http://latex.codecogs.com/gif.latex? b_{1}, b_{2},...,b_{m}" border="0" />和<img src="http://latex.codecogs.com/gif.latex? c_{1}, c_{2}, ..., c_{n}" border="0" />和<img src="http://latex.codecogs.com/gif.latex? x_{1}, x_{2}, ..., x_{n}" border="0" />表示成向量b, c, x，构造m行n列矩阵<img src="http://latex.codecogs.com/gif.latex? A = (a_{ij})" border="0" />。那么标准型也可以写作:

最大化 <img src="http://latex.codecogs.com/gif.latex? c^Tx" border="0" />

满足约束 
<img src="http://latex.codecogs.com/gif.latex? Ax \le b" border="0" />
<img src="http://latex.codecogs.com/gif.latex? x \ge 0" border="0" />

注意到，标准型里面目标函数的目标是最大化，所有变量都具有非负约束，除了非负约束外的约束都是具有 <= 符号的非严格不等式。对于不满足标准型形式的线性规划，我们可以想办法将它转化为标准型:

##### 问题1:目标函数的目标并非最大化，而是最小化。

取负即可。也就是最小化 <img src="http://latex.codecogs.com/gif.latex? c^Tx " border="0" /> 等价于最大化 <img src="http://latex.codecogs.com/gif.latex? -c^Tx " border="0" />

##### 问题2:一些变量不具有非负约束

对于不具有非负约束的变量<img src="http://latex.codecogs.com/gif.latex? x_{j}" border="0"/>，把<img src="http://latex.codecogs.com/gif.latex? x_{j}" border="0"/>每次出现的地方都替换为适当的<img src="http://latex.codecogs.com/gif.latex? x_{j}'-x_{j}''" border="0"/>，并增加非负约束<img src="http://latex.codecogs.com/gif.latex? x_{j}' \ge 0" border="0"/> <img src="http://latex.codecogs.com/gif.latex?, x_{j}'' \ge 0" border="0"/>

##### 问题3:大于等于约束和等式约束

大于等于约束两边同时取负即可。即<img src="http://latex.codecogs.com/gif.latex? \sum_{j=1}^{n}a_{ij} \ge b_{i}" border="0"/> 等价于<img src="http://latex.codecogs.com/gif.latex? \sum_{j=1}^{n}-a_{ij} \le -b_{i}" border="0"/>

等式约束拆成两个不等式约束。对于<img src="http://latex.codecogs.com/gif.latex? \sum_{j=1}^{n}a_{ij} = b_{i}" border="0"/> 等价于<img src="http://latex.codecogs.com/gif.latex? \sum_{j=1}^{n}a_{ij} \le b_{i}" border="0"/> 且 <img src="http://latex.codecogs.com/gif.latex? \sum_{j=1}^{n}-a_{ij} \le -b_{i}" border="0"/>

##### 描述线性规划问题的松弛型

为了利用单纯形算法高效地求解线性规划，我们更喜欢把其中的除非负约束外的约束转换成等式约束。

对于一个约束<img src="http://latex.codecogs.com/gif.latex? \sum_{j=1}^{n}a_{ij} \le b_{i}" border="0"/> 引入一个松弛变量s，约束即可写作:
<img src="http://latex.codecogs.com/gif.latex? s = b_{i} - \sum_{j=1}^{n}a_{ij}, s \ge 0" border="0"/>。
一般地，为了方便常会用<img src="http://latex.codecogs.com/gif.latex? x_{n+i}" border="0"/> 作为第i个约束条件的松弛变量。因此第i约束条件就可以写作: 
<img src="http://latex.codecogs.com/gif.latex? x_{n+i} = b_{i} - \sum_{j=1}^{n}a_{ij}x_{j}, x_{n+i} \ge 0" border="0"/>

##### example:用一个例子来说明上述描述线性规划问题的方法:

最小化 <img src="http://latex.codecogs.com/gif.latex?-2x_{1} + 3x_{2}" border="0"/>

满足约束条件

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} + x_{2} = 7" border="0"/> 　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} - 2x_{2} \le 4" border="0"/>　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} \ge 0" border="0"/>

- 最小化目标转变成最大化:

最大化 <img src="http://latex.codecogs.com/gif.latex?2x_{1} - 3x_{2}" border="0"/>

满足约束条件

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} + x_{2} = 7" border="0"/> 　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} - 2x_{2} \le 4" border="0"/>　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} \ge 0" border="0"/>

- 等式约束

拆开等式约束:

最大化 <img src="http://latex.codecogs.com/gif.latex?2x_{1} - 3x_{2}" border="0"/>

满足约束条件

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} + x_{2} \le 7" border="0"/> 　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?-x_{1} - x_{2} \le -7" border="0"/> 　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} - 2x_{2} \le 4" border="0"/>　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} \ge 0" border="0"/>


- 增加非负约束　

<img src="http://latex.codecogs.com/gif.latex?x_{2}" border="0"/> 替换为 <img src="http://latex.codecogs.com/gif.latex?x_{2}-x_{3}" border="0"/>，添加对<img src="http://latex.codecogs.com/gif.latex?x_{2},x_{3}" border="0"/>的非负约束，得到


最大化 <img src="http://latex.codecogs.com/gif.latex?2x_{1} - 3x_{2}+3x_{3}" border="0"/>

满足约束条件

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} + x_{2} - x_{3}\le 7" border="0"/> 　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?-x_{1} - x_{2}+x_{3} \le -7" border="0"/> 　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} - 2x_{2} + 2x_{3}\le 4" border="0"/>　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} \ge 0, x_{2} \ge 0 ,x_{3} \ge 0" border="0"/>
      
- 标准型到松弛型

除了非负约束外，有3个约束条件，于是增加松弛变量<img src="http://latex.codecogs.com/gif.latex?x_{4} , x_{5}  ,x_{6}" border="0"/>

最大化 <img src="http://latex.codecogs.com/gif.latex?2x_{1} - 3x_{2}+3x_{3}" border="0"/>

满足约束条件

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{4} = 7 - x_{1} - x_{2} + x_{3}" border="0"/> 　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{5} = -7 + x_{1} + x_{2} - x_{3}" border="0"/> 　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{6} = 4 - x_{1} + 2x_{2} - 2x_{3}" border="0"/>　

　　　　　　<img src="http://latex.codecogs.com/gif.latex?x_{1} \ge 0, x_{2} \ge 0 ,x_{3} \ge 0,x_{4} \ge 0,x_{5} \ge 0,x_{6} \ge 0" border="0"/>

<del>作业:请自行练习描述线性规划问题的方法</del>

### 解决线性规划问题的单纯形法:









