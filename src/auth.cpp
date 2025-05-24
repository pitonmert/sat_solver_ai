#include "../include/auth.h"
#include <iostream>
#include <limits>

// Kullanıcıdan yeni hesap oluşturma fonksiyonu
User createNewAccount()
{
    User newUser;
    std::cout << "Yeni hesap olusturma:" << std::endl;
    std::cout << "Kullanici adi girin: ";
    std::cin >> newUser.username;
    std::cout << "Sifre girin: ";
    std::cin >> newUser.password;
    newUser.role = UserRole::User;
    std::cout << "Hesap basariyla olusturuldu!" << std::endl;
    return newUser;
}

// Kullanıcı doğrulama fonksiyonu
bool authenticateUser(const User &registeredUser, UserRole &authenticatedRole, int &attempts)
{
    std::string enteredUsername;
    std::string enteredPassword;
    while (attempts > 0)
    {
        std::cout << "\nGiris yapma:" << std::endl;
        std::cout << "Kullanici adi: ";
        std::cin >> enteredUsername;
        std::cout << "Sifre: ";
        std::cin >> enteredPassword;
        // Kullanıcı adı ve şifre kontrolü
        if (enteredUsername == registeredUser.username && enteredPassword == registeredUser.password)
        {
            std::cout << "Giris basarili!" << std::endl;
            authenticatedRole = registeredUser.role;
            return true;
        }
        else
        {
            attempts--;
            std::cout << "Hatali kullanici adi veya sifre. Kalan deneme hakki: " << attempts << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    authenticatedRole = UserRole::User;
    return false;
}