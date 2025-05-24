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
bool authenticateUser(const User &registeredUser, UserRole &authenticatedRole, int &attempts);