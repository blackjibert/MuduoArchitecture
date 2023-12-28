## Docker和虚拟机的不同
#### 1、启动速度不同
- docker：启动 Docker 相当于启动宿主操作系统上的一个进程，启动速度属于秒级别。

- 虚拟机：启动虚拟机需要先启动虚拟机的操作系统，再启动应用，这个过程非常慢，通常需要几分钟。

#### 2、占用资源不同
- docker：Docker 只是一个进程，只需要将应用以及相关的组件打包，在运行时占用很少的资源，一台机器可以开启成千上万个 Docker。容器运行时，与宿主机共享操作系统内核，容器在inux内核层面 (使用 Cgroups 和 namespaces) 来实现进程间的隔离。
- 虚拟机：虚拟机是一个完整的操作系统，需要占用大量的磁盘、内存和 CPU 资源，一台机器只能开启几十个的虚拟机。

#### 3、隔离性不同
- docker：docker隔离性更弱，docker属于进程之间的隔离。
- 虚拟机：虚拟机隔离性更强，可实现系统级别隔离。

#### 4、安全性不同
- docker：docker的安全性更弱。Docker的租户root和宿主机root等同，一旦容器内的用户从普通用户权限提升为root权限，它就直接具备了宿主机的root权限，进而可进行无限制的操作，容器至今还没有任何形式的硬件隔离，这使得容器容易受到攻击。

- 虚拟机：虚拟机租户root权限和宿主机的root虚拟机权限是分离的，并且虚拟机利用如Intel的VT-d和VT-x的ring-1硬件隔离技术，这种隔离技术可以防止虚拟机突破和彼此交互。

#### 5、可管理性不同
- docker：docker的集中化管理⼯具还不算成熟。

- 虚拟机：各种虚拟化技术都有成熟的管理⼯具，例如VMware vCenter提供完备的虚拟机管理能⼒。

#### 6、高可用和可恢复性
- docker：docker对业务的⾼可⽤⽀持是通过快速重新部署实现的。

- 虚拟机：虚拟化具备负载均衡，⾼可⽤，容错，迁移和数据保护等经过⽣产实践检验的成熟保障机制，VMware可承诺虚拟机99.999%⾼可⽤，保证业务连续性。

#### 7、创建、删除速度不同
- docker：Docker容器创建是秒级别的，Docker的快速迭代性，决定了⽆论是开发、测试、部署都可以节约⼤量时间。

- 虚拟机：虚拟化创建是分钟级别的。

#### 8、交付部署不同
- docker：Docker在Dockerfile中记录了容器构建过程，可在集群中实现快速分发和快速部署。

- 虚拟机：虚拟机可以通过镜像实现环境交付的⼀致性，但镜像分发⽆法体系化。

## Docker
##### Docker是一个开源的应用容器引擎，由于docker影响巨大，今天也用“Docker”指代容器化技术。

### Docker优势

#### 一键部署，开箱即用
- 容器使用基于image镜像的部署模式，image中包含了运行应用程序所需的一切: 代码运行时、系统工具、系统库和配置文件。无论是单个程序还是多个程序组成的复杂服务，或者分布式系统，都可以使用 ```docker run``` 或 ```docker compose up``` 命令一键部署，省去了大量搭建、配置环境、调试和排查错误的时间。
#### 一次打包，到处运行
- Docker 为容器创建了行业标准，使容器成为了软件交付过程中的一种标准化格式，将软打包成容器镜(image)，能够使软件在不同环境下运行一致，应用程序可以快速可靠地从一个环境移植到另外一个环境，并确保在所有的部署目标 (例如开发、测试、生产环境)上都按预期运行，从而避免了“在我电脑上是好的，怎么到你那却不能用了?”的问题。

### Docker安装
#### 安装环境: CentOS7.3+
- 如果之前安装了旧版docker，请先删除
```sudo yum remove docker ocker-client docker-client-latest docker-common docker-latest docker-latest-logrotate docker-logrotate docker-engine```
#### 安装仓库
- ```sudo yum install -y yum-utils```
- 添加源 ```sudo yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo```

#### 安装Docker
- ```sudo yum install docker-ce docker-ce-cli containerd.io docker-compose-plugin```

#### 启动docker
- ```sudo systemctl start  docker```
- ```sudo docker run hello-word```


#### 配置国内镜像
- 配置文件在```/etc/docker```，新建daemon.json
- ```{```
```"registry-mirrors":[```
```"https://registry.docker-cn.com",```
```"http://hub-mirror.c.163.com",```
```"https://fsp2sfpr.mirror.aliyuncs.com/"]```
```}```
#### 然后重启，配置开机启动
- ```sudo system&tl restart docker```
- ```sudo systemctl enable docker``` //docker开机启动
- ```sudo systemctl enable containerd```//containerd开机启动

### docker pull 命令
![Alt text](pic/image1.png)
- 运行镜像可以产生容器
- 如:```docker pull nginx:1.22``` //默认为最新版本
- 查看本地镜像，```docker images``` 
- 查看运行中的镜像命令，```docker ps``` 
- 查看启动日志命令，```docker logs 容器名称或者id``` 

#### 公开端口(-p)
```docker run --name some-nginx -d -p 8080:80 nginx:1.22```
- some-nginx为容器的名称，-d表示容器在后台运行。-p表示将容器的端口80绑定到宿主机的端口8080。
- 默认情况下，容器无法通过外部网络访问。需要使用-p参数将容器的端口映射到宿主机端口，才可以通过宿主机IP进行访问。浏览器打开 http://192.168.56.106:8080
- ```docker stop some-nginx```  //停止容器
- ```docker ps -a``` //查看所有的容器
- ```docker rm 容器id或者名称``` //删除容器
- ```-p 8080-8090:8080-8090``` //公开端口范围，前后必须对应
- ```-p 192.168.56.106:8080:80``` //如果宿主机有多个ip，可以指定绑定到哪个ip

#### docker run开箱即用
- ```docker inspect some-mysql（容器名称）``` //查看容器的信息


#### 前台交互运行
- 创建一个新的容器，使用mysql客户端```docker run -it --rm mysql:5.7 mysgl -h172.17.0.2 -uroot -p``` 
- ```-it```使用交互模式，可以在控制台里输入、输出 
- ```--rm```在容器退出时自动删除容器。一般在使用客户端程序时使用此参数如果每次使用客户端都创建一个新的容器，这样将占用大量的系统空间```mysql -h172.17.0.2 -uroot -p``` 表示启动容器时执行的命令。
- 例如: docker run -it --rm mysql:5.7 mysql -h172.17.0.2 -uroot -p 
- ```docker exec```
- 在运行的容器中执行命令，一般配合```-it``` 参数使用交互模式
- ```docker exec -it db-mysql /bin/bash```

### docker 网络
