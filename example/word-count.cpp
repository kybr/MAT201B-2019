// replicate the wc command
//
// 3. accept multiple lines
// 4. accumulate statistics
// 5. test against the wc command
//

#include <iostream>
#include <string>
using namespace std;
int main() {
  int characterCount = 0;
  int wordCount = 0;
  int lineCount = 0;

  while (true) {
    string line;             // line == ""
    getline(cin, line);      // get a line from the input
    if (!cin.good()) break;  // end while loop

    lineCount++;  // lineCount = 1 + lineCount;

    // 1. calculate the length of a line
    int length = 0;
    while (true) {
      if (line[length] == '\0') break;
      length = 1 + length;
    }
    // printf("the length is %d characters\n", length);
    characterCount += length;  // characterCount = characterCount + length

    // 2. count the words in a line
    int words = 0;
    char last = ' ';
    for (int i = 0; i < length; i++) {
      if (last == ' ' && line[i] != ' ') words++;
      last = line[i];
    }
    // printf("the number of words is %d\n", words);
    wordCount += words;
  }

  printf("\t%d\t%d\t%d\n", lineCount, wordCount, characterCount);
}
