#include <bits/stdc++.h>
using namespace std;

class KMP {

public:

  KMP(vector<int>& p) {
    pattern = p;
    lps.resize(pattern.size());
    int j = 0;
    for (int i = 1; i < pattern.size(); i++) {
      while (j > 0 && pattern[i] != pattern[j]) j = lps[j-1];
      if (pattern[i] == pattern[j]) j++;
      lps[i] = j;
    }
  }

  void match(vector<int>& text, vector<int>& occurrences) {
    int j = 0;
    for (int i = 0; i < text.size(); i++) {
      while (j > 0 && text[i] != pattern[j]) j = lps[j-1];
      if (text[i] == pattern[j]) j++;
      if (j == pattern.size()) {
        occurrences.push_back(i-j+1);
        j = lps[j-1];
      }
    }
  }


private:

  vector<int> pattern;
  vector<int> lps;

};