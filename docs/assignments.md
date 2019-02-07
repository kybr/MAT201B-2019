---
title: Assignments
---

<section>

For each reading assignment, write one page describing your experience[^your_experience] with the reading. Submit a reading response by creating a [Google Document] and sharing it with me. Title your document with the name of the class, your name, and the assignment number. For instance, Frank Zappa might use _MAT201B Frank Zappa Assignment 4_ as the title of his response to reading assignment 4.

[^your_experience]: Answer this question: What is most important thing for _you_ to say about this reading? Was the reading useless?

For each programming assignment, submit your code by pushing it to your [Github] repository for this class. Unless the assignment specifies otherwise, submit your programming assignment solution as a single _.cpp_ placed in a folder named _assignment_.

</section>

## Assignment 3 | Due 2019-02-13 by 1700

Implement a particle system starting with _example/particles-p0.cpp_:

1. Copy the starter code to a file named _particles-p1.cpp_. Implement a stable[^stability] particle system based on _[Newton's law of universal gravitation]_ where all particles have a mass of 1.
2. Copy the file _particles-p1.cpp_ to _particles-p2.cpp_. Implement a stable particle system that uses mass relationships like those found in our solar system[^behaviour]. Refer to [List of Solar System objects]. You do not have to use the exact mass numbers, but there should be only 1 very, very large mass (like the sun), only a few very large masses (like planets), and more medium masses (moons), and many small masses (comets).
3. Copy the file _particles-p2.cpp_ to _particles-p3.cpp_. Introduce a GUI-controlled parameter that reduces the [symmetry] of the gravitational forces, making them gradually asymmetrical. Gravity acts on each pair of particles in an "equal by opposite" way: if $a$ attracts $b$ by $F$ amount, then $b$ attracts $a$ by $F$ amount. If instead, $a$ attracts $b$ by $F$ while $b$ attracts $a$ by $F/2$, then the forces are not equal and opposite; They are asymmetrical. What happens?
4. Copy the file _particles-p3.cpp_ to _particles-p4.cpp_. Start with one of the systems above. Create your own twist on the system. Make something different and interesting.

[^stability]: A stable system is one where most of the particles stay clustered together. If the system is not stable, then many particles will fly away, far from view. There are many strategies to achieve stability. Tune parameters such as time step (smaller is more stable), viscous drag (larger is more stable), and the gravitational constant. Limit large forces.

[^behaviour]: There is a reason why our solar system seems stable. The mass relationships between celestial bodies largely determine how the system behaves as a whole. Here we find another way to achieve stability: mimic a real, stable system.

[Newton's law of universal gravitation]: https://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation
[List of Solar System objects]: https://en.wikipedia.org/wiki/List_of_Solar_System_objects_by_size
[symmetry]: https://en.wikipedia.org/wiki/Symmetry

In completing this assignment, you will face some challenges: collisions, large forces, keeping objects in view, and issues with scale. Here are a few hints.

When particles come very close to one another, the gravitational force between them becomes *very* large. These particles will fly apart *very* quickly and move out of the volume of the camera. You will never see them again. You may limit large forces: 1) decide on a global maximum force value and 2) if any force is larger than the maximum value, limit that force to the maximum value. Alternatively or in addition, you may implement "collisions". When a pair of particles comes close to one another, make them bounce off one another.

While your system is running, ideally most of the particles are "in frame"---That is, they are between the near and far clipping planes of the camera and the whole system in within the volume of the camera. To keep them in the frame, we can dynamically adjust the near and far clipping planes, point the camera at the center of the system, scale the system up or down, and/or tame the system itself by "respawning" particles that go out of frame or using a global gravity to keep the system together.


## Assignment 2 | Due 2019-02-04 by 1700

Study and work along with chapters 1 and 2 of [_The Nature of Code_] by Daniel Shiffman. Use [_Processing_]. Study [mass-spring-two-dimension.cpp] and try to add a fourth Mass and a fourth Spring.

[_The Nature of Code_]: https://natureofcode.com
[_Processing_]: https://processing.org
[mass-spring-two-dimension.cpp]: https://github.com/kybr/MAT201B-2019/blob/master/example/mass-spring-two-dimension.cpp

## Assignment X | Due always

Study the examples in allolib. For each example in the `allolib/examples` folder, build and run the example, observe the output, and study the source code. Make lists of notes and questions to submit to me. If there is no assignment currently pending, then this is your assignment.

## Assignment 1 | Due 2019-01-28 by 1700

Read, study, and report on chapters 5, 6, and 7 of _Fundamentals of Computer Graphics_ (2016 Marschner & Shirley).

Write an allolib program that arranges "pixels" in 3D space according to various systems:

1. Load an image from a file; You choose the image, but it must be a .jpg or .png file. Pick a colorful image that is smaller than 1000x1000.
2. Using the pixel colors from that image, generate a Mesh of points.
3. Allow the user to organize the mesh vertices in 3D using keyboard interaction:
  - `1` returns the points to the row/column positions of each pixel in the original image.
  - `2` places each point in an [RGB color space](https://en.wikipedia.org/wiki/RGB_color_space) "Cube" according to its color.
  - `3` builds an [HSV color space](https://en.wikipedia.org/wiki/HSL_and_HSV) "Cylinder" with the points.
  - `4` organizes the points according to your own aesthetic goals; Pick some good ones. Make something interesting!
4. Animate the transitions between each of the organization states above. Each pixel should take 1 second to move to its new location at a constant velocity.

For the software above, while you are developing, your files and folders should look like this:

    MAT201B-2019/your-repo-name/assignments/color_spaces.cpp
    MAT201B-2019/your-repo-name/assignments/color_spaces.jpg

To turn in your software, you must create a repository on github.com named mat201b. Once that is done, add and commit your work to that repository. The files in that repository should look like this:

    assignments/color_spaces.cpp
    assignments/color_spaces.jpg

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
