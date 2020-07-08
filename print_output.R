# print_output.R
# This script prints the LaTeX code chunks for every generated table in the
# original order of the meta.CSV file

for (.el in var_name) {
  variable_positions <- dplyr::filter(order, (order[, 1] == .el))
  variable_positions <- as.numeric(variable_positions[1, 2])
  cat(output[[variable_positions]])
}

# Free memory
rm(.el, variable_positions)
