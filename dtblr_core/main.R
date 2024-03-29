######################################################################
# Datatblr stable-1.1                                                #
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

# Define is_empty() function
is_empty <- function(x, na.ignore = FALSE) {
  if (na.ignore)
    ifelse(is.na(x), return(FALSE), return(trimws(x) == ""))
  else
    return(trimws(x) == "")
}

# Define %!in% operator
'%!in%' <- function(x, y)!('%in%'(x, y))

cat("\n#! Generating TEX file \U0001F529 ...\n\n")

# Scripts
source("dtblr_core/import.R")
source("dtblr_core/functions.R")
source("dtblr_core/prep_output.R")
source("dtblr_core/gen_f_m.R")
source("dtblr_core/gen_l.R")
source("dtblr_core/gen_n.R")
source("dtblr_core/write_output.R")
