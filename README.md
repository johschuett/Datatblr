## Datatblr
##### Author: Johannes Schütt, Claudia Saalbach

##### [Chair of Empirical Social Research Methods, University of Potsdam](https://uni-potsdam.de/soziologie-methoden)

The Datatblr program generates a table volume containing the univariate description of all metric and categorical variables of a data set. Datatblr delivers the table volume as LaTeX and PDF file.

Datatblr is suitable for generating table volumes that typically appear in the appendix of research reports, or for the preparation of more detailed analysis.

### Dependencies
* R base (3.6.3 or newer)  [CRAN](https://cloud.r-project.org/)
  * [dplyr](https://cran.r-project.org/web/packages/dplyr/index.html) package
  * [rio](https://cran.r-project.org/web/packages/rio/index.html) package
* LaTeX [TeX Live](https://www.tug.org/texlive/)

#### To build the program:
* G++ compiler (std=c++17)
* Make

### Release

We recommend downloading the latest **stable release** of the program. If you download the program from the master branch, there is a chance that it may be unstable or not run at all.

### Installation

The user interface is compatible with **UNIX** systems. If you are running **Windows**, you have to work directly with the R files! (You might want to check out the lite version.)

#### Build

To build the Datatblr user interface, switch to the project folder, and run:

```shell
sh build.sh
```

#### Run

The program is operated via a console (Terminal), either by double-clicking on the executable (datatblr) or running the command:

```shell
./datatblr
```
#### Set R working directory

You can move the executable as you like. Make sure to set your R working directory to `/path/to/datatblr` **or** move the `dtblr_core` folder into your working directory. There, Datatblr saves the table volume (TEX and PDF).

You can set your working directory in your `.Rprofile` with this command:

```R
setwd("/path/to/working_directory")
```

You can also add the path of the executable to your PATH environment variable and then run the program using the command `datatblr`.

### Usage example

Open Datatblr via a console:

```shell
./datatblr
```
and follow the instructions step by step.

**or**

Copy your data and your meta file to your R working directory and run:

```shell
./datatblr data.csv meta.csv 1
```

to generate a table volume with *summarized missings*.

Alternatively, you can exchange the 1 with a 2 to generate a table volume *without missings*:

```shell
./datatblr data.csv meta.csv 2
```

### Output
You can edit the preamble for the LaTeX files in `dtblr_core/write_output.R`.

### License
Copyright (c) Johannes Schütt, Claudia Saalbach 2020.

[GNU General Public License v2.0 only](https://github.com/johschuett/Datatblr/blob/master/GPL-2.0)

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
