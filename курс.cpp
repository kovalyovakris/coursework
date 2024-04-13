#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <locale>
#include <Windows.h>
#include <codecvt>
#include <vector>

using namespace std;

struct Book
{
    wstring name;
    wstring author;
    int year;
    wstring genre;
};
struct Privacy
{
    wstring login;
    wstring password;
};
struct User
{
    wstring request;
    wstring reservation;
    wstring period;
};
void menu_user_not_auto()
{
    cout << "Меню неавторизированного пользователя:" << endl;
    cout << "1: Просмотреть доступные книги" << endl;
    cout << "2: Выйти из программы" << endl;
}
void menu_user_auto()
{
    cout << "Меню пользователя:" << endl;
    cout << "0: Выйти из программы" << endl;
    cout << "1: Просмотреть свои заявки, брони, сроки и уведомления от электронного библиотекаря " << endl;
    cout << "2: Просмотреть доступные книги" << endl;
    cout << "3: Оформить заявку на книгу" << endl;
    cout << "4: Оставить бронь на книгу, которой нет в наличии" << endl;
    cout << "5: Найти книгу: по жанру/названию/автору/году" << endl;
    cout << "6: Удалить заявку на книгу, на которую еще не ответил библиотекарь" << endl;
    cout << "7: Удалить бронь на книгу, на которую еще не ответил библиотекарь" << endl;
    cout << "8: Отсортировать список книг по названию/жанру/году" << endl;
}
void menu_admin()
{
    cout << "Меню админа:" << endl;
    cout << "0: Выйти из программы" << endl;
    cout << "1: Просмотреть всех пользователей, заявки и брони" << endl;
    cout << "2: Добавить новую книгу в библиотеку" << endl;
    cout << "3: Удалить книгу из библиотеки" << endl;
    cout << "4: Оставить уведомление читателю" << endl;
    cout << "5: Просмотреть доступные книги" << endl;
    cout << "6: Отсортировать список книг по названию/жанру/году" << endl;
    cout << "7: Установить для пользователя сроки сдачи" << endl;
    cout << "8: Вернуть книги в библиотеку от пользователя: удалить его заявку или бронь и удалить текущие сроки и уведомления" << endl;
    cout << "9: Найти пользователей по срокам сдачи" << endl;
}
void menu_librarian()
{
    cout << "Меню библиотекаря:" << endl;
    cout << "0: Выйти из программы" << endl;
    cout << "1: Просмотреть всех пользователей, заявки и брони" << endl;
    cout << "2: Оставить уведомление читателю" << endl;
    cout << "3: Просмотреть доступные книги" << endl;
    cout << "4: Отсортировать список книг по названию/жанру/году" << endl;
    cout << "5: Установить для пользователя сроки сдачи" << endl;
    cout << "6: Вернуть книги в библиотеку от пользователя: удалить его заявку или бронь и удалить текущие сроки и уведомления" << endl;
    cout << "7: Найти пользователей по срокам сдачи" << endl;
}
bool check_list(wstring lineremove)
{
    wifstream fout("list_of_books.txt");
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    if (!fout.is_open())
    {
        return false;
    }
    wstring line;
    while (getline(fout, line))
    {
        if (line.find(lineremove) != std::string::npos)
        {
            return true;
        }
    }
    fout.close();
    return false;
}
int linecounter(int choose)
{
    switch (choose)
    {
    case(1):
    {
        wifstream fout("list_of_books.txt");
        fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
        fout.seekg(0, ios::beg);
        wstring linecount;
        int count = 0;
        while (getline(fout, linecount))
        {
            if (linecount.length() != 0)
            {
                count++;
            }
        }
        wfstream fileclose;
        fileclose.close();
        return count;
    }
    case (2):
    {
        wifstream fout("users.txt");
        fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
        fout.seekg(0, ios::beg);
        wstring linecount;
        int count = 0;
        while (getline(fout, linecount))
        {
            count++;
        }
        count++;
        wfstream fileclose;
        fileclose.close();
        return count;
    }
    default:
    {
        cout << "\n";
        return 0;
    }
    }
}
void sort1BookName(wstring* arr, int arr_size) // вставками
{
    for (int i = 1; i < arr_size; i++)
    {
        int sorted = i - 1;
        while (sorted > -1 && arr[sorted] > arr[sorted + 1])
        {
            wstring temp = arr[sorted];
            arr[sorted] = arr[sorted + 1];
            arr[sorted + 1] = temp;
            sorted--;
        }
    }
    return;
}
void sort2BookGenre(wstring *arr,wstring *arrline, int arr_size) // шейкерная
{
    int left, right, m;
    left = 0;
    right = arr_size - 1;
    while (left <= right)
    {
        for (m = right; m > left; m--)
        {
            if (arr[m - 1] > arr[m])
            {
                swap(arr[m - 1], arr[m]);
                swap(arrline[m - 1], arrline[m]);
            }
        }
        left++;
        for (m = left; m <= right; m++)
        {
            if (arr[m - 1] > arr[m])
            {
                swap(arr[m - 1], arr[m]);
                swap(arrline[m - 1], arrline[m]);
            }
        }
        right--;
    }
    return;
}
void sort3BookYear(wstring *arr, wstring *arrline, int arr_size) // выбором
{
    for (int i = 0; i < arr_size - 1; i++)
    {
        int maxIndex = i;
        for (int j = i + 1; j < arr_size; j++) {
            if (arr[j] > arr[maxIndex]) {
                maxIndex = j;
            }
        }
        swap(arr[i], arr[maxIndex]);
        swap(arrline[i], arrline[maxIndex]);
    }
    return;
}
void madearray(int counting)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    wifstream fout("list_of_books.txt");
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    fout.seekg(0, ios::beg);
    wfstream fileclose;
    int count = linecounter(1);
    switch (counting)
    {
    case(1):
    {
        wstring* arr = new wstring[count];
        int i = 0;
        int arr_size = 0;
        wstring line;
        while (getline(fout, line))
        {
            if (line.length() != 0)
            {
                arr[i] = line;
                arr_size++;
                i++;
            }
        }
        sort1BookName(arr, arr_size);
        for (i = 0; i < arr_size; i++)
        {
            wcout << arr[i] << L"\n";
            wcout << L"\n";
        }
        delete[] arr;
        fileclose.close();
        return;
    }
    case(2):
    {
        wstring* arr = new wstring[count];
        wstring* arrline = new wstring[count];
        int i = 0;
        int arr_size = 0;
        wstring line;
        while (getline(fout, line))
        {
            if (line.length() != 0)
            {
                size_t pos = line.find(L"Жанр: ");
                if (pos != std::wstring::npos)
                {
                    wstring genre = line.substr(pos + 6); // 6 - длина строки "Жанр: "
                    arr[i] = genre;
                    arrline[i] = line;
                    arr_size++;
                    i++;
                }
            }
        }
        sort2BookGenre(arr, arrline, arr_size);
        for (i = 0; i < arr_size; i++)
        {
            wcout << arrline[i] << L"\n";
            wcout << L"\n";
        }
        delete[] arr;
        delete[] arrline;
        fileclose.close();
        return;
    }
    case(3):
    {
        wstring* arr = new wstring[count];
        wstring* arrline = new wstring[count];
        int i = 0;
        int arr_size = 0;
        wstring line;
        while (getline(fout, line))
        {
            if (line.length() != 0)
            {
                size_t pos = line.find(L"Год: ");
                if (pos != std::wstring::npos)
                {
                    wstring year = line.substr(pos + 5); // 5 - длина строки "Год: "
                    arr[i] = year;
                    arrline[i] = line;
                    arr_size++;
                    i++;
                }
            }
        }
        sort3BookYear(arr, arrline, arr_size);
        for (i = 0; i < arr_size; i++)
        {
            wcout << arrline[i] << L"\n";
            wcout << L"\n";
        }
        delete[] arr;
        delete[] arrline;
        fileclose.close();
        return;
    }
    default:
        cout << "Введены некорректные значения\n";
        return;
    }
}
void show_list_of_books()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    wifstream fout("list_of_books.txt");
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return;
    }
    wstring line;
    while (getline(fout, line))
    {
        wcout << line << L"\n";
    }
}
void show_users()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    wifstream fout("users.txt");
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return;
    }
    wstring line;
    while (getline(fout, line))
    {
        wcout << line << L"\n";
    }
}
void add_list_of_books()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    wofstream fin("list_of_books.txt", ios::in | ios::app);
    wifstream fout("list_of_books.txt", ios::out | ios::app);
    wfstream F("list_of_books.txt");
    fout.seekg(0, ios::beg);
    wfstream fileclose;
    fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring name;
    wstring author;
    wstring year_publication;
    wstring genre;
    F.clear();
    fout.open("list_of_books.txt", ios::app);
    bool chooselist = 1;
    while (true)
    {
        if ((fout.is_open()) && (chooselist != 0))
        {
            wcout << L"Если хотите добавить книгу в библиотеку введите 1, если хотите закончить введите 0\n";
            wcin >> chooselist;
            if (chooselist == 1)
            {
                wcout << L"Введите название книги" << endl;
                getline(wcin, name);
                getline(wcin, name);
                if (check_list(name) == true)
                {
                    cout << "Такая книга уже есть в библиотеке!";
                    break;
                }
                else if (name == L"")
                {
                    cout << "Введена пустая строка! Книга должны иметь название\n";
                    break;
                }
                else
                {
                    Book newbook;
                    newbook.name = name;
                    wcout << L"Автор книги" << endl;
                    getline(wcin, author);
                    newbook.author = author;
                    wcout << L"Год публикации книги" << endl;
                    int year_publication;
                    cin >> year_publication;
                    newbook.year = year_publication;
                    wcout << L"Жанр книги" << endl;
                    getline(wcin, genre);
                    getline(wcin, genre);
                    newbook.genre = genre;
                    if (newbook.name != L"" && newbook.author != L"" && newbook.genre != L"" && newbook.year > 0)
                    {
                        fin << L"\n";
                        fin << L"'" << newbook.name << L"' ";
                        fin << L"Автор: " << newbook.author << L" ";
                        fin << L"Год: " << year_publication << L" ";
                        fin << L"Жанр: " << genre << L".\n";
                    }
                    else
                    {
                        cout << "Какие-то характеристики пустые или такой формат записи не существует\n";
                        break;
                    }
                }
            }
        }
        else if (chooselist == 0)
        {
            break;
        }
        else
        {
            wcout << "Не удается открыть файл";
            break;
        }
    }
}
void deleteLineFromList(wstring lineToRemove) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    wifstream fout("list_of_books.txt", ios::out | ios::app);
    wfstream F("list_of_books.txt");
    fout.seekg(0, ios::beg);
    wfstream fileclose;
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    vector <wstring> lines;
    wstring line;
    bool cheeck = check_list(lineToRemove);
    if (cheeck == true)
    {
        if (!fout.is_open())
        {
            cout << "Не удается открыть файл\n";
            return;
        }
        else if (lineToRemove == L"")
        {
            cout << "Введена пустая строка!\n";
            return;
        }
        while (getline(fout, line)) {
            if (line.find(lineToRemove) == string::npos) {
                lines.push_back(line);
            }
            else
            {
                getline(fout, line);
            }
        }
        F.close();
        ofstream fileToClear("list_of_books.txt");
        wofstream fin("list_of_books.txt", ios::in | ios::app);
        fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
        for (const wstring& l : lines) {
            fin << l << "\n";
        }
        lines.clear();
        F.close();
    }
    else if (cheeck == false)
    {
        cout << "Такая книга не найдена в библиотеке\n";
        return;
    }
}
wstring reternbook(wstring linesearch) // юзается где нибудь??
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    wifstream fout("list_of_books.txt");
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring line;
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return L"";
    }
    else if (linesearch == L"")
    {
        cout << "Введена пустая строка!\n";
        return L"";
    }
    while (getline(fout, line))
    {
        if (line.find(linesearch) != string::npos)
        {
            return line;
        }
    }
    cout << "Данной книги нет в библиотеке\n";
    return L"";
}
bool searchBin(wstring linesearch, wstring* arrlogin, wstring* arrdate, int arr_size)
{
    int l = 0;
    int r = arr_size - 1;
    int mid;
    bool result = false;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (arrdate[mid] == linesearch)
        {
            wcout << arrlogin[mid] << L"\n";
            result = true;
            int temp = mid;
            if (mid > 0)
            {
                temp--;
                while (temp >= 0 && arrdate[temp] == linesearch)
                {
                    wcout << arrlogin[temp] << L"\n";
                    temp--;
                }
            }
            temp = mid;
            if (mid < arr_size - 1)
            {
                temp++;
                while (temp <= arr_size - 1 && arrdate[temp] == linesearch)
                {
                    wcout << arrlogin[temp] << L"\n";
                    temp++;
                }
            }
            return result;
        }
        if (arrdate[mid] > linesearch)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return result;
}
void madearraysForUsersDate(wstring linesearch)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    wifstream fout("users.txt");
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    fout.seekg(0, ios::beg);
    wfstream fileclose;
    int c = linecounter(2);
    c = c / 9;
    wstring* arrlogin = new wstring[c-1];
    wstring* arrdate = new wstring[c-1];
    int i = 0;
    int arr_size = 0;
    wstring line;
    while (getline(fout, line))
    {
        if (line.length() != 0)
        {
            arrlogin[i] = line;
            for (int l = 0; l < 8; l++)
            {
                getline(fout, line);
            }
            if (line.length() != 0)
            {
                arrdate[i] = line;
                i++;
                arr_size++;
            }
        }
    }
    int n = arr_size;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arrdate[j] > arrdate[j + 1])
            {
                swap(arrdate[j], arrdate[j + 1]);
                swap(arrlogin[j], arrlogin[j + 1]);
            }
        }
    }
    wcout << L"Пользователи, которым до сдачи книги осталось кол-во дней: " << linesearch << L"\n";
    bool res = searchBin(linesearch, arrlogin, arrdate, arr_size);
    if (!res)
    {
        cout << "Пользователи с введенным сроком не найдены!\n";
    }
    return;
}
int searchOfBook(wstring linesearch, wstring *arr, int arr_size)
{
    int countofbook = 0;
    if (linesearch == L"")
    {
        cout << "Введена пустая строка!\n";
        return 0;
    }
    wstring search = L"";
    for (int i = 0; i < arr_size; i++)
    {
        search = arr[i];
        if (search.find(linesearch) != string::npos)
        {
            wcout << arr[i] << L"\n";
            countofbook++;
        }
    }
    cout << endl;
    return countofbook;
}
int madearraylist(wstring linesearch)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    wifstream fout("list_of_books.txt");
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring line;
    int number = linecounter(1);
    wstring* arr = new wstring[number];
    int i = 0;
    int arr_size = 0;
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return 0;
    }
    while (getline(fout, line))
    {
        if (line.length() != 0)
        {
            arr[i] = line;
            i++;
            arr_size++;
        }
    }
    int number2 = searchOfBook(linesearch, arr, arr_size);
    return number2;
}
void make_request(wstring linetorequest, wstring loguser)
{
    if (madearraylist(linetorequest) > 0)
    {
        wifstream fout("users.txt", ios::out | ios::app);
        wfstream F("users.txt");
        fout.seekg(0, ios::beg);
        fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
        wstring line;
        vector <wstring> lines;
        if (!fout.is_open())
        {
            cout << "Не удается открыть файл\n";
            return;
        }
        while (getline(fout, line))
        {
            if (line.find(loguser) != std::string::npos)
            {
                lines.push_back(line);
                getline(fout, line);
                lines.push_back(line); // слово заявки 
                getline(fout, line);
                if (line.length() == 0)
                {
                    lines.push_back(reternbook(linetorequest));
                    getline(fout, line);
                }
                else
                {
                    cout << "У одного пользователя не может быть больше 1 заявки\n";
                    lines.clear();
                    F.close();
                    return;
                }
            }
            lines.push_back(line);
        }
        F.close();
        ofstream fileToClear("users.txt");
        wofstream fin("users.txt", ios::in | ios::app);
        fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
        for (const wstring& l : lines) {
            fin << l << "\n";
        }
        lines.clear();
        F.close();
        deleteLineFromList(linetorequest);
    }
    else
    {
        cout << "Такой книги нет в библиотеке\n";
        return;
    }
}
void make_rezerved(wstring linetorequest, wstring loguser)
{
        wifstream fout("users.txt", ios::out | ios::app);
        wfstream F("users.txt");
        fout.seekg(0, ios::beg);
        fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
        wstring line;
        vector <wstring> lines;
        if (!fout.is_open())
        {
            cout << "Не удается открыть файл\n";
            return;
        }
        while (getline(fout, line))
        {
            if (line.find(loguser) != std::string::npos)
            {
                lines.push_back(line);
                getline(fout, line);
                lines.push_back(line); // слово заявки 
                getline(fout, line);
                lines.push_back(line);// для заявки
                getline(fout, line);
                lines.push_back(line); // слово брони 
                getline(fout, line);
                if (line.length() == 0)
                {
                    lines.push_back(linetorequest);
                    getline(fout, line);
                }
                else
                {
                    cout << "У одного пользователя не может быть больше 1 брони\n";
                    lines.clear();
                    F.close();
                    return;
                }
            }
            lines.push_back(line);
        }
        F.close();
        ofstream fileToClear("users.txt");
        wofstream fin("users.txt", ios::in | ios::app);
        fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
        if (!fin.is_open())
        {
            cout << "Не удается открыть файл\n";
            return;
        }
        for (const wstring& l : lines) {
            fin << l << "\n";
        }
        lines.clear();
        F.close();

}
void leave_notif(wstring loguser)
{
    wifstream fout("users.txt", ios::out | ios::app);
    wfstream F("users.txt");
    fout.seekg(0, ios::beg);
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring line;
    vector <wstring> lines;
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return;
    }
    else if (loguser == L"")
    {
        cout << "Введена пустая строка!\n";
        return;
    }
    while (getline(fout, line))
    {
        if (line == loguser)
        {
            lines.push_back(line);// добав логин
            getline(fout, line);
            lines.push_back(line); // слово заявка
            getline(fout, line);
            lines.push_back(line); // сама заявка 
            getline(fout, line);
            lines.push_back(line); // слово бронь
            getline(fout, line);
            lines.push_back(line); // сама бронь 
            getline(fout, line);
            lines.push_back(line); // слово увед 
            getline(fout, line);
            cout << "Выберите какое уведомление оставить пользователю\n";
            cout << "1: Можете забрать свою заявку!\n";
            cout << "2: Можете забрать свою бронь!\n";
            cout << "3: Можете забрать и заявку, и бронь!\n";
            cout << "4: Вам пора вернуть свою заявку!\n";
            cout << "5: Вам пора вернуть свою бронь!\n";
            int choosenotif;
            cin >> choosenotif;
            switch (choosenotif)
            {
            case(1):
            {
                cout << "Введите дату выдачи заявки\n";
                wstring date;
                wcin >> date;
                wstring beginPeriod = L"Можете забрать свою заявку! Дата: " + date;
                lines.push_back(beginPeriod);
                break;
            }
            case(2):
            {
                cout << "Введите дату выдачи брони\n";
                wstring date;
                wcin >> date;
                wstring beginPeriod = L"Можете забрать свою бронь! Дата: " + date;
                lines.push_back(beginPeriod);
                break;
            }
            case(3):
            {
                cout << "Введите дату выдачи книг\n";
                wstring date;
                wcin >> date;
                wstring beginPeriod = L"Можете забрать свою заявку и бронь! Дата: " + date;
                lines.push_back(beginPeriod);
                break;
            }
            case (4):
            {
                lines.push_back(L"Вам пора вернуть свою заявку!");
                break;
            }
            case(5):
            {
                lines.push_back(L"Вам пора вернуть свою бронь!");
                break;
            }
            default:
            {
                cout << "Введены некорректные значения, уведомление не будет оставлено!\n";
                lines.push_back(L"\n");
                break;
            }
            }
            getline(fout, line);
        }
        lines.push_back(line);
    }
    F.close();
    ofstream fileToClear("users.txt");
    wofstream fin("users.txt", ios::in | ios::app);
    fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
    if (!fin.is_open())
    {
        cout << "Не удается открыть файл\n";
        return;
    }
    for (const wstring& l : lines) {
        fin << l << "\n";
    }
    lines.clear();
    F.close();
}
void leave_date(wstring log_user)
{
    wifstream fout("users.txt", ios::out | ios::app);
    wfstream F("users.txt");
    fout.seekg(0, ios::beg);
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring line;
    vector <wstring> lines;
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return;
    }
    else if (log_user == L"")
    {
        cout << "Введена пустая строка!\n";
        return;
    }
    while (getline(fout, line))
    {
        if (line == log_user)
        {
            lines.push_back(line);// добав логин
            getline(fout, line);
            lines.push_back(line); // слово заявка
            getline(fout, line);
            lines.push_back(line); // сама заявка 
            getline(fout, line);
            lines.push_back(line); // слово бронь
            getline(fout, line);
            lines.push_back(line); // сама бронь 
            getline(fout, line);
            lines.push_back(line); // слово увед 
            getline(fout, line);
            lines.push_back(line); // сам увед 
            getline(fout, line);
            lines.push_back(line); // слово срок
            getline(fout, line);
            cout << "Установите для пользователя оставшееся количество дней для сдачи имеющихся книг в библиотеку\n";
            wstring chooseperiod;
            wcin >> chooseperiod;
            lines.push_back(chooseperiod);
            getline(fout, line);
        }
        lines.push_back(line);
    }
    F.close();
    ofstream fileToClear("users.txt");
    wofstream fin("users.txt", ios::in | ios::app);
    fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
    if (!fin.is_open())
    {
        cout << "Не удается открыть файл\n";
        return;
    }
    for (const wstring& l : lines) {
        fin << l << "\n";
    }
    lines.clear();
    F.close();
}
void view_notif(wstring log_user)
{
    wifstream fout("users.txt", ios::out | ios::app);
    wfstream F("users.txt");
    fout.seekg(0, ios::beg);
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring line;
    bool stop_moment = true;
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return;
    }
    while (getline(fout, line) && stop_moment == true)
    {
        if (line.find(log_user) != std::string::npos)
        {
            wcout << L"Заявки, брони, уведомления и сроки сдачи для пользователя: " << log_user << L"\n";
            for (int i = 0; i < 8; i++)
            {
                getline(fout, line);
                wcout << line << L"\n";
            }
            stop_moment = false;
            break;
        }
    }
}
void addToListRequestorRezerved(wstring line_to_add)
{
    if (check_list(line_to_add))
    {
        return;
    }
    wofstream fin("list_of_books.txt", ios::in | ios::app);
    fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
    fin.open("list_of_books.txt", ios::app);
    fin << L"\n";
    fin << L"\n";
    fin << line_to_add;
    fin.close();
}
bool checknotif(wstring loguser)
{
    wifstream fout("users.txt", ios::out | ios::app);
    wfstream F("users.txt");
    fout.seekg(0, ios::beg);
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring line;
    while (getline(fout, line))
    {
        if (line == loguser)
        {
            for (int i = 0; i < 5; i++)
            {
                getline(fout, line);
            }
            if (line == L"")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
void return_request(wstring log_user)
{
    wifstream fout("users.txt", ios::out | ios::app);
    wfstream F("users.txt");
    fout.seekg(0, ios::beg);
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring line;
    wstring line_to_add;
    vector <wstring> lines;
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return;
    }
    else if (log_user == L"")
    {
        cout << "Введена пустая строка!\n";
        return;
    }
    while (getline(fout, line))
    {
        if (line.find(log_user) != std::string::npos)
        {
            lines.push_back(line);
            getline(fout, line);
            lines.push_back(line); // слово заявки 
            getline(fout, line);
            if (line.length() != 0)
            {
                if (checknotif)
                {
                    line_to_add = line;
                    lines.push_back(L"");
                    getline(fout, line);
                }
                else
                {
                    cout << "Вам нужно вернуть книгу в библиотеку!\n";
                    lines.clear();
                    F.close();
                    return;
                }
            }
            else
            {
                cout << "У вас нет заявки на книгу!\n";
                lines.clear();
                F.close();
                return;
            }
        }
        lines.push_back(line);
    }
    F.close();
    ofstream fileToClear("users.txt");
    wofstream fin("users.txt", ios::in | ios::app);
    fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
    if (!fin.is_open())
    {
        cout << "Не удается открыть файл\n";
        return;
    }
    for (const wstring& l : lines) {
        fin << l << "\n";
    }
    lines.clear();
    F.close();
    addToListRequestorRezerved(line_to_add);
}
wstring checkusernotif(wstring log_user)
{
    wifstream fout("users.txt", ios::out | ios::app);
    wfstream F("users.txt");
    fout.seekg(0, ios::beg);
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring line;
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return L"";
    }
    else if (log_user == L"")
    {
        cout << "Введена пустая строка!\n";
        return L"";
    }
    while (getline(fout, line))
    {
        if (line == log_user)
        {
            for (int i = 0; i < 6; i++)
            {
                getline(fout, line);
            }
            return line;
        }
    }
}
bool return_request_lib(wstring log_user)
{
    wifstream fout("users.txt", ios::out | ios::app);
    wfstream F("users.txt");
    fout.seekg(0, ios::beg);
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring line;
    wstring line_to_add;
    vector <wstring> lines;
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return false;
    }
    else if (log_user == L"")
    {
        cout << "Введена пустая строка!\n";
        return false;
    }
    while (getline(fout, line))
    {
        if (line == log_user)
        {
            lines.push_back(line);
            getline(fout, line);
            lines.push_back(line); // слово заявки 
            getline(fout, line);
            if (line.length() != 0)
            {
                if (checkusernotif(log_user).find(L"Можете забрать свою заявку!") != std::string::npos)
                {
                    line_to_add = line;
                    lines.push_back(L"");
                    getline(fout, line);// слово бронь
                    lines.push_back(line);
                    getline(fout, line); // сама бронь
                    lines.push_back(line);
                    getline(fout, line); // слово увед
                    lines.push_back(line);
                    getline(fout, line); // увед 
                    lines.push_back(L"");
                    getline(fout, line); // слово дни
                    lines.push_back(line);
                    getline(fout, line);// кол во дней
                    lines.push_back(L"");
                    if (!getline(fout, line))
                    {
                        return false;
                    }
                }
                else
                {
                    cout << "Уведомление пользователю не соответсвует тому, что вы хотите удалить!\n";
                    lines.clear();
                    F.close();
                    return false;
                }
            }
            else
            {
                cout << "У пользоватлея нет заявки на книгу!\n";
                lines.clear();
                F.close();
                return false;
            }
        }
        lines.push_back(line);
    }
    F.close();
    ofstream fileToClear("users.txt");
    wofstream fin("users.txt", ios::in | ios::app);
    fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
    if (!fin.is_open())
    {
        cout << "Не удается открыть файл\n";
        return false;
    }
    for (const wstring& l : lines) {
        fin << l << "\n";
    }
    lines.clear();
    F.close();
    addToListRequestorRezerved(line_to_add);
    return true;
}
void return_rezerved(wstring log_user)
{
    wifstream fout("users.txt", ios::out | ios::app);
    wfstream F("users.txt");
    fout.seekg(0, ios::beg);
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring line;
    wstring line_to_add;
    vector <wstring> lines;
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return;
    }
    else if (log_user == L"")
    {
        cout << "Введена пустая строка!\n";
        return;
    }
    while (getline(fout, line))
    {
        if (line.find(log_user) != std::string::npos)
        {
            lines.push_back(line);
            getline(fout, line);
            lines.push_back(line); // слово заявки 
            getline(fout, line);
            lines.push_back(line); // сама заявка 
            getline(fout, line);
            lines.push_back(line); // слово брони
            getline(fout, line);
            if (line.length() != 0)
            {
                if (checknotif(log_user))
                {
                    line_to_add = line;
                    lines.push_back(L"");
                    getline(fout, line);
                }
                else
                {
                    cout << "Вам нужно вернуть книгу в библиотеку!\n";
                    lines.clear();
                    F.close();
                    return;
                }
            }
            else
            {
                cout << "У вас нет заявки на книгу!\n";
                lines.clear();
                F.close();
                return;
            }
        }
        lines.push_back(line);
    }
    F.close();
    ofstream fileToClear("users.txt");
    wofstream fin("users.txt", ios::in | ios::app);
    fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
    if (!fin.is_open())
    {
        cout << "Не удается открыть файл\n";
        return;
    }
    for (const wstring& l : lines) {
        fin << l << "\n";
    }
    lines.clear();
    F.close();
    addToListRequestorRezerved(line_to_add);
}
bool return_rezerved_lib(wstring log_user)
{
    wifstream fout("users.txt", ios::out | ios::app);
    wfstream F("users.txt");
    fout.seekg(0, ios::beg);
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring line;
    wstring line_to_add;
    vector <wstring> lines;
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return false;
    }
    else if (log_user == L"")
    {
        cout << "Введена пустая строка!\n";
        return false;
    }
    while (getline(fout, line))
    {
        if (line.find(log_user) != std::string::npos)
        {
            lines.push_back(line);
            getline(fout, line);
            lines.push_back(line); // слово заявки 
            getline(fout, line);
            lines.push_back(line); // сама заявка 
            getline(fout, line);
            lines.push_back(line); // слово брони
            getline(fout, line);
            if (line.length() != 0)
            {
                if (checkusernotif(log_user).find(L"Можете забрать свою бронь!") != std::string::npos)
                {
                    line_to_add = line;
                    lines.push_back(L"");
                    getline(fout, line); // слово увед
                    lines.push_back(line);
                    getline(fout, line);// сам увед
                    lines.push_back(L"");
                    getline(fout, line);// слово сроки
                    lines.push_back(line);
                    getline(fout, line);// сам срок
                    lines.push_back(L"");
                    if (!getline(fout, line))
                    {
                        return false;
                    }
                }
                else
                {
                    cout << "Уведомление пользователю не соответсвует тому, что вы хотите удалить!\n";
                    lines.clear();
                    F.close();
                    return false;
                }
            }
            else
            {
                cout << "У пользоватлея нет брони на книгу!\n";
                lines.clear();
                F.close();
                return false;
            }
        }
        lines.push_back(line);
    }
    F.close();
    ofstream fileToClear("users.txt");
    wofstream fin("users.txt", ios::in | ios::app);
    fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
    if (!fin.is_open())
    {
        cout << "Не удается открыть файл\n";
        return false;
    }
    for (const wstring& l : lines) {
        fin << l << "\n";
    }
    lines.clear();
    F.close();
    addToListRequestorRezerved(line_to_add);
    return true;
}
bool return_all(wstring log_user)
{
    wifstream fout("users.txt", ios::out | ios::app);
    wfstream F("users.txt");
    fout.seekg(0, ios::beg);
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    wstring line;
    wstring line_to_add;
    vector <wstring> lines;
    if (!fout.is_open())
    {
        cout << "Не удается открыть файл\n";
        return false;
    }
    else if (log_user == L"")
    {
        cout << "Введена пустая строка!\n";
        return false;
    }
    while (getline(fout, line))
    {
        if (line.find(log_user) != std::string::npos)
        {
            lines.push_back(line);
            getline(fout, line);
            lines.push_back(line); // слово заявки 
            getline(fout, line);
            lines.push_back(L""); // сама заявка 
            getline(fout, line);
            lines.push_back(line); // слово брони
            getline(fout, line);
            if (line.length() != 0)
            {
                if (checkusernotif(log_user).find(L"Можете забрать и заявку, и бронь!") != std::string::npos)
                {
                    line_to_add = line;
                    lines.push_back(L"");
                    getline(fout, line); // слово увед
                    lines.push_back(line);
                    getline(fout, line);// сам увед
                    lines.push_back(L"");
                    getline(fout, line);// слово сроки
                    lines.push_back(line);
                    getline(fout, line);// сам срок
                    lines.push_back(L"");
                    if (!getline(fout, line))
                    {
                        return false;
                    }
                }
                else
                {
                    cout << "Уведомление пользователю не соответсвует тому, что вы хотите удалить!\n";
                    lines.clear();
                    F.close();
                    return false;
                }
            }
            else
            {
                cout << "У пользователея нет заявки и брони на книгу!\n";
                lines.clear();
                F.close();
                return false;
            }
        }
        lines.push_back(line);
    }
    F.close();
    ofstream fileToClear("users.txt");
    wofstream fin("users.txt", ios::in | ios::app);
    fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
    if (!fin.is_open())
    {
        cout << "Не удается открыть файл\n";
        return false;
    }
    for (const wstring& l : lines) {
        fin << l << "\n";
    }
    lines.clear();
    F.close();
    addToListRequestorRezerved(line_to_add);
    return true;
};
wstring autorization()
{
    string login_admin = "admin";
    string pass_admin = "123123";
    string login_librarian = "library";
    string pass_librarian = "123456";
    wstring try_log, try_pass;
    wstring login_user, pass_user;
    Privacy whoUser;
    bool time_auto = true;
    while (time_auto)
    {
        system("CLS");
        cout << "Кто хочет авторизироваться: 1: Пользователь, 2: Админ, 3: Библиотекарь. Выйти: 0\n";
        int who_auto;
        cin >> who_auto;
        if (who_auto == 2)
        {
            cout << "Введите логин\n";
            wcin >> try_log;
            whoUser.login = try_log;
            cout << "Введите пароль\n";
            wcin >> try_pass;
            whoUser.password = try_pass;
            cout << endl;
            if ((whoUser.login == L"admin") && (whoUser.password == L"123123"))
            {
                system("CLS");
                cout << "Добро пожаловать, Админ!";
                return L"admin";
            }
            else
            {
                cout << "Неверный логин и(или) пароль\n";
                system("pause");
            }
        }
        else if (who_auto == 3)
        {
            cout << "Введите логин\n";
            wcin >> try_log;
            whoUser.login = try_log;
            cout << "Введите пароль\n";
            wcin >> try_pass;
            whoUser.password = try_pass;
            cout << endl;
            if ((whoUser.login == L"librarian") && (whoUser.password == L"123456"))
            {
                system("CLS");
                cout << "Добро пожаловать, Библиотекарь!";
                return L"librarian";
            }
            else
            {
                cout << "Неверный логин и(или) пароль\n";
                system("pause");
            }
        }
        else if (who_auto == 1)
        {
            wofstream fin(L"log_and_pass.txt", ios::in | ios::app);
            wifstream fout(L"log_and_pass.txt", ios::out | ios::app);
            wfstream F(L"log_and_pass.txt");
            fout.seekg(0, ios::beg);
            wfstream fileclose;
            fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
            fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
            if (!fout.is_open())
            {
                cout << "Не удается открыть файл\n";
            }
            cout << "Хотите войти в существующий аккунт или создать новый\n";
            cout << "Введите 1: Войти или 2: Зарегистроваться\n";
            int variant1;
            cin >> variant1;
            switch (variant1)
            {
            case(1):
            {
                cout << "Введите логин\n";
                wcin >> try_log;
                whoUser.login = try_log;
                cout << "Введите пароль\n";
                wcin >> try_pass;
                whoUser.password = try_pass;
                wstring line;
                while (getline(fout, line))
                {
                    if (line == whoUser.login)
                    {
                        getline(fout, line);
                        if (line == whoUser.password)
                        {
                            system("CLS");
                            wcout << L"Добро пожаловать," << whoUser.login << "!\n";
                            return whoUser.login;
                        }
                    }
                }
                cout << "Неверный логин и(или) пароль или вы раньше не авторизировались в этой библиотеке\n";
                system("pause");
                break;
            }
            case(2):
            {
                cout << "Запомните данные для входа\n";
                bool time_log = true;
                while (time_log)
                {
                    cout << "Введите логин\n";
                    wcin >> try_log;
                    bool reg_log = true;
                    wstring line;
                    while (getline(fout, line))
                    {
                        if (line.find(try_log) != std::string::npos)
                        {
                            cout << "Пользователь с таким именем уже существует\n";
                            system("pause");
                            reg_log = false;
                            break;
                        }
                    }
                    if (reg_log == true)
                    {
                        whoUser.login = try_log;
                        fin << whoUser.login << L"\n";
                        time_log = false;
                    }
                }
                cout << "Введите пароль\n";
                wcin >> try_pass;
                whoUser.password = try_pass;
                fin << whoUser.password << L"\n";
                system("CLS");
                wcout << L"Добро пожаловать," << whoUser.password << L"!\n";
                return whoUser.login;
            }
            default:
                cout << "Введены некорректные значения\n";
                break;
            }
        }
        else if (who_auto == 0)
        {
            time_auto = false;
            return L"exit";
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const wstring list_books = L"list_of_books.txt";
    const wstring path_user = L"users.txt";
    const wstring path_log_pass = L"log_and_pass.txt";
    wofstream fin;
    wifstream fout(list_books);
    wfstream fileclose;
    fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    cout << "Здравствуйте, вы попали в электроннуую библиотеку!\n";
    cout << "Вам доступен просмотр списка книг в бибилиотеке\n";
    cout << "Если хотите расширить возможности, можете пройти авторизацию (Введите 1: Да или 2: Нет)\n";
    int select_auto_1;
    wstring who_user;
    bool time = true;
    int choose_menu = 0;
    while (true)
    {
        cin >> select_auto_1;
        if (select_auto_1 == 1)
        {

            who_user = autorization();
            break;
        }
        else if (select_auto_1 == 2)
        {
            who_user = L"not_auto_user";
            break;
        }
        else
        {

            cout << "Введены некорректные данные\n";
        }
    }
    if (who_user == L"admin")
    {
        while (time)
        {
            system("CLS");
            menu_admin();
            cout << "Выберите:\n";
            cin >> choose_menu;
            switch (choose_menu)
            {
            case (0):
            {
                time = false;
                break;
            }
            case (1):
            {
                system("CLS");
                show_users();
                cout << endl;
                system("pause");
                break;
            }
            case (2):
                system("CLS");
                add_list_of_books();
                cout << endl;
                system("pause");
                break;
            case (3):
            {
                system("CLS");
                wstring lineToRemove;
                wcout << L"Введите название книги, которую нужно удалить\n";
                getline(wcin, lineToRemove);
                getline(wcin, lineToRemove);
                deleteLineFromList(lineToRemove);
                cout << endl;
                system("pause");
                break;
            }
            case (4):
            {
                system("CLS");
                wstring user_notif;
                wcout << L"Введите пользователя, которому нужно оставить уведомление\n";
                getline(wcin, user_notif);
                getline(wcin, user_notif);
                leave_notif(user_notif);
                cout << "Операция выполнена\n";
                cout << endl;
                system("pause");
                break;
            }
            case (5):
                system("CLS");
                show_list_of_books();
                cout << endl;
                system("pause");
                break;
            case (6):
                system("CLS");
                cout << "Как вы хотите отсортировать список книг по алфавиту: 1 - по жанру, 2 - по названию, 3 - по году публикации \n";
                int sort_choose;
                cin >> sort_choose;
                switch (sort_choose)
                {
                case(1):
                {
                    madearray(2);
                    cout << "Список книг отсортирован по алфавиту по жанру!\n";
                    break;
                }
                case(2):
                {
                    madearray(1);
                    cout << "Список книг отсортирован по алфавиту по названию!\n";
                    break;
                }
                case(3):
                {
                    madearray(3);
                    cout << "Список книг отсортирован по убыванию по году публикации!\n";
                    break;
                }
                default:
                    system("CLS");
                    cout << "Введены некорректные значения!" << endl;
                    system("pause");
                    break;
                }
                system("pause");
                break;
            case (7):
            {
                system("CLS");
                wstring user_notif;
                wcout << L"Введите пользователя, которому нужно установить сроки\n";
                getline(wcin, user_notif);
                getline(wcin, user_notif);
                leave_date(user_notif);
                cout << "Операция выполнена\n";
                cout << endl;
                system("pause");
                break;
            }
            case (8):
            {
                system("CLS");
                wstring user_notif;
                wcout << L"Введите пользователя, которого нужно отредактировать\n";
                getline(wcin, user_notif);
                getline(wcin, user_notif);
                cout << "Как хотите редактировать пользователя?\n";
                cout << "1: Удать заявку пользователя. 2: Удалить бронь пользователя. 3: Удалить все вместе\n";
                cout << "Учитывайте, что если пользователь получил и бронь, и заявку, он должен вернуть все книги. Только после вы можете удалить все вместе.\n";
                cout << "Также при успешном возврате книги у пользователя автоматически будут удалены сроки и уведомления\n";
                int choosetodelete;
                cin >> choosetodelete;
                switch (choosetodelete)
                {
                case (1):
                {
                    if (return_request_lib(user_notif))
                    {
                        cout << "Заявка успешно удалена\n";
                    }
                    else
                    {
                        cout << "Заявка не удалена, некорректные значения\n";
                    }
                    break;
                }
                case (2):
                {
                    if (return_rezerved_lib(user_notif))
                    {
                        cout << "Бронь успешно удалена\n";
                    }
                    else
                    {
                        cout << "Заявка не удалена, некорректные значения\n";
                    }
                    break;
                }
                case(3):
                {
                    if (return_all(user_notif))
                    {
                        cout << "Заявка и бронь удалены\n";
                    }
                    else
                    {
                        cout << "Заявка не удалена, некорректные значения\n";
                    }
                    break;
                }
                default:
                    cout << "Введены некорректные данные\n";
                    break;
                }
                cout << endl;
                system("pause");
                break;
            }
            case (9):
            {
                system("CLS");
                cout << "Введите срок, для которого нужно найти соответствующих пользователей\n";
                wstring line;
                wcin >> line;
                madearraysForUsersDate(line);
                cout << endl;
                system("pause");
                break;
            }
            default:
            {
                system("CLS");
                cout << "Введены некорректные значения!" << endl;
                system("pause");
                break;
            }
            }
        }
    }
    else if (who_user == L"librarian")
    {
        while (time)
        {
            system("CLS");
            menu_librarian();
            cout << "Выберите:\n";
            cin >> choose_menu;
            switch (choose_menu)
            {
            case(0):
            {
                time = false;
                break;
            }
            case (1):
            {
                system("CLS");
                show_users();
                cout << endl;
                system("pause");
                break;
            }
            case (2):
            {
                system("CLS");
                wstring user_notif;
                wcout << L"Введите пользователя, которому нужно оставить уведомление\n";
                getline(wcin, user_notif);
                getline(wcin, user_notif);
                leave_notif(user_notif);
                cout << "Операция выполнена\n";
                cout << endl;
                system("pause");
                break;
            }
            case (3):
                system("CLS");
                show_list_of_books();
                cout << endl;
                system("pause");
                break;
            case(4):
            {
                system("CLS");
                cout << "Как вы хотите отсортировать список книг по алфавиту: 1 - по жанру, 2 - по названию, 3 - по году публикации \n";
                int sort_choose;
                cin >> sort_choose;
                switch (sort_choose)
                {
                case(1):
                {
                    madearray(2);
                    cout << "Список книг отсортирован по алфавиту по жанру!\n";
                    break;
                }
                case(2):
                {
                    madearray(1);
                    cout << "Список книг отсортирован по алфавиту по названию!\n";
                    break;
                }
                case(3):
                {
                    madearray(3);
                    cout << "Список книг отсортирован по убыванию по году публикации!\n";
                    break;
                }
                default:
                    system("CLS");
                    cout << "Введены некорректные значения!" << endl;
                    system("pause");
                    break;
                }
                system("pause");
                break;
            }
            case (5):
            {
                system("CLS");
                wstring user_notif;
                wcout << L"Введите пользователя, которому нужно установить сроки\n";
                getline(wcin, user_notif);
                getline(wcin, user_notif);
                leave_date(user_notif);
                cout << "Операция выполнена\n";
                cout << endl;
                system("pause");
                break;
            }
            case (6):
            {
                system("CLS");
                wstring user_notif;
                wcout << L"Введите пользователя, которого нужно отредактировать\n";
                getline(wcin, user_notif);
                getline(wcin, user_notif);
                cout << "Как хотите редактировать пользователя?\n";
                cout << "1: Удать заявку пользователя. 2: Удалить бронь пользователя. 3: Удалить все вместе\n";
                cout << "Учитывайте, что если пользователь получил и бронь, и заявку, он должен вернуть все книги. Только после вы можете удалить все вместе.\n";
                cout << "Также при успешном возврате книги у пользователя автоматически будут удалены сроки и уведомления\n";
                int choosetodelete;
                cin >> choosetodelete;
                switch (choosetodelete)
                {
                case (1):
                {
                    if (return_request_lib(user_notif))
                    {
                        cout << "Заявка успешно удалена\n";
                    }
                    else
                    {
                        cout << "Заявка не удалена, некорректные значения\n";
                    }
                    break;
                }
                case (2):
                {
                    if (return_rezerved_lib(user_notif))
                    {
                        cout << "Бронь успешно удалена\n";
                    }
                    else
                    {
                        cout << "Бронь не удалена, некорректные значения\n";
                    }
                    break;
                }
                case(3):
                {
                    if (return_all(user_notif))
                    {
                        cout << "Заявка и бронь удалены\n";
                    }
                    else
                    {
                        cout << "Заявка и бронь не удалены, некорректные значения\n";
                    }
                    break;
                }
                default:
                    cout << "Введены некорректные данные\n";
                    break;
                }
                cout << endl;
                system("pause");
                break;
            }
            case (7):
            {
                system("CLS");
                cout << "Введите срок, для которого нужно найти соответствующих пользователей\n";
                wstring line;
                wcin >> line;
                madearraysForUsersDate(line);
                cout << endl;
                system("pause");
                break;
            }
            default:
            {
                system("CLS");
                cout << "Введены некорректные значения!" << endl;
                system("pause");
                break;
            }
            }
        }
    }
    else if (who_user == L"exit")
    {
        return 0;
    }
    else if (who_user == L"not_auto_user")
    {
        while (time)
        {
            system("CLS");
            menu_user_not_auto();
            int choose_menu;
            cin >> choose_menu;
            switch (choose_menu)
            {
            case (1):
            {
                system("CLS");
                show_list_of_books();
                cout << endl;
                system("pause");
                break;
            }
            case (2):
            {
                time = false;
                break;
            }
            default:
            {
                system("CLS");
                cout << "Введены некорректные значения!" << endl;
                system("pause");
                break;
            }
            }
        }
    }
    else
    {
        User user;
        while (time)
        {
            wifstream fout("users.txt", ios::out | ios::app);
            wfstream F("users.txt");
            fout.seekg(0, ios::beg);
            fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
            wstring line;
            int finduser = 0;
            while (getline(fout, line))
            {
                if (line.find(who_user) != std::string::npos)
                {
                    finduser++;
                    break;
                }
            }
            if (finduser == 0)
            {
                wofstream fin("users.txt", ios::in | ios::app);
                fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
                fin << who_user << L"\n";
                fin << L"Заявка:" << L"\n";
                fin << endl; // строка для заявки
                fin << L"Бронь:" << L"\n";
                fin << endl; // строка для брони
                fin << L"Уведомления от библиотекаря:" << L"\n";
                fin << endl; // строка для уведа
                fin << L"Количество дней до сдачи книги:" << L"\n";
                fin << endl; // строка для срока
                fin << L"\n";
            }
            system("CLS");
            menu_user_auto();
            cout << "Выберите:\n";
            cin >> choose_menu;
            switch (choose_menu)
            {
            case (0):
                time = false;
                break;
            case (1):
            {
                system("CLS");
                view_notif(who_user);
                cout << endl;
                system("pause");
                break;
            }
            case (2):
            {
                system("CLS");
                show_list_of_books();
                cout << endl;
                system("pause");
                break;
            }
            case (3):
            {
                system("CLS");
                cout << "Введите название книги, на которую хотите оформить заявку\n";
                user.request;
                getline(wcin, user.request);
                getline(wcin, user.request);
                make_request(user.request, who_user);
                system("pause");
                break;
            }
            case (4):
            {
                system("CLS");
                cout << "Введите название книги, на которую хотите оформить бронь\n";
                wstring nameofRez;
                getline(wcin, nameofRez);
                getline(wcin, nameofRez);
                if (madearraylist(nameofRez) == 0)
                {
                    cout << "Введите автора\n";
                    wstring authorofRez;
                    getline(wcin, authorofRez);
                    cout << "Введите год публикации\n";
                    int yearofRez;
                    cin >> yearofRez;
                    wstring year;
                    year = to_wstring(yearofRez);
                    cout << "Введите жанр\n";
                    wstring genreofRez;
                    getline(wcin, genreofRez);
                    getline(wcin, genreofRez);
                    user.reservation = L"'" + nameofRez + L"' " + L"Автор: " + authorofRez + L" " + year + L" " + L"Жанр: " + genreofRez + L" ";
                    make_rezerved(user.reservation, who_user);
                    system("pause");
                    break;
                }
                else
                {
                    cout << "Такая книга уже есть в библиотеке!\n";
                    system("pause");
                    break;
                }
            }
            case (5):
            {
                system("CLS");
                wcout << L"Введите название книги/автора/год/жанр книги, которую вы хотите найти\n";
                wstring searchline;
                getline(wcin, searchline);
                getline(wcin, searchline);
                int countOfBook = madearraylist(searchline);
                cout << "Найдено книг: " << countOfBook << "\n";
                system("pause");
                break;
            }
            case (6):
            {
                system("CLS");
                return_request(who_user);
                cout << "Ваша заявка успешно удалена" << endl;
                system("pause");
                break;
            }
            case (7):
            {
                system("CLS");
                return_rezerved(who_user);
                cout << "Операция выполнена" << endl;
                system("pause");
                break;
            }
            case (8):
            {
                system("CLS");
                cout << "Как вы хотите отсортировать список книг по алфавиту: 1 - по жанру, 2 - по названию, 3 - по году публикации \n";
                int sort_choose;
                cin >> sort_choose;
                switch (sort_choose)
                {
                case(1):
                {
                    madearray(2);
                    cout << "Список книг отсортирован по алфавиту по жанру!\n";
                    break;
                }
                case(2):
                {
                    madearray(1);
                    cout << "Список книг отсортирован по алфавиту по названию!\n";
                    break;
                }
                case(3):
                {
                    madearray(3);
                    cout << "Список книг отсортирован по убыванию по году публикации!\n";
                    break;
                }
                default:
                    system("CLS");
                    cout << "Введены некорректные значения!" << endl;
                    system("pause");
                    break;
                }
                system("pause");
                break;
            }
            default:
            {
                system("CLS");
                cout << "Введены некорректные значения!" << endl;
                system("pause");
                break;
            }
            }
        }
    }
    return 0;
}


