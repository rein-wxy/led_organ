# led_organ
NewMaker校内赛能量机关
![image](https://github.com/rein-wxy/photo/blob/master/%E8%83%BD%E9%87%8F%E6%9C%BA%E5%85%B3/%E8%83%BD%E9%87%8F%E6%9C%BA%E5%85%B3.jpg)
## 实现功能
* 实现定速循环
* 无规律变速运动
* 手动控制led灯带  


## 制作部分  
### 器件
* DJT遥控器DT7
* C型开发板
* M3508电机
* 2*4路24v继电器（控制灯带）
* 灯带
* 距离传感器（判断边界）

## 控制部分
* 往返运动\
  检测到边缘速度取反
* 无规律变相运动\
  利用数组随机下标映射速度系数
~~~ c
factor[8] = {-2,-1.5,-1 -0.7, 0.7, 1, 1.5, 2};//速度变化系数
if(HAL_GetTick() - speed_tim[0] >= 400){
		ftr = factor2[rand() %(8)];
		speed_tim[0] = HAL_GetTick();
}
~~~



## 后续可以升级优化部分
可添加震动传感器检测装甲板是否被击打

