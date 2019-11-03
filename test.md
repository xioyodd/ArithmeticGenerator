算术表达式2个运算符，带计算结果

1. 硬件配置：Intel i5 8250U, 8.00GB RAM, 三星m961 256G固态

2. 软件环境：Windows 10,  Qt 5.12.2 + cpp,

3. 文件类型：.txt

4. 运行时间：

   |         |          | 1w      | 10w      | 100w     | 1000w     |
   | ------- | -------- | ------- | -------- | -------- | --------- |
   | debug   | generate | 193 ms  | 2126 ms  | 19808 ms | 213473 ms |
   | debug   | show     | 169 ms  | 2146 ms  | 27511 ms | -         |
   | debug   | save     | 3277 ms | 4246 ms  | 7499 ms  | -         |
   | debug   | total    | 4487 ms | 14286 ms | 98991 ms | -         |
   | release | generate | 18 ms   | 179 ms   | 1770 ms  | 18276 ms  |
   | release | show     | 21 ms   | 300 ms   | 4342 ms  | 62496 ms  |
   | release | save     | 2638 ms | 4417 ms  | 9098 ms  | 204248 ms |
   | release | total    | 3450 ms | 5907 ms  | 20855 ms | 317058 ms |
   
   

