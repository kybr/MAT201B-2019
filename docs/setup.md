---
title: Getting Started
author: Karl Yerkes
date: 'January 8, 2019'
---

# macOS

- Install _Xcode_: Open the _App Store_ app. Search for "xcode". Install the first result. Wait for this to finish before moving on.
- Install _[Homebrew]_: Open the _Terminal_ app. Aim your browser at <https://brew.sh>. Copy and paste the text of the install command into the _Terminal_ app.
- Use the _brew_ command to install some software. In the _Terminal_ app, run this command: `brew install git git-lfs cmake libsndfile graphviz doxygen`.

# Windows

- Install _[Chocolatey]_: Aim your browser at <https://chocolatey.org/install>. Follow the directions there to install _Chocolatey_. Wait for this to finish before moving on.
- Use the _choco_ command to install a C++ compiler. Open _cmd.exe_ (_Command Prompt_) **as administrator** and run this command: `choco install -y visualstudio2017buildtools visualstudio2017-workload-vctools`
- Use the _choco_ command to install some software. Open _cmd.exe_ (_Command Prompt_) **as administrator** and run this command: `choco install -y git git-lfs cmake graphviz doxygen atom vscode`
- Install _[libsndfile]_: Aim your browser at <http://www.mega-nerd.com/libsndfile/#Download>. Download and install the 64-bit version: _libsndfile-1.0.xx-w64-setup.exe_.

# Ubuntu

- Install things: `sudo apt install build-essential git git-lfs cmake graphviz doxygen libsndfile1-dev`

- - -

# Create a Github repository

If you do not already have a [Github] account, create one now. Aim your browser at <https://github.com> and create an account. Once you have an account, create a repository called _MAT201B-yourname_ where _yourname_ is your name or nick name or internet handle or something.

[Github]: https://github.com
[Chocolatey]: https://chocolatey.org
[Homebrew]: https://brew.sh
[libsndfile]: http://www.mega-nerd.com/libsndfile
