**<p align="center"> Wrocław University of Science and Technology </p>**
**<p align="center"> Computer Science, Faculty of Electronics, 6 semester </p>**
<p align="center"> Radosław Lis, 241385 </p>

# Table of Contents
- [General info](#desc)
- [Run](#run)
- [Prerequisites](#pre)

<a name="desc"></a>
# General info
F1-race simulation
- 14 F1 drivers - with randomly given skill, decreasing fuel condition, overtaking AI and obviously desire of winning the race
- 3 pitstops - with 3 engineers in each, unfortunately each pitstop can handle any driver
- 9 engineers - with randomly given skill, their job is changing wheels and refueling
- 2 storekeepers - with randomly given skill, their job is recycling used wheels and supplying fuel to the pitstop

<a name="run"></a>
# Run

```
$ mkdir build && cd build
$ cmake ..
$ make
$ ./f1-race
```
<a name="pre"></a>
# Prerequisites
- [ncurses](https://en.wikipedia.org/wiki/Ncurses)
- [compiler with c++17 support](https://gcc.gnu.org/)

<a name="pre"></a>
# Simulation
Best to see in 150%. Chill, they are not new Schumachers, just simulation is speeded 4x up. Only 8 bolides because of colours variations :(
![](https://github.com/radosz99/f1-race/blob/master/resized_race.gif)

