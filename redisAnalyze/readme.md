## redis

### 功能
- 缓存
- 分布式锁
- 高效的数据结构和算法
- 备注: redis也可以用作消息队列和流处理，但是不推荐。可以使用专门的消息队列，如Kafka, RabbitMQ

### 特点
- 高性能: 数据存储在内存中，读写速度非常快；C编写，底层采用多路复用和非阻塞模型（异步IO）
- 持久化: 可以将数据写入磁盘中，以防止数据丢失；有两种方式: **快照:RDB**； **日志:AOF**； 
- 高可用/分布式: Sentinel哨兵模式；Replication主从复制；Redis Cluster分布式集群 

### String 字符串
#### 缓存
- String通常用于缓存，可用于存储字符、Json字符串或序列化对象；
- ``set k1 v1``
- ``get k1``  //不存在返回nil
- 设置json， ``set user:1 "{\"id\":1, \"name\":\"user1\", \"age\":20}"``
- ``set k3 v3 XX`` //只有当k3存在的时候才会赋值（XX指令的使用）
- ``set k4 v4 NX`` //只有当K4不存在的时候才会赋值（NX指令的使用）

#### 分布式锁
- 分布式锁可以通过**SET NX**指令来实现
- 当多个客户端同时尝试获取锁时，只有第一个成功获取锁的客户端会成功，其他会失败
![Alt text](pic/image.png)
- 与过期时间配合使用，Redis可以给key设置过期时间，防止数据长时间放在内存中。在分布式锁的场景中，没有设置过期时间，如果某一程序中途异常退出，就会造成死锁。因此，获取锁后，需要设置一个过期时间。即使程序异常退出，超时后会自动释放锁，别的客户端可以重新获取这个锁。
如果程序执行完毕，则使用**DEL**删除键，释放锁。
- ``set mylock client:1 NX EX 1800`` //第一个客户端获取锁，设置过期时间为1800秒
- ``set mylock client:2 NX EX 1800`` //第二个客户端获取锁，返回失败nil
- ``ttl mylock`` //查看过期时间
- ``del mylock`` //程序执行完毕，执行del命令，将锁释放
#### 过期时间
- 过期时间用于设置token，比如单点登录（SSO）
- 门户网站生成token
![Alt text](pic/image3.png)
- 验证token
![Alt text](pic/image4.png)
- 长时间没有返回，需重新登录

#### 计数器
- 计数器可用于统计网页访问量（PV）、独立用户数（UV）等
- ``MSET pv 0 uv 0``
- ``incr uv`` //进行加1操作
- ``incrby pv 3`` //进行加3操作
- ``INCR``命令将字符串值解析为整数，将其增加一，并将得到的值设置为新值
- ``INCR``操作是原子的，不会出现多个请求重复计数的问题
- ``MSET``也是原子的，多个值会被同时设置。
![Alt text](pic/image5.png)
- 其他类似命令
- DECR
- DECRBY
- INCRBYFLOAT


### List 列表
#### redis的List是通过链表（Linked List）实现的。通过不同的指令组组合可以用作栈（stack）和队列（Queue）。
- Queue（先进先出）
![Alt text](pic/image6.png)
``- LPUSH my_queue task:1 `` //往队列push两个元素
``- LPUSH my_queue task:2 ``
``- RPOP my_queue``  //输出为task:1
``- RPOP my_queue``  //输出为task:2
- Stack（先进后出）
![Alt text](pic/image7.png)
``- LPUSH unread_msg msg:1 msg:2 msg:3 msg:4 msg:5 `` //在List中放置最近发布的动态
``- LPOP unread_msg``  //查看最近发布的动态，从同一个方向pop输出为msg:5 
``- LPOP unread_msg``  //查看最近发布的动态，从同一个方向pop输出为msg:4 
``- LPUSH unread_msg msg:6 msg:7 msg:8 msg:9 msg:10 `` //在List中放置最近发布的动态
``- LTRM unread_msg 0 4`` //使用LTRM进行截断保留最新的5条数据
``- LLen unread_msg`` //查看list的长度，输出为5
``- LRANGE unread_msg 0 -1`` //查看list,从0开始到-1（列表最后）,输出如下: 
`` 1）"msg:10"``
`` 1）"msg:9"``
`` 1）"msg:8"``
`` 1）"msg:7"``
`` 1）"msg:6"``

#### 阻塞
#### 列表支持阻塞操作。如果列表为空，``BLPOP``、``BRPOP`` 等命令会处于阻塞状态，当新的元素加入时，才会返回结果。
![Alt text](pic/image8.png)
#### 索引操作
#### 我们可以通过索引去操作List中的元素。由于底层使用了链表，随着数据量增大，索引操作效率会降低。
### Set集合
- 去重
- 交集（共同关注）
- 并集


### Hash 哈希表
- 字典  

### Sort set（有序集合Zset）
- 排行榜
- 热搜

### Bitmap 位图
- 在线人数
- 精确去重统计

### HyperLogLog 基数计算
- 估算不重复元素的数量

