# Premium Silence by Present Day Production

To build, all you have to do is load this project in your favorite IDE 
(CLion/Visual Studio/VSCode/etc) 
and click 'build' for one of the targets (templates, JUCE examples, Projucer, etc).

You can also generate a project for an IDE by using (Mac):
```
cmake -G Xcode -B build
```
Windows:
```
cmake -G "Visual Studio 16 2022" -B build
```

For package management, I'm using the amazing CPM.cmake:
#https://github.com/TheLartians/CPM.cmake
It automatically fetches JUCE from git, but you can also set the variable:
CPM_JUCE_SOURCE to point it to a local folder, by using:
``-DCPM_JUCE_SOURCE="Path_To_JUCE"``
when invoking CMake

JUCE can be found here:
#https://github.com/juce-framework/JUCE

License:
Anything from me in this repo is completely free to use for any purpose. 
However, please check the licenses for CPM and JUCE as described in their repo. 
