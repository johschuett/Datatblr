# gen_l.R
# This script contains the generator for single-choice survey variables

for (.el in type_l) {
  # Get the title and label for the table
  table_title <- subset(.el, class == "Q")
  table_label <- table_title[1, 4]
  table_title <- table_title[1, 3]

  value <- c()
  value_label <- c()
  value_absolute <- c()
  value_relative <- c()
  value_cum_absolute <- c()
  value_cum_relative <- c()

  # Get the variable name, values and their labels
  .i <- 1
  for (.row in 1:nrow(.el)) {
    if (.el[.row, "class"] == "Q") current_variable <- as.character(.el[.row, "name"])
    if (.el[.row, "class"] == "A") {
      value[.i] <- as.character(.el[.row, "name"])
      value_label[.i] <- as.character(.el[.row, "text"])
      .i <- .i + 1
    }
  }

  # Summarize missing categories ... (missing variable from import.R)
  if (missings == 1) {
    total <- count(data)
  }
  # ... or ignore missings
  else if (missings == 2) {
    .com <- paste("absolute_na <- as.numeric(count(dplyr::filter(data, (is.na(", table_title, ") | ", table_title, " %!in% value))))", sep = "")
    eval(parse(text = .com))
    total <- count(data) - absolute_na
  }

  # Calculate the numerical values for the table
  .i <- 1
  for (.row in 1:nrow(.el)) {
    if (.el[.row, "class"] == "A") {
      # Get absolute frequency for current answer
      .com <- paste("value_absolute[", .i, "] <- get_absolute_freq('", current_variable, "', ", value[.i], ")", sep = "")
      eval(parse(text = .com))

      value_relative[.i] <- round(value_absolute[.i] / total * 100, 2)
      value_cum_absolute[.i] <- sum(value_absolute)
      value_cum_relative[.i] <- round(value_cum_absolute[.i] / total * 100, 2)
      .i <- .i + 1
    }
  }

  pack <- ""

  # Write LaTeX code
  .i <- 1
  for (.el in value) {
    value_relative[.i] <- format(as.numeric(value_relative[.i]), nsmall = 2)
    value_cum_relative[.i] <- format(as.numeric(value_cum_relative[.i]), nsmall = 2)

    pack <- paste(pack, value_label[.i], " & ",  value_absolute[.i], " & ", value_relative[.i], " & ", value_cum_relative[.i], " \\\\ ", sep = "")
    .i <- .i + 1
  }

  # Missings -> functions.R
  handle_missings(current_variable, value_cum_absolute, "l", value)

  # Total
  relative_total <- tail(value_cum_relative, n = 1)

  pack <- paste(pack, "\\midrule Gesamt & ", sum(value_absolute), " & ", relative_total, " & \\\\", sep = "")

  # Assemble table
  table <- paste("\\setlength{\\tabcolsep}{10pt}\\renewcommand{\\arraystretch}{1.3}\\begin{longtable}[h]{ p{8.3cm} >{\\raggedleft\\arraybackslash}p{4.5cm} .{2} .{2} }\\caption[", table_title, "]{\\emph{", table_label, "}} \\\\ \\addlinespace[.5cm] \\toprule ", table_title, " & Absolut & \\mc{Prozent} & \\mc{Kumuliert (\\%)} \\\\\\midrule ", pack, "\\bottomrule\\end{longtable}\\vspace{2cm}\n", sep = "")
  .com <- paste("output[[", length(output) + 1, "]] <- table", sep = "")
  eval(parse(text = .com))

  # Save position in output list in order list
  order[nrow(order) + 1, ] <- list(as.character(table_title), length(output))
}

# Free memory
rm(.com, .el, .i, .row, absolute_na, current_variable, pack, relative_total, table_label,
   table_title, total, value, value_absolute, value_cum_absolute, value_cum_relative, value_label, value_relative)
