######################################################################
# Datatblr stable-1.0                                                #
# Johannes Schütt, Chair of Empirical Methods, University of Potsdam #
# johschuett@uni-potsdam.de                                          #
# License: GNU General Public License v2.0 only                      #
######################################################################

# Version: R 4.0.0

## @knitr setup

# Packages
library(dplyr)    # Version 1.0.0
library(pkgcond)  # Version 0.1.0
library(rio)      # Version 0.5.16

# Scripts
source("import.R")

## @knitr main

source("functions.R")
source("prep_output.R")
source("gen_f_m.R")
source("gen_l.R")
source("gen_n.R")
source("print_output.R")
