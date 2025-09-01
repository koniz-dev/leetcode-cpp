# 🚀 C++ I/O Operations: Complete Guide

## 📚 Overview

Input/Output (I/O) operations are fundamental for any program that needs to interact with users or external data. C++ provides a powerful and flexible I/O system through streams that can handle console I/O, file I/O, and string I/O.

## 🎯 Key Concepts

### Streams in C++
- **Streams**: Abstract data sources and destinations
- **Input streams**: Read data (istream, ifstream, istringstream)
- **Output streams**: Write data (ostream, ofstream, ostringstream)
- **Buffered I/O**: Efficient data transfer with buffering

### Stream Hierarchy
```
ios_base
├── ios
    ├── istream (input)
    │   ├── ifstream (file input)
    │   └── istringstream (string input)
    └── ostream (output)
        ├── ofstream (file output)
        └── ostringstream (string output)
```

## 🔧 Console I/O

### Basic Input/Output
```cpp
#include <iostream>
using namespace std;

int main() {
    // Output to console
    cout << "Hello, World!" << endl;
    
    // Input from console
    int number;
    cout << "Enter a number: ";
    cin >> number;
    
    // Multiple values input
    string name;
    int age;
    cout << "Enter name and age: ";
    cin >> name >> age;
    
    // Output with formatting
    cout << "Name: " << name << ", Age: " << age << endl;
    
    return 0;
}
```

### Stream Manipulators
```cpp
#include <iomanip>

int main() {
    int num = 42;
    double pi = 3.14159;
    
    // Set field width and alignment
    cout << setw(10) << left << "Number:" << num << endl;
    cout << setw(10) << left << "Pi:" << pi << endl;
    
    // Set precision for floating point
    cout << setprecision(3) << fixed << pi << endl;  // 3.142
    
    // Set base for integers
    cout << "Decimal: " << num << endl;
    cout << "Hex: " << hex << num << endl;      // 2a
    cout << "Octal: " << oct << num << endl;    // 52
    cout << "Binary: " << bitset<8>(num) << endl;  // 00101010
    
    // Reset to decimal
    cout << dec << num << endl;
    
    return 0;
}
```

### Input Validation
```cpp
int getValidNumber() {
    int number;
    
    while (!(cin >> number)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();  // Clear error flags
        cin.ignore(10000, '\n');  // Clear input buffer
    }
    
    return number;
}

int main() {
    cout << "Enter a number: ";
    int num = getValidNumber();
    cout << "You entered: " << num << endl;
    
    return 0;
}
```

### Line-based Input
```cpp
int main() {
    string line;
    
    // Read entire line
    cout << "Enter a line: ";
    getline(cin, line);
    cout << "You entered: " << line << endl;
    
    // Mix cin and getline (be careful!)
    int age;
    string name;
    
    cout << "Enter age: ";
    cin >> age;
    
    cin.ignore();  // Clear newline from buffer
    
    cout << "Enter name: ";
    getline(cin, name);
    
    cout << "Age: " << age << ", Name: " << name << endl;
    
    return 0;
}
```

## 📁 File I/O

### File Output (Writing)
```cpp
#include <fstream>

int main() {
    // Open file for writing (overwrites existing file)
    ofstream outFile("output.txt");
    
    if (outFile.is_open()) {
        // Write data to file
        outFile << "Hello, File!" << endl;
        outFile << "This is line 2" << endl;
        outFile << "Number: " << 42 << endl;
        
        // Close file
        outFile.close();
        cout << "File written successfully" << endl;
    } else {
        cout << "Error opening file" << endl;
    }
    
    // Append mode
    ofstream appendFile("output.txt", ios::app);
    if (appendFile.is_open()) {
        appendFile << "This line is appended" << endl;
        appendFile.close();
    }
    
    return 0;
}
```

### File Input (Reading)
```cpp
#include <fstream>
#include <string>

int main() {
    // Open file for reading
    ifstream inFile("input.txt");
    
    if (inFile.is_open()) {
        string line;
        
        // Read file line by line
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        
        inFile.close();
    } else {
        cout << "Error opening file" << endl;
    }
    
    // Read specific data types
    ifstream dataFile("data.txt");
    if (dataFile.is_open()) {
        int number;
        string text;
        
        dataFile >> number >> text;  // Read int and string
        cout << "Number: " << number << ", Text: " << text << endl;
        
        dataFile.close();
    }
    
    return 0;
}
```

