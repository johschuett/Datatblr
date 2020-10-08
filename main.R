######################################################################
# Datatblr stable-lite-1.1                                           #
# Johannes Schütt, Chair of Empirical Methods, University of Potsdam #
# johschuett@uni-potsdam.de                                          #
# License: GNU General Public License v2.0 only                      #
######################################################################

# Version: R 4.0.0

# Set encoding
Sys.setlocale("LC_ALL", "en_US.UTF-8")

# Packages
library(dplyr, warn.conflicts = FALSE)  # Version 1.0.0
library(rio, warn.conflicts = FALSE)    # Version 0.5.16

# Define %!in% operator
'%!in%' <- function(x, y)!('%in%'(x, y))

cat("\n#! Generating TEX file \U0001F529 ...\n\n")

# Scripts
source("import.R")
source("functions.R")
source("prep_output.R")
source("gen_f_m.R")
source("gen_l.R")
source("gen_n.R")
source("write_output.R")
