######################################################################
# Datatblr stable-1.0                                                #
# Johannes Schütt, Chair of Empirical Methods, University of Potsdam #
# johschuett@uni-potsdam.de                                          #
######################################################################

# Version: R 4.0.0

## @knitr setup

# Packages
library(dplyr)
library(pkgcond)
library(rapport)
library(rapportools)
library(rio)

# Scripts
if (file.exists("import.R")) { source("import.R") } else { stop("Could not call import.R!") }

## @knitr main

if (file.exists("functions.R")) { source("functions.R") } else { stop("Could not call functions.R!") }
if (file.exists("prep_output.R")) { source("prep_output.R") } else { stop("Could not call prep_output.R!") }
if (file.exists("gen_f_m.R")) { source("gen_f_m.R") } else { stop("Could not call gen_f_m.R!") }
if (file.exists("gen_l.R")) { source("gen_l.R") } else { stop("Could not call gen_l.R!") }
if (file.exists("gen_n.R")) { source("gen_n.R") } else { stop("Could not call gen_n.R!") }
if (file.exists("print_output.R")) { source("print_output.R") } else { stop("Could not call print_output.R!") }
