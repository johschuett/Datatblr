# render.R
# This script provides a simple user input and initializes
# the rendering process of the markdown document

# Set encoding
Sys.setlocale("LC_ALL", "en_US.UTF-8")

# Create environment for command line objects
com_env <- new.env()

# Functions
com_env$check_data <- function(file) {
  if (file.exists(file)) {
    # Render markdown document
    #rmarkdown::render("markdown.Rmd", "all", encoding = "UTF-8")
  }
  else cat("#! Oops I couldn't find the file!\n#! Please check your path and try again.\n")
}

com_env$examples <- function() {
  cat("#! Examples:
#! ~/Desktop/data.csv
#! test1.csv
#! data/my_data.csv\n")
}

com_env$quit <- function() {
  com_env$quit_flag <<- TRUE
  cat("#! take care!\n")
}

com_env$s_o_d <- function() {
  cat("#! watch?v=XtAhISkoJZc\n")
}

com_env$table <- function() {
  cat("#!      _____________________
#!     /                    /|
#!    /                    / |
#!   /____________________/ /
#!  |_____________________|/|
#!   || ||              || ||
#!   || ||              || ||
#!   || ||              || ||
#!   ||                 ||
#!   ||                 ||\n")
}

com_env$version <- "stable-1.0"
com_env$quit_flag <- FALSE

cat("#! Hej, this is Datatblr ", com_env$version, "!
#! License: GNU General Public License v2.0
#!\n", sep = "")
message("#! You are currently in ", getwd())
cat("#!
#! If you wish to change the current working directory
#! you're in, type :q to quit the program and do
#! setwd(\"<your-desired-path>\")
#!
",
sep = "")
cat("#! Issue :e for examples.
#! Issue :q to quit the program.
#!\n")
message("#! Please put in the path of your data file
#! or a command (starting with a colon):")


# Main loop
repeat {
  if (com_env$quit_flag) break
  com_env$input <- readline(prompt = "#~ ")

  switch(com_env$input,
         ":e" = com_env$examples(),
         ":q" = com_env$quit(),
         ":s" = com_env$s_o_d(),
         ":t" = com_env$table(),
         com_env$check_data(com_env$input)
  )
}
