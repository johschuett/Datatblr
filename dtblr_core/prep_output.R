# prep_output.R
# This script creates the output list for the LaTeX code chunks and an order
# list to keep the original order of the survey variables when outputting the
# LaTeX code in print_output.R

output <- list()
order <- data.frame(name = character(0), pos = character(0), stringsAsFactors = FALSE)
