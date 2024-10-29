#pragma once
#include<string>


class CIMImpl
{
public:
  CIMImpl() {}

  virtual void Init() = 0;
  virtual bool Login(std::string userid, std::string usersig) = 0;
  virtual bool Logout() = 0;
  virtual bool isLogined() = 0;
  virtual std::string GetClientId() = 0;
};

