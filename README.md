# 野火Windows平台 C# 和 Cpp 客户端SDK
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
