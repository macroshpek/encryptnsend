#include <iostream>
#include <fstream>

class encdec {
    int m_key;
    // File name to be encrypt
    std::string m_filePath;
    std::string m_fileName;

public:
    void encrypt();
    void decrypt();
    void setKey(std::istream &in);
    void setFilePath(std::istream &in);
    void parseFileName();
};

void encdec::parseFileName()
{
    size_t lastIndex = m_filePath.rfind("\\");
    m_fileName = m_filePath.substr(lastIndex);
}

void encdec::setKey(std::istream &in)
{
    in >> this->m_key;
}

void encdec::setFilePath(std::istream& in)
{
    in >> this->m_filePath;
}

// Definition of encryption function
void encdec::encrypt()
{
    std::fstream fin, fout;
    fin.open(m_filePath, std::fstream::in);
    fout.open("encrypted.txt", std::fstream::out);

    if (fin.is_open()) {
        char c;
        while (fin >> std::noskipws >> c) {
            int temp = (c + m_key);

            fout << (char)temp;
        }
    }

    fin.close();
    fout.close();
}

// Definition of decryption function
//it's just caesar encryption
void encdec::decrypt()
{
    std::fstream fin;
    std::fstream fout;
    fin.open(m_filePath, std::fstream::in);
    fout.open("decrypted.txt", std::fstream::out);
    if (fin.is_open()) {
        char c;
        while (fin >> std::noskipws >> c) {

            // Remove the key from the
            // character
            int temp = (c - m_key);
            fout << (char)temp;
        }
    }
    else
    {
        std::cout << "File does not open";
    }

    fin.close();
    fout.close();
}

// Driver Code
int main()
{
    encdec cryptographer;

    std::cout << "Enter the path to file: ";
    cryptographer.setFilePath(std::cin);

    std::cout << "Enter the cryptographic key: ";
    cryptographer.setKey(std::cin);

    std::string encdec;
    std::cout << "Enter \"encrypt\" or \"decrypt\": ";
    std::cin >> encdec;

    std::string recipient;
    std::cout << "Enter the recipient\'s email: ";
    std::cin >> recipient;

    if (encdec == "encrypt")
    {
        cryptographer.encrypt();
        system((std::string("script.py") + " " + recipient + " " + "encrypted.txt").c_str());
    }
    else if (encdec == "decrypt")
    {
        cryptographer.decrypt();
        system((std::string("script.py") + " " + recipient + " " + "decrypted.txt").c_str());
    }
    else
    {
        std::cout << "Undefined command";
        std::exit(0);
    }
}

