// include/auth.h
#pragma once

#include <string>

enum class UserRole
{
    User,
    Admin
};

struct User
{
    std::string username;
    std::string password;
    UserRole role;
};

User createNewAccount();

// authenticateUser fonksiyonunun prototipi güncellendi: attempts parametresi eklendi
bool authenticateUser(const User &registeredUser, UserRole &authenticatedRole, int &attempts);