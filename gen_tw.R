# gen_tw.R

handleMean <- function() {

}

handleMed <- function() {

}

handleMod <- function() {

}

handleMin <- function() {

}

handleMax <- function() {

}

handleSd <- function() {

}




# Load dependent and independent variables from twoway data table

independent <- c()
dependent <- c()
parameters <- c() # Possible parameters: mean, med, mod, min, max, sd

for (.row in 1:nrow(twoway)) {
  if (!is.empty(twoway[.row, "independent"])) { independent[length(independent) + 1] <- twoway[.row, "independent"] }
  if (!is.empty(twoway[.row, "dependent"])) { dependent[length(dependent) + 1] <- twoway[.row, "dependent"] }
  if (!is.empty(twoway[.row, "parameters"])) { parameters[length(parameters) + 1] <- twoway[.row, "parameters"] }
}


for (.x in parameters) {
  switch(.x,
         mean = handleMean(),
         med = handleMed(),
         mod = handleMod(),
         min = handleMin(),
         max = handleMax(),
         sd = handleSd()
  )
}

nParam <- length(parameters) # Quantity of parameters (required to calculate the total amount of columns)

twTable <- paste("", sep = "")
