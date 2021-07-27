#include "move.h"
#include "move vs copy.h"

void Print(const string& book_list_name, const vector<string>& book_list) {
    cout << book_list_name << endl;
    for (const string& s : book_list) {
        cout << s << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    TestIntVector();
    TestAvoidsCopying();
    TestSplitting();

    vector<string> my_books = { "Chapaev i pustota"s, "Nepobedimoe solnce"s, "Generation P"s, "Jizn' nasekomyh"s,
                              "Taynie vidy na goru Fudzi"s };
    vector<string> given_to_read(my_books.begin(), my_books.begin() + 2);
    vector<string> presented(make_move_iterator(my_books.begin() + 2), make_move_iterator(my_books.end()));

    Print("my_books", my_books);
    cout << endl;
    Print("given_to_read", given_to_read);
    cout << endl;
    Print("presented", presented);
}