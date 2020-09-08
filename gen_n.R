# gen_n.R
# This script contains the generator for numerical survey variables

# type_n list is generated in import.R
for (.el in type_n) {
  # Get the title and label for the table
  table_title <- subset(.el, class == "Q")
  table_label <- table_title[1, 4]
  table_title <- table_title[1, 3]

  # Clean the data from non-numerical entries
  get_numbers <- function() {
    .com <- paste("numbers <- as.numeric(subset(data$", table_title, ", !is.na(as.numeric(data$", table_title, "))))", sep = "")
    eval(parse(text = .com))
    return(numbers)
  }

  numbers <- get_numbers()

  # Calculate the numerical values for the table
  mean_value <- format(round(mean(numbers), 2), nsmall = 2)
  median_value <- format(round(median(numbers), 2), nsmall = 2)
  mode_value <- format(round(get_mode(numbers, na.rm = TRUE), 2), nsmall = 2)
  min_value <- format(round(min(numbers), 2), nsmall = 2)
  max_value <- format(round(max(numbers), 2), nsmall = 2)
  sd_value <- format(round(sd(numbers), 2), nsmall = 2)

  # Assemble the table
  table <- paste("
\\setlength{\\tabcolsep}{15pt}
\\renewcommand{\\arraystretch}{1.3}
\\begin{table}[h]
\\caption{\\label{tab:", table_title, "}
\\emph{", table_label, "} (", table_title, ")}
\\begin{tabularx}{\\linewidth}{@{} >{\\raggedleft\\arraybackslash}p{3.5cm} >{\\raggedleft\\arraybackslash}p{1.9cm} >{\\raggedleft\\arraybackslash}p{1.9cm} >{\\raggedleft\\arraybackslash}p{1.9cm} >{\\raggedleft\\arraybackslash}p{1.9cm} >{\\raggedleft\\arraybackslash}p{2.5cm}@{}}
\\addlinespace[.5cm]
\\toprule
Arith. Mittel $\\varnothing$ & Median & Modus & Min & Max & St.-abweichung \\\\
\\midrule\n",
mean_value, " & ", median_value, " & ", mode_value, " & ", min_value, " & ", max_value, " & ", sd_value, "\\\\
\\bottomrule
\\end{tabularx}
\\end{table}\n
\\vspace{2cm}\n",
sep = "")

  .com <- paste("output[[", length(output) + 1, "]] <- table", sep = "")
  eval(parse(text = .com))

  # Save position in output list in order list
  order[nrow(order) + 1, ] <- list(as.character(table_title), length(output))
}

# Free memory
rm(.com, .el, get_numbers, max_value, mean_value, median_value, min_value,
   mode_value, numbers, sd_value, table, table_label, table_title)
