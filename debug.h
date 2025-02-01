#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <utility>
#include <tuple>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

#ifdef DGF
int _main();
#define main                      \
    main()                        \
    {                             \
        freopen(DGF, "r", stdin); \
        return _main();           \
    }                             \
    int _main
#endif

#if DG == 1
#define dn()      \
    cout << endl; \
    fflush(stdout)
#define dv(...) _print_var(#__VA_ARGS__, __VA_ARGS__)
#define dvw(...)                           \
    _print_var(#__VA_ARGS__, __VA_ARGS__); \
    _debug_wait()
#define da(arr, n) _to_string_custom_arr(arr, n)
#define di(seq, i) _to_string_custom_seq_ind(seq, i)
#define dw() _debug_wait()
template <typename T>
string _to_string_custom(const T &);
template <typename T, typename U>
string _to_string_custom(const pair<T, U> &);
template <typename... Args>
string _to_string_custom(const tuple<Args...> &);
template <typename T>
string _to_string_custom(const vector<T> &);
template <typename T>
string _to_string_custom(const list<T> &);
template <typename T>
string _to_string_custom(const set<T> &);
template <typename T, typename U>
string _to_string_custom(const map<T, U> &);
template <typename T>
string _to_string_custom(const stack<T> &);
template <typename T>
string _to_string_custom(const queue<T> &);
template <typename T>
string _to_string_custom(const deque<T> &);
template <typename T>
string _to_string_custom(const priority_queue<T> &);
template <typename T>
string _to_string_custom(const priority_queue<T, vector<T>, greater<T>> &);
template <typename T>
string _to_string_custom_arr(const T *, int);
template <typename T>
string _to_string_custom_seq_ind(const T &, int);
template <typename T>
string _to_string_custom(const T &t)
{
    stringstream ss;
    ss << t;
    return ss.str();
}
template <typename T, typename U>
string _to_string_custom(const pair<T, U> &p)
{
    stringstream ss;
    ss << "(" << _to_string_custom(p.first) << ", " << _to_string_custom(p.second) << ")";
    return ss.str();
}
template <typename Tuple, size_t... Is>
void _tuple_to_string_helper(stringstream &ss, const Tuple &t, std::index_sequence<Is...>)
{
    size_t n = 0;
    using expander = int[];
    (void)expander{0, (void(ss << (n++ ? ", " : "") << _to_string_custom(std::get<Is>(t))), 0)...};
}
template <typename... Args>
string _to_string_custom(const tuple<Args...> &t)
{
    stringstream ss;
    ss << "(";
    _tuple_to_string_helper(ss, t, std::index_sequence_for<Args...>{});
    ss << ")";
    return ss.str();
}
template <typename T>
string _to_string_custom(const vector<T> &vec)
{
    stringstream ss;
    ss << "[";
    for (int i = 0; i < vec.size(); i++)
    {
        ss << _to_string_custom(vec[i]);
        if (i < vec.size() - 1)
            ss << ", ";
    }
    ss << "]";
    return ss.str();
}
template <typename T>
string _to_string_custom(const list<T> &lst)
{
    stringstream ss;
    ss << "[";
    auto it = lst.begin();
    while (it != lst.end())
    {
        ss << _to_string_custom(*it);
        ++it;
        if (it != lst.end())
            ss << " -> ";
    }
    ss << "]";
    return ss.str();
}
template <typename T>
string _to_string_custom(const set<T> &s)
{
    stringstream ss;
    ss << "{";
    auto it = s.begin();
    while (it != s.end())
    {
        ss << _to_string_custom(*it);
        ++it;
        if (it != s.end())
            ss << ", ";
    }
    ss << "}";
    return ss.str();
}
template <typename T, typename U>
string _to_string_custom(const map<T, U> &m)
{
    stringstream ss;
    ss << "{";
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        ss << _to_string_custom(it->first) << ": " << _to_string_custom(it->second);
        auto temp = it;
        if (++temp != m.end())
            ss << ", ";
    }
    ss << "}";
    return ss.str();
}
template <typename T>
string _to_string_custom(const stack<T> &sk)
{
    stringstream ss;
    stack<T> temp = sk;
    ss << ">";
    while (!temp.empty())
    {
        ss << _to_string_custom(temp.top());
        temp.pop();
        if (!temp.empty())
            ss << ", ";
    }
    ss << ">";
    return ss.str();
}
template <typename T>
string _to_string_custom(const queue<T> &qe)
{
    stringstream ss;
    queue<T> temp = qe;
    ss << "<";
    while (!temp.empty())
    {
        ss << _to_string_custom(temp.front());
        temp.pop();
        if (!temp.empty())
            ss << ", ";
    }
    ss << "<";
    return ss.str();
}
template <typename T>
string _to_string_custom(const deque<T> &dq)
{
    stringstream ss;
    ss << "#";
    for (int i = 0; i < dq.size(); i++)
    {
        ss << _to_string_custom(dq[i]);
        if (i < dq.size() - 1)
            ss << ", ";
    }
    ss << "#";
    return ss.str();
}
template <typename T>
string _to_string_custom(const priority_queue<T> &pq)
{
    stringstream ss;
    priority_queue<T> temp = pq;
    ss << "$";
    while (!temp.empty())
    {
        ss << _to_string_custom(temp.top());
        temp.pop();
        if (!temp.empty())
            ss << ", ";
    }
    ss << "$";
    return ss.str();
}
template <typename T>
string _to_string_custom(const priority_queue<T, vector<T>, greater<T>> &pq)
{
    stringstream ss;
    priority_queue<T, vector<T>, greater<T>> temp = pq;
    ss << "$";
    while (!temp.empty())
    {
        ss << _to_string_custom(temp.top());
        temp.pop();
        if (!temp.empty())
            ss << ", ";
    }
    ss << "$";
    return ss.str();
}
template <typename T>
string _to_string_custom_arr(const T *arr, int n)
{
    stringstream ss;
    ss << "[";
    for (int i = 0; i < n; i++)
    {
        ss << arr[i];
        if (i < n - 1)
            ss << ", ";
    }
    ss << "]";
    return ss.str();
}
template <typename T>
string _to_string_custom_seq_ind(const T &seq, int i)
{
    stringstream ss;
    ss << "[" << i << "] = " << seq[i];
    return ss.str();
}
template <typename... Args>
void _print_var(const char *names, Args &&...args)
{
    stringstream ss(names);
    string name;
    int index = 0;
    vector<string> values = {_to_string_custom(args)...};
    while (getline(ss, name, ','))
    {
        if (index > 0)
            cout << ", ";
        name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
        name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);
        if (name.find("\"") == 0)
        {
            cout << values[index++];
        }
        else if (name.find("da(") == 0)
        {
            name.erase(0, 3);
            cout << name << " = " << values[index++];
            getline(ss, name, ',');
        }
        else if (name.find("di(") == 0)
        {
            name.erase(0, 3);
            cout << name << values[index++];
            getline(ss, name, ',');
        }
        else
        {
            name.erase(0, name.find_first_not_of(" "));
            name.erase(name.find_last_not_of(" ") + 1);
            cout << name << " = " << values[index++];
        }
    }
    cout << endl;
    fflush(stdout);
}
void _debug_wait()
{
#ifdef _WIN32
    FILE *temp = freopen("CON", "r", stdin);
#else
    FILE *temp = freopen("/dev/tty", "r", stdin);
#endif
    printf("Press F5 to continue...");
    fflush(stdout);
    // place a breakpoint here with F9
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
#ifdef DGF
    freopen(DGF, "r", stdin);
    printf("\n");
    fflush(stdout);
#endif
}
#else
#define dn()
#define dv(...)
#define dvw(...)
#define da(arr, n)
#define di(arr, n)
#define dw()
#endif