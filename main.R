######################################################################
# Datatblr stable-1.0                                                #
# Johannes Schütt, Chair of Empirical Methods, University of Potsdam #
# johschuett@uni-potsdam.de                                          #
# License: GNU General Public License v3.0                           #
######################################################################

# Version: R 4.0.0

## @knitr setup

# Packages
library(dplyr)
library(pkgcond)
library(rio)

# Scripts
source("import.R")

## @knitr main

source("functions.R")
source("prep_output.R")
source("gen_f_m.R")
source("gen_l.R")
source("gen_n.R")
source("print_output.R")
