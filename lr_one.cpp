using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

string decimal_to_binary(int decimal) {
    if (decimal == 0) return "0";

    vector<string> binary;

    while (decimal > 0) {
        binary.push_back(to_string(decimal % 2));
        decimal = decimal / 2;
    }

    reverse(binary.begin(), binary.end());

    string result = "";

    for (int i = 0; i < binary.size(); i++) {
        result += binary[i];
    }

    return result;
}

vector<int> get_octets(string ip) {
    vector<int> octet;
    string temp = "";
    string numbers = "0123456789.";

    for (const char c : ip) {

        if (numbers.find(c) == string::npos) break;
        if (c != '.') temp += c;
        if (c == '.') {
            octet.push_back(stoi(temp));
            temp = "";
        }
    }

    if (!temp.empty()) {
        octet.push_back(stoi(temp));
        temp = "";
    }

    return octet;
}

bool validate_adress(string ip) {

    int test_one = 0;

    for (const char c: ip) {
        if (c == '.') test_one++;
    }

    if (test_one != 3) return 0;

    vector<int> octets = get_octets(ip);

    if (octets.size() != 4) return 0;

    for (const int octet : octets) {
        if (octet > 255 || octet < 0) {
            return 0;
        }
    }

    if (octets[0] == 0) return 0;

    return 1;
}

string check_adress_class(int octet) {
    if (octet >= 1 && octet <= 126) return "Class A";
    if (octet == 127) return "Reserve";
    if (octet >= 128 && octet <= 191) return "Class B";
    if (octet >= 192 && octet <= 223) return "Class C";
    if (octet >= 224 && octet <= 239) return "Class D";
    if (octet >= 240 && octet <= 255) return "Class E";
    else return "Unknown";
}

string amount_of_users(string adress_class) {
    if (adress_class == "Class A") return "16.777.214";
    if (adress_class == "Class B") return "65.534";
    if (adress_class == "Class C") return "254";
    else return "Unknown";
}

int main()
{
    string ip;
    
    while (!validate_adress(ip)) {
        cout << "Enter some ip like 127.0.0.1: ";
        cin >> ip;
    }

    vector<int> octets = get_octets(ip);

    string binary_ip = "";
    int point_count = 0;
    for (const int octet : octets) {
        binary_ip += decimal_to_binary(octet);
        if (point_count < 3) {
            point_count++;
            binary_ip += ".";
        }
    }
    cout << "Binary ip (" << ip << ") looks like: " << binary_ip << endl;

    string adress_class = check_adress_class(octets[0]);
    string users = amount_of_users(adress_class);
    cout << "Network class - \"" << adress_class << "\", maximum amount of hosts: " << users << endl;
}