### File Modes and Flags
```cpp
int main() {
    // Different file opening modes
    ofstream file1("file1.txt");                    // Default: truncate
    ofstream file2("file2.txt", ios::app);          // Append
    ofstream file3("file3.txt", ios::ate);          // At end
    ofstream file4("file4.txt", ios::binary);       // Binary mode
    
    // Combined modes
    ofstream file5("file5.txt", ios::app | ios::binary);
    
    // Check file state
    if (file1.good()) {
        cout << "File is in good state" << endl;
    }
    
    if (file1.eof()) {
        cout << "End of file reached" << endl;
    }
    
    if (file1.fail()) {
        cout << "Operation failed" << endl;
    }
    
    if (file1.bad()) {
        cout << "File is in bad state" << endl;
    }
    
    return 0;
}
```

### Binary File I/O
```cpp
#include <fstream>

struct Person {
    char name[50];
    int age;
    double height;
};

int main() {
    // Write binary data
    ofstream binFile("people.bin", ios::binary);
    if (binFile.is_open()) {
        Person person1 = {"Alice", 25, 1.75};
        Person person2 = {"Bob", 30, 1.80};
        
        binFile.write(reinterpret_cast<char*>(&person1), sizeof(Person));
        binFile.write(reinterpret_cast<char*>(&person2), sizeof(Person));
        
        binFile.close();
    }
    
    // Read binary data
    ifstream readBinFile("people.bin", ios::binary);
    if (readBinFile.is_open()) {
        Person person;
        
        while (readBinFile.read(reinterpret_cast<char*>(&person), sizeof(Person))) {
            cout << "Name: " << person.name 
                 << ", Age: " << person.age 
                 << ", Height: " << person.height << endl;
        }
        
        readBinFile.close();
    }
    
    return 0;
}
```

## 🔄 String Streams

### String Output Stream
```cpp
#include <sstream>

int main() {
    // Build string using stream
    ostringstream oss;
    
    oss << "Name: " << "Alice" << endl;
    oss << "Age: " << 25 << endl;
    oss << "Height: " << 1.75 << endl;
    
    string result = oss.str();
    cout << result;
    
    // Format complex strings
    ostringstream formatted;
    formatted << setw(15) << left << "Product" 
              << setw(10) << right << "Price" << endl;
    formatted << setw(15) << left << "Apple" 
              << setw(10) << right << "$1.50" << endl;
    formatted << setw(15) << left << "Banana" 
              << setw(10) << right << "$0.75" << endl;
    
    cout << formatted.str();
    
    return 0;
}
```

### String Input Stream
```cpp
#include <sstream>

int main() {
    string data = "John 25 1.80";
    istringstream iss(data);
    
    string name;
    int age;
    double height;
    
    // Parse string data
    iss >> name >> age >> height;
    
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Height: " << height << endl;
    
    // Parse CSV-like data
    string csv = "apple,banana,cherry,date";
    istringstream csvStream(csv);
    string item;
    
    while (getline(csvStream, item, ',')) {
        cout << "Item: " << item << endl;
    }
    
    return 0;
}
```

## 🎯 Advanced I/O Techniques

### Custom Stream Manipulators
```cpp
#include <iostream>
#include <iomanip>

// Custom manipulator for currency
ostream& currency(ostream& os) {
    os << "$" << fixed << setprecision(2);
    return os;
}

// Custom manipulator for percentage
ostream& percentage(ostream& os) {
    os << fixed << setprecision(1) << "%";
    return os;
}

int main() {
    double price = 19.99;
    double rate = 8.5;
    
    cout << "Price: " << currency << price << endl;
    cout << "Tax Rate: " << percentage << rate << endl;
    
    return 0;
}
```

### Stream Buffers
```cpp
#include <iostream>
#include <fstream>

int main() {
    // Redirect cout to file
    ofstream logFile("log.txt");
    streambuf* originalCout = cout.rdbuf();
    
    cout.rdbuf(logFile.rdbuf());
    cout << "This goes to log file" << endl;
    
    // Restore cout
    cout.rdbuf(originalCout);
    cout << "This goes to console" << endl;
    
    logFile.close();
    
    return 0;
}
```

