#include <bits/stdc++.h>  // Library for lower strings

#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

void _add(int n) {
  regex validation("^[0-9]+$");
  ofstream inventory;

  string name;
  string description;
  string value;
  string quantity;

  inventory.open("inventory.txt", ios::app);

  // [std::ws] is an input stream modifier which discards leading whitespace from an input stream.
  // [getline] stores characters from [cin] into [variable] until '\n' is found

  for (int i = 1; i <= n; i++) {
    cout << "ITEM #" << i << endl;
    cout << "NAME: ";
    getline(cin >> ws, name);
    cout << "DESCRIPTION: ";
    getline(cin >> ws, description);

    // [regex_mathc] indicates if there is a match between the regular expression [validation] and string

    // Validate value input
    cout << "VALUE: ";
    do {
      getline(cin >> ws, value);
      if (!regex_match(value, validation)) {
        cout << "Input error: "
             << "[" << value << "]" << endl;
        cout << "Enter only positive numbers" << endl;
      }
    } while (!regex_match(value, validation));

    // Validate quantity input
    cout << "QUANTITY: ";
    do {
      getline(cin >> ws, quantity);
      if (!regex_match(quantity, validation)) {
        cout << "Input error: "
             << "[" << quantity << "]" << endl;
        cout << "Enter only positive numbers" << endl;
      }
    } while (!regex_match(quantity, validation));

    // Lower item's atributtes
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    transform(description.begin(), description.end(), description.begin(), ::tolower);
    transform(value.begin(), value.end(), value.begin(), ::tolower);
    transform(quantity.begin(), quantity.end(), quantity.begin(), ::tolower);

    // Write item into txt file
    inventory << "-" << endl;
    inventory << "NAME: " << name << endl;
    inventory << "DESCRIPTION: " << description << endl;
    inventory << "VALUE: " << value << endl;
    inventory << "QUANTITY: " << quantity << endl;
    inventory << "-" << endl;

    cout << name << " successfully added" << endl;
  }

  inventory.close();
}

int _search(string query) {
  // Return the line number of the item that match with query, if query does not match return 0

  ifstream inventory;
  string buffer;

  int line = 1;

  inventory.open("inventory.txt");

  // [getline] stores characters from [inventory] into [buffer] until '\n' is found
  while (getline(inventory, buffer)) {
    // Search for [query in [buffer].
    // string::npos is returned if [query] is not found in [buffer] and it is
    // usually defined like so [static const size_t npos = -1] but since it is an
    // unsigned variable, thus [unsigned value = - 1] automatically makes it the
    // largest possible value for [size_t = 18446744073709551615]

    if (buffer.find("NAME: " + query) != string::npos) {
      inventory.close();
      return line;
    }
    line++;
  }

  inventory.close();

  return 0;
}

void _delete(string query) {
  // Delete item by its first line number
  ifstream inventory;
  ofstream temp;
  string buffer;
  int line = _search(query);
  int index = 1;

  // Deleting one item consists of creating two files: [inventory.txt] and [temp.txt]
  // And copy all content excepts item lines to delete from [inventory.txt] into [temp.txt]

  // To find out which lines should be omitted, it's necessary the [query] function,
  // this receive the item name to delete and return its first line number

  inventory.open("inventory.txt");
  temp.open("temp.txt");

  if (line != 0) {
    while (getline(inventory, buffer)) {
      if (index == line - 1) {
        // [getline] is executed six times to omit all item lines
        for (int i = 1; i <= 6; i++) {
          getline(inventory, buffer);
        }
      }
      temp << buffer << endl;
      index++;
    }

    inventory.close();
    temp.close();

    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    cout << "Item [" << query << "] successfully deleted" << endl;

  } else {
    cout << "Item [" << query << "] not found" << endl;
  }
}

void _print(string query) {
  // Print all items

  ifstream inventory;
  string buffer;

  int line = _search(query);
  int index = 1;

  inventory.open("inventory.txt");

  if (line != 0) {
    while (getline(inventory, buffer)) {
      if (index == line - 1) {
        for (int i = 1; i <= 6; i++) {
          cout << buffer << endl;
          getline(inventory, buffer);
        }
        break;
      }
      index++;
    }
  } else {
    cout << "Item [" << query << "] not found " << endl;
  }
  inventory.close();
}

void _list() {
  ifstream inventory;
  string buffer;

  inventory.open("inventory.txt");

  while (getline(inventory, buffer)) {
    cout << buffer << endl;
  }

  inventory.close();
}

void _backup() {
  ifstream inventory("inventory.txt");
  ofstream backup("backup.txt");
  string buffer;

  // Backup file consists of creating a new file: [backup.txt]
  // And copy all content from [inventory.txt] into [backup.txt]

  while (getline(inventory, buffer)) {
    backup << buffer << endl;
  }

  backup.close();
  inventory.close();

  cout << "Backup successfully created" << endl;
}

void _menu() {
  cout << "---------WELCOME TO THE INVENTORY---------" << endl;
  cout << "Select one of the options:" << endl;
  cout << "1. Add item" << endl;
  cout << "2. Delete item" << endl;
  cout << "3. Search item" << endl;
  cout << "4. List elements" << endl;
  cout << "5. Backup inventory" << endl;
  cout << "6. Exit" << endl;
}

int main() {
  string query;

  int option;
  int n;

  system("clear");  // Clean console not for CMD
  _menu();

  do {
    cout << "$ ";
    cin >> option;

    system("clear");  // Clean console not for CMD
    _menu();

    switch (option) {
      case 1:
        cout << "-----------------ADD ITEM-----------------" << endl;
        cout << "How many items do you want to add?" << endl;
        do {
          cin >> n;
          if (n <= 0) {
            cout << "Please enter a valid number" << endl;
          }
        } while (n <= 0);
        _add(n);
        cout << "------------------------------------------" << endl;
        break;
      case 2:
        cout << "-----------------DELETE ITEM--------------" << endl;
        cout << "Query: ";
        cin >> query;
        _delete(query);
        cout << "------------------------------------------" << endl;
        break;
      case 3:
        cout << "-----------------SEARCH ITEM--------------" << endl;
        cout << "Query: ";
        cin >> query;
        _print(query);
        cout << "------------------------------------------" << endl;
        break;
      case 4:
        cout << "-----------------SHOW LIST----------------" << endl;
        _list();
        cout << "------------------------------------------" << endl;
        break;
      case 5:
        cout << "-----------------CREATE BACKUP------------" << endl;
        _backup();
        cout << "------------------------------------------" << endl;
        break;
      case 6:
        cout << "--------------PROGRAM FINISHED------------" << endl;
        break;
      default:
        cout << "------------------------------------------" << endl;
        cout << "Enter a valid option" << endl;
        cout << "------------------------------------------" << endl;
        break;
    }

  } while (option != 6);

  return 0;
}