## Datatblr
##### Author: Johannes Schütt
##### Co-author: Claudia Saalbach

##### [Chair of Empirical Social Research Methods at the University of Potsdam](https://uni-potsdam.de/soziologie-methoden), Universität Potsdam

Datatblr is a program that generates a table collection with the univariate description of all metric and categorical variables in a dataset. Datatblr delivers a LaTeX and a pdf-document.

Datatblr is suitable for generating table volumes that typically appear in the appendix of research reports, or for the preparation of more detailed analysis.

### Dependencies
* R base (3.6.3 or newer)  [CRAN](https://cloud.r-project.org/)
  * [dplyr](https://cran.r-project.org/web/packages/dplyr/index.html) package
  * [knitr](https://yihui.org/knitr/) package
  * [pkgcond](https://cran.r-project.org/web/packages/pkgcond/index.html) package
  * [rio](https://cran.r-project.org/web/packages/rio/index.html) package
* LaTeX [TeX Live](https://www.tug.org/texlive/)
* pandoc  [PANDOC.ORG](https://pandoc.org/)

### Compile & Run
**UNIX:** To compile the Datatblr user interface, run the command `make` inside your console in the directory of the program folder. After that, you can run the compiled executable by double-clicking on it or by running the command `./Datatblr`.

You can of course just dig straight into the `R` code (starting from `render.R`) and have fun with it  :slightly_smiling_face:.

The user interface is compatible with UNIX systems. If you are running **Windows**, you have to work directly with the R files!

### License
[GNU General Public License v2.0 only](https://github.com/johschuett/Datatblr/blob/master/LICENSE)
