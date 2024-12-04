#include <bits/stdc++.h>
using namespace std;

int kmp(string String, string pattern)
{
    int i = 0, j = 0, m = pattern.length(), n = String.length();
    pattern = ' ' + pattern;
    vector<int> piTable(m + 1, 0);

    for (i = 2; i <= m; i++)
    {
        while (j > 0 && pattern[j + 1] != pattern[i])
            j = piTable[j];
        if (pattern[j + 1] == pattern[i])
            j++;
        piTable[i] = j;
    }

    j = 0;
    for (i = 0; i < n; i++)
    {
        while (j > 0 && pattern[j + 1] != String[i])
            j = piTable[j];
        if (pattern[j + 1] == String[i])
            j++;
        if (j == m)
        {
            return i - m + 1;
        }
    }
    return -1;
}

int main()
{
    string pattern, String;

    cout << "Enter the pattern to search: ";
    getline(cin, pattern);

    cout << "Enter the string to search in: ";
    getline(cin, String);
    int index = kmp(String, pattern);
    if (index == -1)
        cout << "The pattern is not found\n";
    else
        cout << "The pattern \"" << pattern << "\" is found in the given string \""
             << String << "\" at index " << index << "\n";

    return 0;
}
