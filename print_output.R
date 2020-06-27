# print_output.R

for (.el in varName) {
  varPos <- dplyr::filter(order, (order[,1] == .el))
  varPos <- as.numeric(varPos[1,2])
  cat(output[[varPos]])
}

# Free memory
rm(.el, varPos)
