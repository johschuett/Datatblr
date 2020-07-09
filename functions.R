# functions.R
# This script contains functions used by the generator scripts

# Gets the absolute frequency
get_absolute_freq <- function(var, value) (as.numeric(count(dplyr::filter(data, eval(parse(text = var)) == value))))

# Gets the mode
get_mode <-  function(x, na.rm = FALSE) { # Source: https://www.politikwissenschaften.ch/pdf.php?id=11
  if (na.rm) {
    x <- na.omit(x)
  }
  ux <- unique(x)
  return(ux[which.max(tabulate(match(x, ux)))])
}

# Handles how to treat missing values
handle_missings <- function(var, cum_absolute, variable_type, val) {
  if (missings == 1) { # Summarize missing categories
    .com <- paste("absolute_na <- as.numeric(count(dplyr::filter(data, (is.na(", var, ") | ", var, " %!in% val))))", sep = "")
    eval(parse(text = .com))

    if (absolute_na != 0) {
      relative_na <- format(round(absolute_na / count(data) * 100, 2), nsmall = 2)
      absolute_cum_na <- tail(cum_absolute, n = 1) + absolute_na
      relative_cum_na <- format(round(absolute_cum_na / count(data) * 100, 2), nsmall = 2)

      # Handles matrix and multiple-choice survey variables
      if (variable_type == "f") {
        pack <<- paste(pack, " & Missings & ", absolute_na, " & ", relative_na, " & ", relative_cum_na, " \\\\ ", sep = "")
        answer_absolute[length(answer_absolute) + 1] <<- absolute_na
        answer_cum_relative[length(answer_cum_relative) + 1] <<- relative_cum_na
      }
      # Handles single-choice survey variables
      else if (variable_type == "l") {
        pack <<- paste(pack, "Missings & ", absolute_na, " & ", relative_na, " & ", relative_cum_na, " \\\\ ", sep = "")
        value_absolute[length(value_absolute) + 1] <<- absolute_na
        value_cum_relative[length(value_cum_relative) + 1] <<- relative_cum_na
      }
    }
  }
}
