# print_output.R
# This script prints the LaTeX code chunks for every generated table in the original order
# of the meta.CSV file

for (.el in varName) {
  varPos <- dplyr::filter(order, (order[,1] == .el))
  varPos <- as.numeric(varPos[1,2])
  cat(output[[varPos]])
}

# Free memory
rm(.el, varPos)
