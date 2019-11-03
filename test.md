算术表达式2个运算符，带计算结果

1. 硬件配置：Intel i5 8250U, 8.00GB RAM

2. 软件环境：Windows 10,  Qt 5.12.2 + cpp

3. 文件类型：.txt

4. 运行时间：

   |         |          | 1w      | 10w      | 100w     | 1000w     |
   | ------- | -------- | ------- | -------- | -------- | --------- |
   | debug   | generate | 205 ms  | 2079 ms  | 21494 ms | 213473 ms |
   | debug   | show     | 2732 ms | 28251 ms |          |           |
   | debug   | total    | 2937 ms | 30330 ms |          |           |
   | release | generate | 18 ms   | 180 ms   | 1869 ms  | 18157 ms  |
| release | show     | 1166 ms | 9038 ms  |          |           |
   | release | total    | 1184 ms | 9218 ms  |          |           |
   
   

