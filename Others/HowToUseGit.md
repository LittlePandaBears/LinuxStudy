很粗略的介绍一下git的用法
---

 - 第一步 安装git

    我们使用的都是debian系的Linux, 安装命令为`sudo apt-get install git`

 - 第二步 从github上克隆项目
    
     - 在github的我们项目的首页， 有一个 clone or download 的按钮， 点击之后复制链接

     - 打开终端， 将目录转到在自己想要存放项目的地方, 输入命令 `git clone xxx.git`

     - 克隆项目成功

 - 提交代码
    - 添加到本地暂存区的的命令 `git add path`，  path 为有更改的文件或者路径
    - 本地提交命令 `git commit "commit msg"`， 提交时， 尽量写上提交说明， 少用无意义的语句
    - 提交到github， 首先先同步， 同步的命令为`git pull`, 同步完成之后， 提交， 命令为`git push origin master`. （我们的项目组并不需要去新建分支, 直接在主分支上提交就行）
