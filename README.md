# 野火Windows平臺 C# 和 Cpp 客戶端
本工程包含野火 Windows平臺上的C# 和C++ 原生客戶端及一個簡單的測試demo。本客戶端具有完整的功能，且接口命名和使用方式都與移動端保持一致，可以和移動端相互藉鑒和參考。本工程依賴野火協議棧，野火協議棧是收費的，需要找到官方進行購買。

## 各個工程的簡介
項目空間内有C++和C#的項目，互相沒有關係，如果您需要使用C++的SDK只看C++部分即可；如果您需要使用C#的SDK只看C#部分即可。

#### C++ 工程
* CppChatClient C++的IMClient，提供所有功能接口，在項目實際使用時調用這個工程的函數。

* CppChatDemo C++ IMClient的測試功能程序，測試IMClient的各個接口，不具備IM的UI。

#### C# 工程
* ClrChatClient Clr的轉接工程，用於協議棧C++到IMClient C#的映射。

* CsChatClient C#的IMClient，提供所有功能接口，在項目實際使用時調用這個工程的函數。依賴於ClrChatClient.

* CsChatDemo C# IMClient的測試功能程序，測試IMClient的各個接口，不具備IM的UI。

## 協議棧説明
協議棧在```${ProjectDir}\CS-Client-SDK\proto```目錄下，分別包含三個目錄```lib```, ```dll```, ```include```。在集成到自由項目時，除了添加對應的ChatClient的依賴外（C#還要添加Clr的工程），還要添加對應的dll到執行目錄。

## 執行
打開 ```${ProjectDir}\CS-Client-SDK\CS-Client-SDK.sln```, 選擇 ```CsChatDemo``` 工程，選擇執行。

## 申請體驗SDK
打開工程后，可以輸入電話號碼和```supercode```，協議棧默認使用的是官方地址，因此不能提供```supercode```進程測試，必須自己部署一套服務，然後向官方申請體驗協議棧。這樣您就可以使用自己的服務進行測試和開發。
