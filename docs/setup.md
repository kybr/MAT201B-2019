---
title: Getting Started
author: Karl Yerkes
date: 'January 8, 2019'
---

# Ready your computer

You will develop software in C++ on you personal machine. We need to prepare your machine for this task.

## macOS

- Install _Xcode_: Open the _App Store_ app. Search for "xcode". Install the first result. Wait for this to finish before moving on.
- Install _[Homebrew]_: Open the _Terminal_ app. Aim your browser at <https://brew.sh>. Copy and paste the text of the install command into the _Terminal_ app.
- Use the _brew_ command to install some software. In the _Terminal_ app, run this command: `brew install git git-lfs cmake libsndfile graphviz doxygen`.
- Use the _brew_ command to install [Atom] and [Code]. In the _Terminal_ app, run this command: `brew cask install atom visual-studio-code`

## Windows

- Install _[Chocolatey]_: Aim your browser at <https://chocolatey.org/install>. Follow the directions there to install _Chocolatey_. Wait for this to finish before moving on.
- Use the _choco_ command to install some software. Open _cmd.exe_ (_Command Prompt_) **as administrator** and run this command: `choco install -y git git-lfs cmake graphviz doxygen.install atom vscode`
- Install _[libsndfile]_: Aim your browser at <http://www.mega-nerd.com/libsndfile/#Download>. Download and install the 64-bit version: _libsndfile-1.0.xx-w64-setup.exe_.
- Use the _choco_ command to install a C++ compiler. Open _cmd.exe_ (_Command Prompt_) **as administrator** and run this command: `choco install -y visualstudio2017buildtools visualstudio2017-workload-vctools`

## Ubuntu

- Install things: `sudo apt install build-essential git git-lfs cmake graphviz doxygen libsndfile1-dev`


# Get the course repository

You will work from a git repository ([MAT201B-2019]) containing examples, starter code, and a creative coding framework called [allolib]. Before you get this repository, think carefully about where on your computer you should keep materials related to this course. Once you have made that folder, get on a command line[^command_line] and execute these commands:

    cd path/to/your/folder/for/this/class
    git clone https://github.com/kybr/MAT201B-2019
    cd MAT201B-2019
    git submodule update --init --recursive
    ./allolib/run.sh allolib/examples/graphics/2D.cpp


[^command_line]: Windows users open _Git Bash_, not _Command Prompt_. macOS users open the _Terminal_ app.

Note that the first command will not work if you take it literally. You must decide for yourself what _path/to/your/folder/for/this/class_ should be.


# Create your Github repository

If you do not already have a [Github] account, create one now. Aim your browser at <https://github.com> and create an account. Once you have an account, create a repository called _MAT201B-yourname_ where _yourname_ is your name or nick name or internet handle or something. Once you have created your repository, get that repository onto your computer, using the command line:

    cd path/to/your/folder/for/this/class
    cd MAT201B-2019
    git clone https://github.com/your-github-name/your-repository-name
    cd your-repository-name


[Github]: https://github.com
[Chocolatey]: https://chocolatey.org
[Homebrew]: https://brew.sh
[libsndfile]: http://www.mega-nerd.com/libsndfile
[MAT201B-2019]: https://github.com/kybr/MAT201B-2019
[allolib]: https://github.com/AlloSphere-Research-Group/allolib
[Atom]: https://atom.io
[Code]: https://code.visualstudio.com
