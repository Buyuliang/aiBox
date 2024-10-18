+-------------------------------------------------------------+
|                        **主线程**                           |
|   +-----------------------------------------------------+   |
|   | 从摄像头读取帧 -> 分配给模型线程池                    |   |
|   +-----------------------------------------------------+   |
+-------------------------------------------------------------+
                |         |         |         |         |
+---------------+---------+---------+---------+---------+----+
|               |              **模型线程**                 |
| +---------------------------------------------------------+ |
| | **PerDet**  | **PerAttr**  | **FallDet**  | **FireSmokeDet** | |
| | infer()     | infer()      | infer()      | infer()          | |
| +---------------------------------------------------------+ |
+-------------------------------------------------------------+
                |         |         |         |         |
+---------------+---------+---------+---------+---------+----+
|                    **结果处理线程**                        |
|   +-----------------------------------------------------+   |
|   | 接收推理结果 -> 结果叠加 -> 输出显示                    |   |
|   +-----------------------------------------------------+   |
+-------------------------------------------------------------+


 构造一个线程池，把模型推理添加到线程池，每个模型都有一个类，其中包含推理接口和获取结果接口，从摄像头获取数据帧到一个队列，队列设置最大size，添加预防fame id 溢出检测，每个模型线程池可以多线程推理不同帧图片，每个模型线程可以设置超时时间，或者通过条件变量告知结果处理线程，结果处理线程通过条件变量或者其他信息显示结果 map 中的已经推理结束的帧，并且是按照帧ID 显示