# iWannaBeGenshinToQt
## 简介
记录一下大二做的c++课设<P>
由于课设允许自定义题目，这里选择用qt实现一个十分简单的iwanna耐久关卡<P>
课设给了大概一个月的时间去完成课设内容，对于一个人的小组来说一个月的时间十分紧张……<P>
一个人在一个月内完成课设选题和设计、素材制作、代码编写……所以请原谅这个游戏比较糙……<P>
项目演示：https://www.bilibili.com/video/BV1Et42187uT
## 版本
Qt Creator 4.3.1<p>
Based on Qt 5.9.0 (MSVC 2015, 32 bit)<p>
Built on May 28 2017 21:47:46<p>
From revision bfd818b2b1<p>
Copyright 2008-2017 The Qt Company Ltd. All rights reserved.<p>
## kid动作转换以及动画效果实现
由于Qt本身不是个游戏引擎，在实现kid动态的时候设计了一套动作转换模型来将kid动作和键盘按键的绑定。<p>
在实现kid动作的动态效果时，参考逐帧动画的原理，将不同动作的动画帧与游戏时钟绑定从而实现动画效果。<p>
动作状态转换如图所示，具体代码参见movestate.h/movestate.cpp：<p>
![image](https://github.com/KyoiLin/iWannaBeGenshinToQt/blob/master/pic/state.png)
## 效果演示
![image](https://github.com/KyoiLin/iWannaBeGenshinToQt/blob/master/pic/start.png)
![image](https://github.com/KyoiLin/iWannaBeGenshinToQt/blob/master/pic/boss.png)
![image](https://github.com/KyoiLin/iWannaBeGenshinToQt/blob/master/pic/gameover.png)
![image](https://github.com/KyoiLin/iWannaBeGenshinToQt/blob/master/pic/gameclear.png)
## 后续是否会继续更新
大概率不会~QWQ<P>
首先iwanna本身有十分成熟的制作平台，同时经过本人一个月与qt的相互折磨的经历，再折腾qt意义不大<P>
其次，这个小游戏只是作者大二时年少轻狂，觉得课设应该做点有趣的东西对自己下的挑战书，<p>
整个游戏制作的过程十分折磨人（主要原因是制作期间几乎没找到多少现成的参考，所有东西都是自己亲自造……），<p>
尽管其中还有很多瑕疵（下一部分会简单概括一下），但是作者不想再戴上痛苦面具啦<p>
## 一些絮絮叨叨的话
在制作过程中作者无数次想放弃，当时觉得能在课设验收前让kid跳起来就十分满意了，实在不行最后交个qt动画上去吧…<P>
（kid动作状态转换及动画效果是本人认为这个小游戏中最核心的部分，这一块让作者挠了整整一周的脑壳……）<p>
### 关于kid的运动
kid的动态动作的实现：利用多态实现动作转换自动机、利用帧交替刷新实现动画效果，<p>
动作状态的设计一方面对应不同动作的不同动画帧，另一方面用于相应键盘事件，<p>
这里原本可以偷工减料，直接使用一个kid图标，用键盘控制图标的位置就行，<p>
但是作者当时认为这样做失去了复刻iwanna的情怀，也失去了iwanna作为一个RPG游戏的灵魂！<p>
于是几乎3/4个项目周期都在研究怎么实现kid的动态……（剩下1/4在改图改音频www……）<p>
### 关于场景
在这个简易耐久关卡中已经实现了kid和地板的交互，但是没有实现其他block。<p>
### 关于一些没填的坑
#### 场景转换的问题
作者在写代码时没研究明白qt中刷新窗口的机制（准确地说是在写报告时才发现qt自带窗口刷新），<p>
所以最后场景转换实际上是简单粗暴地将场景2移出了屏幕……<p>
也许可以使用qt自带的窗口刷新来实现场景切换，这样也有利于实现更多关卡。<p>
#### 碰撞体积的问题
作者在最初设计时打算复刻iwanna常规关卡（也称跳刺儿），<p>
但是在实际实现的过程中，首先kid的动态就耗费了大部分时间和精力，<p>
其次，如何精确实现刺儿的碰撞体积也困扰了作者很久，而这个碰撞体积的对于常规关卡而言十分重要……<p>
作者到DDL也没想出来怎么精确实现这个碰撞体积，于是pass了这条路子……<p>
----关于碰撞体积的更新----<p>
在一个月黑风高作者失眠的夜晚，作者突然意识到2D游戏的碰撞体积实质上是一个几何问题（雾）<p>
关于刺儿的碰撞体积实现可以参考向量叉乘判断点是否在三角形内部的方法，<p>
不过尽管原理清新脱俗简单易懂，但是工程实现相对繁琐……（咕）<p>
