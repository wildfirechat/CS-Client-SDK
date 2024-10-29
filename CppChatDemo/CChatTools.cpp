#include "stdafx.h"
#include "CChatTools.h"


void CChatTools::Init(CIMImpl *p)
{
  if (m_pIMImpl == NULL)
  {
    m_pIMImpl = p;
  }

  if (m_pIMImpl == NULL)
    return;

  m_pIMImpl->Init();
}

bool CChatTools::OnLoginBtn(std::string userid, std::string usersig)
{
  return m_pIMImpl->Login(userid, usersig);
}

bool CChatTools::OnLogoutBtn()
{
  return m_pIMImpl->Logout();
}

bool CChatTools::isLogined()
{
  return m_pIMImpl->isLogined();
}

std::string CChatTools::GetClientId()
{
  return m_pIMImpl->GetClientId();
}
