---
title: Assignments
---

<section>

For each reading assignment, write one page describing your experience[^your_experience] with the reading. Submit a reading response by creating a [Google Document] and sharing it with me. Title your document with the name of the class, your name, and the assignment number. For instance, Frank Zappa might use _MAT201B Frank Zappa Assignment 4_ as the title of his response to reading assignment 4.

[^your_experience]: Answer this question: What is most important thing for _you_ to say about this reading? Was the reading useless?

For each programming assignment, submit your code by pushing it to your [Github] repository for this class. Unless the assignment specifies otherwise, submit your programming assignment solution as a single _.cpp_ placed in a folder named _assignement_.

</section>

## Assignment 1 | Due 2019-01-28 by 1700

Read, study, and report on chapters 5, 6, and 7 of _Fundamentals of Computer Graphics_ (2016 Marschner & Shirley).

Write an allolib program that arranges "pixels" in 3D space according to various systems:

1. Load an image from a file; You choose the image. Pick a colorful image that is smaller than 1000x1000.
2. Using the pixel colors from that image, generate a Mesh of points.
3. Allow the user to organize the mesh vertices in 3D using keyboard interaction:
  - `1` returns the points to the row/column positions of each pixel in the original image.
  - `2` places each point in an [RGB color space](https://en.wikipedia.org/wiki/RGB_color_space) "Cube" according to its color.
  - `3` builds an [HSV color space](https://en.wikipedia.org/wiki/HSL_and_HSV) "Cylinder" with the points.
  - `4` organizes the points according to your own aesthetic goals; Pick some good ones. Make something interesting!
4. Animate the transitions between each of the organization states above. Each pixel should take 1 second to move to its new location at a constant velocity.

For the software above, while you are developing, your files and folders should look like this:

    MAT201B-2019/your-repo-name/color_spaces/color_spaces.cpp
    MAT201B-2019/your-repo-name/color_spaces/color_spaces.jpg

To turn in your software, you must create a repository on github.com named mat201b. Once that is done, add and commit your work to that repository. The files in that repository should look like this:

    color_spaces/color_spaces.cpp
    color_spaces/your_image_file.jpg

Frequently commit and push your code to your repository.


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
