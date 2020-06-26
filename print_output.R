# print_output.R

for (.x in varName) {
  varPos <- dplyr::filter(order, (order[,1] == .x))
  varPos <- as.numeric(varPos[1,2])
  cat(output[[varPos]])
}

# Free memory
rm(.x, varPos)
