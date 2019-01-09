---
title: Assignments
author: Karl Yerkes
date: 'January 8, 2019'
---

<section>

For each reading assignment, write one page describing your experience[^your_experience] with the reading. Submit a reading response by creating a [Google Document] and sharing it with me. Title your document with the name of the class, your name, and the assignment number. For instance, Frank Zappa might use _MAT201B Frank Zappa Assignment 4_ as the title of his response to reading assignment 4.

[^your_experience]: Answer this question: What is most important thing for _you_ to say about this reading? Was the reading useless?

For each programming assignment, submit your code by pushing it to your [Github] repository for this class. Unless the assignment specifies otherwise, submit your programming assignment solution as a single _.cpp_ placed in a folder named _assignement_.

</section>

## Assignment 0 | Due 2019-01-14 by 1700

Read and study the first two chapters of _Fundamentals of Computer Graphics_ (2016 Marschner & Shirley).

Write a C++ program that accepts sentences typed on the terminal, printing each sentence with its words reversed[^words_reversed]. You may start with the code below.

[^words_reversed]: Reverse each word of the sentence individually. For instance: "this is the truth" becomes "siht si eht hturt".

``` {#lst:starter_code .cpp}
#include <iostream>
#include <string>
using namespace std;
int main() {
  while (true) {
    printf("Type a sentence (then hit return): ");
    string line;
    getline(cin, line);
    if (!cin.good()) {
      printf("Done\n");
      return 0;
    }

    // put your code here
    //
  }
}
```

To submit this assignment, place your solution in a file named _reverse_words.cpp_ and put the file in a folder named _assignment_ in your github repository. See [how to git] for more information.

[Google Document]: https://drive.google.com
[Github]: https://github.com
[how to git]: how-to-git.html
