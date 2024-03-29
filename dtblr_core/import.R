# import.R
# This script imports the data from the CSV files and sorts them

# Import job file
job <- import("dtblr_core/job.csv")

# Get data from job file
for (.row in seq_len(nrow(job))) {
  assign(job[.row, 1], job[.row, 2])
}

# Import data from file
data <- rio::import(data_file)
# Convert empty entries to NAs
data[sapply(data, is_empty)] <- NA
# Import metadata from file
meta <- rio::import(meta_file)
# Convert missing value to integer
missings <- as.integer(missings)

# Get survey title
line_of_title <- which(meta$name == "surveyls_title")

if (is.integer(line_of_title) && length(line_of_title) == 0L) {
  survey_title <- "Untitled"
} else if (is.vector(line_of_title)) {
  survey_title <- meta[line_of_title[1], "text"]
} else {
  survey_title <- meta[line_of_title, "text"]
}

# Information about the survey variables
# Possible survey variable types are: matrix, multiple-choice,
# numeric, single-choice, string
var_type <- c()
var_name <- c()
var_row <- c()

for (.row in seq_len(nrow(meta))) {
  if (meta[.row, "class"] == "Q") {
    var_type[length(var_type) + 1] <- tolower(meta[.row, "type/scale"])
    var_name[length(var_name) + 1] <- meta[.row, "name"]
    var_row[length(var_row) + 1] <- which(meta$name == var_name[length(var_name)]) # Where does the survey variable START in the meta data-frame?
  }
}

last_row <- c()

for (.el in var_row) {
  repeat {
    .el <- .el + 1
    if (any(meta[.el, "class"] %!in% c("A", "SQ"))) {
      .el <- .el - 1 # It hit the last row, so go one iteration back and break
      break
    }
  }
  last_row[length(last_row) + 1] <- .el # Where does the survey variable END in the meta data-frame?
}

# Create lists for survey variables
type_f <- list()  # matrix / multiple-choice
type_l <- list()  # single-choice
type_n <- list()  # numeric
type_s <- list()  # string (not in use)

.a <- 1 # Current survey variable

for (.el in var_type) {
  class <- c()  # Q (Question), A (Answer) or SQ (Subquestion)
  type <- c()   # f, m, l, n, s
  name <- c()
  text <- c()

  .b <- 1 # Index for class, type, name, text vectors
  .i <- var_row[.a]

  # Iterate through the rows of the current survey variable and read
  # in the data until the last row has been reached
  repeat {
    if (.i == (last_row[.a] + 1)) break

    class[.b] <- meta[.i, "class"]
    type[.b] <- meta[.i, "type/scale"]
    name[.b] <- meta[.i, "name"]
    text[.b] <- meta[.i, "text"]

    .b <- .b + 1
    .i <- .i + 1
  }

  # Get matching list name
  switch(.el,
         m = current_type <- "type_f", # As already mentioned, multiple-choice survey variables get treated like matrix survey variables
         current_type <- paste("type_", .el, sep = "")
  )

  # Get length of the targeted list
  .list_length <- length(eval(parse(text = current_type)))
  .list_syntax <- paste(parse(text = current_type), "[[", .list_length + 1, "]]", sep = "")
  # Create a data frame out of the collected data and put it into the matching list
  .com <- paste(.list_syntax, "<-", "cbind.data.frame(class, type, name, text)")
  eval(parse(text = .com))

  .a <- .a + 1
}

# Free memory
rm(.a, .b, .com, .el, .i, .list_length, .list_syntax, .row, class, current_type,
  last_row, line_of_title, meta, name, text, type, var_row, var_type)
