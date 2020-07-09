# gen_f_m.R
# This script contains the generator for matrix and multiple-choice survey variables

for (.el in type_f) {
  # Get the title and label for the table
  table_title <- subset(.el, class == "Q")
  table_label <- table_title[1, 4]
  table_title <- table_title[1, 3]

  subquestion <- c()
  subquestion_label <- c()
  answer <- c()
  answer_label <- c()

  # Get the subquestions with their labels and the answers with their labels
  .a <- 1 # Counter for SQ
  .b <- 1 # Counter for A
  for (.row in 1:nrow(.el)) {
    if (.el[.row, "class"] == "SQ") {
      subquestion[.a] <- as.character(.el[.row, "name"])
      subquestion_label[.a] <- as.character(.el[.row, "text"])
      .a <- .a + 1
    }
    else if (.el[.row, "class"] == "A") {
      answer[.b] <- as.character(.el[.row, "name"])
      answer_label[.b] <- as.character(.el[.row, "text"])
      .b <- .b + 1
    }
  }

  pack <- ""
  .a <- 1 # Counter for SQ
  for (.el in subquestion) {
    answer_absolute <- c()
    answer_relative <- c()
    answer_cum_absolute <- c()
    answer_cum_relative <- c()

    pack <- paste(pack, " ", .el, " & & & \\\\ ", sep = "")

    # Summarize missing categories ... (missing variable from import.R)
    if (missings == 1) {
      total <- count(data)
    }
    # ... or ignore missings
    else if (missings == 2) {
      .com <- paste("absNa <- as.numeric(count(dplyr::filter(data, (is.na(", .el, ") | ", .el, " %!in% answer))))", sep = "")
      eval(parse(text = .com))
      total <- count(data) - absNa
    }

    # Calculate the numerical values for the table
    .b <- 1 # Counter for A
    for (.y in answer) {
      # Get absolute frequency for current answer
      .com <- paste("answer_absolute[", .b, "] <- get_absolute_freq('", .el, "', ", answer[.b], ")", sep = "")
      eval(parse(text = .com))

      answer_relative[.b] <- round(answer_absolute[.b] / total * 100, 2)
      answer_cum_absolute[.b] <- sum(answer_absolute)
      answer_cum_relative[.b] <- round(answer_cum_absolute[.b] / total * 100, 2)

      answer_relative[.b] <- format(as.numeric(answer_relative[.b]), nsmall = 2)
      answer_cum_relative[.b] <- format(as.numeric(answer_cum_relative[.b]), nsmall = 2)

      # Check if this is the first iteration. If it is so, put the subquestion label in the LaTeX line
      if (.b == 1) {
        pack <- paste(pack, subquestion_label[.a], " & ", answer_label[.b], " & ", answer_absolute[.b], " & ", answer_relative[.b], " & ", answer_cum_relative[.b], " \\\\", sep = "")
      }
      else {
        pack <- paste(pack, " & ", answer_label[.b], " & ", answer_absolute[.b], " & ", answer_relative[.b], " & ", answer_cum_relative[.b], " \\\\", sep = "")
      }
      .b <- .b + 1
    }

    # Function can be found in functions.R
    handle_missings(.el, answer_cum_absolute, "f", answer)

    # Total
    relative_total <- tail(answer_cum_relative, n = 1)
    pack <- paste(pack, "\\midrule & Gesamt & ", sum(answer_absolute), " & ", relative_total, " & \\\\ \\addlinespace[.5cm] ", sep = "")

    .a <- .a + 1
  }

  # Assemble table
  table <- paste("\n\\newpage\\setlength{\\tabcolsep}{10pt}\\renewcommand{\\arraystretch}{1.3}\\begin{longtable}[h]{ p{6.1cm} p{3.5cm} >{\\raggedleft\\arraybackslash}p{2.5cm} .{2} .{2} }\\caption[", table_title, "]{\\emph{", table_label, "}} \\\\ \\addlinespace[.5cm] \\toprule ", table_title, " & & Absolut & \\mc{Prozent} & \\mc{Kumuliert (\\%)} \\\\\\midrule", pack, "\\addlinespace[-.4cm]\\bottomrule\\end{longtable}\n\\newpage", sep = "")
  .com <- paste("output[[", length(output) + 1, "]] <- table", sep = "")
  eval(parse(text = .com))

  # Save position in output list in order list
  order[nrow(order) + 1, ] <- list(as.character(table_title), length(output))
}

# Free memory
rm(.a, .b, .com, .el, .row, .y, absNa, answer, answer_absolute, answer_relative,
  answer_cum_absolute, answer_cum_relative, answer_label, pack, relative_total,
  subquestion, subquestion_label, table_label, table_title, total)
