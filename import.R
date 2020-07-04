# import.R
# This script imports the data from the CSV files and sorts them

# Import data from files
data <- import("csv/data.csv")
data[data == ""] = NA
meta <- import("csv/meta.csv")
options <- import("csv/options.csv")
if (file.exists("csv/twoway.csv")) { twoway <- import("csv/twoway.csv")}

# Get survey title
setTitle <- subset(meta, name == "surveyls_title")
setTitle <- setTitle[1,5]

# Information about the variables
varType <- c()
varName <- c()
varRow <- c()

for (.row in 1:nrow(meta)) {
  if (meta[.row,2] == "Q") {
    varType[length(varType) + 1] <- tolower(meta[.row,3])
    varName[length(varName) + 1] <- meta[.row,4]
    varRow[length(varRow) + 1] <- which(meta$name == varName[length(varName)]) # Where does the variable START in the meta data-frame?
  }
}

endRow <- c()

for (.el in varRow) {
  repeat {
    .el <- .el + 1
    if (any(meta[.el,2] %!in% c("A", "SQ"))) {
      .el <- .el - 1 # It hit the last row, so go one iteration back and break
      break
    }
  }
  endRow[length(endRow) + 1] <- .el # Where does the variable END in the meta data-frame?
}

# Create lists for variables
type_f <- list()
type_l <- list()
type_n <- list()
type_s <- list()

.a <- 1 # Current variable

for (.el in varType) {
  class <- c()
  type <- c()
  name <- c()
  text <- c()

  .b <- 1 # Index for class, type, name, text vectors
  .i <- varRow[.a]

  # Iterate through the rows of the current variable until the last row has been reached
  repeat {
    if (.i == (endRow[.a] + 1)) break

    class[.b] <- meta[.i,2]
    type[.b] <- meta[.i,3]
    name[.b] <- meta[.i,4]
    text[.b] <- meta[.i,5]

    .b <- .b + 1
    .i <- .i + 1
  }

  # Get matching list name
  switch(.el,
         m = currType <- "type_f", # As already mentioned, Multiple-choice variables get treated like Matrix variables
         currType <- paste("type_", .el, sep="")
  )

  # Create a data frame out of the collected data and put in into the matching list
  .listLength <- length(eval(parse(text = currType)))
  .listSyntax <- paste(parse(text = currType), "[[", .listLength + 1, "]]", sep = "")
  .com <- paste(.listSyntax, "<-", "cbind.data.frame(class, type, name, text)")
  eval(parse(text= .com))

  .a <- .a + 1
}

# Get options
for (.row in 1:nrow(options)) {
  assign(options[.row,1], options[.row,2])
}

# Free memory
rm(.a, .b, .com, .el, .i, .listLength, .listSyntax, .row, class, currType, endRow,
   meta, name, options, text, type, varRow, varType)
