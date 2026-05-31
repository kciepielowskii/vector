#include <iostream>
#include <string>
#include <exception>
#include <unordered_map>
#include <list>
#include <algorithm>


using namespace std;
// LRU cache - Least Recently Used cache

// cache(string id, string value) - zapisuje std::string w cache'u
// get(string id)   			  - wyciąga std::string z cache
// size()                         - obecny rozmiar cache'u
// int max_size 				  - maksymalny rozmiar cache'u (suma długości std::string)

// sprawdzanie, czy pozostało miejsce podczas cache()
// usunąć elementy z list, jeżeli brakuje miejsca


void test(string expected, string value) {
    if (expected != value) {
        cout << "expected: " << expected << "\nvalue: " << value << "\n\n";
    }
}

// void test(bool expected, bool value) {
//     if (expected != value) {
//         cout << "expected: " << expected << "\nvalue: " << value << "\n\n";
//     }
// }

void test(size_t expected, size_t value) {
    if (expected != value) {
        cout << "expected: " << expected << "\nvalue: " << value << "\n\n";
    }
}


class Cache {
    size_t max_size = 8;
    size_t size_ = 0;

    //list<string> list_;               // id
    list<pair<string, string>> list_;   // id, value

    //map<string, string> map_;                 // id -> value
    unordered_map<string, list<pair<string, string>>::iterator> map_;   // id -> iterator

public:
    Cache(long long max_size) {
        if (max_size <= 0) {
            throw runtime_error("max_size must be > 0");
        }
        this->max_size = max_size;
    }

    void cache(string id, string value) {
        if (value.length() > max_size) {
            cout << "Błąd! Przekroczono rozmiar max." << endl;
            return;
        }
        auto it = map_.find(id); // O(log n)
        if (it != map_.end()) {    // O(1)
            size_ -= it->second->second.length();
            list_.erase(it->second);    // O(1)
            map_.erase(it);        // O(log n)
        }
        while (size_ + value.length() > max_size) {
            pair<string, string> temp = list_.front();
            size_ -= temp.second.length();
            list_.erase(list_.begin());
            map_.erase(temp.first);
        }
        list_.push_back({id, value});
        map_[id] = prev(list_.end());
        size_ += value.length();
    }

    string get(string id) {
        auto it = map_.find(id);
        if (it != map_.end()) {
            pair<string, string> temp = *it->second;
            // list_.erase(it->second); // O(n)     // było to
            // list_.push_back(temp);
            list_.splice(list_.end(), list_, it->second);       // dodałem to
            //map_[id] = list_.end()--;     // było to
            map_[id] = prev(list_.end());       // dodałem to
            return temp.second;
        }
        return "";
    }

    void remove(string id) {
        auto it = map_.find(id);
        if (it != map_.end()) {
            size_ -= it->second->second.length();
            list_.erase(it->second);
            map_.erase(it);
        }
    }

    size_t size() const {
        return size_;
    }

    void print() const {
        if (map_.empty()) {
            cout << "List is empty" << endl;
        } else {
            for (const auto &it : map_) {
                cout << "ID: " << it.first << " | Value: " << it.second->second << endl;
            }
        }
        cout << '\n';
    }
};

void operator+=(Cache ch, pair<string, string> p) {
    ch.cache(p.first, p.second);
}

void operator-=(Cache ch, string id) {
    ch.remove(id);
}

// cache += pair<string, string>(key, val)

int main()
{
    /*
    PRZED:
        get() - O(n)
        cache() - O(n)
        zwolnienie miejsca = O(n)
        duplikat - O(n)

    PO 1:
        get() - O(log n)
        cache() - O(n)
        zwolnienie miejsca = O(n)
        duplikat - O(n)

    PO 2:
        get() - O(log n)
        cache() - O(log n)
        zwolnienie miejsca = O(log n)
        duplikat - O(n)

    PO 3:
        get() - O(log n)
        cache() - O(log n)
        zwolnienie miejsca = O(log n)
        duplikat - O(log n)

    PO 4:
        get() - O(1)
        cache() - O(1)
        zwolnienie miejsca = O(1)
        duplikat - O(1)
     */

    // splice - zastąpić niektóre metody tą metodą get,push back

    Cache ch1 (8);

    test(0, ch1.size());
    ch1.cache("X", "test");
    test(4, ch1.size());
    ch1.cache("Y", "abcd");
    test(8, ch1.size());
    ch1.cache("Z", "xyzw");
    test(8, ch1.size());

    ch1.cache("test", "value");
    test("value", ch1.get("test"));

    ch1 += pair<string, string>("test2", "test2");

    int integer = 5;
    integer += 3;
    test(8, integer);

    // Cache ch2 (0);

    // Cache ch3 (8); // dlaczego nie wyrzuca błędu? Uwaga: typy

    // wektory - algebra liniowa

    ch1 -= string("test2");

    ch1.print();

    int liczba = 5;
    liczba -= 3;
}