# functions.R

Absquant <- function(var, value) (as.numeric(count(dplyr::filter(data, eval(parse(text = var)) == value))))

Mode <-  function(x, na.rm = FALSE) { # Quelle: https://www.politikwissenschaften.ch/pdf.php?id=11
  if(na.rm) {
    x = na.omit(x)
  }
  ux = unique(x)
  return(ux[which.max(tabulate(match(x, ux)))])
}

handleMissings <- function(var, cumAbs, varType, val) {
  if (missings == 1) { # Summarize missing categories
    .com <- paste("absNa <- as.numeric(count(dplyr::filter(data, (is.na(", var ,") | ", var, " %!in% val))))", sep = "")
    eval(parse(text = .com))

    if (absNa != 0) {
      relNa <- format(round(absNa / count(data) * 100, 2), nsmall = 2)
      absCumNa <- tail(cumAbs, n = 1) + absNa
      relCumNa <- format(round(absCumNa / count(data) * 100, 2), nsmall = 2)

      if (varType == "f") {
        pack <<- paste(pack, " & Missings & ", absNa ," & ", relNa  ," & ", relCumNa ," \\\\ ", sep = "")
        answerAbs[length(answerAbs) + 1] <<- absNa
        answerCumRel[length(answerCumRel) + 1] <<- relCumNa
      }
      else if (varType == "l"){
        pack <<- paste(pack, "Missings & ", absNa ," & ", relNa  ," & ", relCumNa ," \\\\ ", sep = "")
        valAbs[length(valAbs) + 1] <<- absNa
        valCumRel[length(valCumRel) + 1] <<- relCumNa
      }
    }
  }
}
