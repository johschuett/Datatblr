# gen_n.R

for (.x in type_n) {
  tabTitle <- subset(.x, class == "Q")
  tabLabel <- tabTitle[1,4]
  tabTitle <- tabTitle[1,3]

  getNumbers <- function() {
    .com <- paste("numbers <- as.numeric(subset(data$", tabTitle, ", !is.na(as.numeric(data$", tabTitle, "))))", sep = "")
    eval(parse(text= .com))
    return(numbers)
  }

  numbers <- suppress_warnings(getNumbers(), "NAs introduced by coercion")

  numMean <- format(round(mean(numbers), 2), nsmall = 2)
  numMed <- format(round(median(numbers), 2), nsmall = 2)
  numMod <- format(round(Mode(numbers, na.rm = TRUE), 2), nsmall = 2)
  numMin <- format(round(min(numbers), 2), nsmall = 2)
  numMax <- format(round(max(numbers), 2), nsmall = 2)
  numSd <- format(round(sd(numbers), 2), nsmall = 2)

  table <- paste("\\setlength{\\tabcolsep}{15pt}\\renewcommand{\\arraystretch}{1.3}\\begin{table}[h]\\caption{\\label{tab:", tabTitle, "} \\emph{", tabLabel ,"} (", tabTitle ,")}\\begin{tabularx}{\\linewidth}{@{} >{\\raggedleft\\arraybackslash}p{3.5cm} >{\\raggedleft\\arraybackslash}p{1.9cm} >{\\raggedleft\\arraybackslash}p{1.9cm} >{\\raggedleft\\arraybackslash}p{1.9cm} >{\\raggedleft\\arraybackslash}p{1.9cm} >{\\raggedleft\\arraybackslash}p{2.5cm}@{}} \\addlinespace[.5cm] \\toprule Arith. Mittel $\\varnothing$ & Median & Modus & Min & Max & St.-abweichung \\\\\\midrule ", numMean, " & ", numMed, " & ", numMod, " & ", numMin, " & ", numMax, " & ", numSd ,"\\\\\\bottomrule\\end{tabularx}\\end{table}\\vspace{2cm}\n", sep = "")

  .com <- paste("output[[", length(output) + 1 , "]] <- table", sep = "")
  eval(parse(text= .com))

  order[nrow(order) + 1,] = list(as.character(tabTitle), length(output))
}

# Free memory
rm(.com, getNumbers, numbers, numMax, numMean, numMed, numMin,
   numMod, numSd, tabLabel, table, tabTitle)
