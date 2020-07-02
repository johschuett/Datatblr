# gen_l.R
# This script contains the generator for Single-choice variables

for (.el in type_l) {
  # Get the title and label for the table
  tabTitle <- subset(.el, class == "Q")
  tabLabel <- tabTitle[1,4]
  tabTitle <- tabTitle[1,3]

  val <- c()
  valLabel <- c()
  valAbs <- c()
  valRel <- c()
  valCumAbs <- c()
  valCumRel <- c()

  # Get the variable name, values and their labels
  .i <- 1
  for(.row in 1:nrow(.el)) {
    if (.el[.row, "class"] == "Q") cVar <- as.character(.el[.row, "name"])
    if (.el[.row, "class"] == "A") {
      val[.i] <- as.character(.el[.row, "name"])
      valLabel[.i] <- as.character(.el[.row, "text"])
      .i <- .i + 1
    }
  }

  if (missings == 1) {
    total <- count(data)
  }
  if (missings == 2) {
    .com <- paste("absNa <- as.numeric(count(dplyr::filter(data, (is.na(", tabTitle ,") | ", tabTitle, " %!in% val))))", sep = "")
    eval(parse(text = .com))
    total <- count(data) - absNa
  }

  # Calculate the numerical values for the table
  .i <- 1
  for (.row in 1:nrow(.el)) {
    if (.el[.row, "class"] == "A") {
      # Get absolute frequency for current answer
      .com <- paste("valAbs[", .i ,"] <- Absfreq('", cVar ,"', ", val[.i] ,")", sep = "")
      eval(parse(text = .com))

      valRel[.i] <- round(valAbs[.i] / total * 100, 2)
      valCumAbs[.i] <- sum(valAbs)
      valCumRel[.i] <- round(valCumAbs[.i] / total * 100, 2)
      .i <- .i + 1
    }
  }

  pack <- ""

  # Write LaTeX code
  .i <- 1
  for (.el in val) {
    valRel[.i] <- format(as.numeric(valRel[.i]), nsmall = 2)
    valCumRel[.i] <- format(as.numeric(valCumRel[.i]), nsmall = 2)

    pack <- paste(pack, valLabel[.i] ," & ",  valAbs[.i] ," & ", valRel[.i] ," & ", valCumRel[.i] ," \\\\ ", sep = "")
    .i <- .i + 1
  }

  # Missings -> functions.R
  handleMissings(cVar, valCumAbs, "l", val)

  # Total
  relTotal <- tail(valCumRel, n = 1)

  pack <- paste(pack, "\\midrule Gesamt & ", sum(valAbs) ," & ", relTotal ," & \\\\", sep = "")

  # Assemble table
  table <- paste("\\setlength{\\tabcolsep}{10pt}\\renewcommand{\\arraystretch}{1.3}\\begin{longtable}[h]{ p{8.3cm} >{\\raggedleft\\arraybackslash}p{4.5cm} .{2} .{2} }\\caption[", tabTitle ,"]{\\emph{", tabLabel ,"}} \\\\ \\addlinespace[.5cm] \\toprule ", tabTitle ," & Absolut & \\mc{Prozent} & \\mc{Kumuliert (\\%)} \\\\\\midrule ", pack, "\\bottomrule\\end{longtable}\\vspace{2cm}\n" , sep = "")
  .com <- paste("output[[", length(output) + 1 , "]] <- table", sep = "")
  eval(parse(text= .com))

  # Save position in output list in order list
  order[nrow(order) + 1,] = list(as.character(tabTitle), length(output))
}

# Free memory
rm(.com, .i, .el, .row, absNa, cVar, pack, relTotal, tabLabel,
   tabTitle, total, val, valAbs, valCumAbs, valCumRel, valLabel, valRel)
