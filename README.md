# HdyStudentManager


这是一个基于Qt和C++的道观管理系统

Qt默认不支持MySQL,所以要自己编译驱动，步骤如下：
1.进入Qt安装目录，找到Src\qtbase\src\plugins\sqldrivers
2.添加list(APPEND CMAKE_PREFIX_PATH "D:/Users/MySQL8.4.7")
3.右击CmakeLists.txt,选择生成，最后将out文件夹下的mysql扩展复制到Qt安装目录下的plugins\sqldrivers文件夹中


运行方法：
1.下载项目
2.在项目目录下运行：qmake
3.运行：make
4.运行：./HdyStudentManager

目录树结构：
HdyStudentManager:主目录{
    一.Common:公共类  {	 
           1.Base:基础类
           2.Notify:提示类
           3.Utils:工具类
           4.Widgets:窗口类
    }
    
    二.Resource:资源文件

    三.Dao:数据库访问对象{
           1.UserDao:用户数据访问对象
           2.DatabaseMap:数据库映射
           3.SqlConnection:数据库连接
    }

    四.Entity:实体{
           
    }

}
类列表：
1.LoginPage:登录界面
2.NotifyBox:提示框
3.NotifyManager:提示框管理
4.MsgBox:消息框
5.ClickLabel:点击标签
6.CaptchaMaker:验证码
7.Coating:遮蔽层