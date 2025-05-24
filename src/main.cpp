// src/main.cpp
#include "dpll_solver.h"
#include "visualizer.h"
#include "cnf_parser.h"
#include "auth.h"
#include <iostream>
#include <string>
#include <set>
#include <limits>

int main(int argc, char *argv[])
{
    User registeredUser = createNewAccount();
    UserRole authenticatedRole;
    int loginAttempts = 3; // İlk giriş deneme hakkı

    bool loginSuccess = false;

    while (!loginSuccess)
    {
        if (!authenticateUser(registeredUser, authenticatedRole, loginAttempts))
        {
            // Kimlik doğrulama başarısız ve deneme hakkı bitti
            if (loginAttempts == 0)
            {
                std::cout << "Tum deneme haklariniz bitti. Admin girisi deneniyor..." << std::endl;

                // Varsayılan Admin hesabı
                User adminUser;
                adminUser.username = "admin";
                adminUser.password = "123";
                adminUser.role = UserRole::Admin;

                UserRole adminAuthenticatedRole;
                int adminLoginAttempts = 1; // Admin için tek deneme hakkı
                if (authenticateUser(adminUser, adminAuthenticatedRole, adminLoginAttempts))
                {
                    std::cout << "Admin olarak giris yaptiniz." << std::endl;
                    // Admin'den yeni deneme hakkı al
                    int extraAttempts;
                    std::cout << "Kullaniciya kac ek deneme hakki vermek istersiniz? ";
                    std::cin >> extraAttempts;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Tamponu temizle

                    loginAttempts = extraAttempts; // Kullanıcıya yeni deneme haklarını ver
                    std::cout << "Kullaniciya " << extraAttempts << " ek deneme hakki verildi." << std::endl;
                    // Tekrar kullanıcı giriş döngüsüne dönmek için loginSuccess false kalır
                }
                else
                {
                    std::cerr << "Admin girisi basarisiz. Program sonlandiriliyor." << std::endl;
                    return 1; // Admin girişi de başarısız olursa programı kapat
                }
            }
            else
            {
                // Deneme hakkı var ama giriş başarısız, döngü devam edecek
                // Bu durum aslında authenticateUser içindeki döngü tarafından yönetiliyor.
                // Buraya kod ulaşmaz, eğer authenticateUser'dan false dönüyorsa deneme hakkı bitmiş demektir.
            }
        }
        else
        {
            loginSuccess = true; // Giriş başarılı oldu
        }
    }

    // Kimlik doğrulama başarılı ise, kullanıcının rolünü yazdır (isteğe bağlı)
    if (authenticatedRole == UserRole::Admin)
    {
        std::cout << "Admin olarak giris yaptiniz." << std::endl;
    }
    else
    {
        std::cout << "Normal kullanici olarak giris yaptiniz." << std::endl;
    }

    CNFFormula f;
    std::string input_choice;
    bool valid_choice = false;

    if (argc > 1)
    {
        std::string filename = argv[1];
        try
        {
            std::cout << "Dosya okunuyor: " << filename << std::endl;
            f = parseCNF(filename);
        }
        catch (const std::exception &ex)
        {
            std::cerr << "Hata: " << ex.what() << std::endl;
            return 1;
        }
    }
    else
    {
        while (!valid_choice)
        {
            std::cout << "Giris yontemini secin (dosya/terminal): ";
            std::cin >> input_choice;

            if (input_choice == "dosya" || input_choice == "terminal")
            {
                valid_choice = true;
            }
            else
            {
                std::cerr << "Gecersiz secim. Lutfen 'dosya' veya 'terminal' yazin." << std::endl;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        try
        {
            if (input_choice == "dosya")
            {
                std::cerr << "Dosya girisi secildi ancak dosya yolu belirtilmedi." << std::endl;
                std::cerr << "Kullanim: " << argv[0] << " <cnf dosya yolu>" << std::endl;
                return 1;
            }
            else
            {
                std::cout << "CNF problemini terminalden girin (ornek: p cnf 3 2\\n1 2 0\\n-1 3 0):" << std::endl;
                std::cout << "Girisi bitirmek icin Ctrl+D (Linux/macOS) veya Ctrl+Z (Windows) tuslarina basin." << std::endl;
                f = parseCNFFromStream(std::cin);
            }
        }
        catch (const std::exception &ex)
        {
            std::cerr << "Hata: " << ex.what() << std::endl;
            return 1;
        }
    }

    std::cout << "---- CNF Okundu ----" << std::endl;

    std::set<int> solution;
    std::set<int> initial_assigned;

    bool result = DPLL(f, initial_assigned, solution);

    if (result)
    {
        std::cout << "Cozum bulundu!" << std::endl;
        printSolution(f, solution);
    }
    else
    {
        std::cout << "Cozum yok (UNSAT)." << std::endl;
    }

    std::cout << "Program sorunsuz sona erdi (main'den cikiyor)." << std::endl;
    std::cout << std::flush;

    return 0;
}