## 野火IM解决方案

野火IM是专业级即时通讯和实时音视频整体解决方案，由北京野火无限网络科技有限公司维护和支持。

主要特性有：私有部署安全可靠，性能强大，功能齐全，全平台支持，开源率高，部署运维简单，二次开发友好，方便与第三方系统对接或者嵌入现有系统中。详细情况请参考[在线文档](https://docs.wildfirechat.cn)。

主要包括一下项目：

| [GitHub仓库地址(主站)](https://github.com/wildfirechat)      | [码云仓库地址(镜像)](https://gitee.com/wfchat)        | 说明                                                                                      | 备注                                           |
| ------------------------------------------------------------ | ----------------------------------------------------- | ----------------------------------------------------------------------------------------- | ---------------------------------------------- |
| [android-chat](https://github.com/wildfirechat/android-chat) | [android-chat](https://gitee.com/wfchat/android-chat) | 野火IM Android SDK源码和App源码                                                           | 可以很方便地进行二次开发，或集成到现有应用当中 |
| [ios-chat](https://github.com/wildfirechat/ios-chat)         | [ios-chat](https://gitee.com/wfchat/ios-chat)         | 野火IM iOS SDK源码和App源码                                                               | 可以很方便地进行二次开发，或集成到现有应用当中 |
| [pc-chat](https://github.com/wildfirechat/pc-chat)           | [pc-chat](https://gitee.com/wfchat/pc-chat)           | 基于[Electron](https://electronjs.org/)开发的PC平台应用                                   |                                                |
| [web-chat](https://github.com/wildfirechat/web-chat)         | [web-chat](https://gitee.com/wfchat/web-chat)         | Web平台的Demo, [体验地址](http://web.wildfirechat.cn)                                     |                                                |
| [wx-chat](https://github.com/wildfirechat/wx-chat)           | [wx-chat](https://gitee.com/wfchat/wx-chat)           | 微信小程序平台的Demo                                                                      |                                                |
| [server](https://github.com/wildfirechat/server)             | [server](https://gitee.com/wfchat/server)             | IM server                                                                                 |                                                |
| [app server](https://github.com/wildfirechat/app_server)     | [app server](https://gitee.com/wfchat/app_server)     | 应用服务端                                                                                |                                                |
| [robot_server](https://github.com/wildfirechat/robot_server) | [robot_server](https://gitee.com/wfchat/robot_server) | 机器人服务端                                                                              |                                                |
| [push_server](https://github.com/wildfirechat/push_server)   | [push_server](https://gitee.com/wfchat/push_server)   | 推送服务器                                                                                |                                                |
| [docs](https://github.com/wildfirechat/docs)                 | [docs](https://gitee.com/wfchat/docs)                 | 野火IM相关文档，包含设计、概念、开发、使用说明，[在线查看](https://docs.wildfirechat.cn/) |                                                |  |


本工程包含野火 Windows平台上的 C# 和 C++ 原生客户端SDK及一个简单的测试Demo。客户端SDK具有跟移动端SDK完全一样的功能（因为本质上使用的是同一个协议栈）和一样的接口定义，可以和移动端互相借鉴和参考。本工程依赖野火协议栈，野火协议栈是收费的，需要购买才可以使用。

## 各个工程的简介
项目空间内有 C++ 和 C# 的项目，互相没有关系。如果您需要使用C++的SDK只需要看C++部分即可；如果您需要使用C#的SDK只看C#部分即可。

#### C++ 工程
* CppChatClient C++的IMClient，提供所有功能接口，在项目实际使用时使用这个工程的函数。

* CppChatDemo C++ IMClient的测试功能程序，测试IMClient的各个接口，不具有IM的UI。

#### C# 工程
* ClrChatClient Clr的转接工程，用于协议栈C++到IMClient C#的映射。

* CsChatClient C#的IMClient，提供所有功能接口，在项目实际使用这个工程的函数。依赖于ClrChatClient.

* CsChatDemo C# IMClient的测试功能程序，测试IMClient的各个接口，不具有IM的UI。

## 协议栈说明
协议栈在```${ProjectDir}\CS-Client-SDK\proto```目录下，分別包含三个目录```lib```, ```dll```, ```include```。在集成到自由项目时，除了添加对应的ChatClient的依赖外（C#还要添加Clr的工程），还要添加对应的dll到执行目录。

## 执行
打开 ```${ProjectDir}\CS-Client-SDK\CS-Client-SDK.sln```, 选择 ```CsChatDemo``` 工程，选择执行。

## 申請體驗SDK
打开工程后，可以输入电话号码和```supercode```，协议栈默认使用的是官方地址，因此不能提供```supercode```进行测试，必須自己部署一套服务，然後向官方申請体验协议栈。这样您就可以使用自己的服务进行测试和开发。测试时注意把appserver地址改为自己的地址。