### Error Handling
```cpp
#include <iostream>
#include <fstream>
#include <stdexcept>

class FileHandler {
private:
    ifstream file;
    
public:
    FileHandler(const string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open file: " + filename);
        }
    }
    
    ~FileHandler() {
        if (file.is_open()) {
            file.close();
        }
    }
    
    string readLine() {
        string line;
        if (getline(file, line)) {
            return line;
        } else {
            throw runtime_error("Error reading from file");
        }
    }
    
    bool hasMore() const {
        return !file.eof();
    }
};

int main() {
    try {
        FileHandler handler("input.txt");
        
        while (handler.hasMore()) {
            string line = handler.readLine();
            cout << line << endl;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
```

## 📝 Best Practices

### 1. Always Check File Operations
```cpp
// Good: Check file state
ifstream file("data.txt");
if (!file.is_open()) {
    cerr << "Failed to open file" << endl;
    return 1;
}

// Good: Check read operations
string line;
if (getline(file, line)) {
    // Process line
} else {
    // Handle read error
}
```

### 2. Use RAII for File Management
```cpp
// Good: Automatic cleanup
{
    ifstream file("data.txt");
    if (file.is_open()) {
        // Process file
    }
} // File automatically closed here

// Bad: Manual management
ifstream file("data.txt");
// ... process file ...
file.close(); // Easy to forget
```

### 3. Handle Input Validation
```cpp
// Good: Validate input
int getNumber() {
    int num;
    while (!(cin >> num)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Try again: ";
    }
    return num;
}

// Bad: Assume input is valid
int num;
cin >> num; // May fail silently
```

### 4. Use Appropriate Stream Types
```cpp
// Good: Use stringstream for parsing
string data = "10 20 30";
istringstream iss(data);
int a, b, c;
iss >> a >> b >> c;

// Good: Use fstream for file I/O
fstream file("data.txt", ios::in | ios::out);

// Good: Use binary mode for binary data
ofstream binFile("data.bin", ios::binary);
```

## 🚀 Performance Considerations

### Buffering
```cpp
int main() {
    // Large data output
    ofstream file("large.txt");
    
    // Use buffering for better performance
    const int bufferSize = 8192;
    char buffer[bufferSize];
    
    file.rdbuf()->pubsetbuf(buffer, bufferSize);
    
    // Write large amounts of data
    for (int i = 0; i < 1000000; i++) {
        file << i << endl;
    }
    
    file.close();
    return 0;
}
```

### Synchronization
```cpp
int main() {
    // Disable synchronization for better performance
    ios_base::sync_with_stdio(false);
    
    // Use C++ streams only
    cout << "Fast output" << endl;
    
    return 0;
}
```

## 🎯 Practice Problems

### Problem 1: File Word Counter
```cpp
int countWords(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return -1;
    
    string word;
    int count = 0;
    
    while (file >> word) {
        count++;
    }
    
    file.close();
    return count;
}
```

### Problem 2: CSV Parser
```cpp
vector<vector<string>> parseCSV(const string& filename) {
    ifstream file(filename);
    vector<vector<string>> data;
    
    string line;
    while (getline(file, line)) {
        vector<string> row;
        istringstream iss(line);
        string field;
        
        while (getline(iss, field, ',')) {
            row.push_back(field);
        }
        
        data.push_back(row);
    }
    
    file.close();
    return data;
}
```

### Problem 3: Log File Analyzer
```cpp
struct LogEntry {
    string timestamp;
    string level;
    string message;
};

vector<LogEntry> parseLogFile(const string& filename) {
    ifstream file(filename);
    vector<LogEntry> entries;
    
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        LogEntry entry;
        
        iss >> entry.timestamp >> entry.level;
        getline(iss, entry.message);
        
        entries.push_back(entry);
    }
    
    file.close();
    return entries;
}
```

## 📚 Summary

Key takeaways:
- **Use appropriate streams** for different I/O needs
- **Always check file operations** for errors
- **Use RAII** for automatic resource management
- **Validate input** to prevent crashes
- **Choose right file modes** for your use case
- **Consider performance** with buffering and synchronization

Master these concepts to build robust, efficient C++ applications!

---

## 🔗 Related Topics
- [Data Types](data-types.md)
- [Strings](strings.md)
- [Exception Handling](exception-handling.md)
- [STL Containers](stl-containers.md)
