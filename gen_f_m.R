# gen_f_m.R
# This script contains the generator for Matrix and Multiple-choice variables

for (.el in type_f) {
  # Get the title and label for the table
  tabTitle <- subset(.el, class == "Q")
  tabLabel <- tabTitle[1,4]
  tabTitle <- tabTitle[1,3]

  sq <- c()
  sqLabel <- c()
  answer <- c()
  answerLabel <- c()

  # Get the subquestions with their labels and the answers with their labels
  .a <- 1 # Counter for SQ
  .b <- 1 # Counter for A
  for (.row in 1:nrow(.el)) {
    if (.el[.row, "class"] == "SQ") {
      sq[.a] <- as.character(.el[.row, "name"])
      sqLabel[.a]<- as.character(.el[.row, "text"])
      .a <- .a + 1
    }
    else if (.el[.row, "class"] == "A") {
      answer[.b] <- as.character(.el[.row, "name"])
      answerLabel[.b] <- as.character(.el[.row, "text"])
      .b <- .b + 1
    }
  }

  pack <- ""
  .a <- 1 # Counter for SQ
  for (.el in sq) {
    answerAbs <- c()
    answerRel <- c()
    answerCumAbs <- c()
    answerCumRel <- c()

    pack <- paste(pack, " ", .el ," & & & \\\\ ", sep = "")

    # Summarize missing categories
    if (missings == 1) {
      total <- count(data)
    }
    # Ignore missings
    else if (missings == 2) {
      .com <- paste("absNa <- as.numeric(count(dplyr::filter(data, (is.na(", .el ,") | ", .el, " %!in% answer))))", sep = "")
      eval(parse(text = .com))
      total <- count(data) - absNa
    }

    # Calculate the numerical values for the table
    .b <- 1 # Counter for A
    for (.y in answer) {
      # Get absolute frequency for current answer
      .com <- paste("answerAbs[", .b ,"] <- Absfreq('", .el ,"', ", answer[.b] ,")", sep = "")
      eval(parse(text = .com))

      answerRel[.b] <- round(answerAbs[.b] / total * 100, 2)
      answerCumAbs[.b] <- sum(answerAbs)
      answerCumRel[.b] <- round(answerCumAbs[.b] / total * 100, 2)

      answerRel[.b] <- format(as.numeric(answerRel[.b]), nsmall = 2)
      answerCumRel[.b] <- format(as.numeric(answerCumRel[.b]), nsmall = 2)

      # Check if this is the first iteration. If it is so, put the sqLabel in the LaTeX line
      if (.b == 1) {
        pack <- paste(pack, sqLabel[.a] ," & ", answerLabel[.b] ," & ", answerAbs[.b] ," & ", answerRel[.b] , " & ", answerCumRel[.b] , " \\\\", sep = "")
      }
      else {
        pack <- paste(pack, " & ", answerLabel[.b] ," & ", answerAbs[.b] ," & ", answerRel[.b] , " & ", answerCumRel[.b] , " \\\\", sep = "")
      }
      .b <- .b + 1
    }

    # Missings -> functions.R
    handleMissings(.el, answerCumAbs, "f", answer)

    # Total
    relTotal <- tail(answerCumRel, n = 1)
    pack <- paste(pack, "\\midrule & Gesamt & ", sum(answerAbs) ," & ", relTotal ," & \\\\ \\addlinespace[.5cm] ", sep = "")

    .a <- .a + 1
  }

  # Assemble table
  table <- paste("\n\\newpage\\setlength{\\tabcolsep}{10pt}\\renewcommand{\\arraystretch}{1.3}\\begin{longtable}[h]{ p{6.1cm} p{3.5cm} >{\\raggedleft\\arraybackslash}p{2.5cm} .{2} .{2} }\\caption[", tabTitle ,"]{\\emph{", tabLabel ,"}} \\\\ \\addlinespace[.5cm] \\toprule ", tabTitle ," & & Absolut & \\mc{Prozent} & \\mc{Kumuliert (\\%)} \\\\\\midrule", pack ,"\\addlinespace[-.4cm]\\bottomrule\\end{longtable}\n\\newpage", sep="")
  .com <- paste("output[[", length(output) + 1 , "]] <- table", sep = "")
  eval(parse(text= .com))

  # Save position in output list in order list
  order[nrow(order) + 1,] = list(as.character(tabTitle), length(output))
}

# Free memory
rm(.a, .b, .com, .el, .row, .y, absNa, answer, answerAbs, answerRel, answerCumAbs,
   answerCumRel, answerLabel, pack, relTotal, sq, sqLabel, tabLabel, tabTitle, total)
