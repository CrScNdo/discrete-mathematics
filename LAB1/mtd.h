#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

struct ArrayResult {
    int data[200];
    int size = 0;
};

class Plenty {
private:
    int arr1[61], arr2[61], arr3[61];
    int size1, size2, size3;
    int inputArray(int arr[], int maxSize);
    int randomArray(int arr[], int maxSize);
    int conditionArray(int arr[], int maxSize);
    
    void fillArray(int *arr, int &size, int maxSize);
    void printArray(int *arr, int size, const string &name);
    
    int unionArrays(int *a, int sizeA, int *b, int sizeB, int *res);
    int intersectionArrays(int *a, int sizeA, int *b, int sizeB, int *res);
    int differenceArrays(int *a, int sizeA, int *b, int sizeB, int *res);
    int symmetricDifferenceArrays(int *a, int sizeA, int *b, int sizeB, int *res);
    int complementArray(int *a, int sizeA, int *res);
    friend ArrayResult op_union(Plenty* p, const ArrayResult& a, const ArrayResult& b);
    friend ArrayResult op_intersection(Plenty* p, const ArrayResult& a, const ArrayResult& b);
    friend ArrayResult op_difference(Plenty* p, const ArrayResult& a, const ArrayResult& b);
    friend ArrayResult op_symdiff(Plenty* p, const ArrayResult& a, const ArrayResult& b);
    friend ArrayResult op_complement(Plenty* p, const ArrayResult& a);
    
    public:
        Plenty() : size1(0), size2(0), size3(0) {}
        
        void fillFirst()  { fillArray(arr1, size1, 61); }
        void fillSecond() { fillArray(arr2, size2, 61); }
        void fillThird()  { fillArray(arr3, size3, 61); }
        void printFirst()  { printArray(arr1, size1, "First array"); }
        
        int* getFirst()  { return arr1; }
        int* getSecond() { return arr2; }
        int* getThird()  { return arr3; }
        void printSecond() { printArray(arr2, size2, "Second array"); }
        
        int getSize1() { return size1; }
        int getSize2() { return size2; }
        int getSize3() { return size3; }
        void printThird()  { printArray(arr3, size3, "Third array"); }
    
        void printAll() { printFirst(); printSecond(); printThird();}
        
        void arrayOperations();
    
        void executeFunctionAdvanced();
};


void Plenty::fillArray(int *arr, int &size, int maxSize)
{
    int choice;
    cout << "Choose how to fill array" << endl;
    cout << "Manually [1]\nRandomly [2]\nWith the condition [3]\nExit [4]\n";
    cin >> choice;

    switch(choice) {
        case 1: size = inputArray(arr, maxSize); break;
        case 2: size = randomArray(arr, maxSize); break;
        case 3: size = conditionArray(arr, maxSize); break;
        case 4: cout << "Exit, array not filled.\n"; break;
        default: cout << "Unknown option.\n"; break;
    }
}

int Plenty::inputArray(int *arr, int maxSize)
{
    int x;
    int size = 0;
    cout << "Enter numbers from -30 to 30 (to exit enter 31):" << endl;
    while (size < maxSize)
    {
        cin >> x;
        if (x == 31) break;
        if (x < -30 || x > 30)
        {
            cout << "Error: number must be between -30 and 30!" << endl;
            continue;
        }
        arr[size++] = x;
    }
    return size;
}

int Plenty::randomArray(int *arr, int maxSize)
{
    srand(static_cast<unsigned int>(time(0)));

        int n;
        cout << "Enter number of elements to generate (1-" << maxSize << "): ";
        cin >> n;
        if (n < 1) n = 1;
        if (n > maxSize) n = maxSize;
        int size = 0;
        while (size < n)
        {
            int x = rand() % 61 - 30;
            bool exists = false;
            for (int i = 0; i < size; i++)
            {
                if (arr[i] == x) {
                    exists = true;
                    break;
                }
            }
            if (!exists)
            {
                arr[size++] = x;
            }
        }
        return size;
}

int Plenty::conditionArray(int arr[], int maxSize) {
    int size = 0;

    int cond;
    cout << "Choose condition:" << endl;
    cout << "By sign (+/-) [1]\nEven/Odd [2]\nMultiple of n [3]\n";
    cin >> cond;
    
    int param = 0;
    if(cond == 1) {
        cout << "Choose sign: 1 for positive, -1 for negative: ";
        cin >> param;
    } else if(cond == 2) {
        cout << "Choose parity: 0 for even, 1 for odd: ";
        cin >> param;
    } else if(cond == 3) {
        cout << "Enter n for multiples: ";
        cin >> param;
    }

    // Перебираем все числа в диапазоне [-30, 30]
    for(int x = -30; x <= 30; x++) {
        if(size >= maxSize) break; // защита от переполнения массива

        bool valid = false;
        switch(cond) {
            case 1: // знак
                valid = (param > 0) ? (x > 0) : (x < 0);
                break;
            case 2: // чет/нечет
                valid = (x % 2 == param);
                break;
            case 3: // кратность
                if(param != 0) valid = (x % param == 0);
                break;
        }

        if(valid) {
            arr[size++] = x;
        }
    }
    return size;
}

void Plenty::printArray(int *arr, int size, const string &name) {
    cout << name << " (size " << size << "): ";
    for(int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void Plenty::arrayOperations() {
    cout << "\nChoose arrays:\n";
    cout << "First and Second [1]\n";
    cout << "Second and Third [2]\n";
    cout << "First and Third [3]\n";
    cout << "All three [4]\n";
    int choice; cin >> choice;

    cout << "Choose operation:\n";
    cout << "Union '∪' [1]\nIntersection '∩' [2]\nDifference '/' [3]\n";
    cout << "Symmetric Difference 'Δ' [4]\nComplement '¬' [5]\n";
    int op; cin >> op;

    int result[200], tmp[200];
    int sizeRes=0, sizeTmp=0;

    if(choice==1) { // First & Second
        if(op==1) sizeRes=unionArrays(arr1,size1,arr2,size2,result);
        if(op==2) sizeRes=intersectionArrays(arr1,size1,arr2,size2,result);
        if(op==3) sizeRes=differenceArrays(arr1,size1,arr2,size2,result);
        if(op==4) sizeRes=symmetricDifferenceArrays(arr1,size1,arr2,size2,result);
        if(op==5) {
            cout << "Choose array for complement:\n";
            cout << "First [1], Second [2], Third [3]: ";
            int c; cin >> c;
            if(c==1) sizeRes=complementArray(arr1,size1,result);
            else if(c==2) sizeRes=complementArray(arr2,size2,result);
            else if(c==3) sizeRes=complementArray(arr3,size3,result);
        }
    }
    else if(choice==2) { // Second & Third
        if(op==1) sizeRes=unionArrays(arr2,size2,arr3,size3,result);
        if(op==2) sizeRes=intersectionArrays(arr2,size2,arr3,size3,result);
        if(op==3) sizeRes=differenceArrays(arr2,size2,arr3,size3,result);
        if(op==4) sizeRes=symmetricDifferenceArrays(arr2,size2,arr3,size3,result);
        if(op==5) {
            cout << "Choose array for complement:\n";
            cout << "First [1], Second [2], Third [3]: ";
            int c; cin >> c;
            if(c==1) sizeRes=complementArray(arr1,size1,result);
            else if(c==2) sizeRes=complementArray(arr2,size2,result);
            else if(c==3) sizeRes=complementArray(arr3,size3,result);
        }
    }
    else if(choice==3) { // First & Third
        if(op==1) sizeRes=unionArrays(arr1,size1,arr3,size3,result);
        if(op==2) sizeRes=intersectionArrays(arr1,size1,arr3,size3,result);
        if(op==3) sizeRes=differenceArrays(arr1,size1,arr3,size3,result);
        if(op==4) sizeRes=symmetricDifferenceArrays(arr1,size1,arr3,size3,result);
        if(op==5) {
            cout << "Choose array for complement:\n";
            cout << "First [1], Second [2], Third [3]: ";
            int c; cin >> c;
            if(c==1) sizeRes=complementArray(arr1,size1,result);
            else if(c==2) sizeRes=complementArray(arr2,size2,result);
            else if(c==3) sizeRes=complementArray(arr3,size3,result);
        }
    }
    else if(choice==4) { // All three
        if(op==1) { // объединение всех
            sizeTmp=unionArrays(arr1,size1,arr2,size2,tmp);
            sizeRes=unionArrays(tmp,sizeTmp,arr3,size3,result);
        }
        if(op==2) { // пересечение всех
            sizeTmp=intersectionArrays(arr1,size1,arr2,size2,tmp);
            sizeRes=intersectionArrays(tmp,sizeTmp,arr3,size3,result);
        }
        if(op==3) { // разность A-B-C
            sizeTmp=differenceArrays(arr1,size1,arr2,size2,tmp);
            sizeRes=differenceArrays(tmp,sizeTmp,arr3,size3,result);
        }
        if(op==4) { // симметрическая разность (A Δ B) Δ C
            sizeTmp=symmetricDifferenceArrays(arr1,size1,arr2,size2,tmp);
            sizeRes=symmetricDifferenceArrays(tmp,sizeTmp,arr3,size3,result);
        }
        if(op==5) {
            cout << "Choose array for complement:\n";
            cout << "First [1], Second [2], Third [3]: ";
            int c; cin >> c;
            if(c==1) sizeRes=complementArray(arr1,size1,result);
            else if(c==2) sizeRes=complementArray(arr2,size2,result);
            else if(c==3) sizeRes=complementArray(arr3,size3,result);
        }
    }

    printArray(result,sizeRes,"Result");
}


int Plenty::unionArrays(int *a, int sizeA, int *b, int sizeB, int *res) {
    int k = 0;

    // Сначала копируем все элементы из A
    for (int i = 0; i < sizeA; i++) {
        res[k++] = a[i];
    }

    // Потом добавляем элементы из B, которых нет в A
    for (int i = 0; i < sizeB; i++) {
        bool exists = false;
        for (int j = 0; j < sizeA; j++) {
            if (b[i] == a[j]) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            // Проверяем, нет ли дубликата уже в res (для элементов из B)
            bool alreadyAdded = false;
            for (int j = 0; j < k; j++) {
                if (res[j] == b[i]) {
                    alreadyAdded = true;
                    break;
                }
            }
            if (!alreadyAdded) {
                res[k++] = b[i];
            }
        }
    }

    return k; // возвращаем размер объединенного массива
}


int Plenty::intersectionArrays(int *a, int sizeA, int *b, int sizeB, int *res) {
    int k=0;
    for(int i=0;i<sizeA;i++) {
        for(int j=0;j<sizeB;j++) {
            if(a[i]==b[j]) {res[k++]=a[i]; break;}
        }
    }
    return k;
}

int Plenty::differenceArrays(int *a, int sizeA, int *b, int sizeB, int *res) {
    int k=0;
    for(int i=0;i<sizeA;i++) {
        bool exists=false;
        for(int j=0;j<sizeB;j++) if(a[i]==b[j]) {exists=true;break;}
        if(!exists) res[k++]=a[i];
    }
    return k;
}

int Plenty::symmetricDifferenceArrays(int *a, int sizeA, int *b, int sizeB, int *res) {
    int tmp1[200], tmp2[200];
    int sizeTmp1 = differenceArrays(a, sizeA, b, sizeB, tmp1); // A \ B
    int sizeTmp2 = differenceArrays(b, sizeB, a, sizeA, tmp2); // B \ A
    return unionArrays(tmp1, sizeTmp1, tmp2, sizeTmp2, res);   // (A\B) ∪ (B\A)
}

int Plenty::complementArray(int *a, int sizeA, int *res) {
    int k = 0;
    for(int x=-30; x<=30; x++) {
        bool exists = false;
        for(int i=0; i<sizeA; i++) {
            if(a[i]==x) {exists=true; break;}
        }
        if(!exists) res[k++] = x;
    }
    return k;
}

ArrayResult op_union(Plenty* p, const ArrayResult& a, const ArrayResult& b) {
    ArrayResult r;
    r.size = p->unionArrays((int*)a.data, a.size, (int*)b.data, b.size, r.data);
    return r;
}

ArrayResult op_intersection(Plenty* p, const ArrayResult& a, const ArrayResult& b) {
    ArrayResult r;
    r.size = p->intersectionArrays((int*)a.data, a.size, (int*)b.data, b.size, r.data);
    return r;
}

ArrayResult op_difference(Plenty* p, const ArrayResult& a, const ArrayResult& b) {
    ArrayResult r;
    r.size = p->differenceArrays((int*)a.data, a.size, (int*)b.data, b.size, r.data);
    return r;
}

ArrayResult op_symdiff(Plenty* p, const ArrayResult& a, const ArrayResult& b) {
    ArrayResult r;
    r.size = p->symmetricDifferenceArrays((int*)a.data, a.size, (int*)b.data, b.size, r.data);
    return r;
}

ArrayResult op_complement(Plenty* p, const ArrayResult& a) {
    ArrayResult r;
    r.size = p->complementArray((int*)a.data, a.size, r.data);
    return r;
}

// Возвращает приоритет операции
int precedence(char op) {
    // приоритет: ! (¬) > & (∩) > + (∪), ^ (Δ), / (-)
    if (op == '!') return 3;          // отрицание
    if (op == '&') return 2;          // пересечение
    if (op == '+' || op == '^' || op == '/' || op == '-') return 1; // объединение, сим. разность, разность
    return 0;
}

// Выполняет бинарную операцию
ArrayResult applyOp(Plenty* p, char op, const ArrayResult& a, const ArrayResult& b) {
    switch (op) {
        case '+': return op_union(p, a, b);            // ∪
        case '&': return op_intersection(p, a, b);     // ∩
        case '/': case '-': return op_difference(p, a, b); // /
        case '^': return op_symdiff(p, a, b);          // Δ
        default: return a;
    }
}

string normalizeExpr(const string& expr) {
    string result;
    for (size_t i = 0; i < expr.size(); ++i) {
        unsigned char c = expr[i];
        // ¬ (U+00AC)
        if (c == 0xC2 && i + 1 < expr.size() && expr[i + 1] == 0xAC) {
            result += '!';
            i++;
        }
        // ∪ (U+222A)
        else if (c == 0xE2 && i + 2 < expr.size() && expr[i + 1] == 0x88 && expr[i + 2] == 0xAA) {
            result += '+';
            i += 2;
        }
        // ∩ (U+2229)
        else if (c == 0xE2 && i + 2 < expr.size() && expr[i + 1] == 0x88 && expr[i + 2] == 0xA9) {
            result += '&';
            i += 2;
        }
        // Δ (U+0394)
        else if (c == 0xCE && i + 1 < expr.size() && expr[i + 1] == 0x94) {
            result += '^';
            i++;
        }
        else {
            result += c; // обычный символ
        }
    }
    return result;
}


void Plenty::executeFunctionAdvanced() {
    cout << "Введите выражение (например: (A∪B)∩¬C), символы (∪ = +, ∩ = &, / = /, Δ = ^, ¬ = !): ";
    string expr;
    cin >> expr;

    // Убираем пробелы
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());

    // --- НОРМАЛИЗАЦИЯ Unicode символов ---
    expr = normalizeExpr(expr);

    stack<ArrayResult> values;
    stack<char> ops;

    auto pushArray = [&](char name) {
        ArrayResult arr;
        if (name == 'A') { memcpy(arr.data, arr1, sizeof(int)*size1); arr.size = size1; }
        else if (name == 'B') { memcpy(arr.data, arr2, sizeof(int)*size2); arr.size = size2; }
        else if (name == 'C') { memcpy(arr.data, arr3, sizeof(int)*size3); arr.size = size3; }
        else { cout << "Ошибка: неизвестное множество " << name << endl; arr.size = 0; }
        values.push(arr);
    };

    auto applyTopOp = [&]() {
        char op = ops.top(); ops.pop();
        if (op == '!') {
            if (values.empty()) { cout << "Ошибка: нет операнда для отрицания.\n"; return; }
            ArrayResult a = values.top(); values.pop();
            values.push(op_complement(this, a));
        } else {
            if (values.size() < 2) { cout << "Ошибка: не хватает операндов для бинарной операции.\n"; return; }
            ArrayResult b = values.top(); values.pop();
            ArrayResult a = values.top(); values.pop();
            values.push(applyOp(this, op, a, b));
        }
    };

    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (isspace(c)) continue;

        if (c == 'A' || c == 'B' || c == 'C') {
            pushArray(c);
            // Если сразу перед множеством был '!', выполняем его немедленно
            while (!ops.empty() && ops.top() == '!') {
                applyTopOp();
            }
        }
        else if (c == '(') {
            ops.push(c);
        }
        else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                applyTopOp();
            }
            if (!ops.empty()) ops.pop(); // убираем '('
            // После закрытия скобки мог стоять '!' — применяем
            while (!ops.empty() && ops.top() == '!') {
                applyTopOp();
            }
        }
        else if (c == '+' || c == '&' || c == '/' || c == '-' || c == '^' || c == '!') {
            if (c == '!') {
                ops.push(c); // унарный оператор — просто кладём
            } else {
                while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
                    applyTopOp();
                }
                ops.push(c);
            }
        }
        else {
            cout << "Ошибка: неизвестный символ '" << c << "'\n";
            return;
        }
    }

    while (!ops.empty()) {
        applyTopOp();
    }

    if (!values.empty()) {
        ArrayResult result = values.top();
        printArray(result.data, result.size, "Результат");
    } else {
        cout << "Ошибка: пустое выражение.\n";
    }
}
